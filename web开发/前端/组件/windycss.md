### 概述

- 使用class代替生成style样式
- 属性设置语法`属性-值`
  - 如`h-[1px] w-16`


## 常用属性

### 布局

- 居中
  - `items-center justify-center`
  - 响应式布局`<el-col :lg="16" :md="12">`
    - 不同屏幕宽度不同比例 

- flex
  - `flex`
  - 横向间距`space-x-2`

### @apply抽离

- 将一组class抽离到style中

- ```vue
  .login-container {
      @apply min-h-screen bg-blue-400 relative;
  }
  ```

- 