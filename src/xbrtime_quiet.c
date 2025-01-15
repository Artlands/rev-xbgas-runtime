/*
 * _XBRTIME_BARRIER_C_
 *
 * Copyright (C) 2017-2025 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include "xbrtime.h"

/* ------------------------------------------------- FUNCTION PROTOTYPES */
void __xbrtime_asm_quiet_fence();

extern void xbrtime_quiet(){
	__xbrtime_asm_quiet_fence();
}


/* EOF */
