
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(KMeans_Test) {

	ZEPHIR_REGISTER_CLASS(KMeans, Test, kmeans, test, kmeans_test_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(KMeans_Test, x) {

	zend_bool _0;
	int n, _1, _2;


	n = 0;
	_2 = 9;
	_1 = 0;
	_0 = 0;
	if (_1 <= _2) {
		while (1) {
			if (_0) {
				_1++;
				if (!(_1 <= _2)) {
					break;
				}
			} else {
				_0 = 1;
			}
			n = _1;
			php_printf("%d", n);
		}
	}

}

