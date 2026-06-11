/*
 * Automatically redirect stdout to WHBLogWrite().
 * Copyright 2026  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: Apache-2.0
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * SPDX-License-Identifier: MIT
 *
 * Source: https://github.com/dkosmari/wiiu-stdout
 */

#ifdef __WIIU__

#include <stdlib.h>             // malloc(), free()
#include <string.h>             // memcpy()

#include <sys/iosupport.h>      // devoptab_list, devoptab_t

#include <whb/log.h>
#include <whb/log_cafe.h>
#include <whb/log_module.h>
#include <whb/log_udp.h>

#include "wiiu-stdout.h"


OSMutex* wiiu_whb_log_mutex; // initialized by wiiu-stderr.c


static bool cafe_initialized   = false;
static bool module_initialized = false;
static bool udp_initialized    = false;

static unsigned whb_log_refs  = 0;
static unsigned devoptab_refs = 0;


__attribute__ (( __constructor__ (101) ))
void
wiiu_init_whb_log(void)
{
    if (whb_log_refs++)
        return;
    module_initialized = WHBLogModuleInit();
    if (!module_initialized) {
        cafe_initialized = WHBLogCafeInit();
        udp_initialized = WHBLogUdpInit();
    }
}


__attribute__ (( __destructor__ (101) ))
void
wiiu_fini_whb_log(void)
{
    if (!whb_log_refs)
        return;
    if (--whb_log_refs)
        return;
    if (module_initialized) {
        WHBLogModuleDeinit();
        module_initialized = false;
    }
    if (cafe_initialized) {
        WHBLogCafeDeinit();
        cafe_initialized = false;
    }
    if (udp_initialized) {
        WHBLogUdpDeinit();
        udp_initialized = false;
    }
}


ssize_t
wiiu_devoptab_to_whb_log(struct _reent*,
                         void*,
                         const char* buf,
                         size_t len)
{
    // Note: WHBLogWrite expects a null-terminated string.
    size_t msg_size = len + 1;
    if (msg_size == 0)
        return -1;
    char* msg = malloc(msg_size);
    if (!msg)
        return -1;
    memcpy(msg, buf, len);
    msg[len] = 0;

    if (wiiu_whb_log_mutex) {
        OSLockMutex(wiiu_whb_log_mutex);
        WHBLogWrite(msg);
        OSUnlockMutex(wiiu_whb_log_mutex);
    } else {
        WHBLogWrite(msg);
    }

    free(msg);
    return len;
}


__attribute__(( __constructor__ (102) ))
void
init_stdout(void)
{
    if (!whb_log_refs)
        wiiu_init_whb_log();
    if (devoptab_refs++)
        return;
    static devoptab_t stdout_dev;
    stdout_dev.name = "STDOUT";
    stdout_dev.structSize = sizeof stdout_dev;
    stdout_dev.write_r = wiiu_devoptab_to_whb_log;
    devoptab_list[STD_OUT] = &stdout_dev;
}

#endif // __WIIU__
