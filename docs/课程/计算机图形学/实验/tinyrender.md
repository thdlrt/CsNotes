### 1-线条绘制（DDA）
```cpp
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	int dx = abs(x1-x0),dy=abs(y1-y0);
	if(dx>dy){
		if(x0>x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		for (int x=x0; x<=x1; x++) {
			float t = (x-x0)/(float)(x1-x0);
			int y = y0*(1.-t) + y1*t;
			image.set(x, y, color);
		}
	}
	else{
		if(y0>y1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		for (int y=y0; y<=y1; y++) {
			float t = (y-y0)/(float)(y1-y0);
			int x = x0*(1.-t) + x1*t;
			image.set(x, y, color);
		}
	}
}
```
- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406002841.png)
- obj 格式
	- `v 0.608654 -0.568839 -0.416318` 表示点的坐标
	- `f 1193/1240/1193 1180/1227/1180 1179/1226/1179` 表示三角形（1193,1180, 1179 三个点组成）

### 2-三角形光栅化
- 扫描线方法：逐行扫描
	- 缺点：单线程老方法
```cpp
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
	std::vector<Vec2i> points={t0,t1,t2};
	sort(points.begin(),points.end(),[](Vec2i a,Vec2i b){return a.y<b.y;});
	for(int i=points[0].y;i<=points[1].y;i++)
	{
		int left=points[0].x+(points[1].x-points[0].x)*(i-points[0].y)/(points[1].y-points[0].y);
		int right=points[0].x+(points[2].x-points[0].x)*(i-points[0].y)/(points[2].y-points[0].y);
		if(left>right)std::swap(left,right);
		for(int j=left;j<=right;j++)
		{
			image.set(j,i,color);
		}
	}
	for(int i=points[1].y+1;i<=points[2].y;i++)
	{
		int left=points[1].x+(points[2].x-points[1].x)*(i-points[1].y)/(points[2].y-points[1].y);
		int right=points[0].x+(points[2].x-points[0].x)*(i-points[0].y)/(points[2].y-points[0].y);
		if(left>right)std::swap(left,right);
		for(int j=left;j<=right;j++)
		{
			image.set(j,i,color);
		}
	}
}
```
- 包围盒算法，判断点是否在三角形内部
	- 这里使用质心坐标法（而不是通过叉积进行判断）
	-  $P=(1-u-v)A+uB+vC$ (对于三角形**内**的点 u, v, 1-u-v **均大于 0**)
	- $P=A+uAB+vAC\to uAB+vAC+PA=0$
	- ![image.png|271](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406013702.png)
	- 本质上就是求解这个方程组（之后得到 uv 判断是否大于零，进而判断是否在三角形内部）
	- 求解方程就是找一条直线与(ABx,ACx,PAx) and (ABy,ACy,PAy)垂直，这可以通过**一次叉积解决**
```cpp

```
