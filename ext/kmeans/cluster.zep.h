
extern zend_class_entry *kmeans_cluster_ce;

ZEPHIR_INIT_CLASS(KMeans_Cluster);

PHP_METHOD(KMeans_Cluster, __construct);
PHP_METHOD(KMeans_Cluster, toArray);
PHP_METHOD(KMeans_Cluster, attach);
PHP_METHOD(KMeans_Cluster, detach);
PHP_METHOD(KMeans_Cluster, attachAll);
PHP_METHOD(KMeans_Cluster, detachAll);
PHP_METHOD(KMeans_Cluster, updateCentroid);
PHP_METHOD(KMeans_Cluster, getIterator);
PHP_METHOD(KMeans_Cluster, count);

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_cluster___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, space, KMeans\\Space, 0)
	ZEND_ARG_ARRAY_INFO(0, coordinates, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_cluster_attach, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, point, KMeans\\Point, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_cluster_detach, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, point, KMeans\\Point, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_cluster_attachall, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, points, SplObjectStorage, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_cluster_detachall, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, points, SplObjectStorage, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(kmeans_cluster_method_entry) {
	PHP_ME(KMeans_Cluster, __construct, arginfo_kmeans_cluster___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(KMeans_Cluster, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, attach, arginfo_kmeans_cluster_attach, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, detach, arginfo_kmeans_cluster_detach, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, attachAll, arginfo_kmeans_cluster_attachall, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, detachAll, arginfo_kmeans_cluster_detachall, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, updateCentroid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Cluster, count, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
