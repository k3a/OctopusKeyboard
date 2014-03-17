#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "include/segtree.hpp"
#include "include/sparsetable.hpp"
#include "include/phrase_map.hpp"
#include "include/suggest.hpp"
#include "include/types.hpp"
#include "include/utils.hpp"

#include "complete.h"

extern "C"
{
	#include <gdbm.h>
}

static char* strtolower(char* str)
{
	char* inp = str;
    while (*str)
	{
		*str = tolower(*str);
		str++;
	}
	return inp;
}

typedef int (*compar_t)(const void *, const void *);

#define MAXDBSIZE 1000
#define DB_STORE_PATH "/var/mobile/Library/Keyboard/"

static GDBM_FILE dbf = NULL;
static PhraseMap pm;
static RMQ st;


struct sword
{
	char *word;
	unsigned count;
};

static int sword_cmp(const struct sword *sw1, const struct sword *sw2)
{
	int retval;
	
	if(sw1->count > sw2->count)
		retval = -1;
	else if (sw1->count < sw2->count)
		retval = 1;
	else
		retval = 0;

	return retval;
}

static int loadtomem(struct sword **pmemstore)
{
	printf("loadtomem called!\n");
	datum dword, dcount;
	int curword=0;
	struct sword *memstore = (struct sword*)malloc(sizeof(struct sword));
	
	dword = gdbm_firstkey(dbf);
	if (!dword.dptr)
	{
		printf("No data in database!\n");
		free(memstore);
		return 0;
	}
	
	while (1)
	{
		datum nextword;
		
		memstore[curword].word = (char*)malloc(dword.dsize);
		if (dword.dptr)
			strcpy(memstore[curword].word, dword.dptr);
		else
			strcpy(memstore[curword].word, "");		

		dcount = gdbm_fetch(dbf, dword);
		if (dcount.dptr)
		{
			memstore[curword].count = atoi(dcount.dptr);
			free(dcount.dptr);
		}
		else
			memstore[curword].count = 0;

		nextword = gdbm_nextkey(dbf, dword);
		free(dword.dptr);
		
		curword++;
		if (!nextword.dptr)
			break;
		
		dword = nextword;
		
		memstore = (struct sword*)realloc(memstore, (curword+1)*sizeof(struct sword));
	}

	*pmemstore = memstore;
	return curword;
}

void db_refresh()
{
	if (!dbf) return;

	struct sword *memstore = NULL;
	int numwords = loadtomem(&memstore);
	if (numwords <= MAXDBSIZE)
	{
		free(memstore);
		return;		// Nothing to be done yet
	}
	
	qsort(memstore, numwords, sizeof (struct sword), (compar_t)sword_cmp);
	
	datum dword, dcount;
	dcount.dptr = (char*)malloc(16);
	
	// Delete extra records from DB
	int i;
	for (i=MAXDBSIZE; i<numwords; i++)
	{
		fflush(stdout);
		dword.dptr = memstore[i].word;
		dword.dsize = strlen(dword.dptr) + 1;
		
		if (gdbm_delete(dbf, dword))
			printf("Deleting '%s' failed! Reason: %s\n", dword.dptr, gdbm_strerror(gdbm_errno));
	}
	
	// Normalize word counts and write back to DB
	int mincount = memstore[MAXDBSIZE-1].count;
	for (i=0; i<MAXDBSIZE; i++)
	{
		memstore[i].count /= mincount;
		dword.dptr = memstore[i].word;
		dword.dsize = strlen(dword.dptr) + 1;
		sprintf(dcount.dptr, "%d", memstore[i].count);
		dcount.dsize = strlen(dcount.dptr) + 1;
		gdbm_store(dbf, dword, dcount, GDBM_REPLACE);
	}
	
	// Clean up and sync the DB
	gdbm_reorganize(dbf);
	gdbm_sync(dbf);
	
	for (i=0; i<MAXDBSIZE; i++)
		free(memstore[i].word);
	free(memstore);
}

int db_store(char *wordin)
{
	if (!dbf || !wordin || !*wordin) return 0;

	char* word = strtolower(strdup(wordin));

	unsigned count;
	int retval;
	// Check whether the record is already in DB
	datum dword, dcount;
	dword.dptr = word;
	dword.dsize = strlen(word) + 1;
	
	printf("Storing %d:%s\n", dword.dsize, dword.dptr);
	NSLog(@"Storing %d:%s\n", dword.dsize, dword.dptr);
	dcount = gdbm_fetch(dbf, dword);
	if (dcount.dptr)
	{
		count = atoi(dcount.dptr) + 1;
		dcount.dptr = (char*)realloc(dcount.dptr, 16);
		sprintf(dcount.dptr, "%u", count);
		dcount.dsize = strlen(dcount.dptr) + 1;
	} else
	{
		dcount.dptr = (char*)malloc(4);
		strcpy(dcount.dptr, "1");
		dcount.dsize = 2;
	}
	
	retval = gdbm_store(dbf, dword, dcount, GDBM_REPLACE);
	
	free(dcount.dptr);
	free(word);
	return retval;
}

unsigned face_init()
{
	if (!dbf) return 0;

	struct sword *memstore = NULL;
	int numwords = loadtomem(&memstore);
	pm.repr.clear();
	
	int i;
	for (i=0; i<numwords; i++)
		pm.insert(memstore[i].count, std::string(memstore[i].word), NULL);
	
	pm.finalize();
	
	for (i=0; i<numwords; i++)
		free(memstore[i].word);

	if (memstore) free(memstore);
	
	vui_t weights;
	for (size_t i = 0; i < pm.repr.size(); ++i)
		weights.push_back(pm.repr[i].weight);
	st.initialize(weights);

	return numwords;
}

vp_t face_query(const char* iline, unsigned num)
{
	char* buf = strtolower(strdup(iline));	
	vp_t r = suggest(pm, st, std::string(buf), num);
	free (buf);
	return r;
}


bool db_init(const char* inpMode)
{
	if (!inpMode || !*inpMode) return false;

	char path[512];
	sprintf(path, "%s/%s-k3adict.db", DB_STORE_PATH, inpMode);

	dbf = gdbm_open(path, 8192, GDBM_WRCREAT|GDBM_NOLOCK, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH, NULL);
	return dbf != NULL;	
}

bool db_shutdown()
{
	if (dbf) gdbm_close(dbf);
	dbf = NULL;
	return true;
}

bool db_sync()
{
	if (dbf) gdbm_sync(dbf);
	return true;
}

void db_lowercase()
{
	if (!dbf) return;

	NSLog(@"LOWERCASE--------");

	datum dword, dcount;
    int curword=0;

    dword = gdbm_firstkey(dbf);
    if (!dword.dptr)
    {
        printf("No data in database!\n");
		return;
    }

    while (1)
    {
        datum nextword;

        if (dword.dptr)	strtolower(dword.dptr);

        dcount = gdbm_fetch(dbf, dword);

		gdbm_store(dbf, dword, dcount, GDBM_REPLACE);

        nextword = gdbm_nextkey(dbf, dword);

        free(dword.dptr);
		free(dcount.dptr);

        curword++;
        if (!nextword.dptr)
            break;

        dword = nextword;

    }


	gdbm_sync(dbf);
	NSLog(@"DONE--------");
}
