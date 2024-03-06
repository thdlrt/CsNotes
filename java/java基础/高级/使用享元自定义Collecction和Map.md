- 享元模式：**共享对象**，用于减少应用程序创建的对象数量，以减少内存占用和提高性能。

- 创建一个只读数组
``` java
public class CountingIntegerList
extends AbstractList <Integer> {
  private int size;
  public CountingIntegerList() { size = 0; }
  public CountingIntegerList(int size) {
    this.size = size < 0 ? 0 : size;
  }
    //重写 get 及 set
    //并没有实际存储 list，取值时再计算，可以创建无限大的数据集
  @Override public Integer get(int index) {
    return index;
  }
  @Override public int size() { return size; }
  public static void main(String [] args) {
    List <Integer> cil =
      new CountingIntegerList(30);
    System.out.println(cil);
    System.out.println(cil.get(500));
  }
}
```

- 实现Map享元
``` java
public class CountMap
extends AbstractMap <Integer,String> {
  private int size;
  private static char [] chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
    //自动计算 value
  private static String value(int key) {
    return
      chars [key % chars.length] +
      Integer.toString(key / chars.length);
  }
  public CountMap(int size) {
    this.size = size < 0 ? 0 : size;
  }
  @Override public String get(Object key) {
    return value((Integer)key);
  }
  private static class Entry
  implements Map.Entry <Integer,String> {
    int index;
    Entry(int index) { this.index = index; }
    @Override   public boolean equals(Object o) {
      return o instanceof Entry &&
        Objects.equals(index, ((Entry)o).index);
    }
    @Override public Integer getKey() { return index; }
    @Override public String getValue() {
      return value(index);
    }
    @Override public String setValue(String value) {
      throw new UnsupportedOperationException();
    }
    @Override public int hashCode() {
      return Objects.hashCode(index);
    }
  }
  @Override
  public Set <Map.Entry<Integer,String> > entrySet() {
    // LinkedHashSet retains initialization order:
    return IntStream.range(0, size)
      .mapToObj(Entry:: new)
      .collect(Collectors
        .toCollection(LinkedHashSet:: new));
  }

```
