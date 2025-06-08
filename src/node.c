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

#include "node.h"
#include "nauty.h"

Node* node_make_child(Node *src, int n, int m) {
    Node *dst;
    int lab_sz=0, ptn_sz=0;

    DYNALLOCNODE(dst, "node_deep_copy");
    DYNALLOC1(int,dst->lab,lab_sz,n,"node_deep_copy");
    DYNALLOC1(int,dst->ptn,ptn_sz,n,"node_deep_copy");

    dst->comp_canon = src->comp_canon;
    dst->cosetindex = src->cosetindex;
    dst->eqlev_canon = src->eqlev_canon;
    dst->eqlev_first = src->eqlev_first;
    dst->gca_canon = src->gca_canon;
    dst->gca_first = src->gca_first;
    dst->level = src->level+1;
    dst->numcells = src->numcells;
    dst->target_cell = src->target_cell;
    dst->target_vertex = src->target_vertex;

    dst->path = path_make_child_path(src->path);

    dst->fixedpts = (set*)malloc(m * sizeof(set));
    dst->active = (set*)malloc(m * sizeof(set));
    
    for (int i = 0; i < m; ++i) {
        dst->fixedpts[i] = src->fixedpts[i];
        dst->active[i] = src->active[i];
    }

    for (int i = 0; i < n; ++i) {
        dst->lab[i] = src->lab[i];
        dst->ptn[i] = src->ptn[i];
    }
    return dst;
}

void node_visualize(Node *node, int n) {

    /* print LAB */
    for (int i = 0; i < n; ++i) {
        // if (i > 0) printf(", ");
        printf("%-3d", node->lab[i]);
    }
    printf("\n");

    /* print PTN */
    for (int i = 0; i < n; ++i) {
        // if (i > 0) printf(", ");
        if (node->ptn[i] >= NAUTY_INFINITY)
            printf("-  ");
        else
            printf("%-3d", node->ptn[i]);
    }        
    printf("\nLV: %d  TC: %d  TV: %d\n", node->level, node->target_cell, node->target_vertex);
    printf("EQL_F: %d   COMP_C: %d   EQL_C: %d\n", node->eqlev_first, node->comp_canon, node->eqlev_canon);
}



