//
//  main.cpp
//  OctopusDaemon
//
//  Created by K3A on 5/19/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include <iostream>
#include <unistd.h> // getopt
#include <syslog.h>
#include <sys/time.h>
#include <sqlite3.h>
#include <dispatch/dispatch.h>
#import <AddressBook/AddressBook.h> // addressbook import

#include "main.h"
#include "examples.h"
#include "TextInput.h"

void OLog(int level, const char* format, ...)
{
#ifndef DEBUG
	if (level>1) return;
#endif
	
    std::string strf(format);
    strf.insert(0, "OK INF: ");
    strf.append("\n");
    
    va_list args;
    va_start( args, format );
#ifdef MACOSX
    vprintf( strf.c_str(), args );
#endif
    va_end( args );
    
    char buf[1024];
    vsnprintf(buf, 1024, strf.c_str(), args);
    syslog(LOG_NOTICE, "%s", buf);
}

void OErr(const char* format, ...)
{
    std::string strf(format);
    strf.insert(0, "OK ERR: ");
    strf.append("\n");
    
    va_list args;
    va_start( args, format );
#ifdef MACOSX
    vprintf( strf.c_str(), args );
#endif
    va_end( args );
    
    char buf[1024];
    vsnprintf(buf, 1024, strf.c_str(), args);
    syslog(LOG_ERR, "%s", buf);
}

static unsigned GetTimestampMsec()
{
    timeval time;
    gettimeofday(&time, NULL);
    
    unsigned elapsed_seconds  = time.tv_sec;
    unsigned elapsed_useconds = time.tv_usec;
    
    return elapsed_seconds * 1000 + elapsed_useconds/1000;
}

static unsigned GetTimestampSec()
{
    timeval time;
    gettimeofday(&time, NULL);
    
    unsigned elapsed_seconds  = time.tv_sec;
    
    return elapsed_seconds;
}

// PREFS ------------------------------

NSDictionary* s_prefs = nil;

BOOL prefsLoad()
{
	if (s_prefs) [s_prefs release];
	s_prefs = [[NSDictionary alloc] initWithContentsOfFile:@PREF_FILE];
	if (!s_prefs) OLog(1, "No prefs or failed to load");
	return s_prefs!=nil;
}

NSString* prefString(NSString* key, NSString* def)
{
	NSString* str = [s_prefs objectForKey:key];
	if (!str) return def;
	
	if ([str isKindOfClass:[NSString class]])
		return str;
	else 
		return [str description];
}

int prefInt(NSString* key, int def)
{
	id v = [s_prefs objectForKey:key];
	if (!v) return def;
	return [v intValue];
}

static void prefsLoadApply();

// MACH SERVICE -----------------------

#include <servers/bootstrap.h>
#include "octopus.h"

extern "C" {
    static ostats_t s_stats;
    static unsigned s_startTime = 0;
    static OTextInputSystem* s_is = NULL;
    
    #define EXP_BOOL(x) if (s_is) { return x ? KERN_SUCCESS : KERN_FAILURE;} else return KERN_FAILURE;
    
    kern_return_t srv_oGetStats(mach_port_t server_port, ostats_t* stats)
    {
        s_stats.uptime = GetTimestampSec() - s_startTime;
        *stats = s_stats;
        
        return KERN_SUCCESS;
    }
    
    kern_return_t srv_oSuggConfigure(mach_port_t server_port, uint32_t maxSuggestions, uint32_t suggThreshold, bool proximitySuggestion, bool errorCorrection, bool completion)
    {
        EXP_BOOL( s_is->SuggConfigure(maxSuggestions, suggThreshold, proximitySuggestion, errorCorrection, completion) );
    }
    
    kern_return_t srv_oSuggConfigureCaps(mach_port_t server_port, bool capKnownWords, bool capSentence, bool capUser, bool capNext)
    {
        EXP_BOOL( s_is->SuggConfigureCaps(capKnownWords, capSentence, capUser, capNext) );
    }
    
    kern_return_t srv_oSuggGetSuggestions(mach_port_t server_port, sSuggestions* outSuggs)
    {
        EXP_BOOL( s_is->SuggGetSuggestions(*outSuggs) );
    }
    
    kern_return_t srv_oInputClear(mach_port_t server_port)
    {
        EXP_BOOL( s_is->InputClear() );
    }
    
    kern_return_t srv_oInputInsertString(mach_port_t server_port, const oword_t str, eCapitalizationMode cm, bool disableLearn)
    {
        EXP_BOOL( s_is->InputInsertString(str, cm, disableLearn) );
    }
    
    kern_return_t srv_oInputRemove(mach_port_t server_port, int32_t before, int32_t after)
    {
        EXP_BOOL( s_is->InputRemove(before, after) );
    }
	kern_return_t srv_oInputLearn(mach_port_t server_port)
	{
		EXP_BOOL( s_is->InputLearn(IL_ALL) );
	}
    
    kern_return_t srv_oInputCursorMove(mach_port_t server_port, eSeekOrigin origin, int32_t off)
    {
        EXP_BOOL( s_is->InputCursorMove(origin, off) );
    }
    
    kern_return_t srv_oEnableAutoLearning(mach_port_t server_port, bool learn)
    {
        EXP_BOOL( s_is->EnableAutoLearning(learn) );
    }
    
    kern_return_t srv_oInputInsertSugg(mach_port_t server_port, uint32_t set, uint32_t ident, bool appendSpace)
    {
        EXP_BOOL( s_is->InputInsertSugg(set, ident, appendSpace) );
    }
    
    kern_return_t srv_oProfileSave(mach_port_t server_port)
    {
        EXP_BOOL( s_is->ProfileSave() );
    }
    
    kern_return_t srv_oDictGetList(mach_port_t server_port, sDictionaryArray* outDicts, mach_msg_type_number_t* outDictNum)
    {
        EXP_BOOL( s_is->DictGetList(outDicts, outDictNum) );
    }
    
    kern_return_t srv_oUserDictGetWordForID(mach_port_t server_port, uint32_t idx, oword_t &word)
    {
		char *tWord;
		
		//s_is->UserDictGetWordForID(idx, tWord)
        if (s_is->UserDictGetWordForID(idx,tWord)){
			OLog(1, "W %u: %s",idx,tWord);
		//if (tWord!=NULL) {
			strcpy(word, tWord);
			return KERN_SUCCESS;
		}
		return KERN_FAILURE;
    }
	
	kern_return_t srv_oUserDictClear(mach_port_t server_port)
    {
        EXP_BOOL( s_is->UserDictClear() );
    }
    
    kern_return_t srv_oUserDictGetNumWords(mach_port_t server_port, uint32_t* outNumWords)
    {
        EXP_BOOL( s_is->UserDictGetNumWords(*outNumWords) );
    }
    
    kern_return_t srv_oUserDictImportMessages(mach_port_t server_port)
    {
        if (!s_is) return KERN_FAILURE;
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^{
            
            sqlite3 *sql;
            if (sqlite3_open("/var/mobile/Library/SMS/sms.db", &sql))
                OErr("Failed to open SMS database!");
            else
            {
                sqlite3_stmt *stmt;
                
                if (sqlite3_prepare_v2(sql, "SELECT text from message;", -1, &stmt, NULL))
                {
                    OErr("Failed to prepare SMS statement!");
                    return;
                }
                
                int retval;
                unsigned currBunch = 0;
                unsigned maxW = 0;
                s_is->UserDictGetMaxWords(maxW);
                
                OLog(1, "Started learning from Messages...");
                
                do 
                {
                    retval = sqlite3_step(stmt);
                    if (retval == SQLITE_ROW)
                    {
                        const unsigned char* text = sqlite3_column_text(stmt, 0);
                        s_is->LearnBuffer((const char*)text);
                        
                        // check how many words we have, stop on current maximum
                        if (++currBunch == 100)
                        {
                            currBunch = 0;
                            
                            unsigned numW = 0;
                            s_is->UserDictGetNumWords(numW);
                            if (numW >= maxW)
                            {
                                OLog(1, "Stopping the import - maximum number words in user dict reached.");
                                break;
                            }
                        }
                    }
                }
                while(retval != SQLITE_DONE);
                
                sqlite3_close(sql);
                
                unsigned numW = 0;
                s_is->UserDictGetNumWords(numW);
                OLog(1, "Learning from Messages finished. Now %u words in user dict.", numW);
                
                s_is->ProfileSave(); //TODO: should we do that? now? from this thread?
            }
        });
        
        return KERN_SUCCESS;
    }
	
	kern_return_t srv_oUserDictImportContacts(mach_port_t server_port)
    {
		if (!s_is) return KERN_FAILURE;
        
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^{
            
			int retval;
			unsigned maxW = 0;
			s_is->UserDictGetMaxWords(maxW);
			
			OLog(1, "Started learning from Contacts...");
			
			NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
			ABAddressBookRef addressBook = ABAddressBookCreate();
			
			if (addressBook)
			{
				NSArray *people = (NSArray *)ABAddressBookCopyArrayOfAllPeople(addressBook);
				if ([people count] == 0) OErr("No people in addressbook!");
				
				for (unsigned i=0; i<[people count]; i++ )
				{
					ABRecordRef person = (ABRecordRef)[people objectAtIndex:i];
					CFStringRef firstNameValue = (CFStringRef)ABRecordCopyValue(person, kABPersonFirstNameProperty);
					CFStringRef lastNameValue = (CFStringRef)ABRecordCopyValue(person, kABPersonLastNameProperty);
					
					NSMutableString* wholeName = [NSMutableString string];
					if (firstNameValue != nil) 
					{
						[wholeName appendFormat:@"%@ ", (NSString*)firstNameValue];
						CFRelease(firstNameValue);
					}
					if (lastNameValue != nil) 
					{
						[wholeName appendString:(NSString*)lastNameValue];
						CFRelease(lastNameValue);
					}
					
					if ([wholeName length]>1) s_is->LearnBuffer([wholeName UTF8String]);
					
					unsigned numW = 0;
					s_is->UserDictGetNumWords(numW);
					if (numW >= maxW)
					{
						OLog(1, "Stopping the import - maximum number words in user dict reached.");
						break;
					}
				}
				[people release];
			}
			else 
				OErr("Failed to create addressbook obj.");
			
			if (addressBook) CFRelease(addressBook);
			[pool release];
			
			unsigned numW = 0;
			s_is->UserDictGetNumWords(numW);
			OLog(1, "Learning from Contacts finished. Now %u words in user dict.", numW);
			
			s_is->ProfileSave(); //TODO: should we do that? now? from this thread?
			
		});
		
		return KERN_SUCCESS;
	}
	
	kern_return_t srv_oReloadPrefs(mach_port_t server_port)
	{
		prefsLoadApply();
		return KERN_SUCCESS;
	}

    boolean_t octopus_server(mach_msg_header_t *inhdr, mach_msg_header_t *outhdr);
}

static void prefsLoadApply()
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	OLog(1, "Loading and applying prefs...");
	
	prefsLoad();
	
	s_is->UserDictSetMaxWords(prefInt(@"userDictMaxWords", 3000));
	s_is->EnableAutoLearning(prefInt(@"learn",1)!=0);
	
	s_is->SuggConfigure(8, prefInt(@"threshold", 2), true, true, true);
	s_is->SuggConfigureCaps(true, false, true, false);
	
	// set dictionary states
	sDictionaryArray dicts; unsigned numDicts = 0;
	if (s_is->DictGetList(&dicts, &numDicts))
	{
		for (int i = 0; i<numDicts; i++)
		{
			sDictionary& d = dicts[i];
			NSArray* lc = [[NSString stringWithUTF8String:d.language] componentsSeparatedByString:@"-"];
			NSString* langIdent;
			unsigned lcl = [lc count];
			if (!lcl) continue;
			
			if (lcl==1)
				langIdent = [lc objectAtIndex:0];
			else 
				langIdent = [NSString stringWithFormat:@"%@-%@", [lc objectAtIndex:0],[lc objectAtIndex:1]];
			
			//NSLog(@"LLL '%@' Enabled = %s", langIdent, (prefInt(langIdent, 1) != 0)?"Y":"N" );
			
			s_is->DictEnable(d.componentId, prefInt(langIdent, 1) != 0);
		}
	}
	
	s_is->ProfileSave();
	//s_is->ProfileReload();
	
	[pool release];
}

static void termHandler(int sig)
{
	OLog(1, "Saving profile.");
	if (s_is) s_is->ProfileSave();
	printf("Shutting down");
	fflush(stdout);
	exit(sig);
}

// --------------------------------------

static void Usage()
{
    printf("OCTOPUS KEYBOARD DAEMON\n");
    printf("Copyright (C) 2012 K3A (www.k3a.me)\n\n");
    printf("Usage:\n");
    printf("    -h  This usage list\n");
    printf("    -x  Do not daemonize\n");
    printf("    -s  Print daemon stats\n");
    printf("    -e  Examples and tests\n");
    printf("\n");
}

static mach_port_t GetServerPort()
{
    kern_return_t           kr;
	static mach_port_t		bsPort = 0;
	static mach_port_t		srvPort = 0;
	
	if (bsPort == 0)
	{
		kr = task_get_bootstrap_port( mach_task_self(), &bsPort );
        if (kr != MACH_MSG_SUCCESS)
        {
            mach_error("task_get_bootstrap_port:", kr);
            exit(1);
        }
        
		kr = bootstrap_look_up( bsPort, OCTOPUS_SERVICE, &srvPort );
		if (kr != MACH_MSG_SUCCESS)
		{
            mach_error("Could not lookup the service, is daemon running?", kr);
			exit(1);
		}
	}
    
	return srvPort;
}

static void PrintStats()
{
    printf("OCTOPUS KEYBOARD DAEMON STATS\n");
    
    ostats_t stats;
    oGetStats(GetServerPort(), &stats);
    
    printf("Uptime: %u sec\n", stats.uptime);
}

static void Examples()
{
    //NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    printf("-- OCTOPUS KEYBOARD EXAMPLES --\n\n");
    
    /*printf("\n\n-- COMPONENTS --\n\n");
     Example_KPTCMD_COMPONENT_GETAVAILABLE();
     
     printf("\n\n-- DICT --\n\n");
     Example_KPTCMD_DICTIONARY_GETLANGLIST();
     printf("---\n");
     Example_KPTCMD_DICTIONARY_GETLIST();
     
     printf("\n\n-- KEYMAPS --\n\n");
     Example_KPTCMD_KEYMAP_GETAVAILABLE();
     printf("---\n");
     Example_KPTCMD_KEYMAP_GETLAYOUT();
     
     printf("\n\n-- SUGGESTIONS --\n\n");
     Example_KPTCMD_SUGGS_GETSUGGESTIONS();
     
     printf("\n\n -- KEY MGR -- \n\n");
     //Example_KPTCMD_INPUTMGR_GETCURRWORD();
     
     //Example_KPTCMD_ERROR_POPSTACK();*/
    
	/*
	OTextInputSystem sys("/Work/testtweak/octopuscore/ATXProfile/");
    sys.InputInsertString("hey bod");
    oword_t w;
    sys.InputGetCurrWord(w);
    printf("Current Word: '%s'\n", w);
    sys.SuggPrint();*/
	
	printf("\n\n-- KEYMAPS --\n\n");
	//Example_KPTCMD_KEYMAP_GETAVAILABLE();
	printf("---\n");
	Example_KPTCMD_KEYMAP_GETLAYOUT();
    
    printf("-- END --\n");
    //sleep(30);
}

void* serverThread(void*)
{
	unsigned ms = GetTimestampMsec();
#ifdef MACOSX
    s_is = new OTextInputSystem("/Work/testtweak/octopuscore/layout/Library/Application Support/OctopusKeyboard");
#else
    s_is = new OTextInputSystem("/Library/Application Support/OctopusKeyboard");
#endif
    
    //OLog(3, "DICTIONARIES----------------");
    //Example_KPTCMD_DICTIONARY_GETLIST();
    //OLog(3, "DICTIONARIES LANGS----------------");
    //Example_KPTCMD_DICTIONARY_GETLANGLIST();
	
	prefsLoadApply();
	
	//Examples();
	//Example_KPTCMD_KEYMAP_QUERY();
	
	//atexit(exitHandler);
	signal(SIGTERM, termHandler);
    
    s_startTime = GetTimestampSec();
    OLog(1, "Finished loading in %d ms", GetTimestampMsec()-ms);
    
    mach_port_t server_port;
    kern_return_t kr;
	
	
    // register
    if ((kr = bootstrap_check_in(bootstrap_port, OCTOPUS_SERVICE, &server_port)) != BOOTSTRAP_SUCCESS) 
    {
        mach_port_deallocate(mach_task_self(), server_port);
        mach_error("bootstrap_check_in:", kr);
        exit(1);
    }
    
    // server loop
    mach_msg_server(octopus_server, // call the server-interface module
                    sizeof(msg_octopus_t), // maximum receive size
                    server_port, // port to receive on
                    MACH_MSG_TIMEOUT_NONE); // options
	
	OErr("Server thread exited!!!");
	
	return NULL;
}

void* timeThread(void*)
{
	unsigned tm = GetTimestampSec();
	
	if (tm < 1340060254 + 15*24*60*60)
	{
		//OLog(3, "tm ok");
	}
	else
	{
		//OLog(3, "tm end");
		exit(127);
	}
	return NULL;
}

int main(int argc, char * argv[])
{
    bool        daemonize = false;
    char		c;
    
    while ((opterr == 1) && (c = getopt(argc, argv, "hxse")) != EOF) {
        switch (c) {
			case 'h':
				Usage();
				exit (0);
				
			case 'x':
				daemonize = false;
				break;
				
			case 's':
				PrintStats();
				exit(0);
                
            case 'e':
                Examples();
                exit(0);
				
			default:
				Usage();
				exit(1);
        }
    }
    
    openlog("octopusd", LOG_PID | LOG_NOWAIT, LOG_DAEMON);
	//syslog(LOG_NOTICE, "--- OCTOPUSD STARTING UP (%s) ---", __TIMESTAMP__);
    OLog(1, "--- OCTOPUSD STARTING UP (%s) ---", __TIMESTAMP__);
#ifdef DEBUG
	OLog(0, "--- DEBUG VERSION ---");
#endif

	pthread_t th;
	pthread_create(&th, NULL, serverThread, NULL);

	while(true) sleep(1);
	//serverThread(NULL);
	
	//pthread_t th2;
	//pthread_create(&th2, NULL, timeThread, NULL);
	
	return 0;
}

/*

__attribute__((constructor)) void InitConst()
{
	char* argv[] = {(char*)"foo"};
	mainX(1, argv);
}

int main()
{
	while(true) sleep(1);
	return 0;
}


*/

