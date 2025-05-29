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

 #include "nsb_stack.h"
 #include "node.h"

void stack_push(Stack *stack, Node *node) {
    StackNode *new_stacknode;
    DYNALLOCSTACKNODE(new_stacknode, "stack_push")
    new_stacknode->node = node;
    new_stacknode->next = stack->top;
    stack->top = new_stacknode;
    
    stack->size++;
}

Node* stack_pop(Stack *stack) {
    if (stack->top == NULL)
        return NULL;

    StackNode *top = stack->top;
    stack->top = top->next;
    Node *ret = top->node;
    FREESTACKNODE(top)
    stack->size--;
    
    return ret;
}

Node* stack_peek(Stack *stack) {
    if (stack->top == NULL)
        return NULL;

    return stack->top->node;
}

size_t stack_size(Stack *stack) {
    return stack->size;
}

Node* stack_peek_at(Stack *stack, size_t idx) {
    if (idx >= stack->size) {printf("Index out of bounds peeking at stack location %zu, stack is only %zu\n", idx, stack->size);  exit(0);}
    StackNode *ptr = stack->top;
    
    for (int i = 0; i < idx; ++i, ptr = ptr->next);
    return ptr->node;
}

void stack_delete_from_bottom(Stack * stack, size_t count) {
    size_t start = 0;
    if (count < stack->size) {
        start = stack->size - count;
    }

    StackNode *tmp, *last = NULL, *ptr = stack->top;
    for (int i = 0; i < start; ++i, last = ptr, ptr = ptr->next);

    /* need to set last node->next to NULL and set stack->size */
    if (last == NULL) {
        /* should be that we are deleting all nodes */
        stack->size = 0;
        stack->top = NULL;
    } else {
        stack->size = start;
        last->next = NULL;
    }

    /* actually delete elements, and free memory */
    while (ptr != NULL) {
        tmp = ptr;
        ptr = tmp->next;
        FREENODE(tmp->node)
        FREESTACKNODE(tmp)
    }
}