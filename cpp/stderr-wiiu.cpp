/*
 * Automatically redirect stdout to WHBLogWrite().
 *
 * SPDX-License-Identifier: Apache-2.0
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * SPDX-License-Identifier: MIT
 */

#ifdef __WIIU__

#include <optional>
#include <mutex>

#include <sys/iosupport.h>      // devoptab_list, devoptab_t


extern std::optional<std::mutex> whb_log_mutex;


extern
ssize_t
devoptab_to_whb_log(struct _reent*,
                    void*,
                    const char* buf,
                    size_t len);


__attribute__(( __constructor__ ))
void
init_stderr()
{
    whb_log_mutex.emplace();

    static devoptab_t stderr_dev;
    stderr_dev.name = "STDERR";
    stderr_dev.structSize = sizeof stderr_dev;
    stderr_dev.write_r = devoptab_to_whb_log;
    devoptab_list[STD_ERR] = &stderr_dev;
}

#endif // __WIIU__
