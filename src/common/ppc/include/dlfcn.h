// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// Cafe OS (Wii U) homebrew cannot load shared objects. This shim lets portable code compile;
// every load fails.

#pragma once

#define RTLD_LAZY 0

static inline void* dlopen(const char*, int) {
    return 0;
}

static inline int dlclose(void*) {
    return 0;
}

static inline void* dlsym(void*, const char*) {
    return 0;
}

static inline const char* dlerror() {
    return "dynamic libraries are not supported on this platform";
}
