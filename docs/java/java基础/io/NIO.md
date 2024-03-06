
- **Buffer 包含一些要写入或者刚读出的数据**。在 NIO 库中，所有数据都是用 Buffer 处理的。在读取数据时，它是直接读到 Buffer 中的；在写入数据时，也是写入到 Buffer 中的。
- **ByteBuffer 是唯一和 FileChannel 通信的类型**。在 NIO 中，所有的数据都是通过 Channel 处理的。它就像水管一样，是一个通道。数据可以从 Channel 读取到 Buffer 中，也可以从 Buffer 写入到 Channel 中。
  - `FileChannel` 是 Java NIO（New Input/Output）中的一个关键类，用于文件的读取、写入、映射和操作。它提供了一个与文件相关联的通道，并支持高效的文件处理。
  - 隧道通常绑定一个目标对象，**作为从文件读取到缓冲区、从缓冲区写入到文件的中间桥梁**
  
- 对比传统 IO：
  - NIO 基于缓冲区进行操作，数据的读写都是通过 Buffer 进行的，这使得处理速度更快。
  - NIO 可以进行**非阻塞**的读写操作。

### ByteBuffer 与 Channel

- 创建特定大小的一块字节缓冲区，放入取出数据（注意这是一个底层方法，不能放入取出对象）

- 参数
  - capacity：缓冲区能够容纳的数据元素的**最大数量**。这个容量在缓冲区创建时被设置，且不能被改变。
  - mark：可以通过 `Buffer` 类的 `mark()` 方法来设置。`mark` **保存了一个** `position` 的值，可以通过 `reset()` 方法恢复到这个 `position`。
  - position：`position` 是缓冲区中**下一个要被读写**的元素的索引。`position` 的初始值为 0。
  - limit：`limit` 是**第一个不应该被读或写的数据**的索引（读取模式下为 0）。`limit` 的值不能大于 `capacity`。

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231121132322512.png" alt="image-20231121132322512" style="zoom:50%;" />
  - 相关方法
    - **flip ()**：从**写模式切换到读模式**。调用 `flip()` 后，`position` 被设回 0，`limit` 被设置为之前的 `position` 值。
    - **clear ()**：清除缓冲区，准备重新写数据。`position` 被设回 0，`limit` 被设置为 `capacity`。
    - **rewind ()**：重置 `position` 为 0，可以重新读写缓冲区中的所有数据。
    - **reset ()**：讲 position 移动到 mark 的位置，如果 mark 还没有被设置则会抛出异常

- 创建
  - 直接指定大小 `ByteBuffer buff = ByteBuffer.allocate(BSIZE);`
  - 从数据创建 **wrap**`c.write(ByteBuffer.wrap("Some text ".getBytes()));`
  - 使用 `put` 放入数据：`buff.put(str.getBytes());` 将数据写入缓冲区的当前位置，并将**位置向前移动**。如果缓冲区的剩余空间不足以容纳新的数据，那么 `put` 方法将抛出 `BufferOverflowException` 异常。

- `fc.read(buff);` 写入到缓冲区
- `fc.write(buff);` 从缓冲区读取

- 输出缓冲区的内容 `System.out.println(buff.asCharBuffer());`
  - 直接这么输出是字节内容，没有解码

- 读写文件
  - 三种通道：可读、可写、可读写
  - 通过 `.getChannel()`**获取通道**
``` java
public class GetChannel {
  private static String name = "data.txt";
  private static final int BSIZE = 1024;
  public static void main(String [] args) {
    // Write a file:
    try(
      FileChannel fc = new FileOutputStream(name)
        .getChannel()
    ) {//通道只能和 ByteBuffer 对象交互
      fc.write(ByteBuffer
        .wrap("Some text ".getBytes()));//通过字节创建 ByteBuffer
        //通过隧道从缓冲区写入数据到文件
    } catch(IOException e) {
      throw new RuntimeException(e);
    }
    // Add to the end of the file:
    try(
      FileChannel fc = new RandomAccessFile(
        name, "rw").getChannel()
    ) {
      fc.position(fc.size()); // Move to the end
      fc.write(ByteBuffer
        .wrap("Some more".getBytes()));
    } catch(IOException e) {
      throw new RuntimeException(e);
    }
    // Read the file:
    try(
      FileChannel fc = new FileInputStream(name)
        .getChannel()
    ) {
      ByteBuffer buff = ByteBuffer.allocate(BSIZE);//创建特定大小
        //通过隧道将文件内容读取到缓冲区
      fc.read(buff);
        //设置为读模式
      buff.flip();
      //输出buffer中的读取结果
      while(buff.hasRemaining())
        System.out.write(buff.get());
    } catch(IOException e) {
      throw new RuntimeException(e);
    }
    System.out.flush();
  }
}
```

- 连接通道的内置方法
  - `transferTo` 方法将数据从**源通道传输到目标通道**。它接收三个参数：开始位置、要传输的最大字节数和目标通道。从开始位置开始，最多传输指定数量的字节到目标通道。
    - `Channelin.transferTo(0, Channelin.size(), Channelout);`
  - `transferFrom` 方法将数据从源通道传输到目标通道。它接收三个参数：源通道、开始位置和要传输的最大字节数。从源通道中读取最多指定数量的字节，并将它们写入到目标通道的开始位置。
    - `Channelout.transferFrom(Channelin, 0, Channelin.size());`

- 字符集 CharSet
  - `Charset.forName(String charsetName)` 方法获取指定字符集的 `Charset` 实例 `Charset utf8 = Charset.forName("UTF-8");`
  - 将**字符串转换为字节序列**：`ByteBuffer buffer = utf8.encode("测试文本");` 编码
  - 将**字节序列转换为字符串**：`String text = utf8.decode(buffer).toString();` 
  - 获取系统使用的字符集名称：`String encoding =System.getProperty("file.encoding");`

- 非字节数据
  - 缓冲区是对字节流的操作（不含数据类型）
  - 存储到缓冲区的数据读取出来后是不能直接使用的
  - 对于字符数据，要么在字节**放入时进行编码**，要么在从缓冲区**取出时进行解码**
``` java
String encoding =
    System.getProperty("file.encoding");
//输出时解码
System.out.println("Decoded using " +
                   encoding + ": " + Charset.forName(encoding).decode(buff));
// Encode with something that prints:
try(
    FileChannel fc = new FileOutputStream(
        "data2.txt").getChannel()
) {
    //陷入到隧道是解码
    fc.write(ByteBuffer.wrap(
        "Some text".getBytes("UTF-16BE")));
} catch(IOException e) {
    throw new RuntimeException(e);
}
// Now try reading again:
buff.clear();
try(
    FileChannel fc = new FileInputStream(
        "data2.txt").getChannel()
) {
    fc.read(buff);
} catch(IOException e) {
    throw new RuntimeException(e);
}
buff.flip();
System.out.println(buff.asCharBuffer());
```

- 存储非字符数据的更简单方法
  - `getX()` X 为类型名称
```java
// Store and read a char array:
bb.asCharBuffer().put("Howdy!");
char c;
while((c = bb.getChar()) != 0)//读取字符
    System.out.print(c + " ");
System.out.println();
bb.rewind();
// Store and read a short:
bb.asShortBuffer().put((short)471142);
System.out.println(bb.getShort());
bb.rewind();
// Store and read an int:
bb.asIntBuffer().put(99471142);
System.out.println(bb.getInt());
bb.rewind();
// Store and read a long:
bb.asLongBuffer().put(99471142);
System.out.println(bb.getLong());
bb.rewind();
// Store and read a float:
bb.asFloatBuffer().put(99471142);
System.out.println(bb.getFloat());
bb.rewind();
// Store and read a double:
bb.asDoubleBuffer().put(99471142);
System.out.println(bb.getDouble());
bb.rewind();
```

- 视图缓冲区（即某种特定基本数据类型的专用缓冲期）
  - 透过某个**特定基本类型**的视角来看底层的缓冲区
``` java
public static void main(String [] args) {
  ByteBuffer bb = ByteBuffer.allocate(BSIZE);
  //看作 Int 缓冲区
  IntBuffer ib = bb.asIntBuffer();
  // Store an array of int:
  ib.put(new int []{ 11, 42, 47, 99, 143, 811, 1016 });
  // Absolute location read and write:
  System.out.println(ib.get(3));
  ib.put(3, 1811);
  // Setting a new limit before rewinding the buffer.
  ib.flip();
  while(ib.hasRemaining()) {
      int i = ib.get();
      System.out.println(i);
  }
}
```

- 其它基本类型也有类似的方法
- 可以将同一个字节序类解析为不同类型，同样的缓冲区数据，不一样的解析方式
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231121131949514.png" alt="image-20231121131949514" style="zoom: 33%;" />

### 内存映射文件

- 处理因为太大而无法完整加载到内存的文件，可以根据地址把文件当作一个很大的数组来进行访问
```java
public class LargeMappedFiles {
  static int length = 0x8000000; // 128 MB
  public static void
  main(String [] args) throws Exception {
    try(
      RandomAccessFile tdat =
        new RandomAccessFile("test.dat", "rw")
    ) {
      MappedByteBuffer out = tdat.getChannel().map(
        FileChannel.MapMode.READ_WRITE, 0, length);
      for(int i = 0; i < length; i++)
        out.put((byte)'x');
      System.out.println("Finished writing");
      for(int i = length/2; i < length/2 + 6; i++)
        System.out.print((char)out.get(i));
    }
  }
}
```

### 文件加锁

- 对文件加锁会对文件的访问操作加上同步处理，这样**文件才能作为共享资源**，由于文件并不一定在一个 JVM 被操作（也可能被系统进程等操作），因此 Java 的文件加锁直接映射到本地操作系统，对其它进程可见
``` java
public class FileLocking {
  public static void main(String [] args) {
    try(
      FileOutputStream fos =
        new FileOutputStream("file.txt");
        //加锁
      FileLock fl = fos.getChannel().tryLock()
    ) {
        //得到了锁
      if(fl != null) {
        System.out.println("Locked File");
        TimeUnit.MILLISECONDS.sleep(100);
          //释放锁
        fl.release();
        System.out.println("Released Lock");
      }
    } catch(IOException | InterruptedException e) {
      throw new RuntimeException(e);
    }
  }
}
```

- `lock()` 是阻塞方法，一直等到获得锁，try 指示尝试一下
  - 参数 `long position, long size, bollean shared`
  - 表示锁定的开始位置及长度（锁定范围），最后表示是否是共享锁
- 部分加锁（用于文件映射及数据库等较大共用文件）
``` java
private static class LockAndModify extends Thread {
    private ByteBuffer buff;
    private int start, end;
    LockAndModify(ByteBuffer mbb, int start, int end) {
      this.start = start;
      this.end = end;
      mbb.limit(end);
      mbb.position(start);
      buff = mbb.slice();
      start();
    }
    @Override public void run() {
      try {
        // Exclusive lock with no overlap:
        FileLock fl = fc.lock(start, end, false);
        System.out.println(
          "Locked: "+ start +" to "+ end);
        // Perform modification:
        while(buff.position() < buff.limit() - 1)
          buff.put((byte)(buff.get() + 1));
        fl.release();
        System.out.println(
          "Released: " + start + " to " + end);
      } catch(IOException e) {
        throw new RuntimeException(e);
      }
    }
  }
```