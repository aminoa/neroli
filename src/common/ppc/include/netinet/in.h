// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// Cafe OS (Wii U) networking is IPv4 only and wut's headers define no IPv6 types. The
// definitions below let portable socket code compile; IPv6 sockets cannot be created, so
// those code paths fail at runtime with an address family error.

#pragma once

#include_next <netinet/in.h>

#ifndef AF_INET6
#define AF_INET6 23
#define IPPROTO_IPV6 41
#define INET6_ADDRSTRLEN 46

struct in6_addr {
    unsigned char s6_addr[16];
};

struct sockaddr_in6 {
    sa_family_t sin6_family;
    in_port_t sin6_port;
    uint32_t sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t sin6_scope_id;
};
#endif
