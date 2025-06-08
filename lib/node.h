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


#ifndef _NODE_H_
#define _NODE_H_

#include <stddef.h>
#include "nauty.h"
#include "path.h"

typedef struct
{
    int *lab, *ptn;     /* Define the partition nest of this node */
    int level;          /* Level of the tree this node is at */
    Path *path;         /* Path in the tree of the current node */
    set *fixedpts;      /* points which were explicitly fixed to get current node */
    set *active;        /* used to contain index to cells now active for refinement purposes */
    int target_cell;    /* position of target cell in lab */
    int target_vertex;  /* target vertex within the target cell that produces this child */
    int numcells;       /* Number of cells in the partition nest (lab,ptn) */
    int gca_first;      /* level of greatest common ancestor of current node and first leaf */
    int gca_canon;      /* ditto for current node and bsf leaf */
    int eqlev_first;    /* level to which codes for this node match those for first leaf */
    int eqlev_canon;    /* level to which codes for this node match those for the bsf leaf. */    
    int comp_canon;     /* -1,0,1 according as code at eqlev_canon+1 is <,==,> that for bsf leaf.  Also used for similar purpose during leaf processing */
    int cosetindex;     /* the point being fixed at level gca_first */    
} Node;
 

Node* node_make_child(Node *, int, int);
void node_visualize(Node *, int);


#define DYNALLOCNODE(name,msg) \
    if ((name= (Node*)malloc(sizeof(Node))) == NULL) {alloc_error(msg);}; 


#define FREENODE(name) \
    if(name) { \
        FREES(name->lab); FREES(name->ptn); FREEPATH(name->path); FREES(name->fixedpts); FREES(name->active); \
        FREES(name); \
        name=NULL; }


 #endif /* _NODE_H_ */