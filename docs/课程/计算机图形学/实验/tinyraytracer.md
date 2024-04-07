- 球体类型
	- `ray_interset` 用于判断球与源点为 orig 方向为 dir 的光线是否相交，如果相交距离是多少
```cpp
struct Sphere {
    Vec3f center;
    float radius;

    Sphere(const Vec3f &c, const float &r) : center(c), radius(r) {}
    /*@param orig: origin of the ray
      @param dir: direction of the ray
      @param t0: distance from the origin to the first intersection point*/
    bool ray_intersect(const Vec3f &orig, const Vec3f &dir, float &t0) const {
        Vec3f L = center - orig;
        float tca = L*dir;
        float d2 = L*L - tca*tca;
        if (d2 > radius*radius) return false;
        float thc = sqrtf(radius*radius - d2);
        t0       = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
};
```
- 光线追踪的基本形式
	- ![image.png|500](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240407153133.png)
- 光线追踪**发射光线**的基本实现
```cpp
for (int j = 0; j<height; j++) {
        for (int i = 0; i<width; i++) {
            float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
            float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            framebuffer[i+j*width] = cast_ray(Vec3f(0,0,0), dir, sphere);
        }
    }
```
- 默认相机位于 （0,0,0）屏幕位于（0,0,-1），向 **-z** 方向看
- `float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;`
	- 先将屏幕空间投影到 (-1,1)上的标准空间，之后根据视角映射到真实坐标（默认这个间距是 1，因此直接乘以 tan(FOV/2)）
	- 即将像素点映射到了真实的空间坐标
	- ![image.png|425](https://thdlrt.oss-cn-beijing.aliyuncs.com/20240407160626.png)
- 