
extern zend_class_entry *kmeans_space_ce;

ZEPHIR_INIT_CLASS(KMeans_Space);

PHP_METHOD(KMeans_Space, getDimention);
PHP_METHOD(KMeans_Space, __construct);
PHP_METHOD(KMeans_Space, toArray);
PHP_METHOD(KMeans_Space, newPoint);
PHP_METHOD(KMeans_Space, addPoint);
PHP_METHOD(KMeans_Space, attach);
PHP_METHOD(KMeans_Space, getBoundaries);
PHP_METHOD(KMeans_Space, getRandomPoint);
PHP_METHOD(KMeans_Space, solve);
PHP_METHOD(KMeans_Space, initializeClusters);
PHP_METHOD(KMeans_Space, iterate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, dimention)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_newpoint, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, coordinates, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_addpoint, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, coordinates, 0)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_attach, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, point, KMeans\\Point, 0)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_getrandompoint, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, min, KMeans\\Point, 0)
	ZEND_ARG_OBJ_INFO(0, max, KMeans\\Point, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_solve, 0, 0, 1)
	ZEND_ARG_INFO(0, nbClusters)
	ZEND_ARG_INFO(0, seed)
	ZEND_ARG_INFO(0, iterationCallback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_initializeclusters, 0, 0, 2)
	ZEND_ARG_INFO(0, nbClusters)
	ZEND_ARG_INFO(0, seed)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_space_iterate, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, clusters, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(kmeans_space_method_entry) {
	PHP_ME(KMeans_Space, getDimention, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, __construct, arginfo_kmeans_space___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(KMeans_Space, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, newPoint, arginfo_kmeans_space_newpoint, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, addPoint, arginfo_kmeans_space_addpoint, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, attach, arginfo_kmeans_space_attach, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, getBoundaries, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, getRandomPoint, arginfo_kmeans_space_getrandompoint, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, solve, arginfo_kmeans_space_solve, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Space, initializeClusters, arginfo_kmeans_space_initializeclusters, ZEND_ACC_PROTECTED)
	PHP_ME(KMeans_Space, iterate, arginfo_kmeans_space_iterate, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
