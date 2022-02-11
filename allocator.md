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

一般来说，我们习惯的C++内存申请/释放操作通常是这样：

```c++
class Foo { ... };
Foo* pf = new Foo;	// 分配内存，然后构造对象
delete pf;			// 析构对象，然后释放内存
```

其中的new包括了两个阶段：

1. 调用::operator new分配内存
2. 调用Foo::Foo()构造对象

同理，delete也包括两个阶段：

1. 调用Foo::~Foo()析构对象
2. 调用::operator delete释放内存

在STL中，内存分配由alloc::allocate()负责，内存释放由alloc::deallocate()负责；对象构造由::construct()负责，对象析构由::destroy()负责。

具体的分布见下图：

![alloc](./pics/alloc.png)



## 构造与析构

在上一小节中可以看到，对象的构造与析构由stl_construct.h负责，其中定义了全局函数construct()与destroy()。

