% Java高级程序设计大作业
% 田昊东
% 2023/12/21

### 游戏概述

---

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215214417448.png" alt="image-20231215214417448" style="zoom: 33%;" />

- newgame新建游戏
- onlinegame多人在线游戏
- load继续（恢复游戏）
- game video观看游戏录像

---

<img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215214406539.png" alt="image-20231215214406539" style="zoom: 33%;" />

  - 地图上随机刷新敌人，敌人会自动移动到最近的玩家附近，向玩家发射子弹进行攻击。
  - 玩家通过wasd进行移动，鼠标点击进行攻击（可以向一周八个方向发射子弹）

---

### 游戏框架

使用libgdx进行开发，gradle构建项目

---

core模块文件结构
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215220731990.png" alt="image-20231215220731990" style="zoom:50%;" />

---

整个地图由12*18的地图构成，由map类负责维护

- map持有一个cell（单元格）数组
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215220108622.png" alt="image-20231215220108622" style="zoom: 50%;" />

- 每个cell上可以放置一个being，其派生类表示玩家、障碍物、子弹等实例

---

游戏场景设计

- RougerLike：游戏入口
- GuideScreen：网络游戏的非房主界面
- VideoSCreen：历史回看界面
- MainMenuScreen：主菜单（模式选择界面）
- GameScreen：游戏界面、网络游戏房主界面

---



子弹攻击的判定

- 使用java的反射机制，判断目标是否是要攻击的目标类型

```java
  if(x>=0&&x<col&&y>=0&&y<row&&being.target.isInstance(map.getCell(x,y).getBeing()))
      ((Creature) map.getCell(x,y).getBeing()).underAttack(being.at);
```

- 此外在creature类型中维护class变量标识目标类型`public Class<?extends Creature>target;`

---

### 并发

---

敌人的生成及线程创建
```java
  private void generateEnemy(){
      int[]pos=generateEmptyPosition();
      Enemy enemy = new Enemy(manager.get("pix/enemy.png", Texture.class),pos[0],pos[1],this);
      map.setCell(enemy);
      enemyGroup.addActor(enemy);
      Thread enemyThread = new Thread(enemy);
      enemyThread.start();
  }
```

- enemy类实现了runnable接口，此接口能周期执行策略，控制单位的移动及攻击，创建新敌人时创建新线程运行enemy的run方法

---

```java
@Override
public void run() {
    EnemyAi ai=new EnemyAi(game.map);
    boolean running=true;
    while (!isDead()&&running&&game.getPlayer()!=null) {
        Move nextMove = ai.getNextMove(x,y,minDis);
        Move nextAttack=ai.getAttack(x,y,maxDis);
        if(nextAttack!=null){
            attack(nextAttack);
        }
        else if (nextMove != null) {
            game.move(this, nextMove);
        }
        try {
            Thread.sleep(moveInterval);
        } catch (InterruptedException e) {
            running = false;
        }
    }
}
```

---

防止多线程冲突的设计

- 由于每个敌人会移动以及发送子弹，这可能出现多个线程同时对map进行读取/修改，这可能导致问题，因此做出以下改进：

- Creature的health属性设置为原子变量，防止一个对象同时受到攻击时出现问题

  - `public AtomicInteger health = new AtomicInteger(100);`

---

map操作串行化，防止多个线程同时修改

- ```java
  public synchronized void delCell(Being being) {}
  public synchronized void setCell(Being being) {}
  public synchronized boolean checkCell(int x,int y) {}
  ```

单位移动串行化

- ```java
  public synchronized void move(Creature being, Move op){}
  ```

---

### 测试

---

测试类编写

- 使用Junit4以及mockito进行测试
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215230854382.png" style="zoom: 50%;" />
  - 总共编写了7个测试类

---

mapread（IO）测试

```java
  @Before
  public void setUp() throws IOException {
      testFilePath = Files.createTempFile("testMap", ".txt");
      List<String> lines = Arrays.asList(
          "0 0 1",
          "0 1 0",
          "1 0 0"
      );
      Files.write(testFilePath, lines);
  }
  @Test
  public void testReadMap() throws IOException {
      List<List<Integer>> map = ReadMap.readMap(testFilePath);
      assertEquals(3, map.size());
      assertTrue(map.contains(Arrays.asList(0, 2)));
      assertTrue(map.contains(Arrays.asList(1, 1)));
      assertTrue(map.contains(Arrays.asList(2, 0)));
  }
```

- 设置临时地图文件，进行读取民兵对读取的结果过进行比对测试

---

测试覆盖率

- ![image-20231215230609767](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215230609767.png)

---

### IO

---

- 地图保存

  - 使用数字存储，0表示空格，1表示障碍物
  - ReadMap类的静态方法，从文件读取为list
  - GameScreen根据读取结果进行绘制

---

stage的设置

- 对Stage中的Actor进行分组管理

  - ```java
    public Group enemyGroup;
    public Group bulletGroup;
    public Group itemGroup;
    ```

---

```java
  public void initGame(){
  	...
      stage.addActor(itemGroup = new Group());
      stage.addActor(enemyGroup = new Group());
      //初始化背景
      for (int i = 0; i < row; i++) {
          for (int j = 0; j < col; j++) {
              Base base = new Base(manager.get("pix/base.png", Texture.class), j, i, this);
              itemGroup.addActor(base);
          }
      }
      stage.addActor(bulletGroup=new Group());
      Gdx.input.setInputProcessor(stage);
  }
```

---

```java
public void newGame(String name) throws IOException {
    //初始化玩家
    player = new Player(manager.get("pix/hero.png", Texture.class),8,5,true,this);
    players.put(0,player);
    map.setCell(player);
    stage.addActor(player);
    PlayerInput playerInput = new PlayerInput(this);
    stage.addListener(playerInput);
    //初始化地图(障碍物)
    List<List<Integer>> res= ReadMap.readMap(Paths.get("map/"+name+".txt"));
    for(List<Integer> i:res){
        Wall wall = new Wall(manager.get("pix/wall.png", Texture.class),i.get(1),i.get(0),this);
        map.setCell(wall);
        itemGroup.addActor(wall);
    }
}
```

---

游戏记录回放

- 使用GameVideo类处理

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231215234614712.png" alt="image-20231215234614712" style="zoom: 33%;" />

- 使用libgdx提供的Timer类实现定时周期执行，每次通过map的方法获取当前网格状态的快照（设计用数字表示每个网格上的单位）

- 停止录制时将缓存的帧信息存储到文件

- VideoSCreen负责读取及播放帧
  - 在Render函数中实现定时更新

---


- 游戏存档及恢复

  - 相比视频录制，游戏存档需要不仅需要保存每个格子上的类型，还需要存储每个单位的移动方向（子弹），攻击力生命值等信息

  - map中提供了获取详细快照的方法

  - 在恢复时只需要按照同样的规则从存档加载即可

---

### 网络通信

- 使用帧同步及房主模式
- 即服务器只用于完成一些基本操作，如为加入的玩家分配id，以及接收玩家发来的信息，并进行广播转发
- 第一个加入的玩家作为房主，负责处理游戏逻辑，其他玩家的操作会发送给房主，由房主进行运算，并向其他玩家广播游戏状态

---

#### 服务端设计

- 使用nio实现

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231216001057514.png" alt="image-20231216001057514" style="zoom:50%;" />

---

在start中服务器循环监听，检查是否有新的玩家加入，或者是否有消息需要处理

```java
  public void start() throws Exception {
      while (true) {
          selector.select();
          Set<SelectionKey> selectedKeys = selector.selectedKeys();
          Iterator<SelectionKey> iter = selectedKeys.iterator();
          while (iter.hasNext()) {
              SelectionKey key = iter.next();
              if (key.isAcceptable()) {
                  // 接受客户端连接
                  accept(key);
              } else if (key.isReadable()) {
                  // 读取客户端数据
                  read(key);
              }
              iter.remove();
          }
      }
  }
```

---

- 连接处理

  - ```java
    private void accept(SelectionKey key) throws Exception {
        ServerSocketChannel serverChannel = (ServerSocketChannel) key.channel();
        SocketChannel channel = serverChannel.accept();
        channel.configureBlocking(false);
        // 为新客户端分配唯一的ID
        int clientId = clientIdCounter.getAndIncrement();
        ByteBuffer buffer = ByteBuffer.allocate(Integer.BYTES);
        buffer.putInt(clientId);
        buffer.flip();
        while (buffer.hasRemaining()) {
            channel.write(buffer);
        }
        channel.register(selector, SelectionKey.OP_READ);
        activeConnections.incrementAndGet();
    }
    ```

---

- 断开连接处理

  - 连接断开后对连接码进行复位，并且如果所有连接都已经断开，则重置id编号
- 消息接收

  - 服务器接收到信息后立刻进行广播

---

#### 客户端设计

- 客户端网络模块

  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231216000938974.png" alt="image-20231216000938974" style="zoom:50%;" />

---

- 连接到服务器，并获取分配的id

  - ```java
    public int connect(String hostname, int port) throws Exception {
    
        socketChannel = SocketChannel.open();
        socketChannel.connect(new InetSocketAddress(hostname, port));
        socketChannel.configureBlocking(false);
        // 等待连接完成
        while (!socketChannel.finishConnect()) {
    
        }
        int clientId = receiveClientId(socketChannel);
        System.out.println("Connected to the server. clientId=" + clientId);
        return clientId;
    }
    ```

  - 根据返回的id判断是否作为房主

---

- 发送数据,以\n作为分隔符

接受数据，将缓冲区的数据全部取出，并存储到字符串中，每次取数以`\n`为分隔符取出一条信息

```java
    public String receive() throws Exception {
        ByteBuffer buffer = ByteBuffer.allocate(10000);
        int bytesRead = socketChannel.read(buffer);
        buffer.flip(); 
        incompleteMessage.append(StandardCharsets.UTF_8.decode(buffer).toString());
        // 检查是否包含完整消息（检查分隔符）
        int delimiterIndex = incompleteMessage.indexOf("\n");
        if (delimiterIndex != -1) {
            String completeMessage = incompleteMessage.substring(0, delimiterIndex);
            incompleteMessage.delete(0, delimiterIndex + 1); // 移除已处理的消息部分
            if(completeMessage.equals(""))
                return receive();
            return completeMessage;
        }
        return null;
    }
```

---

#### 通讯逻辑

- 使用GideScreen作为非房主的显示

- 在render中检查是否有来自房主（id=0的信息），如果有则对显示进行更新

- 使用GuideInput处理输入事件，会将移动攻击等事件发送到服务器


---

在房主方，使用一个HashMap维护玩家id和player对象的对应关系

- 当地图信息发生变化时，对地图信息发送到服务器进行广播

- 接收到来自其他玩家的信息时根据id对其操作进行响应

---

[java高级程序设计Rougerlike5（网络通讯）_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1bN4y1h7jT/?vd_source=acab52c21ffa9e9c57428e615e773279)

---

### 谢谢！

