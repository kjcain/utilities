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

#ifndef WRAPPABLE_FUNC_H
#define WRAPPABLE_FUNC_H

/**
 * @brief a function capable of being wrapped
 * 
 * @param params parameters to pass to the function
 * @param args arguments from the superior function
 * @param follow_on next wrapped_function_t to call
 * @return result with value to higher functions
 */
typedef void *wrappable_function_t (
    void *params, 
    void *args,
    wrapped_function_t *follow_on);

/**
 * @brief a struct containing a function, parameters, and a subordinate function
 * 
 */
typedef struct _wrapped_function_t
{
    wrappable_function_t *func; /*!< function to execute */
    void *params; /*!< parameters to pass to the function */
    wrapped_function_t *follow_on; /*!< follow on function */

} wrapped_function_t;

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
    wrapped_function_t *chain);

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
    wrapped_function_t *chain);

/**
 * @brief execute a subordinate function and return the result
 * 
 * @param func function to execute
 * @param args arguments to pass to the subordinate
 * @return void* results from the subordinate
 */
void *unwrap(wrapped_function_t *func, void *args);

/**
 * @brief collect all memory in the chain
 * 
 * @param chain function chain to clean
 */
void free_wrapped_functions(wrapped_function_t *chain);

#endif /* WRAPPABLE_FUNC_H */

/* end of wrappable_func.h */
