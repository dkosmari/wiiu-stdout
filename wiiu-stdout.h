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

#ifndef WIIU_STDOUT_H
#define WIIU_STDOUT_H

#ifdef __WIIU__

#include <coreinit/mutex.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Call this manually when the automatic initialization doesn't work.
 * It's safe to call it multiple times.
 */
void
wiiu_init_stdout(void);

#ifdef __cplusplus
}
#endif

#endif /* __WIIU__ */

#endif
