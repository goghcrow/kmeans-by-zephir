
extern zend_class_entry *kmeans_point_ce;

ZEPHIR_INIT_CLASS(KMeans_Point);

PHP_METHOD(KMeans_Point, getSpace);
PHP_METHOD(KMeans_Point, getCoordinates);
PHP_METHOD(KMeans_Point, __construct);
PHP_METHOD(KMeans_Point, toArray);
PHP_METHOD(KMeans_Point, getDistanceWith);
PHP_METHOD(KMeans_Point, getClosest);
PHP_METHOD(KMeans_Point, belongsTo);
PHP_METHOD(KMeans_Point, offsetExists);
PHP_METHOD(KMeans_Point, offsetGet);
PHP_METHOD(KMeans_Point, offsetSet);
PHP_METHOD(KMeans_Point, offsetUnset);
static zend_object_value zephir_init_properties_KMeans_Point(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, space, KMeans\\Space, 0)
	ZEND_ARG_ARRAY_INFO(0, coordinates, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_getdistancewith, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, point, KMeans\\Point, 0)
	ZEND_ARG_INFO(0, precise)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_getclosest, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, points, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_belongsto, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, space, KMeans\\Space, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_offsetexists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_offsetget, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_offsetset, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_kmeans_point_offsetunset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(kmeans_point_method_entry) {
	PHP_ME(KMeans_Point, getSpace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, getCoordinates, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, __construct, arginfo_kmeans_point___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(KMeans_Point, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, getDistanceWith, arginfo_kmeans_point_getdistancewith, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, getClosest, arginfo_kmeans_point_getclosest, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, belongsTo, arginfo_kmeans_point_belongsto, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, offsetExists, arginfo_kmeans_point_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, offsetGet, arginfo_kmeans_point_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, offsetSet, arginfo_kmeans_point_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(KMeans_Point, offsetUnset, arginfo_kmeans_point_offsetunset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
