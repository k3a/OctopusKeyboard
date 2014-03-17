#ifndef	_octopus_user_
#define	_octopus_user_

/* Module octopus */

#include <string.h>
#include <mach/ndr.h>
#include <mach/boolean.h>
#include <mach/kern_return.h>
#include <mach/notify.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/mig_errors.h>
#include <mach/port.h>

#ifdef AUTOTEST
#ifndef FUNCTION_PTR_T
#define FUNCTION_PTR_T
typedef void (*function_ptr_t)(mach_port_t, char *, mach_msg_type_number_t);
typedef struct {
        char            *name;
        function_ptr_t  function;
} function_table_entry;
typedef function_table_entry   *function_table_t;
#endif /* FUNCTION_PTR_T */
#endif /* AUTOTEST */

#ifndef	octopus_MSG_COUNT
#define	octopus_MSG_COUNT	19
#endif	/* octopus_MSG_COUNT */

#include <mach/std_types.h>
#include <mach/mig.h>
#include <mach/mig.h>
#include <mach/mach_types.h>
#include "octopus_mach_types.h"

#ifdef __BeforeMigUserHeader
__BeforeMigUserHeader
#endif /* __BeforeMigUserHeader */

#include <sys/cdefs.h>
__BEGIN_DECLS


/* Routine oGetStats */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oGetStats
(
	mach_port_t server,
	ostats_t *stats
);

/* Routine oSuggConfigure */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oSuggConfigure
(
	mach_port_t server,
	uint32_t maxSugg,
	uint32_t suggThreshold,
	bool proximitySuggestion,
	bool errorCorrection,
	bool completion
);

/* Routine oSuggConfigureCaps */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oSuggConfigureCaps
(
	mach_port_t server,
	bool capKnownWords,
	bool capSentence,
	bool capUser,
	bool capNext
);

/* Routine oSuggGetSuggestions */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oSuggGetSuggestions
(
	mach_port_t server,
	sSuggestions *suggs
);

/* Routine oInputClear */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputClear
(
	mach_port_t server
);

/* Routine oInputInsertString */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputInsertString
(
	mach_port_t server,
	const oword_t str,
	int32_t capitalize,
	bool disableLearn
);

/* Routine oInputCursorMove */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputCursorMove
(
	mach_port_t server,
	int32_t typex,
	int32_t offset
);

/* Routine oInputRemove */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputRemove
(
	mach_port_t server,
	int32_t before,
	int32_t after
);

/* Routine oEnableAutoLearning */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oEnableAutoLearning
(
	mach_port_t server,
	bool autolearn
);

/* Routine oInputInsertSugg */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputInsertSugg
(
	mach_port_t server,
	uint32_t set,
	uint32_t ident,
	bool appendSpace
);

/* Routine oInputLearn */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oInputLearn
(
	mach_port_t server
);

/* Routine oProfileSave */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oProfileSave
(
	mach_port_t server
);

/* Routine oDictGetList */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oDictGetList
(
	mach_port_t server,
	sDictionaryArray *dicts,
	mach_msg_type_number_t *dictsCnt
);

/* Routine oUserDictGetWordForID */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oUserDictGetWordForID
(
	mach_port_t server,
	uint32_t idx,
	oword_t_ptr word
);

/* Routine oUserDictClear */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oUserDictClear
(
	mach_port_t server
);

/* Routine oUserDictGetNumWords */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oUserDictGetNumWords
(
	mach_port_t server,
	uint32_t *numWords
);

/* Routine oUserDictImportMessages */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oUserDictImportMessages
(
	mach_port_t server
);

/* Routine oUserDictImportContacts */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oUserDictImportContacts
(
	mach_port_t server
);

/* Routine oReloadPrefs */
#ifdef	mig_external
mig_external
#else
extern
#endif	/* mig_external */
kern_return_t oReloadPrefs
(
	mach_port_t server
);

__END_DECLS

/********************** Caution **************************/
/* The following data types should be used to calculate  */
/* maximum message sizes only. The actual message may be */
/* smaller, and the position of the arguments within the */
/* message layout may vary from what is presented here.  */
/* For example, if any of the arguments are variable-    */
/* sized, and less than the maximum is sent, the data    */
/* will be packed tight in the actual message to reduce  */
/* the presence of holes.                                */
/********************** Caution **************************/

/* typedefs for all requests */

#ifndef __Request__octopus_subsystem__defined
#define __Request__octopus_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oGetStats_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		uint32_t maxSugg;
		uint32_t suggThreshold;
		bool proximitySuggestion;
		char proximitySuggestionPad[3];
		bool errorCorrection;
		char errorCorrectionPad[3];
		bool completion;
		char completionPad[3];
	} __Request__oSuggConfigure_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		bool capKnownWords;
		char capKnownWordsPad[3];
		bool capSentence;
		char capSentencePad[3];
		bool capUser;
		char capUserPad[3];
		bool capNext;
		char capNextPad[3];
	} __Request__oSuggConfigureCaps_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oSuggGetSuggestions_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oInputClear_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		mach_msg_type_number_t strOffset; /* MiG doesn't use it */
		mach_msg_type_number_t strCnt;
		char str[257];
		char strPad[3];
		int32_t capitalize;
		bool disableLearn;
		char disableLearnPad[3];
	} __Request__oInputInsertString_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int32_t typex;
		int32_t offset;
	} __Request__oInputCursorMove_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		int32_t before;
		int32_t after;
	} __Request__oInputRemove_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		bool autolearn;
		char autolearnPad[3];
	} __Request__oEnableAutoLearning_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		uint32_t set;
		uint32_t ident;
		bool appendSpace;
		char appendSpacePad[3];
	} __Request__oInputInsertSugg_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oInputLearn_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oProfileSave_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oDictGetList_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		uint32_t idx;
	} __Request__oUserDictGetWordForID_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oUserDictClear_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oUserDictGetNumWords_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oUserDictImportMessages_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oUserDictImportContacts_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
	} __Request__oReloadPrefs_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Request__octopus_subsystem__defined */

/* union of all requests */

#ifndef __RequestUnion__octopus_subsystem__defined
#define __RequestUnion__octopus_subsystem__defined
union __RequestUnion__octopus_subsystem {
	__Request__oGetStats_t Request_oGetStats;
	__Request__oSuggConfigure_t Request_oSuggConfigure;
	__Request__oSuggConfigureCaps_t Request_oSuggConfigureCaps;
	__Request__oSuggGetSuggestions_t Request_oSuggGetSuggestions;
	__Request__oInputClear_t Request_oInputClear;
	__Request__oInputInsertString_t Request_oInputInsertString;
	__Request__oInputCursorMove_t Request_oInputCursorMove;
	__Request__oInputRemove_t Request_oInputRemove;
	__Request__oEnableAutoLearning_t Request_oEnableAutoLearning;
	__Request__oInputInsertSugg_t Request_oInputInsertSugg;
	__Request__oInputLearn_t Request_oInputLearn;
	__Request__oProfileSave_t Request_oProfileSave;
	__Request__oDictGetList_t Request_oDictGetList;
	__Request__oUserDictGetWordForID_t Request_oUserDictGetWordForID;
	__Request__oUserDictClear_t Request_oUserDictClear;
	__Request__oUserDictGetNumWords_t Request_oUserDictGetNumWords;
	__Request__oUserDictImportMessages_t Request_oUserDictImportMessages;
	__Request__oUserDictImportContacts_t Request_oUserDictImportContacts;
	__Request__oReloadPrefs_t Request_oReloadPrefs;
};
#endif /* !__RequestUnion__octopus_subsystem__defined */
/* typedefs for all replies */

#ifndef __Reply__octopus_subsystem__defined
#define __Reply__octopus_subsystem__defined

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		ostats_t stats;
	} __Reply__oGetStats_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oSuggConfigure_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oSuggConfigureCaps_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		sSuggestions suggs;
	} __Reply__oSuggGetSuggestions_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputClear_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputInsertString_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputCursorMove_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputRemove_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oEnableAutoLearning_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputInsertSugg_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oInputLearn_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oProfileSave_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		/* start of the kernel processed data */
		mach_msg_body_t msgh_body;
		mach_msg_ool_descriptor_t dicts;
		/* end of the kernel processed data */
		NDR_record_t NDR;
		mach_msg_type_number_t dictsCnt;
	} __Reply__oDictGetList_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		mach_msg_type_number_t wordOffset; /* MiG doesn't use it */
		mach_msg_type_number_t wordCnt;
		oword_t word[1];
		char wordPad[3];
	} __Reply__oUserDictGetWordForID_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oUserDictClear_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
		uint32_t numWords;
	} __Reply__oUserDictGetNumWords_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oUserDictImportMessages_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oUserDictImportContacts_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif

#ifdef  __MigPackStructs
#pragma pack(4)
#endif
	typedef struct {
		mach_msg_header_t Head;
		NDR_record_t NDR;
		kern_return_t RetCode;
	} __Reply__oReloadPrefs_t;
#ifdef  __MigPackStructs
#pragma pack()
#endif
#endif /* !__Reply__octopus_subsystem__defined */

/* union of all replies */

#ifndef __ReplyUnion__octopus_subsystem__defined
#define __ReplyUnion__octopus_subsystem__defined
union __ReplyUnion__octopus_subsystem {
	__Reply__oGetStats_t Reply_oGetStats;
	__Reply__oSuggConfigure_t Reply_oSuggConfigure;
	__Reply__oSuggConfigureCaps_t Reply_oSuggConfigureCaps;
	__Reply__oSuggGetSuggestions_t Reply_oSuggGetSuggestions;
	__Reply__oInputClear_t Reply_oInputClear;
	__Reply__oInputInsertString_t Reply_oInputInsertString;
	__Reply__oInputCursorMove_t Reply_oInputCursorMove;
	__Reply__oInputRemove_t Reply_oInputRemove;
	__Reply__oEnableAutoLearning_t Reply_oEnableAutoLearning;
	__Reply__oInputInsertSugg_t Reply_oInputInsertSugg;
	__Reply__oInputLearn_t Reply_oInputLearn;
	__Reply__oProfileSave_t Reply_oProfileSave;
	__Reply__oDictGetList_t Reply_oDictGetList;
	__Reply__oUserDictGetWordForID_t Reply_oUserDictGetWordForID;
	__Reply__oUserDictClear_t Reply_oUserDictClear;
	__Reply__oUserDictGetNumWords_t Reply_oUserDictGetNumWords;
	__Reply__oUserDictImportMessages_t Reply_oUserDictImportMessages;
	__Reply__oUserDictImportContacts_t Reply_oUserDictImportContacts;
	__Reply__oReloadPrefs_t Reply_oReloadPrefs;
};
#endif /* !__RequestUnion__octopus_subsystem__defined */

#ifndef subsystem_to_name_map_octopus
#define subsystem_to_name_map_octopus \
    { "oGetStats", 777 },\
    { "oSuggConfigure", 778 },\
    { "oSuggConfigureCaps", 779 },\
    { "oSuggGetSuggestions", 780 },\
    { "oInputClear", 781 },\
    { "oInputInsertString", 782 },\
    { "oInputCursorMove", 783 },\
    { "oInputRemove", 784 },\
    { "oEnableAutoLearning", 785 },\
    { "oInputInsertSugg", 786 },\
    { "oInputLearn", 787 },\
    { "oProfileSave", 788 },\
    { "oDictGetList", 789 },\
    { "oUserDictGetWordForID", 790 },\
    { "oUserDictClear", 791 },\
    { "oUserDictGetNumWords", 792 },\
    { "oUserDictImportMessages", 793 },\
    { "oUserDictImportContacts", 794 },\
    { "oReloadPrefs", 795 }
#endif

#ifdef __AfterMigUserHeader
__AfterMigUserHeader
#endif /* __AfterMigUserHeader */

#endif	 /* _octopus_user_ */
