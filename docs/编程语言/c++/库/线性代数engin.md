### 矩阵得定义与初始化
- 模板类型
```c++
    typedef Matrix<Scalar, RowsAtCompileTime, ColsAtCompileTime, Options> MyMatrixType;
    typedef Array<Scalar, RowsAtCompileTime, ColsAtCompileTime, Options> MyArrayType
```
- Scalar：指定元素类型，比如，float, double, bool, int 等。
- ColsAtCompileTime：指定列数或者设置成动态（Dynamic）；
- Options：标志位，可以是ColMajor或RowMajor，默认是ColMajor；
- 如`Matrix<double, 10, Dynamic>`
- RowsAtCompileTime：指定行数或者设置成动态（Dynamic）；
```c++
      typedef Matrix<float, Dynamic, Dynamic> MatrixXf;
      typedef Matrix<float, 3, 1> Vector3f;
```
- 预定义数据类型
  - `Eigen::Matrix3d` 3x3的双精度浮点矩阵
  - `Eigen::Matrix4f` 4x4的单精度浮点单位矩阵
-   预设值初始化
```c++
      matrix1 = Eigen::MatrixXf::Zero(3,4); //创建动态大小的矩阵（这里是3*4）
      vector1 = Eigen::Vector3f::Ones();
      matDyn = Eigen::MatrixXd::Random(10,10);
```
- Zero 是初始化为全0，而 Ones 是初始化为全1
	- `Identity(4,4);` 单位矩阵初始化
	- `Constant(3,3, 1.23);`所有元素初始化为同一个常数

- 赋值
```c++
    matrix1 << 1, 2,  3,  4, 
                   5, 6,  7,  8,
                   9, 10, 11, 12;
        vector1 << 1, 2, 3;
```
#### 向量
- 常用的向量类型，如 `Vector3f`
### 矩阵运算
- 重载了常见的运算符，如+-\*\/，支持矩阵之间、矩阵与标量的运算
	- 向量运算 `vec1.dot(vec2); vec1.cross(vec2);`
- `.transpose()` 矩阵转置
- `.conjugate()` 矩阵共轭
- `.inverse()` 矩阵逆
- `.eigenvalues();` 特征值；`.eigenvectors();` 特征向量