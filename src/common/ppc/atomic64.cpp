// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// The Wii U's 32-bit PowerPC CPU has no native 64-bit atomic instructions and devkitPPC ships
// no libatomic, so GCC emits calls to the out-of-line helpers below for 64-bit std::atomic
// and __sync builtins. They are implemented with Cafe OS's 64-bit atomic primitives, which
// all return the previous value.

#include <cstdint>
#include <coreinit/atomic64.h>

using u64 = std::uint64_t;

template <typename T = u64>
static volatile T* Cast(const volatile void* ptr) {
    return static_cast<volatile T*>(const_cast<volatile void*>(ptr));
}

extern "C" {

u64 __atomic_load_8(const volatile void* ptr, int) {
    return OSGetAtomic64(Cast(ptr));
}

void __atomic_store_8(volatile void* ptr, u64 value, int) {
    OSSetAtomic64(Cast(ptr), value);
}

u64 __atomic_exchange_8(volatile void* ptr, u64 value, int) {
    return OSSwapAtomic64(Cast(ptr), value);
}

// The parameter list has to match GCC's built-in declaration, which includes `weak`, even
// though the calls GCC emits drop it. The trailing arguments are unused either way.
bool __atomic_compare_exchange_8(volatile void* ptr, void* expected, u64 desired, bool, int,
                                 int) {
    auto* old = static_cast<u64*>(expected);
    return OSCompareAndSwapAtomicEx64(Cast(ptr), *old, desired, old);
}

u64 __atomic_fetch_add_8(volatile void* ptr, u64 value, int) {
    return OSAddAtomic64(Cast<std::int64_t>(ptr), value);
}

u64 __atomic_fetch_sub_8(volatile void* ptr, u64 value, int) {
    return OSAddAtomic64(Cast<std::int64_t>(ptr), -value);
}

u64 __atomic_fetch_and_8(volatile void* ptr, u64 value, int) {
    return OSAndAtomic64(Cast(ptr), value);
}

u64 __atomic_fetch_or_8(volatile void* ptr, u64 value, int) {
    return OSOrAtomic64(Cast(ptr), value);
}

u64 __atomic_fetch_xor_8(volatile void* ptr, u64 value, int) {
    return OSXorAtomic64(Cast(ptr), value);
}

bool __sync_bool_compare_and_swap_8(volatile void* ptr, u64 expected, u64 desired) {
    return OSCompareAndSwapAtomic64(Cast(ptr), expected, desired);
}

u64 __sync_val_compare_and_swap_8(volatile void* ptr, u64 expected, u64 desired) {
    u64 old = expected;
    OSCompareAndSwapAtomicEx64(Cast(ptr), expected, desired, &old);
    return old;
}

} // extern "C"
