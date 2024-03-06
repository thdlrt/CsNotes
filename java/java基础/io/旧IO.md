#### InputStream

- 面向 **字节** 的 IO
- ByteArrayInputStream：将内存缓冲区充当InputStream
- StringBufferInputStream：将字符串转化为InputStream
- FileInputStream：从文件读取信息
- PipedInputStream：生成写入到对应PipedOutStream的数据，实现管道传输
- SequenceInputStream：将两个以上的InputStream转化为单个InputStream
- FilterInputStream：作为**装饰器**接口抽象类，为其他InputStream提供功能
  - DataInputStream：从流读取**基本类型**，有方法如readFloat()等
  - Buffered-InputStream：声明使用**缓冲区**（提高效率）

#### OutputStream

- ByteArrayOutputStream：在内存创建一块缓冲区，发送到流的数据被存储在缓冲区
- FileOutStream：用于向文件发送信息
- PipedOutStream：向其中写入的任何信息作为PipedInputStream的输入（双向管道传输）
- FilterOutStream：装饰器
  - DataOutputStream：writeFloat等
  - PrintStream：生成格式化输出，即用于处理数据的显示
  - BufferedOutStream：声明使用缓冲区

#### Reader和Writer

- Input/OutStream类提出了**面向字节**的IO能力，ReadWrite提供了**兼容Unicode并且兼容字符的IO能力**
- 适配器InputStreamReader和OutputStreamWriter可以将Input/OutputStream转化为Reader/Writer
  - 都有对应的，后缀为R/W

#### Scanning

- 用于扫描和解析文本数据
- 可以用不同的输入源来创建 `Scanner` 对象`Scanner scanner = new Scanner(System.in); // 从标准输入读取`
- `Scanner` 类提供了一系列的方法来读取不同类型的数据，如 `nextInt()`, `nextDouble()`, `nextLine()`,`hasNext()` 等。
```java
int number = scanner.nextInt();
String str = scanner.nextLine();
```
- 关闭`scanner.close();`
#### RandomAccessFile

- 用于处理由大小已知的记录组成的文件，可以通过seek()在各条记录上来回移动，并读取或修改记录

### 典型用法

- 从文件输入
``` java
public static String read(String filename) {
    try(BufferedReader in = new BufferedReader(
        new FileReader(filename))) {
        return in.lines()
            .collect(Collectors.joining("\n"));
    } catch(IOException e) {
        throw new RuntimeException(e);
    }
}
```
- try-with-resource
- 通过装饰器创建的带有缓冲区的文件读取 `BufferedReader in = new BufferedReader(new FileReader(filename))`

``` java
public static void main(String [] args) throws IOException {
    StringReader in = new StringReader(BufferedInputFile.read("MemoryInput.java"));
    int c;
    while((c = in.read()) != -1)
        System.out.print((char)c);
}
```
- 按照字符读取

- 读取为基本数据类型
``` java
public static void main(String [] args) {
    try(
        //复原为字节流再用 DatInputStream 重新进行读取
        DataInputStream in = new DataInputStream(
            new ByteArrayInputStream(
                BufferedInputFile.read(
                    "FormattedMemoryInput.java")
                .getBytes()))
    ) {
        while(true)
            System.out.write((char)in.readByte());
    } catch(EOFException e) {
        System.out.println("\nEnd of stream");
    } catch(IOException e) {
        throw new RuntimeException(e);
    }
}
```
- 格式化读取
- 使用 `in.available!=0` 判断字符读取是否终止，当然也可以使用异常进行控制

- 文件输出
``` java
public static void main(String [] args) {
    try(
        BufferedReader in = new BufferedReader(
            new StringReader(
                BufferedInputFile.read(
                    "BasicFileOutput.java")));
        PrintWriter out = new PrintWriter(
            new BufferedWriter(new FileWriter(file)))
    ) {
        //逐行写入
        in.lines().forEach(out:: println);
    } catch(IOException e) {
        throw new RuntimeException(e);
    }
    // Show the stored file:
    System.out.println(BufferedInputFile.read(file));
}
```

- 存储和恢复恢复数据
  - 使用DataOutputStream写入数据，一定可以通过DataInputStream精确的恢复数据
``` java
public static void main(String [] args) {
    try(
        DataOutputStream out = new DataOutputStream(
            new BufferedOutputStream(
                new FileOutputStream("Data.txt")))
    ) {
        out.writeDouble(3.14159);
        out.writeUTF("That was pi");
        out.writeDouble(1.41413);
        out.writeUTF("Square root of 2");
    } catch(IOException e) {
        throw new RuntimeException(e);
    }
    try(
        DataInputStream in = new DataInputStream(
            new BufferedInputStream(
                new FileInputStream("Data.txt")))
    ) {
        System.out.println(in.readDouble());
        // Only readUTF() will recover the
        // Java-UTF String properly:
        System.out.println(in.readUTF());
        System.out.println(in.readDouble());
        System.out.println(in.readUTF());
    } catch(IOException e) {
        throw new RuntimeException(e);
    }
}
```

- 随机访问文件
  - 可以使用DataInputStream相似的接口进行数据读取写入
``` java
public class UsingRandomAccessFile {
    static String file = "rtest.dat";
    public static void display() {
        try(
            RandomAccessFile rf =
            new RandomAccessFile(file, "r")//有访问控制方法
        ) {
            for(int i = 0; i < 7; i++)
                System.out.println(
                "Value " + i + ": " + rf.readDouble());
            System.out.println(rf.readUTF());
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
    public static void main(String [] args) {
        try(//独立使用，不支持使用装饰器
            RandomAccessFile rf =
            new RandomAccessFile(file, "rw")
        ) {
            for(int i = 0; i < 7; i++)
                rf.writeDouble(i*1.414);
            rf.writeUTF("The end of the file");
            rf.close();
            display();//顺序读取
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
        try(
            RandomAccessFile rf =
            new RandomAccessFile(file, "rw")
        ) {
            rf.seek(5*8);
            rf.writeDouble(47.0001);//一个元素为 8 字节，就是对第 5 个元素进行修改
            rf.close();
            display();
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
}
```
