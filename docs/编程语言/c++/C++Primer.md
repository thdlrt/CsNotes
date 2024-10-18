## 基础&杂项
- 只有全局变量才会进行默认初始化，局部变量未初始化的值为未定义的
- 声明使得名字为程序所知。定义负责创建与名字关联的实体；声明规定了变量类型和名字。定义申请存储空间，也可能为变量赋初值。
- const 变量默认是**文件作用域**的，不同文件的同名变量相互独立
	- 要想在多个文件中使用 const 变量共享，定义和声明都加 extern 关键字即可
```cpp
//file_1.cc定义初始化常量，能被其它文件访问
extern const  int bufSize = fcn();
//file_1.h 头文件
extern const  int bufSize ;//与file_1.cc中定义的bufSize是同一个
```
- 将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量的表达式。
	- `constexpr int mf=20;`
- 设定类型别名
	- 传统别名：使用**typedef**来定义类型的同义词
	- 新标准别名：`using SI = Sales_item;`
- 从表达式的类型推断出要定义的变量的类型。
	- `decltype(f()) sum = x;` 推断 `sum` 的类型是函数 `f` 的返回类型。
```cpp
//指针数组
int*ptrs[10];
//数组指针
int(*ptrs)[10];
```
- `decltype(*p)` 的结果是int&(**左值是引用**)
- 可变形参 `initializer_list<T> lst` 得到一个相同类型数据组成的 vector
```cpp
void err_msg(ErrCode e, initializer_list<string> il){
    cout << e.msg << endl;
    for (auto bed = il.begin(); beg != il.end(); ++ beg)
        cout << *beg << " ";
    cout << endl;
}
err_msg(ErrCode(0), {"functionX", "okay"});
```
- 在变量声明中加mutable关键字,即使在一个const成员函数内也可以修改类的某个数据成员
```cpp
class Screen{
public:
    void som_member() const;
private:
    mutable size_t access_ctr;
};
void Screen::some_member() const{
    ++access_ctr;
}
```
- 类在**声明后定义前**是一个**不完全类型**。
	- 可以定义指向这种类型的指针或引用
	- 可以**声明**（不能定义）不完全类型作为参数或返回类型的函数。
- 如果构造函数**只接受一个实参**，则它实际上定义了转换为此类类型的**隐式转换机制**。
	- 编译器只会自动地执行**仅一步**类型转换。
	-  explicit 只对一个实参的构造函数有效，用于禁止自动隐式转换
	- `explicit Sales_data(std::istream);`
- 在类**外部**定义静态成员时**不能重复 static 关键字**，该关键字只出现在类内部的声明语句
- 不能在类内部初始化静态成员，必须在**类外部定义和初始化每个静态成员**（const、constexpr 类型可以类内初始化）
- 刷新缓冲区的几种方式
	- ends 附加空字符
	- endl 附加换行
	- flush 不附加
### 标准库
- 利用插入迭代器添加元素 `fill_n(back_inserter(vec),10,0);` 添加 10 个 0 到末尾
- 常见的三迭代器算法（begin 1, end 1, begin 2）
	- copy
	- equal
- 希望改变被 lambda 捕获的值，则添加 mutable 关键字
	- `auto f = [v1] () mutable { return ++v1; };`

- `bind` 用于将函数或函数对象与一组参数绑定，生成一个具有部分参数的可调用对象
```cpp
#include <iostream>
#include <functional>

void print_sum(int a, int b) {
    std::cout << "Sum: " << a + b << std::endl;
}

int main() {
    // 使用 std::bind 将第一个参数固定为 10
    auto bound_func = std::bind(print_sum, 10, std::placeholders::_1);
    // 调用 bound_func 时只需要提供第二个参数
    bound_func(20);  // 输出: Sum: 30
    return 0;
}
//_n表示待定参数的位置
```
- 可以作为一个函数对象传递，有时可以替代 lambda 表达式
 ```cpp
 //使用bind可将原来lambda的find_if
 auto wc = find_if(words.begin(),words.end(),[sz](const string& a));
 //替换为
 auto wc = find_if(words.begin(),words.end(),bind(check_size,_1,sz));
 ```
- 用占位符实现颠倒参数`bind (isShorter,_2,_1)`

- ref 生成一个**可以传递的引用类型**，可以用于创建引用类型的容器
	- `std::reference_wrapper<T> std::ref(T& t);`
	- `std::vector<std::reference_wrapper<int>> vec = {std::ref(a), std::ref(b), std::ref(c)};`

- 创建动态数组时进行初始化 `new int[10](); ` 即额外加一组小括号
### 智能指针
- 创建一个只能指针 `make_shared<T>(args)`
- `shared_ptr ` 的构造函数可以传入指针、`unique_ptr` 、`shared_ptr`
- 获取共享对象的指针数量 `p.use_count()`；获取指针 `.get()`
- 指向新对象 `p.reset(new int(1024)); `

- `unique_ptr `：`release` 放弃对指针的控制权，返回指针并置空；`reset` 释放指向的对象；`reset(q)` 令指向 q 指向的对象 

- `weak_ptr`：用一个 `shared_ptr` 来初始化， 一旦最后一个指向对象的 shared_ptr 被销毁，对象就会被释放。
	- `use_count` 获取与其共享的 share_ptr 的数量
	- `expired` 若use_count () 为 0，返回 true，否则返回 false 
	- `lock` 如果expired为true，则返回一个空shared_ptr；否则返回一个指向w的对象的shared_ptr。（weak_ptr 不能直接访问对象，不许使用 lock）
### OOP
- 禁止拷贝&赋值：可以将拷贝构造函数和拷贝赋值函数定义为删除的函数来阻止使用，如 `NoCopy &operator=(const NoCopy&) = delete;`
	- 删除了析构函数的类只能动态创建而且不能被释放
- 如果一个类**有数据成员**不能默认构造、拷贝、复制或销毁则**对应的成员函数**将被定义为删除的。
	- 比如 const、引用对象、IO 类等就不能拷贝
- 移动 `move`：使一个左值可以被当做右值进行右值引用 `int &&rr3 = std::move(rr1); `
	- 同时承诺之后将不再使用它
	- 在移动操作之后，移后源对象必须保持有效的、可析构的状态，但是用户不能对其值进行任何假设。
- 通过 `noexcept` 关键字可以表示函数不会抛出异常：如 `StrVec::StrVec(StrVec &&s) noexcept : {}`
	- 声明可以提高性能
	- 除非 vector 知道元素类型的移动构造函数**不会抛出异常**，否则在重新分配内存的过程中，它就必须使用拷贝构造函数而不是移动构造函数。
- 成员函数也可以定义右值引用版本来进行优化
- 重载类型转换（转化为其他类型）：`operator int() const { return val; }`
	- 添加 `explicit` 可以禁止隐式自动转换

- 虚函数的默认实参：如果某次函数调用使用了默认实参，则该实参值由本次调用的**静态类型**决定。（即使是通过指针动态调用**也是使用基类的默认参数**）
- 指明执行特定版本的虚函数 `baseP->Quote::net_price(42);`

- 改变基类成员的可访问性
```C++
class Base {
public:
    std::size_t size() const { return n; }
protected:
    std::size_t n;
};
class Derived : private Base {    //  note: private inheritance
public:
    //改变可见性
    using Base::size;
protected:
    using Base::n;
};
```

### 泛型
- 可以定义模版类型别名
```c++
template<typename T> using twin = pair<T, T>;
twin<string> authors;
```

- **相同模版类型**的模版类共享静态成员
- 静态成员的类外初始化
```c++
template <typename T> int MyClass<T>::staticVar = 0;
```

- 返回类型
```c++
template <typename T>
typename T::value_type top(const T& c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}
```

- 类模板的成员模板函数
```c++
template <typename T> class Blob {
    template <typename It> Blob(It b, It e);
    // ...
};

template <typename T>     // type parameter for the class
template <typename It>    // type parameter for the constructor
    Blob<T>::Blob(It b, It e):
              data(std::make_shared<std::vector<T>>(b, e)) {
}
```

- 显示实例化：明确是否生成一个模板的实例而不依赖编译器自动生成
	- 生成模板实例的代码 `template class MyClass<int>;  // 生成 MyClass<int> 的实例`
	- 声明模板实例已在其他地方生成，不在当前翻译单元中生成实例 `extern template class MyClass<int>;  // 不生成 MyClass<int> 实例`
	- 显式实例化常用于大型项目中，帮助优化编译和管理模板代码。

- 自定义返回类型
```C++
template <typename It>
auto fcn(It beg, It end) -> decltype(*beg)
{
// process the range
return *beg; // return a reference to an element from the range 
}
```

- 当一个函数参数是一个右值引用（形如 T&&）时，如果**传递一个左值对象(如 int)** 此时有 `int&` ，为 ` int& && ` 即双重引用
-  双重引用会进行**引用折叠**成一个普通引用，除了右值引用的右值引用 `X&& &&` 为右值引用外**均会被折叠为左值引用**
	- 这也就是说可以传递任意类型的数据给 `T&`（传入左值时会通过引用折叠转化为左值引用） 

- `move` 函数工作原理
```C++
template <typename T>
typename remove_reference<T>::type&& move(T&& t)
{
   // static_cast covered in § 4.11.3 
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```
- 通过引用折叠使得 move 既可以接受一个左值也可以接受一个右值
- 传递一个右值时，推断出 T 为非引用，即 `T&&` 为右值引用
	- remove_reference\<string>的 type 成员是 string。move 的返回类型是 string\&\&
- 传递一个左值时，推断出 T 为 `string&`， remove_reference<string&>的type成员是string，move的返回类型仍是string&&。
	- 折叠后的 t 为 string&类型，转化后为 string&&
	- **可以用 static_cast 显式地将一个左值转换为一个右值引用。**

- 参数转发：将函数的一个或多个实参连同类型不变的转发给其他函数
	- 用于解决**传递引用类型参数**的问题
	- 引用折叠可以保持原始实参的引用类型
```C++
template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}
```
- 传入左值引用类型参数后，T1 就是一个 int&类型的
- 如果一个函数参数是指向模板类型参数的右值引用（如 T&&），它对应的实参的 const 属性和左值/右值属性将得到保持。
- 此外还需要 `std::forward` 转发，因为无论参数原本是左值还是右值，因为在函数体中，函数参数本身总是左值。
```C++
#include <iostream>
#include <utility>  // std::forward

void g(int&& x) {
    std::cout << "g(int&&): " << x << std::endl;
}

void g(int& x) {
    std::cout << "g(int&): " << x << std::endl;
}

template <typename T>
void caller(T&& t) {
    g(std::forward<T>(t));  // 使用 forward 来转发参数
}

int main() {
    int a = 10;
    
    caller(a);      // 调用时传入左值
    caller(20);     // 调用时传入右值
}

```

- 模版方法与非模版方法也可以重载
	- 如果参数匹配同样好的函数中只有一个是非模板函数，则选择此函数。

- 可变参数模板
	- 可变数目的参数称为参数包：**模板参数包**表示零个或多个模板参数；**函数参数包**表示零个或多个函数参数
- 一般模版参数可变同时也有函数参数可变
```C++
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);
int i = 0; double d = 3.14; string s = "how now brown cow";
foo(i, s, 42, d);
//实例化为
void foo(const int&, const string&, const int&, double&);
```
- 可变参数函数通常递归调用，每次处理包中的第一个实参，然后用剩余的参数递归调用
	- 注意要有非可变参数版本作为停止条件，否则会无限递归
```C++
template<typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t;
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";
    return print(os, rest...);
}
```

- 包扩展：直接展开可变参数，**对每个参数应用特定的操作**，形成一组独立的结果。
	- 

- 模版特例化