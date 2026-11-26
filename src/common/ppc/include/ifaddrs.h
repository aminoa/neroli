// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// Cafe OS (Wii U) has no getifaddrs(). This shim lets portable code compile; enumeration
// always fails, which callers already handle as "no interfaces available".

#pragma once

struct ifaddrs {
    struct ifaddrs* ifa_next;
    struct sockaddr* ifa_addr;
    struct sockaddr* ifa_netmask;
    struct sockaddr* ifa_broadaddr;
};

static inline int getifaddrs(struct ifaddrs**) {
    return -1;
}

static inline void freeifaddrs(struct ifaddrs*) {}
