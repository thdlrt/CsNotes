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
- 