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