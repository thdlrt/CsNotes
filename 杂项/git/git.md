# git

## 概念

- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20230318091418872.png" alt="image-20230318091418872" style="zoom: 33%;" />
- <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231006100846612.png" alt="image-20231006100846612" style="zoom:33%;" />

## 基本配置

### 用户信息

- 设置
  - git config --global user.name "name"
  - git config --global user.email "email"

- 查看
  - git config --global user.name
  - git config --global user.email

### 命令别名

- 在用户文件夹下新建.bashrc文件，在里面输入
- alias newname='oldname'


## 本地仓库

### 获取

- 在任意位置创建一个空目录（文件夹）作为本地仓库
- 右键打开git bash
- 执行git init
- 创建成功后可以看到文件夹下隐藏的.git目录

## 基础操作

 ![](https://thdlrt.oss-cn-beijing.aliyuncs.com/20221125101245.png)

- git add 工作区->暂存区
  - git add xxx 添加单个文件可以用|来添加多个文件
  - git add . 添加全部文件
  - 在.gitignore文件中设置不需要git管理的文件
    - 可以写全名，也可以如*.a这种匹配
    - ！lib.a lib不能被忽略，要求管理
    - xxx/ 忽略一个文件夹
    - xxx/*.a 忽略文件夹中的一类文件,但不忽略子文件夹中的
    - xxx/\**/\*.a 全部忽略
    - /xxx忽略根目录下文件/文件夹
- 如过想要删除文件，处理在资源管理器删除，还需要告诉git
  - `git add -A` 命令会添加所有新的、已修改的和已删除的文件到暂存区。
  - 或git rm filename

- git commit 暂存区->本地仓库
  - git commit -m ‘注释’
- git status 检查文件状态
- 查看文件被修改的内容git diff filename
- git checkout -- filename丢弃工作区的修改
  - 回到上一次commit的状况
- git log检查仓库状态（提交记录）
  - 已配置git-log显示更直观简介
  - 也可以使用git reset HEAD filename
- git reset --hard commitID 版本回退
  - id可以通过git-log查看
  - git reflog 可以查看已经删除了的提交记录
  - 快捷回退git reset --hard HEAD\^，有几个\^回退几个
- git中选择文字就可自动复制，按鼠标中键粘贴
- git tag打标签，与commit绑定，更便于阅读
  - 因为创建的标签都只存储在本地，不会自动推送到远程。
  - 先切换到需要打tag的分支
  - `git tag v1.0`；查看`git tag`
  - 打在指定的commit`git tag v0.9 f52c633`
    - 还可以附加一些注释`git tag -a v0.1 -m "version 0.1 released" 1094adb`

  - 查看指定tag对应的分支`git show v0.9`
  - 删除`git tag -d v0.1`
    - 本地删除之后才可以远程删除`git push origin :refs/tags/v0.9`

  - 将标签推送`git push origin v1.0`
    - 全部推送`git push origin --tags`


## 分支

### 操作

- git branch 查看分支（也可以用git-log）
- gti branch xxx 新建分支
- git branch -d 删除分支（-D强制删除）
  - 切换到别的分支才能删除当前分支
- git checkout xxx 切换分支

  - git checkout -b xxx 如果分支不存在则会自动创建给i他

  - 一次只能对一个分支进行操作
  - 不同分支可能处于不同的版本
  - head->指向当前的分支
  - 创建分支，并从远端分支拉取作为初始化`git checkout -b dev origin/dev  `
- 绑定本地与远端分支`git branch --set-upstream-to=origin/dev dev`
- git merge xxx 把其它分支合并到当前的分支上 
- git rebase xxx 另一种合并分支的方法，把一个分支直接移动到另一个分支的末端，使得并行开发的任务看起来像线性先后开发的
  - 把当前分支移动到xxx目标分支上


### head指针

- 默认情况下head指针指向当前分支的最新节点
- `git checkout HEAD^`表示向上移动一个节点
  - ~n 表示向上移动n个节点
- 移动分支指向：`git brunch -f master HEAD~3`
  - 将master分支以到HEAD上3个点的位置
- 撤销提交：`git reset HEAD^1`
  - `git revert`:用于对已经上传的修改进行撤销，即创建一个与修改前内容完全相同的新分支

### 分支冲突

- 通过git status查看需要解决冲突的文件

  - ```bash
    $ git status
    On branch master
    Your branch is ahead of 'origin/master' by 2 commits.
      (use "git push" to publish your local commits)
    You have unmerged paths.
      (fix conflicts and run "git commit")
      (use "git merge --abort" to abort the merge)
    Unmerged paths:
      (use "git add <file>..." to mark resolution)
        both modified:   readme.txt
    no changes added to commit (use "git add" and/or "git commit -a")
    ```

- 比如两个分支对同一文件同一处进行了 不同修改，那么合并时就会失败

  <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/20221125111646.png" style="zoom:25%;" />

  - git 会在文件中保存两个文件的共同信息，需要手动选择，并移除<<<<<<<，\=\=\=\=\=\=\=，>>>>>>>等标记
  - 对文件修改完成，解决冲突后再次add 并commit

- 如果本地仓库已经过时，而又进行了修改：

  - 先用git pull 把最新的提交从origin/dev 抓下来，然后在本地合并解决冲突，再推送

- 命名规范

  - master线上分支（主分支）
  - develop开发分支  
  - feature新功能分支
  - hotfix修复分支（修复bug）
  - feature hotfix用后可以删除


### 分支策略

- 每个人都在dev分支上干活，每个人都有自己的分支，时不时地往dev分支上合并就可以了。
  - <img src="https://thdlrt.oss-cn-beijing.aliyuncs.com/image-20231006110652742.png" alt="image-20231006110652742" style="zoom:33%;" />
- 每个bug都可以通过一个新的临时分支来修复，修复后，合并分支，然后将临时分支删除。
  - 可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作（即先去处理bug而不是提交当前的半成品分支）
  - git stash存储当前状态
  - git stash list查看缓存列表
  - git stash apply只应用
    - 指定缓存git stash apply stash@{0}
  - git stash drop删除
  - git stash pop应用并删除缓存

## 远程仓库

### 配置 [[网络#ssh|ssh]] 公钥

- 生成  ssh-keygen -t rsa
- 获取cat ~/.ssh/id_rsa.pub
- 把公钥输入网站
- 测试连接 ssh -T git@github.com

###  推送

- 添加远程仓库 git remote add xxx（名字随便起，通常用origin） xxx(ssh地址)
- git remote 查看远程仓库

- 删除git remove 

- 推送 git push (-f强制覆盖) (--set-upstream 推送到远端并建立起和远端分支的关联关系) origin(远端名称) master(选择本地分支)(:远端分支名称(可选))

  - 如git push --set-upstream origin master:master进行绑定 

  - 如果已经关联，可以只用git push
  - 用git branch -vv可以查看绑定状态

### 获取

- 克隆: git clone ssh地址 name（不显式指出的话会自动按照仓库名称指定）
  - 会生成名称为name的文件夹
  - 第一次获取仓库使用
- 抓取：git fetch (远端名称)（分支名称）

  - 抓取指令是将仓库里的更新都抓取到本地，不进行合并。

  - 更新的是远程分支，而不是本地正在使用的分支，还要进行合并操作。
  - git merge origin/master合并。
  - 不指定分支时会抓取所有分支。
- 拉取：git pull (远端名称)（分支名称）
  - 将修改拉取到本地并自动进行合并，等同于fetch+merge

### 解决合并冲突

- 产生：A,B修改同一文件的同一处，A先修改完后push到远程仓库，而B修改后已经提交到本地仓库，由于远程库已经发生了更改，因此要先拉取远程仓库合并后再推送，在合并过程中就会发生冲突。
- 解决冲突后再add，commit即可
  - 可以直接 git commit (不-m)然后直接wq

## ide 中使用（待补充）

## [[代码规范#版本控制 |git 规范]]
## 补充

### 报错

```
  kex_exchange_identification: Connection closed by remote host
  Connection closed by 20.205.243.166 port 22
  fatal: Could not read from remote repository.
  
  Please make sure you have the correct access rights
  and the repository exists.
  
```
  - 解决：关闭代理

### Git LFS大文件存储管理

- Git LFS（Large File Storage, 大文件存储）是可以把音乐、图片、视频等指定的任意文件存在 Git 仓库之外，而在 Git 仓库中用一个占用空间 1KB 不到的文本指针来代替的小工具。

- 版本库如果要使用LFS需要在版本库中执行以下命令`git lfs install `

- 告诉gif管理哪些大文件：`git lfs track "*.psd"`

- 执行完之后，会在版本库的根目录生成一个.gitattributes 文件，里面记录了需要LFS跟踪的文件，也可以直接手动编辑这个.gitattributes 文件，将需要lfs跟踪的文件类型写入这个文件。

  - ```bash
    # text files
    *.meta text eol=lf
    ProjectSettings/*.asset text
    
    # model files
    *.fbx filter=lfs diff=lfs merge=lfs -text
    *.FBX filter=lfs diff=lfs merge=lfs -text
    *.max filter=lfs diff=lfs merge=lfs -text
    *.MAX filter=lfs diff=lfs merge=lfs -text
    *.ma filter=lfs diff=lfs merge=lfs -text
    *.mb filter=lfs diff=lfs merge=lfs -text
    *.obj filter=lfs diff=lfs merge=lfs -text
    *.OBJ filter=lfs diff=lfs merge=lfs -text
    *.spm filter=lfs diff=lfs merge=lfs -text
    
    # texture files
    *.bmp filter=lfs diff=lfs merge=lfs -text
    *.BMP filter=lfs diff=lfs merge=lfs -text
    *.psd filter=lfs diff=lfs merge=lfs -text
    *.PSD filter=lfs diff=lfs merge=lfs -text
    *.jpg filter=lfs diff=lfs merge=lfs -text
    *.JPG filter=lfs diff=lfs merge=lfs -text
    *.png filter=lfs diff=lfs merge=lfs -text
    *.PNG filter=lfs diff=lfs merge=lfs -text
    *.tga filter=lfs diff=lfs merge=lfs -text
    *.TGA filter=lfs diff=lfs merge=lfs -text
    *.tif filter=lfs diff=lfs merge=lfs -text
    *.TIF filter=lfs diff=lfs merge=lfs -text
    *.tiff filter=lfs diff=lfs merge=lfs -text
    *.ttf filter=lfs diff=lfs merge=lfs -text
    *.svg filter=lfs diff=lfs merge=lfs -text
    *.gif filter=lfs diff=lfs merge=lfs -text
    *.exr filter=lfs diff=lfs merge=lfs -text
    *.hdr filter=lfs diff=lfs merge=lfs -text
    *.renderTexture filter=lfs diff=lfs merge=lfs -text
    
    # dll files
    *.dll filter=lfs diff=lfs merge=lfs -text
    *.DLL filter=lfs diff=lfs merge=lfs -text
    *.so filter=lfs diff=lfs merge=lfs -text
    *.mdb filter=lfs diff=lfs merge=lfs -text
    *.pdb filter=lfs diff=lfs merge=lfs -text
    
    # font files
    *.ttc filter=lfs diff=lfs merge=lfs -text
    *.TTC filter=lfs diff=lfs merge=lfs -text
    *.ttf filter=lfs diff=lfs merge=lfs -text
    *.TTF filter=lfs diff=lfs merge=lfs -text
    
    # bundle files
    *.bundle filter=lfs diff=lfs merge=lfs -text
    *.zip filter=lfs diff=lfs merge=lfs -text
    
    # config files
    **/Assets/**/*.asset filter=lfs diff=lfs merge=lfs -text
    
    # doc files
    *.pdf filter=lfs diff=lfs merge=lfs -text
    *.PDF filter=lfs diff=lfs merge=lfs -text
    
    # video files
    *.mov filter=lfs diff=lfs merge=lfs -text
    *.mp4 filter=lfs diff=lfs merge=lfs -text
    *.ogv filter=lfs diff=lfs merge=lfs -text
    
    # audio files
    *.mp3 filter=lfs diff=lfs merge=lfs -text
    *.wav filter=lfs diff=lfs merge=lfs -text
    *.ogg filter=lfs diff=lfs merge=lfs -text
    ```

- 常用命令

  - ```bash
    # 查看当前使用 Git LFS 管理的匹配列表
    git lfs track
    
    # 使用 Git LFS 管理指定的文件
    git lfs track "*.psd"
    
    # 不再使用 Git LFS 管理指定的文件
    git lfs untrack "*.psd"
    
    # 类似 `git status`，查看当前 Git LFS 对象的状态
    git lfs status
    
    # 枚举目前所有被 Git LFS 管理的具体文件
    git lfs ls-files
    
    # 检查当前所用 Git LFS 的版本
    git lfs version
    
    # 针对使用了 LFS 的仓库进行了特别优化的 clone 命令，显著提升获取
    # LFS 对象的速度，接受和 `git clone` 一样的参数。 [1] [2]
    ```

## 配置文件



### gitignore编写

#### Git忽略文件的原则

- 忽略操作系统自动生成的文件，比如缩略图等；
- 忽略编译生成的中间文件、可执行文件等，也就是如果一个文件是通过另一个文件自动生成的，那自动生成的文件就没必要放进版本库，比如产生的.log日志文件；
- 忽略你自己的带有敏感信息的配置文件，比如存放口令的配置文件。

#### 基本语法

- 可能需要手动创建.gitignore文件

- ```gitignore
  # dir 不需要提交的目录
  /node_modules
  
  # file 不需要提交的文件
  config.ini
  
  # log 不需要提交的任意包含后缀名为log的文件
  *.log
  
  # Package Files 不需要提交的任意包含后缀名为jar的文件
  *.jar
  ```

- **强制添加**被忽略的文件`git add -f node_modules/jquery/dist/jquery.min.js`

  - `git check-ignore -v Table.unitypackage`查看被忽略的文件和对应的规则

- 规则

  - 空格不匹配任意文件，可作为分隔符，可用反斜杠转义
  - 以“＃”开头的行都会被 Git 忽略。即#开头的文件标识注释，可以使用反斜杠进行转义。
  - 可以使用标准的glob模式匹配。所谓的glob模式是指shell所使用的简化了的正则表达式。
  - 以斜杠"/"开头表示目录；"/"结束的模式只匹配文件夹以及在该文件夹路径下的内容，但是不匹配该文件；"/"开始的模式匹配项目跟目录；如果一个模式不包含斜杠，则它匹配相对于当前 .gitignore 文件路径的内容，如果该模式不在 .gitignore 文件中，则相对于项目根目录。
  - 以星号"*"通配多个字符，即匹配多个任意字符；使用两个星号"\*\*" 表示匹配任意中间目录，比如a/**/z可以匹配 a/z, a/b/z 或 a/b/c/z等。
  - 以问号"?"通配单个字符，即匹配一个任意字符；
  - 以方括号"[]"包含单个字符的匹配列表，即匹配任何一个列在方括号中的字符。比如[abc]表示要么匹配一个a，要么匹配一个b，要么匹配一个c；如果在方括号中使用短划线分隔两个字符，表示所有在这两个字符范围内的都可以匹配。比如[0-9]表示匹配所有0到9的数字，[a-z]表示匹配任意的小写字母）。
  - 以叹号"!"表示不忽略(跟踪)匹配到的文件或目录，即要忽略指定模式以外的文件或目录，可以在模式前加上惊叹号（!）取反。需要特别注意的是：如果文件的父目录已经被前面的规则排除掉了，那么对这个文件用"!"规则是不起作用的。也就是说"!"开头的模式表示否定，该文件将会再次被包含，如果排除了该文件的父级目录，则使用"!"也不会再次被包含。可以使用反斜杠进行转义。

- 如果你不慎在创建.gitignore文件**之前**就push了项目，那么即使你在.gitignore文件中写入新的过滤规则，这些规则也不会起作用，Git仍然会对所有文件进行版本管理。

- 补充

  - ```gitignore
    #               表示此为注释,将被Git忽略
    *.a             表示忽略所有 .a 结尾的文件
    !lib.a          表示但lib.a除外
    /TODO           表示仅仅忽略项目根目录下的 TODO 文件，不包括 subdir/TODO
    build/          表示忽略 build/目录下的所有文件，过滤整个build文件夹；
    doc/*.txt       表示会忽略doc/notes.txt但不包括 doc/server/arch.txt
     
    bin/:           表示忽略当前路径下的bin文件夹，该文件夹下的所有内容都会被忽略，不忽略 bin 文件
    /bin:           表示忽略根目录下的bin文件
    /*.c:           表示忽略cat.c，不忽略 build/cat.c
    debug/*.obj:    表示忽略debug/io.obj，不忽略 debug/common/io.obj和tools/debug/io.obj
    **/foo:         表示忽略/foo,a/foo,a/b/foo等
    a/**/b:         表示忽略a/b, a/x/b,a/x/y/b等
    !/bin/run.sh    表示不忽略bin目录下的run.sh文件
    *.log:          表示忽略所有 .log 文件
    config.php:     表示忽略当前路径的 config.php 文件
     
    /mtk/           表示过滤整个文件夹
    *.zip           表示过滤所有.zip文件
    /mtk/do.c       表示过滤某个具体文件
     
    被过滤掉的文件就不会出现在git仓库中（gitlab或github）了，当然本地库中还有，只是push的时候不会上传。
     
    需要注意的是，gitignore还可以指定要将哪些文件添加到版本管理中，如下：
    !*.zip
    !/mtk/one.txt
     
    唯一的区别就是规则开头多了一个感叹号，Git会将满足这类规则的文件添加到版本管理中。为什么要有两种规则呢？
    想象一个场景：假如我们只需要管理/mtk/目录中的one.txt文件，这个目录中的其他文件都不需要管理，那么.gitignore规则应写为：：
    /mtk/*
    !/mtk/one.txt
     
    假设我们只有过滤规则，而没有添加规则，那么我们就需要把/mtk/目录下除了one.txt以外的所有文件都写出来！
    注意上面的/mtk/*不能写为/mtk/，否则父目录被前面的规则排除掉了，one.txt文件虽然加了!过滤规则，也不会生效！
     
    ----------------------------------------------------------------------------------
    还有一些规则如下：
    fd1/*
    说明：忽略目录 fd1 下的全部内容；注意，不管是根目录下的 /fd1/ 目录，还是某个子目录 /child/fd1/ 目录，都会被忽略；
     
    /fd1/*
    说明：忽略根目录下的 /fd1/ 目录的全部内容；
     
    /*
    !.gitignore
    !/fw/ 
    /fw/*
    !/fw/bin/
    !/fw/sf/
    说明：忽略全部内容，但是不忽略 .gitignore 文件、根目录下的 /fw/bin/ 和 /fw/sf/ 目录；注意要先对bin/的父目录使用!规则，使其不被排除。
    ```
