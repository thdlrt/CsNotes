- 定义变量 `let title: string = 'xxx'`
- 常用数据类型：`string`、`number` 、`boolean`
	- 数组 `let arr: stringg[] = ['小红', ...]`
		- 长的 `.length`
		- 增加 `.push(,...)` 向数组末尾添加元素；`.unshift(,...)` 向数组首提那家元素
		- 删除 `pop()`，`shift()`
		- 修改 `.splice(开始位置，删除个数，新增...)`
	- 联合类型，一个变量可以存储不同类型的数据 `let judge: number|string = 100`
	- 限定具体的可选数据范围 `let gender: 'man' | 'woman' | 'secret'`
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