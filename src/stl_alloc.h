/* 
 * Created by vanilla.
 * Just for leaning STL.
 */

#ifndef VANILLA_SGI_STL_ALLOC_H
#define VANILLA_SGI_STL_ALLOC_H

#include <cstdlib>
#include <cstdio>
#include "stl_config.h"
#include "stl_construct.h"

__STL_BEGIN_NAMESPACE
template<int __inst>
// 第一级配置器
class __malloc_alloc_template {

private:
    static void* _S_oom_malloc(size_t);
    static void* _S_oom_realloc(void*, size_t);
/*
    static void (* __malloc_alloc_oom_handler)();
*/
public:
    static void* allocate(size_t __n) {
        void *__result = malloc(__n);
        if (0 == __result) {
            __result = _S_oom_malloc(__n);
        }
        return __result;
    }
    static void deallocate(void* __p, size_t /* __n */) {
        free(__p); 
    
    static void* reallocate(void* __p, size_t /* old_sz */, size_t __new_sz) {
        void* __result = realloc(__p, __new_sz);
        if (0 == __result) {
            __result = _S_oom_realloc(__p, __new_sz);
        }
        return __result;
    }
};

template <int __inst>
void*
__malloc_alloc_template<__inst>::_S_oom_malloc(/* size_t __n */)
{
    // void __n;
    printf("calling _S_oom_malloc, out of memory.\n");
    exit(1);
}

template <int __inst>
void* __malloc_alloc_template<__inst>::_S_oom_realloc(/* void* __p, size_t __n */)
{
    // void __p;
    // void __n;
    printf("calling _S_oom_realloc, out of memory.\n");
    exit(1);
}

typedef __malloc_alloc_template<0> malloc_alloc;

template<class _Tp, class _Alloc>
class simple_alloc {

public:
    static _Tp* allocate(size_t __n)
      { return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp)); }
    static _Tp* allocate(void)
      { return (_Tp*) _Alloc::allocate(sizeof (_Tp)); }
    static void deallocate(_Tp* __p, size_t __n)
      { if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp)); }
    static void deallocate(_Tp* __p)
      { _Alloc::deallocate(__p, sizeof (_Tp)); }
};

// 令alloc为一级配置器
typedef malloc_alloc alloc;

__STL_END_NAMESPACE

#endif // VANILLA_SGI_STL_ALLOC_H