## Maven

### 基本概念

#### **POM Files**的基本内容

- **POM**（Project Object Model）文件定义了项目的构建配置，包括项目的依赖、插件、目标等。（就是所说的pom项目对象模型）包含：
- **项目基本信息**：如项目名称、版本、描述、URL等。
- **依赖关系**：列出了项目需要的所有库和框架的依赖项，包括它们的版本和配置。
- **构建设置**：定义了编译源代码、打包输出和执行测试等任务所需的配置。
- **构建生命周期**：指定了项目构建过程中要经历的一系列阶段，如编译、测试和打包。
  - **clean 生命周期**:旨在**清理项目**，删除所有由之前构建生成的文件。
  - **default 生命周期**:是进行项目实际构建的主要生命周期，包括**编译、测试、打包、安装和部署等阶段。**
  - **site 生命周期**:用于创建和处理项目文档站点。
- **插件和目标**：指明了Maven在构建过程中需要执行的插件以及插件目标。
- **项目目录结构**：规定了源代码、资源、测试和输出文件的标准文件夹结构。
- **属性**：可以定义一些属性，以便在POM的不同部分重用。
- **构建配置文件**：可以为不同的构建环境指定不同的设置。
- **项目继承**：允许一个项目POM继承另一个POM的配置。
- **模块**：在多模块项目中，一个父POM可以定义多个子模块。

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231224215018560.png" alt="image-20231224215018560" style="zoom:33%;" />

#### pom树

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231224220431482.png" alt="image-20231224220431482" style="zoom:33%;" />
- POM的**继承结构**指的是在Maven项目中，一个POM文件可以**继承另一个POM文件的配置**。这类似于面向对象编程中类的继承机制。这个特性允许子项目继承父项目的一些公共配置，减少重复的配置信息，使得项目管理更为高效。
- **父POM（Parent POM）**:
  - 父POM文件通常包含多个子模块共有的配置信息，例如项目组织信息、项目依赖关系、插件管理、属性等。
  - 父POM定义了子POM应该继承的通用配置，这样子POM就不需要重复这些相同的配置。
- **子POM（Child POM）**:
  - 子POM文件在继承父POM的同时，也可以有自己的特定配置。
  - 子POM可以覆盖父POM中的某些配置，也可以添加自己独特的依赖和插件等。
- **继承关系**:
  - 子POM通过在其`pom.xml`文件的`<parent>`标签中指定父POM的坐标（`groupId`、`artifactId`、`version`）来实现继承。
  - 一旦继承关系建立，子POM会继承父POM中定义的所有配置，除非在子POM中明确覆盖。
- **多模块项目**:
  - 在多模块项目中，有一个顶级的父POM，它的`<modules>`标签会列出所有的子模块。
  - 子模块的POM文件则通过`<parent>`标签指回顶级父POM。

#### 构建的基本过程

1. **validate（验证）**:
   - 在实际构建过程开始之前，**验证项目是否正确**，确保所有必需的信息都可用。
   - 这通常包括检查POM文件的正确性和完整性。
2. **compile（编译）**:
   - **编译**项目的源代码。
   - 这个阶段编译位于 `src/main/java` 目录下的源代码，并将输出放在 `target` 目录中。
3. **test（测试）**:
   - 使用合适的单元测试框架（如JUnit）**测试编译后的源代码**。
   - 这些测试通常不应该要求代码被打包或部署。
   - 测试代码通常位于 `src/test/java` 目录。
4. **package（打包）**:
   - 将编译后的代码**打包**成可分发的格式，**如JAR文件**。
   - 打包阶段不仅包括编译的代码，还包括项目的资源文件，如属性文件、图片等。
5. **integration-test（集成测试）**:
   - 在需要的情况下，将打包好的软件部署到可以运行**集成测试**的环境。
   - 这个阶段通常涉及到在模拟的生产环境中运行应用，以确保各个组件能够正常协同工作。
6. **verify（验证）**:
   - 运行任何必要的检查来**验证打包是否有效**，并且满足质量标准。
   - 这可能包括代码质量评估、性能测试等。
7. **install（安装）**:
   - 将软件包安装到本地仓库，供本地其他项目作为依赖使用。
   - 这使得其他本地项目可以轻松地引用正在开发的项目。
8. **deploy（部署）**:
   - 在集成或发布环境中进行，将最终的软件包复制到远程仓库，以便与其他开发者和项目共享。
   - 这通常用于将构建的成果发布到可以供其他项目或团队成员访问的中央仓库。

### 基本命令

- 运行特定阶段的构建
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231224221949199.png" alt="image-20231224221949199" style="zoom:33%;" />

## Gradle

- 文件结构

  - ```bash
    my-project/                    # 项目根目录
    ├── gradle/                    # Gradle 脚本目录
    │   └── wrapper/               # Gradle Wrapper 相关文件
    │       ├── gradle-wrapper.jar # Gradle Wrapper 可执行 JAR 文件
    │       └── gradle-wrapper.properties # Gradle Wrapper 配置文件
    ├── src/                       # 源代码目录
    │   ├── main/                  # 主源代码
    │   │   ├── java/              # Java 源文件
    │   │   └── resources/         # 资源文件，如配置文件
    │   └── test/                  # 测试源代码
    │       ├── java/              # Java 测试源文件
    │       └── resources/         # 测试用的资源文件
    ├── build.gradle               # 项目的构建脚本
    ├── settings.gradle            # Gradle 设置文件，用于配置项目
    └── gradlew                    # Unix/Linux 系统上的 Gradle Wrapper 启动脚本
    └── gradlew.bat                # Windows 系统上的 Gradle Wrapper 启动脚本
    ```

  - **`gradle/` 目录**：包含与 Gradle Wrapper 相关的文件。这些文件允许项目使用预定义的 Gradle 版本，无需手动安装。

  - **`src/` 目录**：包含所有源代码。它通常分为 `main` 和 `test`，分别用于项目的主要代码和测试代码。

  - **`build.gradle`**：这是项目的主要构建脚本文件，定义了项目如何构建，包括依赖项、插件、任务等。

  - **`settings.gradle`**：用于配置 Gradle 的设置，如项目名称和包含的子项目。

  - **`gradlew` 和 `gradlew.bat`**：这些是 Gradle Wrapper 脚本，允许在没有安装 Gradle 的情况下构建项目。

### 配置文件

#### build.gradle

- `build.gradle` 文件定义了项目的构建逻辑。这包括了项目依赖、插件、任务和其他构建相关的配置。

- ```bash
  // 插件
  plugins {
      id 'java'
  }
  
  // 项目版本和组织信息
  group 'com.example'
  version '1.0-SNAPSHOT'
  
  // 仓库
  repositories {
      mavenCentral()
  }
  
  // 依赖项
  dependencies {
      implementation 'org.springframework.boot:spring-boot-starter-web'
      testImplementation 'junit:junit:4.12'
  }
  
  // 自定义任务
  task customTask {
      doLast {
          println 'This is a custom task.'
      }
  }
  
  ```

- **插件**：使用 `plugins` 代码块定义项目使用的插件。

- **仓库**：使用 `repositories` 代码块定义从哪里获取依赖（如 Maven 中央仓库）。

- **依赖项**：使用 `dependencies` 代码块定义项目依赖。

- **自定义任务**：创建自定义任务以扩展构建过程。

#### settings.gradle

- `settings.gradle` 文件用于配置 Gradle 构建的基本设置，特别是在多项目构建中。

- ```bash
  rootProject.name = 'my-project'
  
  // 包含的子项目
  include 'subproject1', 'subproject2'
  ```

- **项目名称**：设置根项目名称。

- **子项目**：定义项目中包含的子项目。

### Gradlew

- `gradlew` 是 Gradle Wrapper 的缩写，它是一个脚本，允许用户运行项目构建而**无需在系统上预先安装 Gradle**。这个脚本会**自动下载**并使用为项目配置的正确版本的 Gradle（而忽略本地安装的版本）。
  - 通过`gradle/wrapper/gradle-wrapper.properties`编辑

#### 常用命令

- 构建项目`./gradlew build`
- 清理`./gradlew clean`

- 运行(单元)测试`./gradlew test`
- 运行应用`./gradlew`
- 可用任务`./gradlew tasks`
- 运行特定任务`./gradlew chapter:ExampleName`
  - 查看项目中所有可以运行的任务`gradlew tasks --all `
- 更新`./gradlew wrapper --gradle-version <version>`