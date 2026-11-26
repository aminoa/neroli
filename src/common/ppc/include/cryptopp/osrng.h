// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// Crypto++ has no operating system RNG backend for Cafe OS (Wii U), so its osrng.h defines
// nothing there. This wrapper provides CryptoPP::AutoSeededRandomPool on top of RandomPool.
//
// NOTE: The pool is seeded from system timers only. That is adequate for the emulator's uses
// (console-unique IDs, nonces for emulated services) but it is not a cryptographically strong
// entropy source.

#pragma once

#include_next <cryptopp/osrng.h>

#ifndef OS_RNG_AVAILABLE

#include <coreinit/thread.h>
#include <coreinit/time.h>
#include <cryptopp/randpool.h>

namespace CryptoPP {

struct AutoSeededRandomPool : RandomPool {
    AutoSeededRandomPool() {
        static unsigned int counter = 0;
        const struct {
            OSTime system_time;
            OSTime time;
            OSTick tick;
            unsigned int counter;
            const void* thread;
            const void* self;
        } seed{OSGetSystemTime(), OSGetTime(), OSGetSystemTick(), counter++, OSGetCurrentThread(),
               this};
        IncorporateEntropy(reinterpret_cast<const byte*>(&seed), sizeof(seed));
    }
};

} // namespace CryptoPP

#endif // OS_RNG_AVAILABLE
