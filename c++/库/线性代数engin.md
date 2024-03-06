- 模板类型

  - ```c++
    typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime, Options> MyMatrixType;
    typedef Array<Scalar, RowsAtCompileTime, ColsAtCompileTime, Options> MyArrayType
    ```

  - Scalar：指定元素类型，比如，float, double, bool, int 等。

  - RowsAtCompileTime：指定行数或者设置成动态（Dynamic）；

  - ColsAtCompileTime：指定列数或者设置成动态（Dynamic）；

  - Options：标志位，可以是ColMajor或RowMajor，默认是ColMajor；

  - 如`Matrix<double, 10, Dynamic>`

  - 预定义数据类型

    - ```c++
      typedef Matrix<float, Dynamic, Dynamic> MatrixXf;
      typedef Matrix<float, 3, 1> Vector3f;
      ```

  - 预设值初始化

    - ```c++
      matrix1 = Eigen::MatrixXf::Zero(3,4); //对矩阵进行初始化。
          vector1 = Eigen::Vector3f::Ones();
      ```

    - Zero是初始化为全0，而Ones是初始化为全1

- 矩阵的转置、共轭和共轭转置：

  - `transpose（） conjugate（） adjoint（）`

- 赋值

  - ```c++
    matrix1 << 1, 2,  3,  4, 
                   5, 6,  7,  8,
                   9, 10, 11, 12;
        vector1 << 1, 2, 3;
    ```

  - 