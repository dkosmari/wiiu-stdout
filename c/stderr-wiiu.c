/*
 * Automatically redirect stdout to WHBLogWrite().
 *
 * SPDX-License-Identifier: Apache-2.0
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * SPDX-License-Identifier: MIT
 *
 * Source: https://github.com/dkosmari/wiiu-stdout
 */

#ifdef __WIIU__

#include <coreinit/mutex.h>

#include <sys/iosupport.h>      // devoptab_list, devoptab_t


extern OSMutex whb_log_mutex;


__attribute__(( __constructor__ (101) ))
void
init_whb_log_mutex(void)
{
    OSInitMutex(&whb_log_mutex);
}


extern
ssize_t
devoptab_to_whb_log(struct _reent*,
                    void*,
                    const char* buf,
                    size_t len);


__attribute__(( __constructor__ (102) ))
void
init_stderr(void)
{
    static devoptab_t stderr_dev;
    stderr_dev.name = "STDERR";
    stderr_dev.structSize = sizeof stderr_dev;
    stderr_dev.write_r = devoptab_to_whb_log;
    devoptab_list[STD_ERR] = &stderr_dev;
}

#endif // __WIIU__
