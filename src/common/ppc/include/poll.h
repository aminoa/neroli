// Copyright 2026 Neroli Emulator Project / Azahar Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the misc/licenses/gplv2.txt file included.

// wut's <poll.h> lacks the normal/priority band flags. Cafe OS does not report them, so they
// are defined as distinct bits that poll() never sets.

#pragma once

#include_next <poll.h>

#ifndef POLLRDNORM
#define POLLRDNORM 0x0040
#define POLLRDBAND 0x0080
#define POLLWRNORM 0x0100
#define POLLWRBAND 0x0200
#endif
