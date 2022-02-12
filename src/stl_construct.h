/* 
 * Created by vanilla.
 * Just for leaning STL.
 */

#ifndef VANILLA_SGI_STL_CONSTRUCT_H
#define VANILLA_SGI_STL_CONSTRUCT_H

#include <new>
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template<class _T1, class _T2>
inline void _Construct(_T1* __p, const _T2& __value) {
	new((void *)__p) _T1(__value);
}

template <class _T1>
inline void _Construct(_T1* __p) {
  new ((void*) __p) _T1();
}

/*
template<class _Tp>
void destroy_impl(_Tp *, __true_type) {}

template<class _Tp>
void destroy_impl(_Tp *__pointer, __false_type) {
	if(__pointer != nullptr) {
		__pointer->~_Tp();
	}
}

template <class _Tp>
inline void _Destroy(_Tp* __pointer) {
	// __type_traits will be implemented in "type_traits.h".
	// Here's the reference to SGI STL's source code.
	destroy_impl(__pointer, typename __type_traits<_Tp>::has_trivial_destructor());
}
*/

// _Destroy's first version, which received a pointer parameter.
template <class _Tp>
inline void _Destroy(_Tp* __pointer) {
	if(__pointer != nullptr) {
		__pointer->~_Tp();
	}
}

// _Destroy's second version, which received two parameters:Iterator first, Iterator last.
template <class _Tp>
inline void _Destroy(_ForwardIterator __first, _ForwardIterator __last) {}

// Old names from the HP STL.
template <class _T1, class _T2>
inline void construct(_T1* __p, const _T2& __value) {
  _Construct(__p, __value);
}

template <class _T1>
inline void construct(_T1* __p) {
  _Construct(__p);
}


__STL_END_NAMESPACE


#endif // VANILLA_SGI_STL_CONSTRUCT_H