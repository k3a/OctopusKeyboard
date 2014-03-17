//
//  main.cpp
//  OctopusTest
//
//  Created by K3A on 5/20/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "octopus.h"
#include <servers/bootstrap.h>

int main (int argc, const char * argv[])
{
    printf("Client Test\n");
    
    kern_return_t kr;
    mach_port_t server_port;
    
    // look up the service to find the server's port
    if ((kr = bootstrap_look_up(bootstrap_port, OCTOPUS_SERVICE,
                                &server_port)) != BOOTSTRAP_SUCCESS) {
        mach_error("bootstrap_look_up:", kr);
        exit(1);
    }
    
    string_t str;
    kr = hello(server_port, str);
    printf("RESP: '%s'\n", str);
    
    mach_port_deallocate(mach_task_self(), server_port);
    
    return 0;
}

