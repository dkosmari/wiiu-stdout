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

#include <sys/iosupport.h>      // devoptab_list, devoptab_t

#include <coreinit/debug.h>     // OSWriteConsole()

#include "wiiu-stdout.h"


static devoptab_t stdout_dev;
static devoptab_t stderr_dev;


ssize_t
wiiu_devoptab_to_os(struct _reent*,
                    void*,
                    const char* buf,
                    size_t len)
{
    OSConsoleWrite(buf, len);
    return len;
}


__attribute__(( __constructor__ (101) ))
void
wiiu_init_stdout(void)
{
    stdout_dev.name = "STDOUT";
    stdout_dev.structSize = sizeof stdout_dev;
    stdout_dev.write_r = wiiu_devoptab_to_os;
    devoptab_list[STD_OUT] = &stdout_dev;

    stderr_dev.name = "STDERR";
    stderr_dev.structSize = sizeof stderr_dev;
    stderr_dev.write_r = wiiu_devoptab_to_os;
    devoptab_list[STD_ERR] = &stderr_dev;
}

#endif // __WIIU__
