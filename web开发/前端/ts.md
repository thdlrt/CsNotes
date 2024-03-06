### 强数据类型

- `let num:number=0`在变量后面使用:加类型进行声明

  - ```typescript
    sum(x:number,y:number):number{
        return x+y;
    }
    ```

#### interface接口

- 对象的类型声明

  - interface描述了对象应该具有的属性和方法（接口），但并不提供实现细节。

  - ```ts
    interface Person {//声明类型
      name: string;
      age: number;
      greet(): void;
    }
    
    const person: Person = {//声明具体的数值（直接把接口看作一种数据类型）
      name: "John",
      age: 30,
      greet() {
        console.log(`Hello, my name is ${this.name} and I'm ${this.age} years old.`);
      }
    };
    
    ```

- 与类的关系

  - 接口（interface）：

    - 用于描述对象的结构和类型，定义了对象应该具有的属性和方法，但没有具体的实现。
    - 接口可以被**多个**类实现，一个类可以实现**多个**接口。
    - 接口可以用于类型检查和约束，确保对象符合特定的结构和行为要求。
    - 接口不会被编译为 JavaScript 代码，它仅存在于 TypeScript 的类型系统中。

  - 类（class）：

    - 用于创建对象的模板，可以定义对象的属性、方法和行为。
    - 类可以实例化为具体的对象，通过 `new` 关键字进行创建。
    - 类可以拥有构造函数、实例方法、静态方法、属性等。
    - 类可以继承其他类，并添加自己的属性和方法。
    - 类的实例化对象可以被直接使用和操作。

  - 将类关联到接口（约束）

    - 使用`implement`关键字

    - ```
      interface Animal {
          name: string;
          sound(): void;
      }
      
      class Dog implements Animal {
          name: string;
      
          constructor(name: string) {
              this.name = name;
          }
      
          sound(): void {
              console.log("Woof!");
          }
      }
      ```

  - 使用接口
    - 直接使用实例化的对象来使用（接口只是一种规范（类型））

