- 微服务架构是一种将单一应用拆分为**一组独立的小服务**的开发方式，每个服务在自己的进程中运行，使用轻量级**通信机制**（如 HTTP API），围绕特定业务功能构建，能够**独立部署和管理**。
	- 集中系统->服务之间相互调动的分布式系统
- 对功能进行划分：
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240514235648.png)

- 断路器：防止系统中的一个服务出现故障而故障蔓延并导致系统崩溃
	- 正常状态下所有请求能通过断路器，如果一个服务请求失败次数过多，断路器就会打开
	- 断路器打开后阻止对服务的访问，直接返回特定错误响应；断路器打开一段时间之后，会半开（允许部分请求通过），检测服务是否恢复
- 有点：反之级联故障；快速失败；恢复检测
在计算机体系结构中，阻塞（Stall）是指指令的执行被迫暂停，从而影响流水线的处理效率。阻塞的原因可以是多种多样的，包括数据依赖、结构性冲突和控制毛线。根据阻塞的实施方式，可以分为软件阻塞（气泡）和硬件阻塞。下面详细解释两者的区别：

### 软件阻塞（气泡）

软件阻塞通常由编译器在编译阶段插入，以应对流水线中的潜在冲突。气泡（Bubble）是一种特殊的NOP（No Operation）指令，用于填补流水线，使其能继续运行而不造成错误。软件阻塞的主要特点是：

1. **由编译器插入**：编译器在生成机器代码时分析指令依赖性和流水线冲突，并在需要时插入NOP指令。
2. **静态分析**：编译器基于程序的静态分析确定需要插入气泡的位置，不需要在运行时进行复杂的动态判断。
3. **预防性措施**：软件阻塞是预防性措施，目的是确保流水线在遇到数据依赖、结构冲突或控制毛线时不会产生错误。
4. **性能影响**：由于插入了额外的NOP指令，可能导致程序执行时间增加，但这种方法简单且不需要复杂的硬件支持。

#### 示例
假设有以下指令序列，其中`SUB`指令依赖于`ADD`指令的结果：

```
1. ADD R1, R2, R3
2. SUB R4, R1, R5
```

为了避免数据依赖冲突，编译器可能会插入一个气泡：

```
1. ADD R1, R2, R3
2. NOP
3. SUB R4, R1, R5
```

### 硬件阻塞

硬件阻塞由处理器硬件在运行时动态检测和处理，主要通过暂停流水线的某些阶段来等待依赖的解决。硬件阻塞的主要特点是：

1. **由硬件控制**：处理器在运行时实时检测指令间的依赖关系和冲突，并决定是否需要暂停某些流水线阶段。
2. **动态判断**：硬件阻塞基于运行时的实际情况做出决定，通常采用复杂的控制逻辑和缓冲机制。
3. **灵活处理**：硬件阻塞可以更灵活地处理各种依赖和冲突，不需要编译器的静态分析和插入NOP指令。
4. **复杂性和成本**：硬件阻塞需要处理器设计中增加复杂的控制逻辑和检测机制，可能增加芯片设计的复杂性和成本，但可以减少气泡插入导致的性能损失。

#### 示例
对于同样的指令序列：

```
1. ADD R1, R2, R3
2. SUB R4, R1, R5
```

处理器在执行`SUB`指令时，检测到它依赖于`ADD`指令的结果。处理器会暂停`SUB`指令的执行，直到`ADD`指令完成并写回结果。

### 比较

| 特性 | 软件阻塞（气泡） | 硬件阻塞 |
|------|------------------|----------|
| 实施者 | 编译器 | 处理器硬件 |
| 时机 | 编译时 | 运行时 |
| 决策依据 | 静态分析 | 动态检测 |
| 灵活性 | 低，基于编译时信息 | 高，基于运行时信息 |
| 复杂性 | 低，编译器实现 | 高，硬件实现 |
| 性能影响 | 增加执行时间，插入NOP | 更有效利用流水线，但硬件复杂度高 |
| 预防性 | 是 | 否 |

### 总结

- **软件阻塞（气泡）**：由编译器在编译阶段插入，通过静态分析确定需要插入气泡的位置，主要用于预防性地解决数据依赖和流水线冲突，增加了执行时间但实现简单。
- **硬件阻塞**：由处理器在运行时动态控制，通过硬件实时检测和解决依赖关系和冲突，灵活高效地利用流水线，但增加了处理器设计的复杂性和成本。

两者各有优缺点，实际应用中可能会结合使用以达到最佳的性能和设计平衡。