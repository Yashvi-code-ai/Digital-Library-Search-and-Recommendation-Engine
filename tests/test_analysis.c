#include "analysis.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    size_t target = 999;
    assert(analysis_reduce_independent_set_to_vertex_cover(5, 3, &target));
    assert(target == 2);
    assert(analysis_reduce_independent_set_to_vertex_cover(10, 0, &target));
    assert(target == 10);
    assert(analysis_reduce_independent_set_to_vertex_cover(10, 10, &target));
    assert(target == 0);
    assert(!analysis_reduce_independent_set_to_vertex_cover(4, 5, &target));
    assert(!analysis_reduce_independent_set_to_vertex_cover(4, 2, NULL));
    puts("Phase 9 analysis tests passed.");
    return 0;
}
