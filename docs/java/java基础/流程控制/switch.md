- 枚举类型可以直接作为case标签

- switch箭头语法：(JDK14) ^7ad22e
``` java
//传统方式
case 1: xxx;
    break;
//箭头语法
case 1-> xxx;
```

- cases null检查（JDK17）
  - 可以在switch内部检查是否为null
  - default并不会处理null的情况，会抛出Null异常
  - 这不是强制要求的

- switch作为表达式（JDK14）
  - 使用`yield`返回结果，不需要（也不能）使用break；
  - 使用箭头表达式并且只有一个语句时可以省略yield
  - 不止有一个语句时用花括号
``` java
static int colon(String s) {
    var result = switch(s) {
      case "i": yield 1;
      case "j": yield 2;
      case "k": yield 3;
      default:  yield 0;
    };
    return result;
  }
  static int arrow(String s) {
    var result = switch(s) {
      case "i" -> 1;
      case "j" -> 2;
      case "k" -> 3;
      default  -> 0;
    };
    return result;
  }
```
