# 空间配置器

在STL中，allocator隐藏在一切container的背后，整个STL的操作对象都存放在容器之内，而容器一定需要配置空间以放置资料。所以在理解整个STL设计实现的过程中，第一步先需要了解配置器。



# 具备次配能力(sub-allocation)的SGI空间配置器

SGI STL配置器的名称是alloc而非allocator，而且不接受任何参数。

不可以采用标准写法：

```c++
vector<int, std::allocator<int>> iv;
```

而必须这样写：

```c++
vector<int, std::alloc> iv;
```

SGI STL中的每个container都指定了缺省的空间配置器alloc，如vector中声明：

```c++
template <class T, class Alloc = alloc> // 缺省使用alloc为分配器
class vector { ... };
```



## SGI标准的空间配置器，std::allocator

SGI STL中也有符合标准，名称为allocator的配置器，但是其仅仅是对`::operator new`和`::operator::delete`做了一层封装，效率不佳。所以SGI中从未使用过它，也不建议使用。

## SGI特殊的空间配置器，std::alloc







