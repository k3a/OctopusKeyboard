
#include <mach/mach.h>
#include <servers/bootstrap.h>

typedef char string_t[1024];


typedef struct {
    mach_msg_header_t head;
    
    // The following fields do not represent the actual layout of the request
    // and reply messages that MIG will use. However, a request or reply
    // message will not be larger in size than the sum of the sizes of these
    // fields. We need the size to put an upper bound on the size of an
    // incoming message in a mach_msg() call.
    NDR_record_t NDR;
    union {
        string_t string;
        //other types
    } data;
    
    kern_return_t RetCode;
    mach_msg_trailer_t trailer;
} msg_octopus_t;

#define OCTOPUS_SERVICE "me.k3a.octopusd"