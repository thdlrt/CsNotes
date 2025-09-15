# [PostMan中文文档](https://postman.org.cn/)

## 发送请求（测试后端）

### 发送参数

- 参数：通过在 URL 中添加查询参数来传递数据。查询参数通常用于传递简单的数据，如字符串或数字等。例如，在 URL 中添加 `?name=John&age=30` 就是传递了两个查询参数。
- body 属性：通过在请求体中添加数据来传递更复杂的数据，如 JSON、XML、form-data 等。这种方式通常用于传递结构化的数据或文件等。在 Postman 中，可以使用不同的 body 类型来发送不同格式的数据。

### 变量

- 选择Postman 右上角的**Environment quick look 。** ![外部链接图标](https://thdlrt.oss-cn-beijing.aliyuncs.com/eye.jpg)
  - 也可以直接选中文件来进行设置
- 便于在多个地方使用相同的值
- 使用`{{变量名}}`

#### 动态变量

- 使用[faker 库](https://www.npmjs.com/package/@faker-js/faker)来生成样本数据，包括随机姓名、地址、电子邮件地址等等。您可以多次使用这些预定义变量来为每个请求返回不同的值
  - 如`$randomIP`等等

#### 环境变量

- 环境变量只能在激活指定环境时使用
- 如对模拟服务器使用`{{url}}/api/user/login`

## 模拟服务器（测试前端）

- 模拟服务器依赖于保存在集合中的[示例](https://postman.org.cn/sending-requests/examples/)来返回模拟数据。
- 使用服务器的地址加上后缀进行访问`https://b9118b5d-3ca9-48d2-aabf-cc7a77901b86.mock.pstmn.io`+`/api.user/login`