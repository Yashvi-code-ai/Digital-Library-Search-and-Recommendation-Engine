#include "analysis.h"
int analysis_reduce_independent_set_to_vertex_cover(size_t vertices,size_t independent_k,size_t *cover_k){
    if(!cover_k||independent_k>vertices)return 0;
    *cover_k=vertices-independent_k;return 1;
}
