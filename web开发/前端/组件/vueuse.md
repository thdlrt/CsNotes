### 常用函数

- 监听组件（窗口）大小变化

  - ```js
        useResizeObserver(el, (entries) => {
          const entry = entries[0]
          const { width, height } = entry.contentRect
          text.value = `width: ${width}, height: ${height}`
        })
    ```

  - el为用ref绑定要监听的元素