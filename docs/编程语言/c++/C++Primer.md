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