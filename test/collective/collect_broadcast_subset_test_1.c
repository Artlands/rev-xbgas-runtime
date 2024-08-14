#include "xbrtime.h"
#include <math.h>

// Define the new subset broadcast function
XBGAS_BROADCAST(int, int);

int main(int argc, char **argv) {
    int my_pe, *b_val;
    int subset[] = {1, 2, 5, 6, 7};
    size_t subset_size = sizeof(subset) / sizeof(subset[0]);
    
    // Initialize the runtime
    xbrtime_init();
    my_pe = xbrtime_mype();

    // Allocate a symmetric memory region
    b_val = (int*) xbrtime_malloc(sizeof(int));

    // Set the value to the PE number
    *b_val = my_pe;

    printf("Pre-Broadcast - PE:%d B_Val: %d\n", my_pe, *b_val);

    // Perform a barrier
    xbrtime_barrier();

    // Check if the current PE is part of the subset
    int is_in_subset = 0;
    for (int i = 0; i < subset_size; i++) {
        if (subset[i] == my_pe) {
            is_in_subset = 1;
            break;
        }
    }
    int ROOT_RANK = 1;
    if (my_pe == ROOT_RANK) {
        printf("Broadcasting from PE:%d, value=%d\n", ROOT_RANK, *b_val);
    }

    xbrtime_int_broadcast_subset_tree(b_val, b_val, 1, 1, ROOT_RANK, subset, subset_size);

    // Perform a barrier
    xbrtime_barrier();

    printf("Post-Broadcast - PE:%d B_Val: %d\n", my_pe, *b_val);

    // Finalize the runtime
    xbrtime_close();

    return 0;
}
