START
问答题
正面: StringBuffer与StringBuilder区别
背面: - `StringBuilder` 类是在 Java 5 引入的，它**不是线程安全**的，而 `StringBuffer` 类存在于 Java 的早期版本中，它是线程安全的。
- 因此在单线程环境下，`StringBuilder` 比 `StringBuffer` 拥有更好的性能。
<!--ID: 1709657368571-->
END