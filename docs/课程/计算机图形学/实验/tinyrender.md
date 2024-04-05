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
