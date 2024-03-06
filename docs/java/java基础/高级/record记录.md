

- 作为数据传输对象
- 使用record关键字时编译器会自动生成：
  - **不可变字段**
  - 规范构造器
  - 每个元素都有的访问器方法
  - equals()
  - hashCode()
  - toString()

- 创建
``` java
recoed Employee(String name, int id){}
var bob = new Employee("",0);
```
- 会**自动创建规范的构造器**根据传入的参数进行初始化，recoed的字段要定义在头部
- 不能加入静态方法、字段和初始化器
- record内的方法只能读取字段，不能进行修改，定义在{}内
- record不能继承其他类，但是可以实现接口

``` java
interface Strar{
    double brightness();
    double density();
}

record RedDwarf(double brightness) implement Star{
    @Override public double density(){return 100.0;}
}
//record 会自动为 brightness 提供访问器，正好匹配了接口的要求
```
- 可以嵌套在类或方法中，并且隐含都是静态的
- 可以自定义一个紧凑构造器（没有参数列表）

``` java
Redwarf {
    //可以修改字段的初始化值(这不是对 final 继续进行修改，而是在对 final 进行初始化前对初始化值进行修改)
    //也可以对参数进行验证
}
```
- 如果想要使用带参构造器，构造器必须静秋额复制record的签名（括号内完全一致）并且必须在函数体中对字段进行初始化