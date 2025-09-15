### 基础组件

#### layout布局

- 将页面分为24列

#### 表单

- 插槽在前后添加图标

- ```html
  <el-form :model="form" :rules="rules" ref="formRef" label-width="90px" >
              <el-form-item prop="oldpassword" label="旧密码" >
                  <el-input type="password" v-model="form.oldpassword" placeholder="请输入旧密码">
                  </el-input>
              </el-form-item>
              <el-form-item prop="password" label="新密码">
                  <el-input type="password" v-model="form.password" placeholder="请输入新密码">
                  </el-input>
              </el-form-item>
              <el-form-item prop="repassword" label="确认密码">
                  <el-input type="password" v-model="form.repassword" placeholder="请再次输入密码" show-password>
                  </el-input>
              </el-form-item>
              <!-- 按钮 -->
              <el-form-item>
                  <el-button :round="true" type="primary" @click="onSubmit"  class="bg-blue-400 w-[120px]" :loading="loading">确定</el-button>
                  <el-button :round="true" @click="onCancel" class="w-[118px]" :loading="loading">取消</el-button>
              </el-form-item>
          </el-form>
  ```

-  `:model="form"`用于绑定双向同步数据

  - ```js
    const form = reactive({
        oldpassword: '',
        password: '',
        repassword: '',
    })
    ```

- `:rules="rules"`绑定规则

  - ```javascript
    const rules = {
        oldpassword: [
            { required: true, message: '旧密码不能为空', trigger: 'blur' },
        ],
        password: [
            { required: true, message: '新密码不能为空', trigger: 'blur' },
        ],
        repassword: [
            { required: true, message: '请重新输入密码', trigger: 'blur' },
        ]
    }
    ```

- `ref="formRef"`获取表单对象

- ```js
  const onSubmit = () => {
      formRef.value.validate((valid) => {
          if (valid) {
              
          } else {
              return false
          }
      })
  }
  ```

- `el-form-item prop="oldpassword" label="旧密码" >`

  - prop用于给表项命名，可以用于绑定rule（prop名称要与绑定的变量名称相同）

- `<el-input type="password" v-model="form.oldpassword" placeholder="请输入旧密码">`

  - 指定表单输入进行绑定


#### 杂项

- result结果：可以用于制作反馈信息/404等

