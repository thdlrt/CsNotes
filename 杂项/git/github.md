## 基本使用

### 贡献

- 创建一个[议题（issue）](https://help.github.com/en/github/managing-your-work-on-github/creating-an-issue)。 议题可以用来反映软件运行的问题或者请求新的功能。创建议题并不需要创建者阅读或者编写代码，所以它是一个轻量化的贡献方式。高质量的问题报告对于开发者十分重要。在现有的议题发表评论也可以对项目的开发作出贡献。
- 使用[拉取请求（pull request）](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/about-pull-requests)提交代码更改。由于涉及到阅读和编写代码，提交拉取请求总的来说比创建议题更加深入。拉取请求是请求别人把你自己的代码拉取（且合并）到他们的仓库里。很多开源项目仅允许认证的管理者管理项目代码，所以一般需要[复刻（fork）](https://help.github.com/en/github/getting-started-with-github/fork-a-repo)这些项目的上游仓库（upstream repository），在你的 Github 账号下创建一个内容完全相同但是由你控制的复刻仓库。这样你就可以在这个复刻仓库自由创建新的分支并推送修复问题或者实现新功能的代码。完成修改以后再回到开源项目的 Github 页面[创建一个拉取请求](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request)。

## git action

#### 基本流程

- 创建文件夹`.github/workflows`，文件夹内创建`github-actions-demo.yml`作为配置文件，每个工作流都作为单独的 YAML 文件存储

  - 示例

  - ```yaml
    name: GitHub Actions Demo
    run-name: ${{ github.actor }} is testing out GitHub Actions 🚀
    on: [push]
    jobs:
      Explore-GitHub-Actions:
        runs-on: ubuntu-latest
        steps:
          - run: echo "🎉 The job was automatically triggered by a ${{ github.event_name }} event."
          - run: echo "🐧 This job is now running on a ${{ runner.os }} server hosted by GitHub!"
          - run: echo "🔎 The name of your branch is ${{ github.ref }} and your repository is ${{ github.repository }}."
          - name: Check out repository code
            uses: actions/checkout@v3
          - run: echo "💡 The ${{ github.repository }} repository has been cloned to the runner."
          - run: echo "🖥️ The workflow is now ready to test your code on the runner."
          - name: List files in the repository
            run: |
              ls ${{ github.workspace }}
          - run: echo "🍏 This job's status is ${{ job.status }}."
    ```

- 把配置文件push到一个新分支（可选）

### 基本概念

- **workflow** （工作流程）：持续集成一次运行的过程，就是一个 workflow。
- **job** （任务）：一个 workflow 由一个或多个 jobs 构成，含义是一次持续集成的运行，可以完成多个任务。
- step**（步骤）：每个 job 由多个 step 构成，一步步完成。**
- **action** （动作）：每个 step 可以依次执行一个或多个命令（action）。

### 基本语法

- `name: learn-github-actions`为action命名

- `run-name: ${{ github.actor }} is learning GitHub Actions`动态属性名称

- `on: [push]`action的触发方式

  - `[push, pull_request]`

  - 指定分支

    - ```yaml
      on:
        push:
          branches:    
            - master
      ```

- `check-bats-version:`action的显示名称

- `steps:`运行步骤

- `jobs`指定工作及依赖关系，实现自动运行

  - ```yaml
    jobs:
      job1:
      job2:
        needs: job1
      job3:
        needs: [job1, job2]
    ```

  - `runs-on: ubuntu-18.04`指定运行环境

### 示例

- 运行java程序

  - ```yaml
    name: sort-actions
    run-name: ${{ github.actor }} sort
    on: [push]
    jobs:
      runs-sort-with-zulu-17:
        runs-on: ubuntu-latest
        steps:
          - uses: actions/checkout@v3
          - uses: actions/setup-java@v3
            with:
              distribution: 'zulu' # See 'Supported distributions' for available options
              java-version: '17'
          - run: java HelloWorld.java
    ```

- 运行有多个文件的程序，需要先编译

  - ```yaml
    - name: Compile Java code
          run: |
            mkdir -p build
            javac -d build src/*.java
    
        - name: Run Java code
          run: |
            java -cp build com.example.MainClass # 替换 com.example.MainClass 为你的程序入口类的全名
    ```


## git book

### 项目初始化

> Node 版本 **10.23.0** 以下版本可使用。

- 进入项目文件夹

- `gitbook init`

- `npm init`

- 在`package.json`文件的`scripts`中配置如下的脚本命令：

  ```json
  "scripts": {
      "serve": "gitbook serve",
      "build": "gitbook build"
  }
  ```

- `npm run serve`本地运行

### 内容配置

- GitBook 使用文件 `SUMMARY.md` 来定义书本的章节和子章节的结构。文件 `SUMMARY.md` 被用来生成书本内容的预览表。

- 名字->路径

- ```
  # 概要
  - [第一章](part1/README.md)
    - [1.1 第一节](part1/writing.md)
    - [1.2 第二节](part1/gitbook.md)
  - [第二章](part2/README.md)
    - [2.1 第一节](part2/feedback_please.md)
    - [2.2 第二节](part2/better_tools.md)
  ```

- 任何在文件夹下的文件，在最后生成电子书时都会被拷贝到输出目录中，如果想要忽略某些文件，和 Git 一样， Gitbook 会依次读取 `.gitignore`, `.bookignore` 和 `.ignore` 文件来将一些文件和目录排除。

- Gitbook 在编译书籍的时候会读取书籍源码顶层目录中的 `book.js` 或者 `book.json`，这里以 `book.json` 为例，参考 [gitbook 文档](https://github.com/GitbookIO/gitbook) 可以知道，`book.js` 常用的配置如下。

  ```js
  module.exports = {
    // 书籍信息
    title: 'nju计网手册',
    description: '描述',
    isbn: 'xxxx',
    author: 'thdlrt',
    lang: 'zh-cn',
  
    // 插件列表
    plugins: [],
  
    // 插件全局配置
    pluginsConfig: {},
  
    // 模板变量
    variables: {
      // 自定义
    },
  };
  ```

### 插件

- 所有插件的命名都是以`gitbook-plugin-xxx`的形式

- 安装并添加到配置文件

  - `npm install gitbook-plugin-search-pro`

  - 

  - ```js
    {
      plugins: ['search-pro'];
    }
    ```

### 部署到github

- `gitbook build`编译为静态网页（book_文件夹）
- 对内容分离保存，全部文件（包含源码）推送到master分支
- book_内的内容push到gh-pages分支，用于部署静态网页
- 在设置中选择参数![image-20230711234259776](https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230711234259776.png)