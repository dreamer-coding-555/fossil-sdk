/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#ifndef FOSSIL_STRUCTURES_STACK_H
#define FOSSIL_STRUCTURES_STACK_H

/**
 * @brief Stack Data Structure
 * 
 * This library provides functions for working with stacks, which are linear data structures
 * that follow the Last-In-First-Out (LIFO) principle.
 *
 * @defgroup create_delete CREATE and DELETE
 * @defgroup push_pop Push and Pop Functions
 * @defgroup top Top Function
 * @defgroup capacity Capacity Functions
 * @defgroup utility Utility Functions
 */

#include "fossil/generic/tofu.h"
#include "fossil/generic/actionof.h"

// Stack structure
typedef struct fossil_stack_node_t {
    fossil_tofu_t data; // Data stored in the stack node
    struct fossil_stack_node_t* next; // Pointer to the next node
} fossil_stack_node_t;

typedef struct fossil_stack_t {
    char* type; // Type of the stack
    fossil_stack_node_t* top; // Pointer to the top node of the stack
} fossil_stack_t;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Create a new stack with the specified data type.
 *
 * @param list_type The type of data the stack will store.
 * @return          The created stack.
 */
fossil_stack_t* fossil_stack_create(char* type);

/**
 * Erase the contents of the stack and free allocated memory.
 *
 * @param stack The stack to erase.
 */
void fossil_stack_erase(fossil_stack_t* stack);

/**
 * Insert data into the stack.
 *
 * @param stack The stack to insert data into.
 * @param data  The data to insert.
 * @return      The error code indicating the success or failure of the operation.
 */
int32_t fossil_stack_insert(fossil_stack_t* stack, fossil_tofu_t data);

/**
 * Remove data from the stack.
 *
 * @param stack       The stack to remove data from.
 * @param[out] data   A pointer to store the removed data.
 * @return            The error code indicating the success or failure of the operation.
 */
int32_t fossil_stack_remove(fossil_stack_t* stack, fossil_tofu_t* data);

/**
 * Search for data in the stack.
 *
 * @param stack The stack to search.
 * @param data  The data to search for.
 * @return      The error code indicating the success or failure of the operation.
 */
int32_t fossil_stack_search(const fossil_stack_t* stack, fossil_tofu_t data);

/**
 * Get the size of the stack.
 *
 * @param stack The stack for which to get the size.
 * @return      The size of the stack.
 */
size_t fossil_stack_size(const fossil_stack_t* stack);

/**
 * Get the data from the stack matching the specified data.
 *
 * @param stack The stack from which to get the data.
 * @param data  The data to search for.
 * @return      A pointer to the matching data, or NULL if not found.
 */
fossil_tofu_t* fossil_stack_getter(fossil_stack_t* stack, fossil_tofu_t data);

/**
 * Set data in the stack.
 *
 * @param stack The stack in which to set the data.
 * @param data  The data to set.
 * @return      The error code indicating the success or failure of the operation.
 */
int32_t fossil_stack_setter(fossil_stack_t* stack, fossil_tofu_t data);

/**
 * Check if the stack is not empty.
 *
 * @param stack The stack to check.
 * @return      True if the stack is not empty, false otherwise.
 */
bool fossil_stack_not_empty(const fossil_stack_t* stack);

/**
 * Check if the stack is not a null pointer.
 *
 * @param stack The stack to check.
 * @return      True if the stack is not a null pointer, false otherwise.
 */
bool fossil_stack_not_cnullptr(const fossil_stack_t* stack);

/**
 * Check if the stack is empty.
 *
 * @param stack The stack to check.
 * @return      True if the stack is empty, false otherwise.
 */
bool fossil_stack_is_empty(const fossil_stack_t* stack);

/**
 * Check if the stack is a null pointer.
 *
 * @param stack The stack to check.
 * @return      True if the stack is a null pointer, false otherwise.
 */
bool fossil_stack_is_cnullptr(const fossil_stack_t* stack);

/**
 * Get the top element of the stack.
 *
 * @param stack         The stack to get the top element from.
 * @param default_value The default value to return if the stack is empty.
 * @return              The top element of the stack or the default value if the stack is empty.
 */
fossil_tofu_t fossil_stack_top(fossil_stack_t* stack, fossil_tofu_t default_value);

#ifdef __cplusplus
}
#endif

#endif
