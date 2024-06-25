排序和混排

  - **sort (List\<T> list)**: 对指定列表按自然顺序进行排序。
  - **sort(List\<T> list, Comparator\<? super T> c)**: 根据提供的比较器对列表进行排序。
``` java
Comparator <Person> ageComparator = new Comparator <Person>() {
    @Override
    public int compare(Person p1, Person p2) {
        return Integer.compare(p1.getAge(), p2.getAge());
    }
};
```

- **shuffle(List\<?> list)**: 随机打乱指定列表中元素的顺序。
- **shuffle(List\<?> list, Random rnd)**: 使用指定的随机源随机打乱列表。

- 查找和替换
  - **binarySearch(List\<? extends Comparable\<? super T>> list, T key)**: 使用二分查找算法在有序列表中查找指定对象。
  - **binarySearch(List\<? extends T> list, T key, Comparator\<? super T> c)**: 使用比较器进行二分查找。
  - **max(Collection\<? extends T> coll)**: 返回给定集合的最大元素。
  - **min(Collection\<? extends T> coll)**: 返回给定集合的最小元素。
  - **replaceAll(List\<T> list, T oldVal, T newVal)**: 替换列表中所有出现的指定值。
  - **`frequency(Collection, Object x)`**返回和x等价的元素数目

- 反转和旋转
  - **reverse(List\<?> list)**: 反转指定列表中元素的顺序。
  - **rotate(List\<?> list, int distance)**: 将列表中的元素旋转指定的距离。

- 集合的视图和包装
  - **unmodifiableCollection(Collection\<? extends T> c)**: 返回指定集合的不可修改视图。
  - **synchronizedCollection(Collection\<T> c)**: 返回指定集合的线程安全视图。
  - **singleton(T o)**: 返回只包含指定对象的不可变集合。
  - **emptyList()**, **emptySet()**, **emptyMap()**: 返回空的不可变列表、集合或映射。

- 复制和填充
  - **copy(List\<? super T> dest, List\<? extends T> src)**: 将所有元素从一个列表复制到另一个列表。
  - **fill(List\<? super T> list, T obj)**: 使用指定元素替换列表中的所有元素。只能用于 list 但是生成的列表可以用于构造器或 addAll
    - 只能替换已有的元素不能添加新元素
  - **`Collections.nCopies(n,item)`**创建具有相同元素的list

- 添加和移除
  - **addAll(Collection\<? super T> c, T... elements)**: 将所有指定元素添加到指定集合。
  - **disjoint(Collection\<?> c1, Collection\<?> c2)**: 如果两个指定集合没有共同的元素，则返回 true。
  - `removeIf(s->xx)`填入一个表达式，删除满足条件的元素