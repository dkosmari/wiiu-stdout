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

#ifndef WIIU_STDERR_HPP
#define WIIU_STDERR_HPP

#ifdef __WIIU__

/*
 * Call this manually when the automatic call doesn't work.
 * It's safe to call it multiple times.
 */
void
wiiu_init_stderr()
    noexcept;

#endif // __WIIU__

#endif
