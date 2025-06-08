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

#ifndef _PATH_H_
#define _PATH_H_

#include <stddef.h>
#include "nauty.h"

typedef struct {
    int *path;  /* path array */
    int sz;     /* size of the path array */
} Path;

int path_find_equiv_level(Path *, Path *);
Path* path_make_child_path(Path *);
Path* path_deep_copy(Path *);
void path_visualize(Path *);

#define DYNALLOCPATH(name, size, msg) \
    if ((name= (Path*)malloc(sizeof(Path))) == NULL) {alloc_error(msg);}; \
    if ((name->path = (int*)malloc(size * sizeof(int))) == NULL) {alloc_error(msg);}; \
    name->sz = size;


#define FREEPATH(name) \
    if(name) { \
        FREES(name->path); \
        FREES(name); }\
    name = NULL; 

#endif /* _PATH_H_ */