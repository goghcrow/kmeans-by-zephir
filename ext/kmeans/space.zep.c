
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
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/iterator.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/hash.h"


ZEPHIR_INIT_CLASS(KMeans_Space) {

	ZEPHIR_REGISTER_CLASS_EX(KMeans, Space, kmeans, space, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC), kmeans_space_method_entry, 0);

	zend_declare_property_long(kmeans_space_ce, SL("dimention"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_class_constant_long(kmeans_space_ce, SL("SEED_DEFAULT"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(kmeans_space_ce, SL("SEED_DASV"), 2 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(KMeans_Space, getDimention) {

	

	RETURN_MEMBER(this_ptr, "dimention");

}

PHP_METHOD(KMeans_Space, __construct) {

	zval *dimention_param = NULL, *_0;
	int dimention;

	zephir_fetch_params(0, 0, 1, &dimention_param);

	if (!dimention_param) {
		dimention = 2;
	} else {
		dimention = zephir_get_intval(dimention_param);
	}


	if (unlikely(dimention < 1)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_LogicException, "a space dimention cannot be null or negative", "kmeans/space.zep", 22);
		return;
	}
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(_0, dimention);
	zephir_update_property_this(this_ptr, SL("dimention"), _0 TSRMLS_CC);

}

PHP_METHOD(KMeans_Space, toArray) {

	zend_object_iterator *_0;
	zval *points, *_2$$3 = NULL;
	zval *point = NULL, *_1$$3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	ZEPHIR_INIT_VAR(points);
	array_init(points);
	_0 = zephir_get_iterator(this_ptr TSRMLS_CC);
	_0->funcs->rewind(_0 TSRMLS_CC);
	for (;_0->funcs->valid(_0 TSRMLS_CC) == SUCCESS && !EG(exception); _0->funcs->move_forward(_0 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_0->funcs->get_current_data(_0, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		ZEPHIR_CALL_METHOD(&_1$$3, point, "toarray", NULL, 0);
		zephir_check_call_status();
		zephir_get_arrval(_2$$3, _1$$3);
		zephir_array_append(&points, _2$$3, PH_SEPARATE, "kmeans/space.zep", 34);
	}
	_0->funcs->dtor(_0 TSRMLS_CC);
	zephir_create_array(return_value, 1, 0 TSRMLS_CC);
	zephir_array_update_string(&return_value, SL("points"), &points, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

PHP_METHOD(KMeans_Space, newPoint) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *coordinates_param = NULL, *_0, *_1$$3, *_2$$3, *_3$$3;
	zval *coordinates = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &coordinates_param);

	zephir_get_arrval(coordinates, coordinates_param);


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	if (unlikely(!ZEPHIR_IS_LONG_IDENTICAL(_0, zephir_fast_count_int(coordinates TSRMLS_CC)))) {
		ZEPHIR_INIT_VAR(_1$$3);
		object_init_ex(_1$$3, spl_ce_LogicException);
		ZEPHIR_INIT_VAR(_2$$3);
		zephir_fast_join_str(_2$$3, SL(","), coordinates TSRMLS_CC);
		ZEPHIR_INIT_VAR(_3$$3);
		ZEPHIR_CONCAT_SVS(_3$$3, "(", _2$$3, ") is not a point of this space");
		ZEPHIR_CALL_METHOD(NULL, _1$$3, "__construct", NULL, 4, _3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(_1$$3, "kmeans/space.zep", 43 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	object_init_ex(return_value, kmeans_point_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, this_ptr, coordinates);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(KMeans_Space, addPoint) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *coordinates_param = NULL, *data = NULL, *_0 = NULL;
	zval *coordinates = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &coordinates_param, &data);

	zephir_get_arrval(coordinates, coordinates_param);
	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "newpoint", NULL, 0, coordinates);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "attach", NULL, 0, _0, data);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Space, attach) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *point, *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &point, &data);

	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	if (zephir_instance_of_ev(point, kmeans_point_ce TSRMLS_CC)) {
		ZEPHIR_CALL_PARENT(NULL, kmeans_space_ce, this_ptr, "attach", NULL, 0, point, data);
		zephir_check_call_status();
	} else {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "can only attach points to spaces", "kmeans/space.zep", 59);
		return;
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Space, getBoundaries) {

	zend_bool _11$$4, _19$$5, _24$$5;
	zend_object_iterator *_9;
	zval *min = NULL, *max = NULL, *point = NULL, *_0 = NULL, *_1, *_2 = NULL, *_3 = NULL, *_4 = NULL, *_7, *_8 = NULL, *_10$$4, *_14$$5 = NULL, *_15$$5 = NULL, *_17$$5 = NULL, *_20$$5 = NULL, *_21$$5 = NULL, *_22$$5 = NULL, *_25$$5 = NULL, *_26$$6 = NULL, *_27$$6 = NULL, *_30$$7 = NULL, *_31$$7 = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_6 = NULL, *_16 = NULL, *_18 = NULL, *_23 = NULL, *_28 = NULL, *_29 = NULL, *_32 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, n, _12$$4, _13$$4;

	ZEPHIR_MM_GROW();

	n = 0;
	ZEPHIR_INIT_VAR(min);
	ZVAL_NULL(min);
	ZEPHIR_INIT_VAR(max);
	ZVAL_NULL(max);
	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "count", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG_IDENTICAL(_0, 0)) {
		array_init(return_value);
		RETURN_MM();
	}
	_1 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, 0);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_NULL(_3);
	ZEPHIR_CALL_FUNCTION(&_4, "array_fill", &_5, 3, _2, _1, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&min, this_ptr, "newpoint", &_6, 0, _4);
	zephir_check_call_status();
	_7 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	ZEPHIR_INIT_NVAR(_2);
	ZVAL_LONG(_2, 0);
	ZEPHIR_INIT_NVAR(_3);
	ZVAL_NULL(_3);
	ZEPHIR_CALL_FUNCTION(&_8, "array_fill", &_5, 3, _2, _7, _3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&max, this_ptr, "newpoint", &_6, 0, _8);
	zephir_check_call_status();
	_9 = zephir_get_iterator(this_ptr TSRMLS_CC);
	_9->funcs->rewind(_9 TSRMLS_CC);
	for (;_9->funcs->valid(_9 TSRMLS_CC) == SUCCESS && !EG(exception); _9->funcs->move_forward(_9 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_9->funcs->get_current_data(_9, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		_10$$4 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
		_13$$4 = (zephir_get_numberval(_10$$4) - 1);
		_12$$4 = 0;
		_11$$4 = 0;
		if (_12$$4 <= _13$$4) {
			while (1) {
				if (_11$$4) {
					_12$$4++;
					if (!(_12$$4 <= _13$$4)) {
						break;
					}
				} else {
					_11$$4 = 1;
				}
				n = _12$$4;
				ZEPHIR_INIT_NVAR(_15$$5);
				ZVAL_LONG(_15$$5, n);
				ZEPHIR_CALL_METHOD(&_14$$5, min, "offsetget", &_16, 0, _15$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_15$$5);
				ZVAL_LONG(_15$$5, n);
				ZEPHIR_CALL_METHOD(&_17$$5, point, "offsetget", &_18, 0, _15$$5);
				zephir_check_call_status();
				_19$$5 = ZEPHIR_GT(_14$$5, _17$$5);
				if (!(_19$$5)) {
					ZEPHIR_INIT_NVAR(_15$$5);
					ZVAL_LONG(_15$$5, n);
					ZEPHIR_CALL_METHOD(&_20$$5, min, "offsetget", &_16, 0, _15$$5);
					zephir_check_call_status();
					_19$$5 = Z_TYPE_P(_20$$5) == IS_NULL;
				}
				ZEPHIR_INIT_NVAR(_15$$5);
				ZVAL_LONG(_15$$5, n);
				ZEPHIR_CALL_METHOD(&_21$$5, max, "offsetget", &_16, 0, _15$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(_15$$5);
				ZVAL_LONG(_15$$5, n);
				ZEPHIR_CALL_METHOD(&_22$$5, point, "offsetget", &_23, 0, _15$$5);
				zephir_check_call_status();
				_24$$5 = ZEPHIR_LT(_21$$5, _22$$5);
				if (!(_24$$5)) {
					ZEPHIR_INIT_NVAR(_15$$5);
					ZVAL_LONG(_15$$5, n);
					ZEPHIR_CALL_METHOD(&_25$$5, max, "offsetget", &_16, 0, _15$$5);
					zephir_check_call_status();
					_24$$5 = Z_TYPE_P(_25$$5) == IS_NULL;
				}
				if (_19$$5) {
					ZEPHIR_INIT_NVAR(_27$$6);
					ZVAL_LONG(_27$$6, n);
					ZEPHIR_CALL_METHOD(&_26$$6, point, "offsetget", &_28, 0, _27$$6);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_27$$6);
					ZVAL_LONG(_27$$6, n);
					ZEPHIR_CALL_METHOD(NULL, min, "offsetset", &_29, 0, _27$$6, _26$$6);
					zephir_check_call_status();
				} else if (_24$$5) {
					ZEPHIR_INIT_NVAR(_31$$7);
					ZVAL_LONG(_31$$7, n);
					ZEPHIR_CALL_METHOD(&_30$$7, point, "offsetget", &_32, 0, _31$$7);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(_31$$7);
					ZVAL_LONG(_31$$7, n);
					ZEPHIR_CALL_METHOD(NULL, max, "offsetset", &_29, 0, _31$$7, _30$$7);
					zephir_check_call_status();
				}
			}
		}
	}
	_9->funcs->dtor(_9 TSRMLS_CC);
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, min);
	zephir_array_fast_append(return_value, max);
	RETURN_MM();

}

PHP_METHOD(KMeans_Space, getRandomPoint) {

	zend_bool _6;
	zval *_4 = NULL;
	zephir_fcall_cache_entry *_11 = NULL, *_14 = NULL, *_16 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, n, _7, _8;
	zval *min, *max, *point = NULL, *_0, *_1, *_2, *_3 = NULL, *_5, *_9$$3 = NULL, *_10$$3 = NULL, *_12$$3 = NULL, *_13$$3 = NULL, *_15$$3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &min, &max);



	n = 0;
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_1);
	ZVAL_LONG(_1, 0);
	ZEPHIR_INIT_VAR(_2);
	ZVAL_NULL(_2);
	ZEPHIR_CALL_FUNCTION(&_3, "array_fill", NULL, 3, _1, _0, _2);
	zephir_check_call_status();
	zephir_get_arrval(_4, _3);
	ZEPHIR_CALL_METHOD(&point, this_ptr, "newpoint", NULL, 0, _4);
	zephir_check_call_status();
	_5 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	_8 = (zephir_get_numberval(_5) - 1);
	_7 = 0;
	_6 = 0;
	if (_7 <= _8) {
		while (1) {
			if (_6) {
				_7++;
				if (!(_7 <= _8)) {
					break;
				}
			} else {
				_6 = 1;
			}
			n = _7;
			ZEPHIR_INIT_NVAR(_10$$3);
			ZVAL_LONG(_10$$3, n);
			ZEPHIR_CALL_METHOD(&_9$$3, min, "offsetget", &_11, 0, _10$$3);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_10$$3);
			ZVAL_LONG(_10$$3, n);
			ZEPHIR_CALL_METHOD(&_12$$3, max, "offsetget", &_11, 0, _10$$3);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&_13$$3, "rand", &_14, 5, _9$$3, _12$$3);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(_10$$3);
			ZVAL_LONG(_10$$3, n);
			ZEPHIR_INIT_NVAR(_15$$3);
			ZVAL_DOUBLE(_15$$3, zephir_get_doubleval(_13$$3));
			ZEPHIR_CALL_METHOD(NULL, point, "offsetset", &_16, 0, _10$$3, _15$$3);
			zephir_check_call_status();
		}
	}
	RETURN_CCTOR(point);

}

PHP_METHOD(KMeans_Space, solve) {

	zend_bool _0;
	zval *clusters = NULL, *_4 = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zval *nbClusters_param = NULL, *seed_param = NULL, *iterationCallback = NULL, *_1 = NULL, *_2, *_3, *_6 = NULL, *_5$$4;
	int nbClusters, seed, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &nbClusters_param, &seed_param, &iterationCallback);

	nbClusters = zephir_get_intval(nbClusters_param);
	if (!seed_param) {
		seed = 1;
	} else {
		seed = zephir_get_intval(seed_param);
	}
	if (!iterationCallback) {
		iterationCallback = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_INIT_VAR(clusters);
	array_init(clusters);
	_0 = zephir_is_true(iterationCallback);
	if (_0) {
		_0 = !(zephir_is_callable(iterationCallback TSRMLS_CC));
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "invalid iteration callback", "kmeans/space.zep", 107);
		return;
	}
	ZEPHIR_INIT_VAR(_2);
	ZVAL_LONG(_2, nbClusters);
	ZEPHIR_INIT_VAR(_3);
	ZVAL_LONG(_3, seed);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "initializeclusters", NULL, 0, _2, _3);
	zephir_check_call_status();
	zephir_get_arrval(_4, _1);
	ZEPHIR_CPY_WRT(clusters, _4);
	if (zephir_fast_count_int(clusters TSRMLS_CC) == 1) {
		zephir_array_fetch_long(&_5$$4, clusters, 0, PH_NOISY | PH_READONLY, "kmeans/space.zep", 115 TSRMLS_CC);
		RETURN_CTOR(_5$$4);
	}
	do {
		if (unlikely(zephir_is_true(iterationCallback))) {
			ZEPHIR_CALL_ZVAL_FUNCTION(NULL, iterationCallback, NULL, 0, this_ptr, clusters);
			zephir_check_call_status();
		}
		ZEPHIR_CALL_METHOD(&_6, this_ptr, "iterate", &_7, 0, clusters);
		zephir_check_call_status();
	} while (zephir_is_true(_6));
	RETURN_CTOR(clusters);

}

PHP_METHOD(KMeans_Space, initializeClusters) {

	zend_object_iterator *_25$$9, *_33$$9;
	zend_bool _2$$4, _15$$7, _22$$7;
	zval *clusters, *boundaries$$4 = NULL, *_1$$4 = NULL;
	double sum, distance;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL, *_10 = NULL, *_14 = NULL, *_17 = NULL, *_18 = NULL, *_29 = NULL, *_35 = NULL;
	zval *nbClusters_param = NULL, *seed_param = NULL, *min = NULL, *max = NULL, *distances = NULL, *point = NULL, *_38, *_0$$4 = NULL, *_5$$6 = NULL, *_6$$6 = NULL, *_8$$6 = NULL, *_11$$7 = NULL, _12$$7, *_13$$7 = NULL, *_16$$7 = NULL, *_19$$7, *_20$$7 = NULL, *_21$$7 = NULL, _30$$9 = zval_used_for_init, _31$$9 = zval_used_for_init, *_32$$9 = NULL, *_26$$10 = NULL, *_27$$10 = NULL, *_28$$10 = NULL, *_34$$11 = NULL, *_36$$11 = NULL, *_37$$11 = NULL;
	int nbClusters, seed, ZEPHIR_LAST_CALL_STATUS, n, i, position, _3$$4, _4$$4, _23$$7, _24$$7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &nbClusters_param, &seed_param);

	nbClusters = zephir_get_intval(nbClusters_param);
	seed = zephir_get_intval(seed_param);


	ZEPHIR_INIT_VAR(min);
	ZVAL_NULL(min);
	ZEPHIR_INIT_VAR(max);
	ZVAL_NULL(max);
	ZEPHIR_INIT_VAR(distances);
	ZVAL_NULL(distances);
	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	n = 0;
	i = 0;
	position = 0;
	sum = 0.0;
	distance = 0.0;
	ZEPHIR_INIT_VAR(clusters);
	array_init(clusters);
	if (nbClusters <= 0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "invalid clusters number", "kmeans/space.zep", 142);
		return;
	}
	do {
		if (seed == 1) {
			ZEPHIR_CALL_METHOD(&_0$$4, this_ptr, "getboundaries", NULL, 0);
			zephir_check_call_status();
			zephir_get_arrval(_1$$4, _0$$4);
			ZEPHIR_CPY_WRT(boundaries$$4, _1$$4);
			if (ZEPHIR_IS_EMPTY(boundaries$$4)) {
			} else {
				ZEPHIR_OBS_NVAR(min);
				zephir_array_fetch_long(&min, boundaries$$4, 0, PH_NOISY, "kmeans/space.zep", 154 TSRMLS_CC);
				ZEPHIR_OBS_NVAR(max);
				zephir_array_fetch_long(&max, boundaries$$4, 1, PH_NOISY, "kmeans/space.zep", 155 TSRMLS_CC);
			}
			_4$$4 = (nbClusters - 1);
			_3$$4 = 0;
			_2$$4 = 0;
			if (_3$$4 <= _4$$4) {
				while (1) {
					if (_2$$4) {
						_3$$4++;
						if (!(_3$$4 <= _4$$4)) {
							break;
						}
					} else {
						_2$$4 = 1;
					}
					n = _3$$4;
					ZEPHIR_INIT_NVAR(_5$$6);
					object_init_ex(_5$$6, kmeans_cluster_ce);
					ZEPHIR_CALL_METHOD(&_6$$6, this_ptr, "getrandompoint", &_7, 0, min, max);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&_8$$6, _6$$6, "getcoordinates", &_9, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, _5$$6, "__construct", &_10, 6, this_ptr, _8$$6);
					zephir_check_call_status();
					zephir_array_append(&clusters, _5$$6, PH_SEPARATE, "kmeans/space.zep", 160);
				}
			}
			break;
		}
		if (seed == 2) {
			ZEPHIR_CALL_METHOD(&_11$$7, this_ptr, "count", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_SINIT_VAR(_12$$7);
			ZVAL_LONG(&_12$$7, 1);
			ZEPHIR_CALL_FUNCTION(&_13$$7, "rand", &_14, 5, &_12$$7, _11$$7);
			zephir_check_call_status();
			position = zephir_get_intval(_13$$7);
			i = 1;
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				_15$$7 = (i < position);
				if (_15$$7) {
					ZEPHIR_CALL_METHOD(&_16$$7, this_ptr, "valid", &_17, 0);
					zephir_check_call_status();
					_15$$7 = zephir_is_true(_16$$7);
				}
				if (!(_15$$7)) {
					break;
				}
				i++;
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "next", &_18, 0);
				zephir_check_call_status();
			}
			ZEPHIR_INIT_VAR(_19$$7);
			object_init_ex(_19$$7, kmeans_cluster_ce);
			ZEPHIR_CALL_METHOD(&_20$$7, this_ptr, "current", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_21$$7, _20$$7, "getcoordinates", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _19$$7, "__construct", &_10, 6, this_ptr, _21$$7);
			zephir_check_call_status();
			zephir_array_append(&clusters, _19$$7, PH_SEPARATE, "kmeans/space.zep", 174);
			ZEPHIR_INIT_NVAR(distances);
			object_init_ex(distances, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
			if (zephir_has_constructor(distances TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, distances, "__construct", NULL, 0);
				zephir_check_call_status();
			}
			_24$$7 = (nbClusters - 1);
			_23$$7 = 1;
			_22$$7 = 0;
			if (_23$$7 <= _24$$7) {
				while (1) {
					if (_22$$7) {
						_23$$7++;
						if (!(_23$$7 <= _24$$7)) {
							break;
						}
					} else {
						_22$$7 = 1;
					}
					i = _23$$7;
					sum = 0.0;
					_25$$9 = zephir_get_iterator(this_ptr TSRMLS_CC);
					_25$$9->funcs->rewind(_25$$9 TSRMLS_CC);
					for (;_25$$9->funcs->valid(_25$$9 TSRMLS_CC) == SUCCESS && !EG(exception); _25$$9->funcs->move_forward(_25$$9 TSRMLS_CC)) {
						{
							zval **ZEPHIR_TMP_ITERATOR_PTR;
							_25$$9->funcs->get_current_data(_25$$9, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
							ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
						}
						ZEPHIR_CALL_METHOD(&_27$$10, point, "getclosest", NULL, 0, clusters);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&_26$$10, point, "getdistancewith", NULL, 0, _27$$10);
						zephir_check_call_status();
						distance = zephir_get_numberval(_26$$10);
						ZEPHIR_INIT_NVAR(_28$$10);
						ZVAL_DOUBLE(_28$$10, distance);
						ZEPHIR_CALL_METHOD(NULL, distances, "offsetset", &_29, 7, point, _28$$10);
						zephir_check_call_status();
						sum = (sum + distance);
					}
					_25$$9->funcs->dtor(_25$$9 TSRMLS_CC);
					ZEPHIR_SINIT_NVAR(_30$$9);
					ZVAL_LONG(&_30$$9, 0);
					ZEPHIR_SINIT_NVAR(_31$$9);
					ZVAL_LONG(&_31$$9, (int) (sum));
					ZEPHIR_CALL_FUNCTION(&_32$$9, "rand", &_14, 5, &_30$$9, &_31$$9);
					zephir_check_call_status();
					sum = zephir_get_doubleval(_32$$9);
					_33$$9 = zephir_get_iterator(this_ptr TSRMLS_CC);
					_33$$9->funcs->rewind(_33$$9 TSRMLS_CC);
					for (;_33$$9->funcs->valid(_33$$9 TSRMLS_CC) == SUCCESS && !EG(exception); _33$$9->funcs->move_forward(_33$$9 TSRMLS_CC)) {
						{
							zval **ZEPHIR_TMP_ITERATOR_PTR;
							_33$$9->funcs->get_current_data(_33$$9, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
							ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
						}
						ZEPHIR_CALL_METHOD(&_34$$11, distances, "offsetget", &_35, 8, point);
						zephir_check_call_status();
						sum = (double) ((sum - zephir_get_numberval(_34$$11)));
						if (sum > 0) {
							continue;
						}
						ZEPHIR_INIT_NVAR(_36$$11);
						object_init_ex(_36$$11, kmeans_cluster_ce);
						ZEPHIR_CALL_METHOD(&_37$$11, point, "getcoordinates", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, _36$$11, "__construct", &_10, 6, this_ptr, _37$$11);
						zephir_check_call_status();
						zephir_array_append(&clusters, _36$$11, PH_SEPARATE, "kmeans/space.zep", 199);
						break;
					}
					_33$$9->funcs->dtor(_33$$9 TSRMLS_CC);
				}
			}
			break;
		}
	} while(0);

	zephir_array_fetch_long(&_38, clusters, 0, PH_NOISY | PH_READONLY, "kmeans/space.zep", 208 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(NULL, _38, "attachall", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_CTOR(clusters);

}

PHP_METHOD(KMeans_Space, iterate) {

	zend_object_iterator *_13, *_15, *_3$$3;
	HashTable *_1, *_18;
	HashPosition _0, _17;
	zend_bool _continue;
	zephir_fcall_cache_entry *_5 = NULL, *_7 = NULL, *_11 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *clusters_param = NULL, *cluster = NULL, *point = NULL, *closest = NULL, *attach = NULL, *detach = NULL, **_2, **_19, *_4$$4 = NULL, *_8$$4 = NULL, *_10$$4 = NULL, *_12$$4 = NULL, *_6$$6 = NULL, *_9$$7 = NULL, *_14$$8 = NULL, *_16$$9 = NULL;
	zval *clusters = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &clusters_param);

	zephir_get_arrval(clusters, clusters_param);


	_continue = 0;
	ZEPHIR_INIT_VAR(cluster);
	ZVAL_NULL(cluster);
	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	ZEPHIR_INIT_VAR(closest);
	ZVAL_NULL(closest);
	ZEPHIR_INIT_VAR(attach);
	ZVAL_NULL(attach);
	ZEPHIR_INIT_VAR(detach);
	ZVAL_NULL(detach);
	ZEPHIR_INIT_NVAR(attach);
	object_init_ex(attach, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
	if (zephir_has_constructor(attach TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, attach, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(detach);
	object_init_ex(detach, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
	if (zephir_has_constructor(detach TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, detach, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_is_iterable(clusters, &_1, &_0, 0, 0, "kmeans/space.zep", 253);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(cluster, _2);
		_3$$3 = zephir_get_iterator(cluster TSRMLS_CC);
		_3$$3->funcs->rewind(_3$$3 TSRMLS_CC);
		for (;_3$$3->funcs->valid(_3$$3 TSRMLS_CC) == SUCCESS && !EG(exception); _3$$3->funcs->move_forward(_3$$3 TSRMLS_CC)) {
			{
				zval **ZEPHIR_TMP_ITERATOR_PTR;
				_3$$3->funcs->get_current_data(_3$$3, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
				ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
			}
			ZEPHIR_CALL_METHOD(&closest, point, "getclosest", NULL, 0, clusters);
			zephir_check_call_status();
			if (unlikely(ZEPHIR_IS_IDENTICAL(closest, cluster))) {
				continue;
			}
			ZEPHIR_CALL_METHOD(&_4$$4, attach, "offsetexists", &_5, 9, closest);
			zephir_check_call_status();
			if (!(zephir_is_true(_4$$4))) {
				ZEPHIR_INIT_NVAR(_6$$6);
				object_init_ex(_6$$6, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
				if (zephir_has_constructor(_6$$6 TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, _6$$6, "__construct", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(NULL, attach, "offsetset", &_7, 7, closest, _6$$6);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_8$$4, detach, "offsetexists", &_5, 9, cluster);
			zephir_check_call_status();
			if (!(zephir_is_true(_8$$4))) {
				ZEPHIR_INIT_NVAR(_9$$7);
				object_init_ex(_9$$7, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
				if (zephir_has_constructor(_9$$7 TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, _9$$7, "__construct", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(NULL, detach, "offsetset", &_7, 7, cluster, _9$$7);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_10$$4, attach, "offsetget", &_11, 8, closest);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _10$$4, "attach", NULL, 0, point);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_12$$4, detach, "offsetget", &_11, 8, cluster);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, _12$$4, "attach", NULL, 0, point);
			zephir_check_call_status();
			_continue = 1;
		}
		_3$$3->funcs->dtor(_3$$3 TSRMLS_CC);
	}
	_13 = zephir_get_iterator(attach TSRMLS_CC);
	_13->funcs->rewind(_13 TSRMLS_CC);
	for (;_13->funcs->valid(_13 TSRMLS_CC) == SUCCESS && !EG(exception); _13->funcs->move_forward(_13 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_13->funcs->get_current_data(_13, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(cluster, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		ZEPHIR_CALL_METHOD(&_14$$8, attach, "offsetget", &_11, 8, cluster);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, cluster, "attachall", NULL, 0, _14$$8);
		zephir_check_call_status();
	}
	_13->funcs->dtor(_13 TSRMLS_CC);
	_15 = zephir_get_iterator(detach TSRMLS_CC);
	_15->funcs->rewind(_15 TSRMLS_CC);
	for (;_15->funcs->valid(_15 TSRMLS_CC) == SUCCESS && !EG(exception); _15->funcs->move_forward(_15 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_15->funcs->get_current_data(_15, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(cluster, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		ZEPHIR_CALL_METHOD(&_16$$9, detach, "offsetget", &_11, 8, cluster);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, cluster, "detachall", NULL, 0, _16$$9);
		zephir_check_call_status();
	}
	_15->funcs->dtor(_15 TSRMLS_CC);
	zephir_is_iterable(clusters, &_18, &_17, 0, 0, "kmeans/space.zep", 266);
	for (
	  ; zephir_hash_get_current_data_ex(_18, (void**) &_19, &_17) == SUCCESS
	  ; zephir_hash_move_forward_ex(_18, &_17)
	) {
		ZEPHIR_GET_HVALUE(cluster, _19);
		ZEPHIR_CALL_METHOD(NULL, cluster, "updatecentroid", NULL, 0);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(_continue);

}

