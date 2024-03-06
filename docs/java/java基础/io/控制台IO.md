### 控制台输入输出

- 绑定字符流到控制台 `BufferedReader br = new BufferedReader(new InputStreamReader(System.in));`
  - 可以使用 read () 方法从控制台读取一个字符，或者用 readLine () 方法读取一个字符串。

- 使用 [[旧IO#Scanning|Scanning]] 获取更强大更强大 (格式化)的输出

- Console
  - 封装好的控制台类，支持更加方便的功能
```java
public class Password {
    
    public static void main (String args[]) throws IOException {
		//获取控制台对象
        Console c = System.console();
        if (c == null) {
            System.err.println("No console.");
            System.exit(1);
        }

        String login = c.readLine("Enter your login: ");
        //读取密码模式
        char [] oldPassword = c.readPassword("Enter your old password: ");
        ...
    }
}
```

### 标准 IO

- 输出 `System.out.println(...);`
  - 也可以格式化输出 `System.out.printf("%d==%d %b%n",x,y,x==y)`

- 所有的输入都可以来自标准输入，所有的输出都可以发送到标准输出，可以将多个程序串联起来
- System. In System. Out System. Err
  - Out\err 被包装成了 PrintStream，但是 in 是为包装的 InputStream，要在读取之前进行手动包装
- System. In 的包装和使用
``` java
public static void main(String [] args) {
    TimedAbort abort = new TimedAbort(2);
    new BufferedReader(
        new InputStreamReader(System.in))
        .lines()
        .peek(ln -> abort.restart())
        .forEach(System.out:: println);
    // Ctrl-Z or two seconds inactivity
    // terminates the program
}
```

- 流是懒加载的，并且会随着输入自动变化（如 lines 获取到更多的行）
- 如果在 2 秒内没有新的输入，那么程序就会被终止。

- 将 System. Out 作为 PrintWriter
``` java
public static void main(String [] args) {
    PrintWriter out =
        new PrintWriter(System.out, true);//第二个参数 autoFlush
    out.println("Hello, world");
}//即将输出定向到标准输出
```
- 清空缓冲区 `System.out.flush();`

- 重定向
  - `SetIn(InputStream)`、`SetOut(PrintStream)`、`SetErr(PrintStream)`
``` java
public static void main(String [] args) {
    PrintStream console = System.out;//缓存默认控制台输出对象用于后面进行恢复
    try(
      BufferedInputStream in = new BufferedInputStream(
        new FileInputStream("Redirecting.java"));
      PrintStream out = new PrintStream(
        new BufferedOutputStream(
          new FileOutputStream("Redirecting.txt")))
    ) {
      System.setIn(in);//重定向为文件读取文件输出
      System.setOut(out);
      System.setErr(out);
      new BufferedReader(
        new InputStreamReader(System.in))
        .lines()
        .forEach(System.out:: println);
    } catch(IOException e) {
      throw new RuntimeException(e);
    } finally {
      System.setOut(console);
    }
  }
```

- 进程控制
  - 通过标准流实现**向控制台发送命令**，并监视输出到控制台的信息
``` java
public class OSExecute {
  public static void command(String command) {
    boolean err = false;
    try {
        //启动一个新进程。这个新进程的命令和参数就是输入的命令字符串。
      Process process = new ProcessBuilder(
        command.split(" ")).start();//执行命令
      try(//监控输出
        BufferedReader results = new BufferedReader(
          new InputStreamReader(
            process.getInputStream()));
        BufferedReader errors = new BufferedReader(
          new InputStreamReader(
            process.getErrorStream()))
      ) {
        results.lines()
          .forEach(System.out:: println);
        err = errors.lines()
          .peek(System.err:: println)
          .count() > 0;
      }
    } catch(IOException e) {
      throw new RuntimeException(e);
    }
    if(err)
      throw new OSExecuteException(
        "Errors executing " + command);
  }
}
```
