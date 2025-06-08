/**
 * Copyright 2025 Jim Haslett
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "path.h"

int path_find_equiv_level(Path *a, Path *b) {
    int i = 0;
    for (i = 0; i < a->sz && i < b->sz; ++i) {
        if (a->path[i] != b->path[i]) return i+1;  /* while i is the first node that doesn't match, 
                                                    we don't do -1 because of the 1 indexed nature 
                                                    of nauty's levels */
    }
    return i; /* while i is the first node that doesn't match, 
                 we don't do -1 because of the 1 indexed nature 
                 of nauty's levels */
}

Path* path_make_child_path(Path *src) {
    Path *dst;
    DYNALLOCPATH(dst, src->sz+1, "Path Make Child Path"); 

    for (int i = 0; i < src->sz; ++i) {
        dst->path[i] = src->path[i];
    }
    dst->path[dst->sz-1] = -1;
    return dst;
}

Path* path_deep_copy(Path *src) {
    Path *dst;
    DYNALLOCPATH(dst, src->sz, "Path Deep Copy"); 

    for (int i = 0; i < src->sz; ++i) {
        dst->path[i] = src->path[i];
    }
    return dst;
}

void path_visualize(Path *path) {
    printf("[");
    for (int i = 0; i < path->sz; ++i) {
        if (i > 0) printf(", ");
        printf("%d", path->path[i]);
    }
    printf("]");    
}
