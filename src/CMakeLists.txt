# src/xbgas-runtime CMakeLists.txt driver
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory of
# this distribution.
#

set(XbrtimeSrcs
xbrtime_init.c
xbrtime_util.c
xbrtime_api.c
xbrtime_alloc.c
xbrtime_barrier.c
xbrtime_atomics.c
xbrtime_alltoall.c
xbrtime_broadcast.c
xbrtime_gather.c
xbrtime_gather_all.c
xbrtime_reduce.c
xbrtime_reduce_all.c
xbrtime_scatter.c
xbrtime_util_asm.s
xbrtime_api_asm.s
xbrtime_atomics_asm.s
malloc.c
)

add_library( xbrtime STATIC ${XbrtimeSrcs} )

# Install the xbrtime library
install(TARGETS xbrtime DESTINATION ${XBGAS_RUNTIME}/lib )

# Install header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${XBGAS_RUNTIME}/include
        FILES_MATCHING PATTERN "*.h" 
)

# EOF
