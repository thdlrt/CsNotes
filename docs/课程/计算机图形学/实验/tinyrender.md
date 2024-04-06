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
	- 本质上就是求解这个方程组（之后得到 uv 判断是否大于零，进而判断是否在三角形内部）对于三维点也是一样的，因为两个方程就能解出两个量了
	- 求解方程就是找一条直线与(ABx,ACx,PAx) and (ABy,ACy,PAy)垂直，这可以通过**一次叉积解决**
```cpp
//求三角形的重心坐标  
Vec3f barycentric(Vec2i *pts, Vec2i P) {  
    Vec3f u = Vec3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0]) ^ Vec3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]);  
    if (std::abs(u.z)<1) return Vec3f(-1,1,1);  
    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);  
}  
//包围盒绘制三角形  
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {  
    int minx = std::max(0,std::min(t0.x, std::min(t1.x, t2.x)));  
    int maxx = std::min(image.get_width()-1,std::max(t0.x, std::max(t1.x, t2.x)));  
    int miny = std::max(0,std::min(t0.y, std::min(t1.y, t2.y)));  
    int maxy = std::min(image.get_height()-1,std::max(t0.y, std::max(t1.y, t2.y)));  
    for(int i=minx;i<=maxx;i++){  
       for(int j=miny;j<=maxy;j++){  
          Vec3f bc_screen = barycentric(&t0, Vec2i(i,j));  
          if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;  
          image.set(i, j, color);  
       }  
    }  
}
```
- 稍作修改可以得到 3 f 版本
### 3-深度缓冲
```cpp
//zBuffer单例类
class zBuffer {
private:
    zBuffer(int width, int height) {
        this->width = width;
        this->height = height;
        buffer = new float[width*height];
        for(int i=0;i<width*height;i++){
            buffer[i] = -std::numeric_limits<float>::max();
        }
    }
    ~zBuffer() {
        delete [] buffer;
    }
public:
    int width, height;
    float *buffer;
    static zBuffer* getInstance(int width, int height) {
        static zBuffer instance(width, height);
        return &instance;
    }
    bool test(int x, int y, float z) {
        if(x<0||x>=width||y<0||y>=height) return false;
        if(z>buffer[y*width+x]) {
            buffer[y*width+x] = z;
            return true;
        }
        return false;
    }
};
```
### 4-投影
- 正交投影就是从-1~1 的立方体映射到二维平面上
```cpp
Vec3f world2screen(Vec3f v) {
	return Vec3f(int((v.x+1.)*width/2.+.5), int((v.y+1.)*height/2.+.5), v.z);
}
```
- 透视投影（另一种透视思路，不是压缩透视为正交）
	- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406115705.png)
	- 左下角区域可以进行一种 `透视` 操作
	- ![image.png](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406115734.png)
- 因此，可以定义一种新的操作：透视
	- ![image.png|475](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406115956.png)
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240406120858.png)
- 

