// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// wut's <netdb.h> lacks AI_NUMERICSERV, which nsysnet does not implement. It is defined as a
// bit getaddrinfo() ignores.

#pragma once

#include_next <netdb.h>

#ifndef AI_NUMERICSERV
#define AI_NUMERICSERV 0x0400
#endif
