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
### 泛型