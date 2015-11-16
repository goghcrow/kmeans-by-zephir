
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#if PHP_VERSION_ID < 50500
#include <locale.h>
#endif

#include "php_ext.h"
#include "kmeans.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *kmeans_point_ce;
zend_class_entry *kmeans_cluster_ce;
zend_class_entry *kmeans_space_ce;

ZEND_DECLARE_MODULE_GLOBALS(kmeans)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(kmeans)
{
#if PHP_VERSION_ID < 50500
	char* old_lc_all = setlocale(LC_ALL, NULL);
	if (old_lc_all) {
		size_t len = strlen(old_lc_all);
		char *tmp  = calloc(len+1, 1);
		if (UNEXPECTED(!tmp)) {
			return FAILURE;
		}

		memcpy(tmp, old_lc_all, len);
		old_lc_all = tmp;
	}

	setlocale(LC_ALL, "C");
#endif
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(KMeans_Point);
	ZEPHIR_INIT(KMeans_Cluster);
	ZEPHIR_INIT(KMeans_Space);

#if PHP_VERSION_ID < 50500
	setlocale(LC_ALL, old_lc_all);
	free(old_lc_all);
#endif
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(kmeans)
{

	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_kmeans_globals *kmeans_globals TSRMLS_DC)
{
	kmeans_globals->initialized = 0;

	/* Memory options */
	kmeans_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	kmeans_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	kmeans_globals->cache_enabled = 1;

	/* Recursive Lock */
	kmeans_globals->recursive_lock = 0;

	/* Static cache */
	memset(kmeans_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

static PHP_RINIT_FUNCTION(kmeans)
{

	zend_kmeans_globals *kmeans_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(kmeans_globals_ptr TSRMLS_CC);
	//zephir_init_interned_strings(TSRMLS_C);

	zephir_initialize_memory(kmeans_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(kmeans)
{

	

	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(kmeans)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_KMEANS_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_KMEANS_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_KMEANS_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_KMEANS_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_KMEANS_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(kmeans)
{
	php_zephir_init_globals(kmeans_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(kmeans)
{

}


zend_function_entry php_kmeans_functions[] = {
ZEND_FE_END

};

zend_module_entry kmeans_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_KMEANS_EXTNAME,
	php_kmeans_functions,
	PHP_MINIT(kmeans),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(kmeans),
#else
	NULL,
#endif
	PHP_RINIT(kmeans),
	PHP_RSHUTDOWN(kmeans),
	PHP_MINFO(kmeans),
	PHP_KMEANS_VERSION,
	ZEND_MODULE_GLOBALS(kmeans),
	PHP_GINIT(kmeans),
	PHP_GSHUTDOWN(kmeans),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_KMEANS
ZEND_GET_MODULE(kmeans)
#endif
