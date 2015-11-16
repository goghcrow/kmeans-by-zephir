
extern zend_class_entry *kmeans_test_ce;

ZEPHIR_INIT_CLASS(KMeans_Test);

PHP_METHOD(KMeans_Test, x);

ZEPHIR_INIT_FUNCS(kmeans_test_method_entry) {
	PHP_ME(KMeans_Test, x, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
