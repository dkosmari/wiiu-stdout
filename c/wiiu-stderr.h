/*
 * Automatically redirect stderr to WHBLogWrite().
 * Copyright 2026  Daniel K. O. (dkosmari)
 *
 * SPDX-License-Identifier: Apache-2.0
 * SPDX-License-Identifier: LGPL-3.0-or-later
 * SPDX-License-Identifier: MIT
 *
 * Source: https://github.com/dkosmari/wiiu-stdout
 */

#ifndef WIIU_STDERR_H
#define WIIU_STDERR_H

#ifdef __WIIU__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Call this manually when the automatic call doesn't work.
 * It's safe to call it multiple times.
 */
void
wiiu_init_stderr(void);

#ifdef __cplusplus
}
#endif

#endif /* __WIIU__ */

#endif
