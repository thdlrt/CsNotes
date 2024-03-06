START
问答题
正面: sort基本用法
背面: - `sort`：对数组进行排序。
  - 要求被排序对现象实现Comparable接口（含compareTo）
``` java
@Override public int compareTo(CompType rv) {
    return (i < rv.i ? -1 : (i == rv.i ? 0 : 1));
  }
```
- 颠倒排序`Arrays.sort(arr,Collections.reverseOrder())`
- 也可以传入自定义的Comparator
``` java
class CompTypeComparator
implements Comparator <CompType> {
  public int compare(CompType o1, CompType o2) {
    return (o1.j < o2.j ? -1 : (o1.j == o2.j ? 0 : 1));
  }
}
Arrays.sort(a, new CompTypeComparator());
```
<!--ID: 1709657368576-->
END