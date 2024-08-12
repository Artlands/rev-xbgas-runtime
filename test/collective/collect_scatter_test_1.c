/*
 * _SCATTER_DEMO_C_
 *
 * Copyright (C) 2017-2019 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include "xbrtime.h"

int main()
{
    xbrtime_init();
    int i, my_pe, nelems, *src_array;
    my_pe = xbrtime_mype();
    nelems = 15;
    src_array = (int*) xbrtime_malloc(nelems * sizeof(int));

    if(my_pe == 3)
    {
        for(i = 0; i <= nelems; i++)
        {
            src_array[i] = i+1;
        }
    }
    else
    {
        for(i = 0; i < nelems; i++)
        {
            src_array[i] = 0;
        }
    }

	int pe_msg_sz[5] = {3, 2, 1, 5, 4};
	int pe_disp[5] = {0, 3, 5, 6, 11};
	int dest_array[5] = {0, 0, 0, 0, 0};

	printf("Pre-Scatter - PE %d src_array = %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", my_pe, src_array[0], src_array[1], src_array[2], src_array[3],
                                                                                src_array[4], src_array[5], src_array[6], src_array[7],
                                                                                src_array[8], src_array[9], src_array[10], src_array[11],
                                                                                src_array[12], src_array[13], src_array[14], src_array[15]);

	xbrtime_barrier();

	xbrtime_int_scatter(dest_array, src_array, pe_msg_sz, pe_disp, nelems, 3);

	xbrtime_barrier();

	printf("Post-Scatter - PE %d dest_array = %d %d %d %d %d\n", my_pe, dest_array[0], dest_array[1], dest_array[2], dest_array[3], dest_array[4]);

	xbrtime_close();

    return 0;
}
