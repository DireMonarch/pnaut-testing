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

 Node* node_deep_copy(Node *src, int n) {
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
    dst->level = src->level;
    dst->numcells = src->numcells;


    for (int i = 1; i < n; ++i) {
        dst->lab[i] = src->lab[i];
        dst->ptn[i] = src->ptn[i];
    }
    return dst;
 }