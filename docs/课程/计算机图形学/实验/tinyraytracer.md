### 基本框架搭建
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
- 检测发出涉嫌是否打到球体，并且可能存在多个球体
```cpp
bool intersect(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres, Vec3f &hit_p, Vec3f &normal, Material &material) {  
    float spheres_dist = std::numeric_limits<float>::max();  
    for (size_t i=0; i<spheres.size(); i++) {  
        float dist_i;  
        //击中更近的球体  
        if (spheres[i].ray_intersect(orig, dir, dist_i) && dist_i < spheres_dist) {  
            spheres_dist = dist_i;  
            hit_p = orig + dir*dist_i;  
            normal = (hit_p - spheres[i].center).normalize();  
            material = spheres[i].material;  
        }  
    }  
    return spheres_dist<1000;  
}  
Vec3f cast_ray(const Vec3f &orig, const Vec3f &dir, const std::vector<Sphere> &spheres) {  
    Vec3f hit_p, normal;  
    Material material;  
    if (!intersect(orig, dir, spheres, hit_p, normal, material)) {  
        return backgroud.color;  
    }  
    return material.color;  
}
```
- 对一个方向发射线条之后，检测所有球体，寻找最近的碰撞点作为结果，并记录材质，坐标以及法线等信息
### 灯光与反射
- 一个简单的思路，将像**素点与光源的连线**，以及**像素点的法线比较**，计算光照强度。(类似布林冯里的漫反射强度影响因素之一)
```cpp

```
- 镜面反射

