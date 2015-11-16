
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_KMEANS_H
#define PHP_KMEANS_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_KMEANS_NAME        "kmeans"
#define PHP_KMEANS_VERSION     "0.0.1"
#define PHP_KMEANS_EXTNAME     "kmeans"
#define PHP_KMEANS_AUTHOR      "xiaofeng"
#define PHP_KMEANS_ZEPVERSION  "0.9a-dev"
#define PHP_KMEANS_DESCRIPTION "kmeans"



ZEND_BEGIN_MODULE_GLOBALS(kmeans)

	int initialized;

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(kmeans)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(kmeans)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(kmeans_globals_id, zend_kmeans_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (kmeans_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_kmeans_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(kmeans_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(kmeans_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def kmeans_globals
#define zend_zephir_globals_def zend_kmeans_globals

extern zend_module_entry kmeans_module_entry;
#define phpext_kmeans_ptr &kmeans_module_entry

#endif
