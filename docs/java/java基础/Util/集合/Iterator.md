- 迭代器可以用于**对不同集合**进行**通用的处理**
  - 只输入一个迭代器就可以对集合元素进行一系列的操作，迭代器**统一了对集合的访问**
  - `Iterator<Pet>it`**迭代器类型**
  - `Iterable<Pet>ip`可以**产生**特定类型**迭代器**的对象

- 是一种轻量级对象，创建成本很低
- 只能向一个方向移动
- 任何实现了Iterable接口的类都可以使用for-in循环
  - 数组、Map没有实现

- 基本操作
  - 创建`集合对象.iterator()`会创建一个指向第一个元素的迭代器
  - 使用`next()`获取下一个对象
  - 使用`hasNext()`检查是否还有更多对象
  - 使用`remove()`删除迭代器最近返回的元素
``` java
List <Pet> pets = new PetCreator().list(12);
Iterator <Pet> it = pets.iterator();
while(it.hasNext()) {
    Pet p = it.next();
    System.out.print(p.id() + ":" + p + " ");
}
//删除元素
for(int i = 0; i < 6; i++) {
      it.next();
      it.remove();
    }
//更简单的遍历方式
for(Pet p : pets)
      System.out.print(p.id() + ":" + p + " ");
```

- 自定义迭代器并实现多种顺序的for-in访问
``` java
public class MultiIterableClass extends IterableClass {
  public Iterable <String> reversed() {
    return new Iterable <String>() {
        //自定义逆向迭代器
      public Iterator <String> iterator() {
        return new Iterator <String>() {
          int current = words.length - 1;
          @Override public boolean hasNext() {
            return current > -1;
          }
          @Override public String next() {
            return words [current--];
          }
          @Override
          public void remove() { // Not implemented
            throw new UnsupportedOperationException();
          }
        };
      }
    };
  }
  public Iterable <String> randomized() {
    return new Iterable <String>() {
      public Iterator <String> iterator() {
        List <String> shuffled =
          new ArrayList <>(Arrays.asList(words));
        Collections.shuffle(shuffled, new Random(47));
          //不会影响原始数组，只是影响引用的顺序
        return shuffled.iterator();
      }
    };
  }
  public static void main(String [] args) {
    MultiIterableClass mic = new MultiIterableClass();
    for(String s : mic.reversed())
      System.out.print(s + " ");
    System.out.println();
    for(String s : mic.randomized())
      System.out.print(s + " ");
    System.out.println();
    for(String s : mic)
      System.out.print(s + " ");
  }
}
```

#### ListIterator

- Iterator 的更加强大的子类型，List 类集合独有的
- 通过 `.listIterator([index])` 获取一个指向索引为 index 运算的迭代器
- 前后元素的索引 `it.nextIndex() it.previousIndex()`
- 双向移动 `.previous() .next()`
- `hasNext()`、`hasPrevious()`
- `.set(xx)` 替换访问的最后一个元素