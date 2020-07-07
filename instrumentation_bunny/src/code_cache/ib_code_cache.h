/**
 *  @file instrument_code_cache.h
 *  @brief Provides functionality to handle code caches. The benefit of
 *  code caches is thatit avoids weaving the same clunky analysis code
 *  prior to instructions and includes simple jmp instructions instead.
 *  @author John F.X. Galea
 */

#ifndef INSTRUMENT_CODE_CACHE_H_
#define INSTRUMENT_CODE_CACHE_H_

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>
#include "../ib_defines.h"

void ib_code_cache_manager_init();

void ib_code_cache_manager_destroy();

/**
 *  Creates a private code cache to conduct analysis for the given instruction type.
 *  The private cache will always jump back to the address stored in XBX.
 *  Takes a function as a parameter, which is responsible for including the main code inside the cache

 *  @return The newly created code cache.
 */
void *ib_code_cache_init(ib_insert_hndle_data_t *code_cache_data);

/**
 *  Destroys a code cache.
 *
 *  @param code_cache The code cache to destroy
 */
void ib_code_cache_exit(void *code_cache);

/**
 *  Inserts a jump instruction that directs control to the private code cache.
 *
 *  Note that the register specified in \p ib_code_cache_init needs to be spilled
 *  and restored by the user. The user needs to insert code that handles this task.
 *  The register is used to maintain control once the cache is executed.
 *
 *  Moreover, the register must store the value of the thread local storage storing the
 *  ib_thread_data. The load_thread_data flag may be set to true so that the function
 *  performs this task.
 *
 *  @param where The instruction where instrumentation will be placed before it.
 *  @param code_cache An initialised code cache obtained via \p ib_code_cache_init.
 *  @param load_thread_data If true, loads thread data to the return register.
 */
void ib_code_cache_insert_jmp_cache_instr(void *drcontext, instrlist_t *ilist,
		instr_t *where, void *code_cache);

#endif /* INSTRUMENT_CODE_CACHE_H_ */
