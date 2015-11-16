
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
#include "ext/spl/spl_iterators.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/iterator.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"


ZEPHIR_INIT_CLASS(KMeans_Cluster) {

	ZEPHIR_REGISTER_CLASS_EX(KMeans, Cluster, kmeans, cluster, kmeans_point_ce, kmeans_cluster_method_entry, 0);

	zend_declare_property_null(kmeans_cluster_ce, SL("space"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(kmeans_cluster_ce, SL("points"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(kmeans_cluster_ce TSRMLS_CC, 1, zend_ce_aggregate);
	zend_class_implements(kmeans_cluster_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

PHP_METHOD(KMeans_Cluster, __construct) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *coordinates = NULL;
	zval *space, *coordinates_param = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &space, &coordinates_param);

	zephir_get_arrval(coordinates, coordinates_param);


	ZEPHIR_CALL_PARENT(NULL, kmeans_cluster_ce, this_ptr, "__construct", &_0, 1, space, coordinates);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_1);
	object_init_ex(_1, zephir_get_internal_ce(SS("splobjectstorage") TSRMLS_CC));
	if (zephir_has_constructor(_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, _1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	zephir_update_property_this(this_ptr, SL("points"), _1 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Cluster, toArray) {

	zend_object_iterator *_0;
	zval *point = NULL, *_1, *_3 = NULL, *_2$$3 = NULL;
	zval *points;
	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(points);
	array_init(points);
	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("points"), PH_NOISY_CC);
	_0 = zephir_get_iterator(_1 TSRMLS_CC);
	_0->funcs->rewind(_0 TSRMLS_CC);
	for (;_0->funcs->valid(_0 TSRMLS_CC) == SUCCESS && !EG(exception); _0->funcs->move_forward(_0 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_0->funcs->get_current_data(_0, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		ZEPHIR_CALL_METHOD(&_2$$3, point, "toarray", NULL, 0);
		zephir_check_call_status();
		zephir_array_append(&points, _2$$3, PH_SEPARATE, "kmeans/cluster.zep", 26);
	}
	_0->funcs->dtor(_0 TSRMLS_CC);
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	ZEPHIR_CALL_PARENT(&_3, kmeans_cluster_ce, this_ptr, "toarray", &_4, 2);
	zephir_check_call_status();
	zephir_array_update_string(&return_value, SL("centroid"), &_3, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&return_value, SL("points"), &points, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

PHP_METHOD(KMeans_Cluster, attach) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *point, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &point);



	if (zephir_instance_of_ev(point, kmeans_cluster_ce TSRMLS_CC)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_LogicException, "cannot attach a cluster to another", "kmeans/cluster.zep", 38);
		return;
	}
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "attach", NULL, 0, point);
	zephir_check_call_status();
	RETVAL_ZVAL(point, 1, 0);
	RETURN_MM();

}

PHP_METHOD(KMeans_Cluster, detach) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *point, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &point);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "detach", NULL, 0, point);
	zephir_check_call_status();
	RETVAL_ZVAL(point, 1, 0);
	RETURN_MM();

}

PHP_METHOD(KMeans_Cluster, attachAll) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *points, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &points);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "addall", NULL, 0, points);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Cluster, detachAll) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *points, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &points);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(NULL, _0, "removeall", NULL, 0, points);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Cluster, updateCentroid) {

	zend_bool _20, _10$$4;
	zend_object_iterator *_7;
	zval *centroid = NULL, *point = NULL, *_0, *_1 = NULL, *_2, *_3, *_4, *_5, *_6 = NULL, *_8, *_19, *_9$$4, *_13$$5 = NULL, *_14$$5, *_15$$5 = NULL, *_16$$5, *_17$$5 = NULL, *_18$$5 = NULL, *_23$$6 = NULL, *_24$$6, *_25$$6, *_26$$6 = NULL, *_27$$6 = NULL, *_28$$6 = NULL;
	int ZEPHIR_LAST_CALL_STATUS, n, _21, _22, _11$$4, _12$$4;

	ZEPHIR_MM_GROW();

	n = 0;
	ZEPHIR_INIT_VAR(centroid);
	ZVAL_NULL(centroid);
	ZEPHIR_INIT_VAR(point);
	ZVAL_NULL(point);
	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_CALL_METHOD(&_1, _0, "count", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_LONG_IDENTICAL(_1, 0)) {
		RETURN_MM_NULL();
	}
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("space"), PH_NOISY_CC);
	_3 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(_4);
	ZVAL_LONG(_4, 0);
	ZEPHIR_INIT_VAR(_5);
	ZVAL_LONG(_5, 0);
	ZEPHIR_CALL_FUNCTION(&_6, "array_fill", NULL, 3, _4, _3, _5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&centroid, _2, "newpoint", NULL, 0, _6);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(_8);
	zephir_read_property_this(&_8, this_ptr, SL("points"), PH_NOISY_CC);
	_7 = zephir_get_iterator(_8 TSRMLS_CC);
	_7->funcs->rewind(_7 TSRMLS_CC);
	for (;_7->funcs->valid(_7 TSRMLS_CC) == SUCCESS && !EG(exception); _7->funcs->move_forward(_7 TSRMLS_CC)) {
		{
			zval **ZEPHIR_TMP_ITERATOR_PTR;
			_7->funcs->get_current_data(_7, &ZEPHIR_TMP_ITERATOR_PTR TSRMLS_CC);
			ZEPHIR_CPY_WRT(point, (*ZEPHIR_TMP_ITERATOR_PTR));
		}
		_9$$4 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
		_12$$4 = (zephir_get_numberval(_9$$4) - 1);
		_11$$4 = 0;
		_10$$4 = 0;
		if (_11$$4 <= _12$$4) {
			while (1) {
				if (_10$$4) {
					_11$$4++;
					if (!(_11$$4 <= _12$$4)) {
						break;
					}
				} else {
					_10$$4 = 1;
				}
				n = _11$$4;
				ZEPHIR_OBS_NVAR(_13$$5);
				zephir_read_property(&_13$$5, centroid, SL("coordinates"), PH_NOISY_CC);
				zephir_array_fetch_long(&_14$$5, _13$$5, n, PH_NOISY | PH_READONLY, "kmeans/cluster.zep", 76 TSRMLS_CC);
				ZEPHIR_OBS_NVAR(_15$$5);
				zephir_read_property(&_15$$5, point, SL("coordinates"), PH_NOISY_CC);
				zephir_array_fetch_long(&_16$$5, _15$$5, n, PH_NOISY | PH_READONLY, "kmeans/cluster.zep", 76 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_17$$5);
				zephir_add_function(_17$$5, _14$$5, _16$$5);
				ZEPHIR_INIT_NVAR(_18$$5);
				ZVAL_LONG(_18$$5, n);
				zephir_update_property_array(centroid, SL("coordinates"), _18$$5, _17$$5 TSRMLS_CC);
			}
		}
	}
	_7->funcs->dtor(_7 TSRMLS_CC);
	_19 = zephir_fetch_nproperty_this(this_ptr, SL("dimention"), PH_NOISY_CC);
	_22 = (zephir_get_numberval(_19) - 1);
	_21 = 0;
	_20 = 0;
	if (_21 <= _22) {
		while (1) {
			if (_20) {
				_21++;
				if (!(_21 <= _22)) {
					break;
				}
			} else {
				_20 = 1;
			}
			n = _21;
			ZEPHIR_OBS_NVAR(_23$$6);
			zephir_read_property(&_23$$6, centroid, SL("coordinates"), PH_NOISY_CC);
			zephir_array_fetch_long(&_24$$6, _23$$6, n, PH_NOISY | PH_READONLY, "kmeans/cluster.zep", 86 TSRMLS_CC);
			_25$$6 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
			ZEPHIR_CALL_METHOD(&_26$$6, _25$$6, "count", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_27$$6);
			div_function(_27$$6, _24$$6, _26$$6 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(_28$$6);
			ZVAL_LONG(_28$$6, n);
			zephir_update_property_array(this_ptr, SL("coordinates"), _28$$6, _27$$6 TSRMLS_CC);
		}
	}
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(KMeans_Cluster, getIterator) {

	

	RETURN_MEMBER(this_ptr, "points");

}

PHP_METHOD(KMeans_Cluster, count) {

	zval *_0;
	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_nproperty_this(this_ptr, SL("points"), PH_NOISY_CC);
	ZEPHIR_RETURN_CALL_METHOD(_0, "count", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

