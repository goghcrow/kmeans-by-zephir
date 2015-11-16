
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "math.h"
#include "kernel/hash.h"


ZEPHIR_INIT_CLASS(KMeans_Point) {

	ZEPHIR_REGISTER_CLASS(KMeans, Point, kmeans, point, kmeans_point_method_entry, 0);

	zend_declare_property_null(kmeans_point_ce, SL("space"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(kmeans_point_ce, SL("dimention"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(kmeans_point_ce, SL("coordinates"), ZEND_ACC_PROTECTED TSRMLS_CC);

	kmeans_point_ce->create_object = zephir_init_properties_KMeans_Point;

	zend_class_implements(kmeans_point_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	return SUCCESS;

}

PHP_METHOD(KMeans_Point, getSpace) {

	

	RETURN_MEMBER(this_ptr, "space");

}

PHP_METHOD(KMeans_Point, getCoordinates) {

	

	RETURN_MEMBER(this_ptr, "coordinates");

}

PHP_METHOD(KMeans_Point, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *coordinates = NULL;
	zval *space, *coordinates_param = NULL, *_0 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &space, &coordinates_param);

	coordinates = coordinates_param;


	zephir_update_property_this(this_ptr, SL("space"), space TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_0, space, "getdimention", NULL, 0);
	zephir_check_call_status();
	zephir_update_property_this(this_ptr, SL("dimention"), _0 TSRMLS_CC);
	zephir_update_property_this(this_ptr, SL("coordinates"), coordinates TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Point, toArray) {

	zval *_0, *_1 = NULL, *_2, *_3;

	ZEPHIR_MM_GROW();

	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(_0);
	zephir_read_property_this(&_0, this_ptr, SL("coordinates"), PH_NOISY_CC);
	zephir_array_update_string(&return_value, SL("coordinates"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(_1);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("space"), PH_NOISY_CC);
	if (zephir_array_isset(_2, this_ptr)) {
		_3 = zephir_fetch_nproperty_this(this_ptr, SL("space"), PH_NOISY_CC);
		ZEPHIR_OBS_NVAR(_1);
		zephir_array_fetch(&_1, _3, this_ptr, PH_NOISY, "kmeans/point.zep", 23 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_NULL(_1);
	}
	zephir_array_update_string(&return_value, SL("data"), &_1, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

PHP_METHOD(KMeans_Point, getDistanceWith) {

	double distance, difference;
	int n, _4, _5;
	zend_bool precise, _3;
	zval *point, *precise_param = NULL, *_0, *_1, *_2, *_11, *_12, *_6$$4, *_7$$4, *_8$$4, *_9$$4, *_10$$4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &point, &precise_param);

	if (!precise_param) {
		precise = 1;
	} else {
	if (unlikely(Z_TYPE_P(precise_param) != IS_BOOL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'precise' must be a bool") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	precise = Z_BVAL_P(precise_param);
	}


	n = 0;
	distance = 0.0;
	difference = 0.0;
	_0 = zephir_fetch_nproperty_this(point, SL("space"), PH_NOISY_CC);
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("space"), PH_NOISY_CC);
	if (unlikely(!ZEPHIR_IS_IDENTICAL(_0, _1))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_LogicException, "can only calculate distances from points in the same space", "kmeans/point.zep", 34);
		return;
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	_5 = (zephir_get_numberval(_2) - 1);
	_4 = 0;
	_3 = 0;
	if (_4 <= _5) {
		while (1) {
			if (_3) {
				_4++;
				if (!(_4 <= _5)) {
					break;
				}
			} else {
				_3 = 1;
			}
			n = _4;
			_6$$4 = zephir_fetch_nproperty_this(this_ptr, SL("coordinates"), PH_NOISY_CC);
			zephir_array_fetch_long(&_7$$4, _6$$4, n, PH_NOISY | PH_READONLY, "kmeans/point.zep", 38 TSRMLS_CC);
			_8$$4 = zephir_fetch_nproperty_this(point, SL("coordinates"), PH_NOISY_CC);
			zephir_array_fetch_long(&_9$$4, _8$$4, n, PH_NOISY | PH_READONLY, "kmeans/point.zep", 38 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_10$$4);
			zephir_sub_function(_10$$4, _7$$4, _9$$4);
			difference = zephir_get_numberval(_10$$4);
			distance += (difference * difference);
		}
	}
	ZEPHIR_INIT_VAR(_11);
	if (precise) {
		ZEPHIR_INIT_VAR(_12);
		ZVAL_DOUBLE(_12, distance);
		ZVAL_DOUBLE(_11, sqrt(distance));
	} else {
		ZVAL_DOUBLE(_11, distance);
	}
	RETURN_CCTOR(_11);

}

PHP_METHOD(KMeans_Point, getClosest) {

	HashTable *_1;
	HashPosition _0;
	double minDistance, distance;
	zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *points_param = NULL, *point = NULL, *minPoint = NULL, **_2, *_3$$3 = NULL, *_4$$3 = NULL;
	zval *points = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &points_param);

	points = points_param;


	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	ZEPHIR_INIT_VAR(minPoint);
	ZVAL_NULL(minPoint);
	minDistance = (double) (-1);
	distance = (double) (0);
	zephir_is_iterable(points, &_1, &_0, 0, 0, "kmeans/point.zep", 67);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(point, _2);
		ZEPHIR_INIT_NVAR(_4$$3);
		ZVAL_BOOL(_4$$3, 0);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "getdistancewith", &_5, 0, point, _4$$3);
		zephir_check_call_status();
		distance = zephir_get_doubleval(_3$$3);
		if (unlikely(minDistance == -1)) {
			minDistance = distance;
			ZEPHIR_CPY_WRT(minPoint, point);
			continue;
		}
		if (distance < minDistance) {
			minDistance = distance;
			ZEPHIR_CPY_WRT(minPoint, point);
		}
	}
	RETURN_CCTOR(minPoint);

}

PHP_METHOD(KMeans_Point, belongsTo) {

	zval *space, *_0;

	zephir_fetch_params(0, 1, 0, &space);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("space"), PH_NOISY_CC);
	RETURN_BOOL(ZEPHIR_IS_IDENTICAL(_0, space));

}

PHP_METHOD(KMeans_Point, offsetExists) {

	zval *offset_param = NULL, *_0;
	int offset;

	zephir_fetch_params(0, 1, 0, &offset_param);

	if (unlikely(Z_TYPE_P(offset_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'offset' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	offset = Z_LVAL_P(offset_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("coordinates"), PH_NOISY_CC);
	RETURN_BOOL(zephir_array_isset_long(_0, offset));

}

PHP_METHOD(KMeans_Point, offsetGet) {

	zval *offset_param = NULL, *_0, *_1;
	int offset;

	zephir_fetch_params(0, 1, 0, &offset_param);

	if (unlikely(Z_TYPE_P(offset_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'offset' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	offset = Z_LVAL_P(offset_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("coordinates"), PH_NOISY_CC);
	zephir_array_fetch_long(&_1, _0, offset, PH_NOISY | PH_READONLY, "kmeans/point.zep", 83 TSRMLS_CC);
	RETURN_CTORW(_1);

}

PHP_METHOD(KMeans_Point, offsetSet) {

	zval *offset_param = NULL, *value, *_0;
	int offset;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &offset_param, &value);

	if (unlikely(Z_TYPE_P(offset_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'offset' must be a int") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	offset = Z_LVAL_P(offset_param);


	ZEPHIR_INIT_VAR(_0);
	ZVAL_LONG(_0, offset);
	zephir_update_property_array(this_ptr, SL("coordinates"), _0, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Point, offsetUnset) {

	zval *offset_param = NULL, *_0;
	int offset;

	zephir_fetch_params(0, 1, 0, &offset_param);

	if (unlikely(Z_TYPE_P(offset_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'offset' must be a int") TSRMLS_CC);
		RETURN_NULL();
	}
	offset = Z_LVAL_P(offset_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("coordinates"), PH_NOISY_CC);
	zephir_array_unset_long(&_0, offset, PH_SEPARATE);

}

static zend_object_value zephir_init_properties_KMeans_Point(zend_class_entry *class_type TSRMLS_DC) {

		zval *_0, *_1$$3;

		ZEPHIR_MM_GROW();
	
	{
		zval *this_ptr = NULL;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("coordinates"), PH_NOISY_CC);
		if (Z_TYPE_P(_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(_1$$3);
			array_init(_1$$3);
			zephir_update_property_this(this_ptr, SL("coordinates"), _1$$3 TSRMLS_CC);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJVAL_P(this_ptr);
	}

}

