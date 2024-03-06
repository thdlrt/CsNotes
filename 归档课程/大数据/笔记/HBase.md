## HBase

- HBase 对应谷歌的 BigTable

- Hadoop的局限性
  - 无法满足大规模数据实时访问模式
  - HDFS面向**批量访问**不是随机访问
- 传统关系型数据库的局限性
	- 扩展性差
	- 在数据结构变化时一般需要停机维护；结构化造成空列浪费存储空间。

- 设计目标
  - **应对HDFS局限**：旨在为HDFS提供一个处理大规模结构化和半结构化数据存储访问的分布式数据管理系统。
  - **列存储模式**：提供了基于列存储的大数据表管理能力，适合于管理包含数十亿行记录和百万列元素的数据表。
  - **高性能读写**：专注于提供随机和实时的数据读写访问能力。
  - **高扩展性和可用性**：具备高可扩展性、高可用性、容错能力、负载平衡以及实时数据查询能力。

- 功能特点
  - **列式存储**：采用列式存储方式，适合于稀疏数据的存储和处理。
  - **稀疏的多维映射表**：表数据被视为稀疏的，多维的映射表。
  - **优化的数据读写速度**：特别优化了数据写操作的速度。
  - **线性可扩展性**：良好的线性扩展能力。
  - **海量数据存储**：支持存储和管理海量数据记录。
  - **自动数据分片**：数据自动分片以优化存储和查询效率。
  - **高容错性**：具有自动故障检测和恢复能力，保证数据的持久性。

- 与传统RDBMS的对比 ^c0574a
  - **数据模型**：RDBMS使用**关系模型**，具有丰富的数据类型和存储方式，而HBase使用**简单**的数据模型，存储未经解释的字符串。
  - **数据操作**：RDBMS支持**复杂**的多表连接和丰富的操作，而HBase操作**简单**，避免了复杂的表间关系。
  - **存储模式**：RDBMS基于**行**模式存储，HBase是基于**列**存储的。
  - **数据索引**：RDBMS支持多个复杂的索引，HBase只有行键索引。
  - **数据维护**：RDBMS的更新操作覆盖旧值，HBase保留数据的所有版本。
  - **可伸缩性**：RDBMS难以水平扩展，而HBase设计用于**灵活的水平扩展**。

### HBase基本工作原理

#### 数据模型

- HBase的数据模型是一个**稀疏、多维度、排序**的映射表，这张表的索引是**行键、列族、列限定符和时间戳**。
- 所有数据都以**字符串**进行存储，用户需要自行进行数据类型的转换

- **每一行**都有一个可排序的**行键**和**任意多的列**
- 表由一个或多个**列族**组成，一个列族可以包含很多个**列**。列族支持动态扩展，不需要预定义数量及类型。
- 由行键、列族、列限定符可以确定一个单元格，单元格内有数据的不同版本（HBase执行更新操作时不删除，只生成新的），再使用**时间戳**进行索引
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123133925382.png" alt="image-20231123133925382" style="zoom:33%;" />
- 即通过四元组获取数据 `[行键, 列族, 列限定符, 时间戳]`

- 行主键：用来检索记录的主键
  - 通过单个row key访问/通过row key的范围range来访问/全表扫描。
  - 存储时，数据按照Row key的字典序排序存储，因此应该将经常一起读取的行存储放到一起。
  - 行的一次读写是原子操作。

- 列族：
  - HBase表中的每个列，都归属于某个列族，**列名都以列族作为前缀**。
  - **列族**是表的schema的一部分，**必须在使用表之前定义。**
  - **访问控制**（读/写）、磁盘和内存的使用统计都是在列族层面进行的。
  - 在 HDFS 中是以列族为单位存储的

- 时间戳：
  - 每个cell都保存着同一份数据的多个版本。
  - HBase 提供了两种数据版本回收方式。一是保存数据的最后 n 个版本，二是保存最近一段时间内的版本（比如最近七天）。可以针对每个列族进行设置。

- 与关系型数据库对比：对于**关系型数据库**：在创建时定义好的**固定列集合**。**每一行都有相同的列结构**，即使某些列的值为空；对于**HBase**：每一行可以有**任意数量的列**，并且每行的列**可以不同**。列是按需添加的，不需要在表创建时定义所有可能的列。

##### 概念视图

- HBase一定程度上又可以看成一个多维度的Map模型去理解它的数据模型。可以看作一个逐级映射的字典
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123134441951.png" style="zoom:33%;" />
- 在一定程度上也可以看作key-Value数据库

##### 物理视图

- 按照列存储的稀疏行/列矩阵。物理存储格式上按逻辑模型中的行进行分割，并**按照列族存储**。值为空的列不予存储。（这也是容易扩充的本质，想想按行存储就像数组，插入元素很难）
  - 每一行的列标识符都可以不一样！
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123172818623.png" alt="image-20231123172818623" style="zoom: 33%;" />
  - :前面的列族一样，后面的列标识符可以不一样

##### 列存储与行存储

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123173519243.png" alt="image-20231123173519243" style="zoom:50%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123173608508.png" alt="image-20231123173608508" style="zoom:33%;" />
  - 列式数据库在**并行查询处理**和压缩上更有优势。而且数据是以列为单元存储，完全不用考虑数据建模或者说建模更简单了。要查询计算哪些列上的数据，直接读取列就行。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123173808660.png" alt="image-20231123173808660" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123173823977.png" style="zoom:33%;" />

#### HBase表设计

- 传统数据库：通常需要满足**第三范式**（3NF）指表中的所有数据元素不但要能唯一地被主关键字所标识，而且它们之间还**必须相互独立**，不存在其他的函数关系。
- NoSQL 数据库：反规范化。应该将相关的数据都存放在一起，**不担心冗余**。

- 例1 Row key 的设计： 
  - 行键可以不仅仅包含一个指标，可以进行较为复杂的组合，如 `user123_2021-07-15_post`，之后**根据字典序**进行排序并存储
  - 存储一个集群的 log（机器名，时间，事件，事件正文）
  - 查询需求：
    - 需求一：对于**某台机器**，查询一个大的时间段（例如1个月）内的所有满足条件的记录（单机查询）
    - 需求二：查询**某个时间段内**对所有机器满足条件的记录（全局查询）

  - 方案：
    - 方案一：\[机器名]\[时间]\[事件]
    - 方案二：\[时间]\[机器名]\[事件]
    - 方案一对单机查询友好，对插入友好（Region分散，并发度高）；由于数据是**根据机器名分散存储的**，插入操作可以在不同的Region（区域）上并发进行，提高了插入效率。
    - 方案二对全局查询友好，对插入不友好（Region集中，并发度低）;数据可能在**较少的Region上集中**，从而减少了插入时的并发度，可能会造成某些Region的负载过高。

  - 加盐（分散Region，提升并发性能）
    - 通过计算一个盐值并将其添加到行键的前面，可以**打破数据的自然排序**，使得原本会连续存储的数据分散到不同的Region。
    - 如：盐值 = 时间 % 桶个数
    - row key：\[盐值]\[时间]\[机器名]\[事件]
    - 副作用：**查询变慢**(尤其是范围查询)，降低了系统的吞吐量，桶个数不宜太大

  - 一张大表 or 按时间进行分表？
    - 大表：查询都在单张表完成
    - 数据过期时需要依赖major compaction进行压缩，会造成大量的数据读写；活跃Region在RegionServer间的分布可能不均匀。
    - 按时间分表：据过期可以通过简单删除整张表完成；活跃Region可以得到分布均匀。需要跨表查询时，性能会比较差。

- 例2：设计一张表，用来保存微博上用户互粉的信息。
  - 读场景业务要求：每个用户都关注了谁；用户A有没有关注用户B；谁关注了用户A
  - 写场景业务要求：用户关注了另一个用户；用户取消关注某个用户
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123234137385.png" alt="image-20231123234137385" style="zoom:50%;" />
    - 每一行的列标识符不一样，number:name，count:number
    - 读场景：
      - **关注列表查询**：行键**直接映射**到用户ID，可以迅速找到该用户关注的人的列表。
      - **特定关注关系查询**：**组合行键和列限定符**可以快速确定用户A是否关注了用户B。
      - **被关注者查询**：使用反向索引表或者通过扫描整个表来查找谁关注了用户A。
    - 写场景：
      - **新增关注**：在用户ID对应的行中添加新的列限定符和值，并更新关注计数器。
      - **取消关注**：从用户 ID 对应的行中删除列限定符，并更新关注计数器。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123235516910.png" alt="image-20231123235516910" style="zoom:50%;" />
    - 行键由关注者（follower）和被关注者（followed）的ID组合而成，使得对特定的关系进行检索时，可以直接通过行键访问，而不需要进行全表扫描。
    - 列族名（CF）被保持简短，例如使用`f`，减少了存储和网络传输时的开销。列限定符（CQ）使用了被关注用户的名称，这样客户端在获取关系信息时就不需要查找额外的用户信息。

- 设计经验
  - 对Row Key的Hash优化能获得固定长度的Row Key并使**数据分布更加均匀一些**，而不是集中在一台服务器上，但是也**牺牲了一定的数据排序和读取性能**。
  - 列标识名字的长度和列族名字的**长度**都会影响I/O的读写性能和发送给客户端的数据量，所以它们的命名应该**简洁**。

#### HBase的基本架构

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123223021342.png" alt="image-20231123223021342" style="zoom:50%;" />
  - **客户端**：包含访问HBase的接口，同时在缓存中维护着已经访问过的Region位置信息，用来加快后续数据访问过程
  - **Zookeeper**：可以帮助选举出一个Master作为集群的总管，并保证在任何时刻总有唯一一个Master在运行，这就避免了Master的“单点失效”问题
  - **Master：** 主服务器 Master 主要负责表和 Region 的管理工作：
    - 管理用户对表的增加、删除、修改、查询等操作
    - 实现不同Region服务器之间的**负载均衡**
    - 在Region分裂或合并后，负责重新调整Region的分布
    - 对发生故障失效的Region服务器上的Region进行迁移
  - **RegionServer**：服务器是HBase中最核心的模块，负责维护分配给自己的Region，并响应用户的读写请求

#### HBase数据存储管理方法

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123225704179.png" alt="image-20231123225704179" style="zoom:33%;" />
  - Region Server cluster->Region server->Region->memStore+StoreFile

- region：
  - Region是表的一个子集，包含了一系列连续的行。它是数据**物理存储和分布的基本单元**。
  - 每个Region由一个RegionServer负责管理，它负责Region内部所有数据的读写操作。当Region的数据量增长到一定阈值时，Region会被**分裂**（Split）成两个新的Region，以保持系统的可伸缩性和性能。（一个Server内有多个Region）
    - 拆分：拆分操作之后，新的Region最初并不复制或移动数据。它们仍然读取原始Region的存储文件（由于不需要立即复制数据，这使得拆分操作可以非常快速地完成，几乎是瞬间的）。（异步）随后，HBase会在后台进行合并过程，它会逐渐把原始文件中属于新Region的数据异步地写入新的独立文件。
    - **即时可用**：由于新Region**一开始就可以读取**原始Region的文件，它们立即变得可用，无需等待数据的物理复制。
    - **最终一致性**：随着时间的推移，新 Region**最终**会有自己独立的存储文件，这些文件只包含该 Region 负责的数据范围。

- store：
  - Store 是 Region 中的逻辑分区，对应于一个列族，每个列族存储在自己的 Store 中。

- memstore：
  - MemStore 是 Store 的一部分，是一个位于**内存**中的数据结构，用来**缓存**即将写入文件系统的数据。

- storefile：
  - StoreFile是Store的**持久化表示**，是存储在**HDFS上的文件**，具体格式为HFile。
  - 为了优化读取操作，StoreFiles 可能会被合并（Compaction）来减少它们的数量和提高读取效率。

- 查询和定位：
  - 为了加速寻址，客户端会**缓存位置信息**，同时，需要解决缓存失效问题
  - 寻址过程客户端只需要询问Zookeeper服务器，不需要连接Master服务器
  - HBase使用三层类似B+树的结构来保存Region位置
  - 通过Zookeeper里的文件得到**-ROOT-表**的位置，-ROOT-表永远不会被分割为多个Region
  - 通过-ROOT-表**查找.META.表**中**相应Region**的位置，为了加快访问，.META.表的全部Region的数据都会全部保存在**内存**中
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123231021108.png" style="zoom:33%;" />
  - 根子表->用户表的元数据表->用户表
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231123231111940.png" alt="image-20231123231111940" style="zoom:33%;" />
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124000340457.png" alt="image-20231124000340457" style="zoom:50%;" />

####  HBase 数据工作原理

- HLog
  - HBase采用HLog保证**系统恢复**
  - HBase系统为**每个Region服务器**配置了一个HLog文件，它是一种**预写式日志**
  - 用户更新数据必须首**先写入日志后**，才能写入MemStore缓存，直到MemStore缓存内容对应的**日志已经写入磁盘**，该缓存内容才能被刷写到磁盘
  - 故障恢复
    - **故障检测**：当Region服务器发生故障，Zookeeper检测到并通知HBase Master。
    - **HLog处理**：Master处理故障Region服务器的HLog文件。由于HLog包含**来自多个Region**的日志记录，这些记录必须被处理以恢复数据。
    - **HLog拆分**：Master根据HLog中的记录属于哪个Region，将日志数据**拆分**，把它们放入对应的Region目录下。
    - **Region重新分配**：Master将**失效的Region**重新分配到健康的Region服务器，并将**相关的HLog**记录发送给这些服务器。
    - **数据恢复**：接收新Region和HLog的Region服务器会重放日志记录中的操作，将数据写入MemStore，并最终刷新到磁盘上的StoreFile文件中，从而完成数据的恢复。
  - 一个节点上不同Region共用日志：提高对表的写操作性能；缺点：恢复时需要分拆日志

- 用户读写数据
  - 用户写入数据时，被分配到相应**Region服务器**去执行
  - 用户数据首先被写入到**MemStore**和**Hlog中**
  - 只有当**操作写入Hlog**之后，**commit()调用**才会将其返回给客户端
    - 这意味着只有写操作**安全地存储在HLog中**之后，用户才会收到写入成功的通知。
  - 当用户读取数据时，Region 服务器会**首先访问 MemStore 缓存**，如果找不到，再去磁盘上面的 StoreFile 中寻找

- 缓存的刷新
  - 系统会周期性地把MemStore缓存里的内容刷**写到磁盘的StoreFile**文件中，清空缓存，并在Hlog里面写入一个标记
  - **每次刷写都生成一个新的StoreFile文件**，因此，每个Store包含多个StoreFile文件
  - 每个 Region 服务器都有一个自己的 HLog 文件，每次启动都检查该文件，确认最近一次执行缓存刷新操作之后**是否发生新的写入操作**；如果发现更新，则先写入 MemStore，再刷写到 StoreFile，最后删除旧 Hlog 文件，开始为用户提供服务

- **StoreFile的合并**
  - 每次刷写都生成一个新的StoreFile，数量太多，影响查找速度
  - 调用Store.compact()把多个合并成一个
  - 合并操作比较耗费资源，只有数量达到一个阈值才启动合并
  - 单个StoreFile过大时，又触发分裂操作，1个父Region被分裂成两个子Region
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124001033932.png" alt="image-20231124001033932" style="zoom:33%;" />

### 配置和安装

- 启动关闭Hadoop和HBase的顺序一定是：启动Hadoop->启动HBase->关闭HBase->关闭Hadoop

### HBase基本操作

- 控制台：16010端口

#### HBase Shell

- 所有**字符串参数**都必须包含在**单引号中**，且区分大小写。

##### 表的管理

- 查看有哪些表：`list`
- **创建表**：` create <table>, {NAME => <family>[, VERSIONS => <VERSIONS>]}`
  - 如 `create 'myTable', {NAME => 'myFamily', VERSIONS => 3}`
  - 创建时指定列族 `create 'student', 'stuInfo'`
  - `VERSIONS => <VERSIONS>`：这是一个可选配置，用来指定列族中保留的数据版本数量。

- **删除表**：`disable <table>`
- 查看表结构：`describe <table>`
- **修改表结构**：`alter 't1', {NAME => 'f1'}, {NAME => 'f2', METHOD => 'delete'}`
  - `{NAME => 'f1'}`：第一个修改操作。它没有指定 `METHOD` 属性，所以**默认**是**添加**或者修改名为 `f1` 的**列族**。如果列族 `f1` 已经存在，它将保持不变，除非指定了额外的属性来修改它。
  - 对列族的操作属于对表结构的操作，对列的操作才属于对数据的操作

- disable与enable
  - disable和enable都是HBase中比较常见的操作，很多对table的修改**都需要表在disable的状态下才能进行**

##### 数据增删查改：

- **添加数据**：`put <table>,<rowkey>,<family:column>,<value>,<timestamp>`
- **查询某行记录**（获取行）：`get <table>,<rowkey>[,<family:column>,<timestamp>]`
  - 可以指定列族和列名来查询特定的列，或者省略来获取整行的数据。

- **扫描表**(获取列)：`scan <table>, {COLUMNS => [ <family:column>,.... ], LIMIT => num}`
  - `COLUMNS`: 指定要扫描的列或列族。
  - `LIMIT`: 指定要返回的记录数量限制。

- 查询表中的数据行数：`count <table>, {INTERVAL => intervalNum, CACHE => cacheNum}`
  - `INTERVAL`: 每处理`intervalNum`**行数据**后，会向客户端报告进度。
  - `CACHE`: 用于指定在单个RPC请求中预取的行数，以提高扫描操作的性能。

- **删除行中的某个列值**：`delete <table>, <rowkey>, <family:column> , <timestamp>`
- **删除行**：`deleteall '<table>', '<rowkey>'`
  - 这将删除指定行键的所有列数据
- 删除表中的所有数据：`truncate <table>`

##### 例子

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124003735850.png" alt="image-20231124003735850" style="zoom:50%;" />
- 创建表
  - `create 'Student', 'StuInfo', 'Grades’`
- 查看表
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124081149406.png" alt="image-20231124081149406" style="zoom: 50%;" />
  - 查看表中的数据`scan 'name'`
- 修改列族
    - `alter 'Student', {NAME => 'Grades', VERSIONS => 3}`
    - 修改已有数据的列族属性时，HBase需要对列族里**所有数据**进行修改，如果数据量较大，则修改可能要占用很长时间
- 增加列族
    - `alter 'Student', 'hobby'`
- 删除列族
    - `alter 'Student', { NAME => 'hobby', METHOD => 'delete' }`
    - 或 `alter 'Student', 'delete' => 'hobby'`
    - 当只有一个列族时无法删除
- 删除表
    - 先禁用`disable 'Student'`，再删除`drop 'Student'`
    - 只想清空数据`truncate 'Student'`
- 插入数据put
    - `put 'Student', '0001', 'Stulnfo:Name', 'Tom Green', 1`
    - 如果 put 语句中的单元格是已经存在的，即行键、列族及列名都已经存在，且不考虑时间戳的情况下，执行 put 语句，则可对数据进行**更新操作**。
- 删除数据delete
    - `delete 'Student', '0002', 'Grades'`
    - delete命令不能**跨列族操作**，如需删除表中所有列族在某一行上的数据，即删除上表中一个逻辑行，则需要使用 deleteall 命令` deleteall 'Student', ‘0001'`
    - delete 操作并不会马上删除数据，只会将对应的数据**打上删除标记,**只有在合并数据时，数据才会被删除。
- 获取数据和查询全表数据get
    - get 命令必须设置表名和行键名，同时可以选择指明列族名称、时间戳范围、数据版本等参数。`get 'Student', '0001'`
- 查询全表数据scan
    - `scan 'Student`
    - 条件输出 `scan 'Student', {COLUMNS =>'Grades'}`
      

#难点 
##### 过滤器

- 所有的过滤器都在**服务端**生效，即谓词下推。这样可以保证过滤掉的数据不会被传送到客户端，从而减轻网络传输和客户端处理的压力。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124084051034.png" alt="image-20231124084051034" style="zoom:33%;" />
- get 和 scan 操作都可以使用过滤器来设置输出的范围
- 如 `scan 'course', {COLUMNS => ['couInfo:C_No', 'couInfo:C_Name'], FILTER => "SingleColumnValueFilter('couInfo', 'C_Name', =, 'binary:BigData')"}`

- 使用比较器实现高级比较
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124084202730.png" alt="image-20231124084202730" style="zoom: 50%;" />
  -  使用 `比较器:text` 如 `substring:xx`

- **行键过滤器RowFilter**
  - 配合比较器和运算符，实现行键字符串的比较和过滤
  - 选出0001开头行键`scan 'Student',{Filter=>"RowFilter(=,'substring:0001')"}`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124085513220.png" alt="image-20231124085513220" style="zoom:50%;" />

- **列族与列过滤器 FamilyFIiter**
  - 对列族名称进行过滤
  - `scan 'Student', FILTER=>" FamilyFilter(= , 'substring:Grades')"`
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124090214269.png" alt="image-20231124090214269" style="zoom:50%;" />

- **值过滤器ValueFilter**
  - 针对单元格进行扫描的过滤器
  - 利用 get 和 scan 方法对单元格进行过滤，但是使用 get 方法时，需要**指定行键**。**SingleColumnValueFilter** 和 SingleColumnValueExcludeFilter 过滤器扫描的结果是相反的， 都需要在过滤条件中指定列族和列的名称。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124090609148.png" alt="image-20231124090609148" style="zoom:50%;" />

- 其他过滤器
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231124090619359.png" alt="image-20231124090619359" style="zoom:50%;" />

### HBase编程*

- Put和Get是操作**指定行**的数据的，所以需要提供行键来进行操作。Scan是操作**一定范围**内的数据，通过指定开始行键和结束行键来获取范围，如果没有指定开始行键和结束行键，则默认获取所有行数据。

- HBaseConfiguration
  - HBase配置信息
  - 默认的构造方式会尝试从hbase-default.xml和hbase-site.xml中读取配置。
```java
Configuration HBASE_CONFIG = new Configuration();
HBASE_CONFIG.set(“hbase.zookeeper.quorum”, “zkServer”);
HBASE_CONFIG.set(“hbase.zookeeper.property.clientPort”, “2181″);
HBaseConfiguration cfg= new BaseConfiguration(HBASE_CONFIG);
```

- HTableDescriptor
  - **含义**：`HTableDescriptor`是一个类，它表示**HBase表**的架构。
  - 作用：
    - 描述了**表的结构**，包括表的名字和它包含的列族。
    - 可以用来创建新表，或者修改现有表的属性。
    - 包含了表级别的设置。

- HColumnDescriptor
  - **含义**：`HColumnDescriptor`是一个类，代表**列族**的架构。
  - 作用：
    - 描述了**列族的特性**，例如版本号、压缩设置、TTL（Time To Live）等。
    - 列族是HBase中组织数据的逻辑结构，一个表可以有一个或多个列族。
    - 每个列族的配置可以独立于其他列族设置，这提供了针对不同类型数据的优化机会。

- 创建表
  - 创建表是通过Admin对象来操作的。Admin负责表的META信息处理。
```java
Connection conn= ConnectionFactory.createConnection(config);
Admin admin= conn.getAdmin();
//获取表架构
HTableDescriptor t = new HTableDescriptor(tableName);
//创建并添加列架构
t.addFamily(new HColumnDescriptor(“f1″));
t.addFamily(new HColumnDescriptor(“f2″));
t.addFamily(new HColumnDescriptor(“f3″));
t.addFamily(new HColumnDescriptor(“f4″));
admin.createTable(t);
```

- 删除表

  - 删除表之前首先要disable表。这是一个非常耗时的操作，所以不建议频繁删除表。


```java
if(admin.tableExists(tableName)){
    admin.disableTable(tableName);
    admin.deleteTable(tableName);
}
```

- 切分表

  - 参数hbase.hregion.max.filesize指示在当前ReigonServer上单个Reigon的最大存储空间，单个Region超过该值时，这个Region会被自动split成更小的region。
  - Admin提供split方法来将table进行手工split`public void split(TableName tableName)`
  - Admin提供splitRegion方法来将region进行手工split`public void splitRegion(byte[] regionName)`
  - 由于split是一个异步操作，并不能确切地控制region的个数。

- 插入数据


```java
public static void addData(String tableName, String rowKey, String family, String qualifier, String value) throws Exception{
    try{
        Connection conn= ConnectionFactory.createConnection(config);
        //获取表
        Table table =conn.getTable(tableName);
        //配置put对象
        Put put= new Put(Bytes.toBytes(rowKey));
        put.add(Bytes.toBytes(family), Bytes.toBytes(qualifier),Bytes.toBytes(value));
        //将put对象put进表
        table.put(put);
        System.out.println(“insert record success!");
                           } catch(IOException e) { e.printStackTrace(); }
                           }
```

- 查询数据

  - 单条查询是通过row key在table中查询某一行的数据。Table提供了**get方法**来完成单条查询。

  - 批量查询是通过制定一段row key的范围来查询。Table提供了个**getScanner方法**来完成批量查询。


```java
Scan s = new Scan();
s.setMaxVersions();
//进行批量查询
ResultScanner ss= table.getScanner(s);
for(Result r:ss){
    //jian'c
    System.out.println(new String(r.getRow()));
    for(KeyValuekv:r.raw()){ System.out.println(new String(kv.getColumn()));}
}
```

- 删除数据

  - eleteFamily或deleteColumns：指定要删除的family或者column的数据。如果不调用任何这样的方法，将会删除整行


```java
Table table = conn.getTable(“mytest”);
Delete d = new Delete(“row1″.getBytes());
table.delete(d)
```