- 定义变量 `let title: string = 'xxx'`
- 常用数据类型：`string`、`number` 、`boolean`
	- 数组 `let arr: stringg[] = ['小红', ...]`
		- 长的 `.length`
		- 增加 `.push(,...)` 向数组末尾添加元素；`.unshift(,...)` 向数组首提那家元素
		- 删除 `pop()`，`shift()`
		- 修改 `.splice(开始位置，删除个数，新增...)`
		- 遍历数组 `for(let item of names)`
	- 联合类型，一个变量可以存储不同类型的数据 `let judge: number|string = 100`
	- 限定具体的可选数据范围 `let gender: 'man' | 'woman' | 'secret'`
	- 允许为空 `name?: string`
	- 静态 `static`
- 遍历数组
```ts
forEach(items, (item: string, index)) => {

}
```
- 类型转换
	- 字符串转数字 `Number(str)`
	- `preseInt()` 转换为整数，失败返回 NaN
	- `pareseFloat()`
	- 转字符串 `toString()`，`toFixed(x)` 保留 x 位小数
- 模板字符串 
```ts
console.log('简介信息', `姓名是${name},今年${age}岁了`)
console.log('简介信息', '姓名是' + name + ',今年' + age + '岁了')
```
- 枚举类型
```ts
enum ThemeColor {
    Red = '#ff0f29',
    Orange = '#ff7100',
    Green = '#30b30e'
}
let color: ThemeColor = ThemeColor.Red
```
- 局部变量 `let`，常量 `const`
- 输出 `console.log(,...)`
- 函数
```ts
function fn(a: number){

}
fn(x)
```
- lambda `()=>{}`
	- 可以 `let fn = () => {}`
- 接口与实现接口的对象
```ts
interface Person{
    name: string
    age: number
    dance: () => void
    sing: (song: string) => void
}
let person: Person = {
	name: 'xx',
	age: 18,
	dance: () => {
 console.log()
 },
 sing: (song: string) => {
 console.log()
 }
}
//一次性
let person: { name: string, age: number } = {
  name: 'Alice',
  age: 30
};
```
- 类
```ts
// 类名 首字母大写（规范）
class 类名{
    // 1. 实例属性(字段)
    字段A:类型
    字段B:类型
    // 2. 构造函数
    constructor(参数...) {
        // 通过 new 实例化的时候 会调用 constructor
        // 通过关键字 this 可以获取到实例对象
        this.字段名A = 参数
    }
    // 3. 方法
}
// 使用类 实例化对象 基于类 创建对象
const p:类名 = new 类名()
```
- 权限修饰符 `readonly、private、protected 和 public`
- 继承
```ts
class 子类 extends 父类 {
    constructor() {
        super() // 调用父类构造函数
    }
    方法(){
        super.方法() // 调用父类方法
    }
}
```
- 实现接口
```ts
class 类 implements 接口{
// 必须实现 接口中定义的 属性、方法，
// 否则会报错
}
```
- 泛型
```ts
function 函数名<Type>(temp:Type):Type{
    return temp
}
fn<string>('123')
//带约束的泛型
function 函数<Type extends 接口>(){}
```