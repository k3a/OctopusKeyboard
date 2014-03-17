//
//  OKDicts.m
//  OKPrefs
//
//  Created by K3A on 6/15/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#import "OKDicts.h"

@implementation OKDicts

- (id)init 
{
    if ( (self = [super init]) )
    {
        self.view = [[UITableView alloc] initWithFrame:CGRectMake(0,0,320,400)];
        [self.view setDataSource:self];
		[self.view setDelegate:self];
        [[self navigationItem] setTitle:@"Dictionaries"];
        
        // GET DICTIONARIES
		//NSLog(@"GETTING DICTZ");
        
        _dicts = [NSMutableArray new];
        
        sDictionaryArray dicts;
        uint32_t numDicts = 0;
        oDictGetList(GetServerPort(), &dicts, &numDicts);
        
        for (unsigned i=0; i<numDicts; i++)
        {
            sDictionary& inDict = dicts[i];
            const char* name = inDict.name;
            if (!name) name = "Unnamed";
            
			NSArray* lc = [[NSString stringWithUTF8String:inDict.language] componentsSeparatedByString:@"-"];
			NSString* langIdent;
			unsigned lcl = [lc count];

			if (!lcl) 
				langIdent = @"unkn";
			else 
			{
				if (lcl==1)
					langIdent = [lc objectAtIndex:0];
				else 
					langIdent = [NSString stringWithFormat:@"%@-%@", [lc objectAtIndex:0],[lc objectAtIndex:1]];
			}
				
            NSDictionary* dict = [NSDictionary dictionaryWithObjectsAndKeys:
                                  [NSString stringWithUTF8String:name], @"name",
                                  [NSNumber numberWithUnsignedInt:inDict.priority], @"priority",
                                  [NSNumber numberWithBool:inDict.loaded], @"loaded",
                                  [NSNumber numberWithBool:inDict.active], @"active",
								  langIdent, @"ident",
                                  nil];
			
            [_dicts addObject:dict];
        }
     
        // sort by priority
        [_dicts sortUsingComparator:^NSComparisonResult(NSDictionary* d1, NSDictionary* d2) {
            return ([[d1 objectForKey:@"priority"] unsignedIntValue] > [[d2 objectForKey:@"priority"] unsignedIntValue]) ?
                NSOrderedAscending : NSOrderedDescending;
        }];
        
    }
    
    return self;
}
-(void)dealloc
{
    [_dicts release];
    //[_view release];
	[super dealloc];
}
/*- (id) view
{
    return _view;
}*/

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_dicts count]?[_dicts count]:1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString* CellIdentifier = @"DictCell";
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) 
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
	
	//cell.selectionStyle = UITableViewCellSelectionStyleNone;
	cell.accessoryType = UITableViewCellAccessoryNone;
	
	if ([_dicts count])
	{
		if ([[[_dicts objectAtIndex:indexPath.row] objectForKey:@"active"] boolValue])
			cell.accessoryType = UITableViewCellAccessoryCheckmark;
		
		cell.textLabel.text = [[_dicts objectAtIndex:indexPath.row] objectForKey:@"name"];
	}
	else {
		cell.textLabel.text = @"(No Dictionaries Installed)";
		cell.accessoryType = UITableViewCellAccessoryNone;
	}
    return  cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	if ([_dicts count])
	{
		NSMutableDictionary* info = [[[_dicts objectAtIndex:indexPath.row] mutableCopy] autorelease];
		bool enabled = ![[info objectForKey:@"active"] boolValue];
		[info setObject:[NSNumber numberWithBool:enabled] forKey:@"active"];
		
		//NSLog(@"INFO %@", info);
		
		// save
		K3AOKPrefsController* prefs = [K3AOKPrefsController instance];
		[prefs setPrefInt:[info objectForKey:@"ident"] value:enabled?1:0];
		[prefs saveSettings];
		
		[_dicts replaceObjectAtIndex:indexPath.row withObject:info];
		
		[self.view reloadData];
	}
}


@end











