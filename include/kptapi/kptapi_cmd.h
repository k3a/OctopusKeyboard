/******************************************************************************
 *
 * Copyright 2011 KeyPoint Technologies (UK) Ltd.   
 * All rights reserved. This program and the accompanying materials   
 * are made available under the terms of the Eclipse Public License v1.0  
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html

 *           
 * Contributors: 
 * KeyPoint Technologies (UK) Ltd - Initial API and implementation
 *
 *****************************************************************************/
/**
 * @file    kptapi_cmd.h
 *
 * @brief   Defines for available API commands
 *
 * @details 
 *
 *****************************************************************************/
#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef H_KPTAPI_CMD_H
#define H_KPTAPI_CMD_H

/*****************************************************************************
 * Defines for available API commands
 *****************************************************************************/

/*****************************************************************************
 * Configuration Commands 
 */
#define KPTCMD_CONFIG                           20
#define KPTCMD_CONFIG_GETLOCKINGSTATE           (KPTCMD_CONFIG + 1)
#define KPTCMD_CONFIG_SETLOCKINGSTATE           (KPTCMD_CONFIG + 2)

/*****************************************************************************
 * Dictionary Commands 
 */
#define KPTCMD_DICTIONARY                       40
#define KPTCMD_DICTIONARY_GETLIST               (KPTCMD_DICTIONARY + 1)
#define KPTCMD_DICTIONARY_GETLANGLIST           (KPTCMD_DICTIONARY + 2)
#define KPTCMD_DICTIONARY_GETSTATE              (KPTCMD_DICTIONARY + 3)
#define KPTCMD_DICTIONARY_SETSTATES             (KPTCMD_DICTIONARY + 4)

/*****************************************************************************
 * Error Manager Commands 
 */
#define KPTCMD_ERROR                            60
#define KPTCMD_ERROR_POPSTACK                   (KPTCMD_ERROR + 1)
#define KPTCMD_ERROR_CLEARSTACK                 (KPTCMD_ERROR + 2)

/*****************************************************************************
 * Input Management Commands 
 */
#define KPTCMD_INPUTMGR                         80
#define KPTCMD_INPUTMGR_INSERTCHAR              (KPTCMD_INPUTMGR + 1)
#define KPTCMD_INPUTMGR_INSERTSTRING            (KPTCMD_INPUTMGR + 2)
#define KPTCMD_INPUTMGR_INSERTSUGG              (KPTCMD_INPUTMGR + 3)
#define KPTCMD_INPUTMGR_SYNCTOSUGG              (KPTCMD_INPUTMGR + 4)
#define KPTCMD_INPUTMGR_REMOVE                  (KPTCMD_INPUTMGR + 5)
#define KPTCMD_INPUTMGR_RESET                   (KPTCMD_INPUTMGR + 6)
#define KPTCMD_INPUTMGR_REPLACECONTENTS         (KPTCMD_INPUTMGR + 7)
#define KPTCMD_INPUTMGR_GETCURRWORD             (KPTCMD_INPUTMGR + 8)
#define KPTCMD_INPUTMGR_UPDATECURRWORD          (KPTCMD_INPUTMGR + 9)
#define KPTCMD_INPUTMGR_GETCURSOR               (KPTCMD_INPUTMGR + 10)
#define KPTCMD_INPUTMGR_MOVECURSOR              (KPTCMD_INPUTMGR + 11)
#define KPTCMD_INPUTMGR_GETCONFIG               (KPTCMD_INPUTMGR + 12)
#define KPTCMD_INPUTMGR_SETCONFIG               (KPTCMD_INPUTMGR + 13)
#define KPTCMD_INPUTMGR_GETIPINFO				(KPTCMD_INPUTMGR + 14)

/*****************************************************************************
 * Key Map Commands 
 */
#define KPTCMD_KEYMAP                           100
#define KPTCMD_KEYMAP_GETOPEN                   (KPTCMD_KEYMAP + 1)
#define KPTCMD_KEYMAP_GETAVAILABLE              (KPTCMD_KEYMAP + 2)
#define KPTCMD_KEYMAP_GETACTIVE                 (KPTCMD_KEYMAP + 3)
#define KPTCMD_KEYMAP_SETACTIVE                 (KPTCMD_KEYMAP + 4)
#define KPTCMD_KEYMAP_DELETE                    (KPTCMD_KEYMAP + 5)
#define KPTCMD_KEYMAP_OPEN                      (KPTCMD_KEYMAP + 6)
#define KPTCMD_KEYMAP_CLOSE                     (KPTCMD_KEYMAP + 7)
#define KPTCMD_KEYMAP_SAVE                      (KPTCMD_KEYMAP + 8)
#define KPTCMD_KEYMAP_GETLAYOUT                 (KPTCMD_KEYMAP + 9)
#define KPTCMD_KEYMAP_SETLAYOUT                 (KPTCMD_KEYMAP + 10)
#define KPTCMD_KEYMAP_QUERY                     (KPTCMD_KEYMAP + 11)

/*****************************************************************************
 * Learning Commands 
 */
#define KPTCMD_LEARN                            120
#define KPTCMD_LEARN_GETOPTIONS                 (KPTCMD_LEARN + 1)
#define KPTCMD_LEARN_SETOPTIONS                 (KPTCMD_LEARN + 2)
#define KPTCMD_LEARN_CONTENTS                   (KPTCMD_LEARN + 3)
#define KPTCMD_LEARN_BUFFER                     (KPTCMD_LEARN + 4)


/*****************************************************************************
 * Components Commands 
 */
#define KPTCMD_COMPONENT                        180
#define KPTCMD_COMPONENT_GETAVAILABLE           (KPTCMD_COMPONENT + 1)
#define KPTCMD_COMPONENT_GETLOADED              (KPTCMD_COMPONENT + 2)
#define KPTCMD_COMPONENT_LOAD                   (KPTCMD_COMPONENT + 3)
#define KPTCMD_COMPONENT_UNLOAD                 (KPTCMD_COMPONENT + 4)

/*****************************************************************************
 * Output Commands 
 */
#define KPTCMD_OUTPUT                           220
#define KPTCMD_OUTPUT_GETOPTIONS                (KPTCMD_OUTPUT + 1)
#define KPTCMD_OUTPUT_SETOPTIONS                (KPTCMD_OUTPUT + 2)
#define KPTCMD_OUTPUT_GETCATEGORIES             (KPTCMD_OUTPUT + 3)
#define KPTCMD_OUTPUT_SETCATEGORIES             (KPTCMD_OUTPUT + 4)
#define KPTCMD_OUTPUT_MODIFYINDENT              (KPTCMD_OUTPUT + 5)
#define KPTCMD_OUTPUT_ENABLEOUTPUT              (KPTCMD_OUTPUT + 6)
#define KPTCMD_OUTPUT_DISABLEOUTPUT             (KPTCMD_OUTPUT + 7)
#define KPTCMD_OUTPUT_ADDCUSTOMOUTPUT           (KPTCMD_OUTPUT + 8)
#define KPTCMD_OUTPUT_REMOVECUSTOMOUTPUT        (KPTCMD_OUTPUT + 9)
#define KPTCMD_OUTPUT_WRITE                     (KPTCMD_OUTPUT + 10)

/*****************************************************************************
 * Package Management Commands 
 */
#define KPTCMD_PACKAGE                          240
#define KPTCMD_PACKAGE_INSTALL                  (KPTCMD_PACKAGE + 1)
#define KPTCMD_PACKAGE_GETAVAILABLE             (KPTCMD_PACKAGE + 2)
#define KPTCMD_PACKAGE_GETINSTALLED             (KPTCMD_PACKAGE + 3)
#define KPTCMD_PACKAGE_UNINSTALL                (KPTCMD_PACKAGE + 4)

/*****************************************************************************
 * Personal Dictionary Commands 
 */
#define KPTCMD_PERSONAL                         260
#define KPTCMD_PERSONAL_OPENVIEW                (KPTCMD_PERSONAL + 1)
#define KPTCMD_PERSONAL_VIEWPAGE                (KPTCMD_PERSONAL + 2)
#define KPTCMD_PERSONAL_CLOSEVIEW               (KPTCMD_PERSONAL + 3)
#define KPTCMD_PERSONAL_GETENTRYCOUNT           (KPTCMD_PERSONAL + 4)
#define KPTCMD_PERSONAL_COMMITWORDS             (KPTCMD_PERSONAL + 5)
#define KPTCMD_PERSONAL_ADDWORDS                (KPTCMD_PERSONAL + 6)
#define KPTCMD_PERSONAL_EDITWORD                (KPTCMD_PERSONAL + 7)
#define KPTCMD_PERSONAL_REMOVEWORDS             (KPTCMD_PERSONAL + 8)
#define KPTCMD_PERSONAL_REMOVEALLWORDS          (KPTCMD_PERSONAL + 9)
#define KPTCMD_PERSONAL_GETIDFORWORD            (KPTCMD_PERSONAL + 10)
#define KPTCMD_PERSONAL_GETIDSFORTAG            (KPTCMD_PERSONAL + 11)
#define KPTCMD_PERSONAL_GETTAGFORWORD           (KPTCMD_PERSONAL + 12)
#define KPTCMD_PERSONAL_GETWORDFORID            (KPTCMD_PERSONAL + 13)
#define KPTCMD_PERSONAL_EXPORTTOFILE            (KPTCMD_PERSONAL + 14)
#define KPTCMD_PERSONAL_IMPORTFROMFILE          (KPTCMD_PERSONAL + 15)
#define KPTCMD_PERSONAL_GETCONFIG               (KPTCMD_PERSONAL + 16)
#define KPTCMD_PERSONAL_SETCONFIG               (KPTCMD_PERSONAL + 17)


/*****************************************************************************
 * Suggestion Generation Commands 
 */
#define KPTCMD_SUGGS                            320
#define KPTCMD_SUGGS_GETSUGGESTIONS             (KPTCMD_SUGGS + 1)
#define KPTCMD_SUGGS_GETCONFIG                  (KPTCMD_SUGGS + 2)
#define KPTCMD_SUGGS_SETCONFIG                  (KPTCMD_SUGGS + 3)
#define KPTCMD_SUGGS_SELECTLANGUAGES            (KPTCMD_SUGGS + 4)
#define KPTCMD_SUGGS_SELECTDICTIONARIES         (KPTCMD_SUGGS + 5)

///*****************************************************************************
// * Profile save Commands 
// */
#define KPTCMD_PROFILE                             360
#define KPTCMD_PROFILE_SAVE                        (KPTCMD_PROFILE + 1)
#define KPTCMD_PROFILE_RELOAD                      (KPTCMD_PROFILE + 2)



#endif /* #ifndef H_KPTAPI_CMD_H */
