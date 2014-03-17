//
//  AntiGDB.h
//
//  Created by K3A on 2/9/12.
//  Copyright (c) 2012 K3A. All rights reserved.
//
#pragma once

#include <math.h>
#include <sys/sysctl.h>
#include <unistd.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

static __attribute__((always_inline)) bool gdb_disable(){return true;};
static __attribute__((always_inline)) bool gdb_check(bool terminateIfYes=true){return false;};
