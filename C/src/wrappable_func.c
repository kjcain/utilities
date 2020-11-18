/**
 * @file wrappable_func.h
 * @author kyler cain
 * @date 18 november 2020
 * @brief tool for wrapping a function chain at runtime
 * @note a lot of not so graceful choices were made here, 
 * re-evaluate prior to reuse
 * @note not seen in this project, but this could set the stage for exceeding
 * the maximum stack depth in another
 */

#include <stddef.h>

#include "wrappable_func.h"

/**
 * @brief add a new superior function to the function chain
 * 
 * @param func the new function to add
 * @param params parameters to include
 * @param chain subordinate function chain
 * @return wrapped_function_t* 
 */
wrapped_function_t *wrap_top(
    wrappable_function_t *func, 
    void *params, 
    wrapped_function_t *chain)
{
    wrapped_function_t *sup_function = malloc(sizeof(wrapped_function_t));
    
    sup_function->func = func;
    sup_function->params = params;
    sup_function->follow_on = chain;
    
    return sup_function;
}

/**
 * @brief add a new subordinate function to the function chain
 * 
 * @param func the new function to add
 * @param params parameters to include
 * @param chain superior function chain
 * @return wrapped_function_t* 
 */
wrapped_function_t *wrap_bottom(
    wrappable_function_t *func, 
    void *params, 
    wrapped_function_t *chain)
{
    wrapped_function_t *sub_function = malloc(sizeof(wrapped_function_t));

    sub_function->func = func;
    sub_function->params = params;
    sub_function->follow_on = NULL;

    wrapped_function_t *last = chain;

    /* find last item in the chain */
    while(last->follow_on != NULL)
    {
        last = last->follow_on;
    }

    last->follow_on = sub_function;

    return chain;
}

/**
 * @brief execute a subordinate function and return the result
 * 
 * @param func function to execute
 * @param args arguments to pass to the subordinate
 * @return void* results from the subordinate
 */
void *unwrap(wrapped_function_t *func, void *args)
{
    if(func != NULL)
    {
        wrappable_function_t *function = func->func;
        wrapped_function_t *follow_on = func->follow_on;
        void *params = func->params;

        void *result = function(params, args, follow_on);
        
        return result;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief collect all memory in the chain
 * 
 * @param chain function chain to clean
 */
void free_wrapped_functions(wrapped_function_t *chain)
{
    wrapped_function_t *func = chain;
    wrapped_function_t *next_func;
    while(func != NULL)
    {
        next_func = func->follow_on;
        free(func->func);
        free(func->params);
        free(func);
        func = next_func;
    }
}

/* end of wrappable_func.c */
