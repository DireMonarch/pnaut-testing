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


#ifndef _NSB_STACK_H_
#define _NSB_STACK_H_

#include <stddef.h>
#include <stdlib.h>
#include "node.h"
#include "nauty.h"

typedef struct StackNode StackNode;
struct StackNode {
    Node *node;         /* Node data */
    StackNode *next;    /* Pointer to next stack node */
};

typedef struct {
    StackNode *top;     /* Pointer to top of stack node */
    size_t size;
} Stack;


void stack_push(Stack *stack, Node *node);
Node* stack_pop(Stack *stack);
Node* stack_peek(Stack *stack);
size_t stack_size(Stack *stack);
Node* stack_peek_at(Stack *stack, size_t idx);
void stack_delete_from_bottom(Stack * stack, size_t count);
void stack_visualize(Stack*, int);


#define DYNALLOCSTACK(name,msg) \
    if ((name= (Stack*)malloc(sizeof(Stack))) == NULL) {alloc_error(msg);}; \
    name->top = NULL; \
    name->size = 0;

#define FREESTACK(name) \
    if(name) { \
        while (name->top != NULL) { StackNode *n = name->top; name->top = n->next; FREESTACKNODE(n)} \
        FREES(name); \
        name=NULL; }



#define DYNALLOCSTACKNODE(name,msg) \
    if ((name= (StackNode*)malloc(sizeof(StackNode))) == NULL) {alloc_error(msg);}; \
    name->node = NULL; \
    name->next = NULL;
 

#define FREESTACKNODE(name) \
    if(name) { \
        FREES(name); \
        name=NULL; }


#endif /* _NSB_STACK_H_ */