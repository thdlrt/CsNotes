### equals()与hashCode()

#### equals()

- 使用哈希集合需要自定义 `equals()` 和 `hashCode()`
	- 作为 set 和 map 键的类必须定义

- Object默认的equals：
  - **比较引用**，只有是同一个对象才返回true
  - 包装数据类型默认比较值而不是引用

- equals应该有的性质：自反性、对称性、传递性、一致性，与null比较应该返回flase

- Objects提供了一些使用方法
  - `Objects.equals(obj1, obj2);`对**null安全的比较**
    - 首先检查两个对象引用是否相同
    - 然后检查其中一个对象是否为`null`
    - 最后使用`equals`方法比较两个对象
  - `Objects.hashCode(obj);`

- 经典的比较
``` java
@Override public boolean equals(Object rval) {
    //既确保不为 null，也确保类型相同
    return rval instanceof SuccinctEquality &&
        Objects.equals(i, ((SuccinctEquality)rval).i) &&
        Objects.equals(s, ((SuccinctEquality)rval).s) &&
        Objects.equals(d, ((SuccinctEquality)rval).d);
}
```

- 有继承的比较
``` java
@Override public boolean equals(Object rval) {
    return rval instanceof ComposedEquality &&
      super.equals(rval) &&//先比较基类
      Objects.equals(part,999
        ((ComposedEquality)rval).part);
  }
```

#### hashCode()

- 重写原则：
  - 一致性：如果在应用的执行过程中一个对象的等价信息没有被修改，那么对这个对象调用 `hashCode()` 方法**多次应该始终返回相同的值**。
  - 高效率，均匀分布
  - 等价对等：如果两个对象通过 `equals()` 方法比较是相等的，那么这两个对象的 `hashCode()` 方法必须产生相同的整数结果。