START
问答题
正面: 如何配置clone
背面: - 需要将想要克隆的子类中将 `clone()` 方法重写为 public
- 实现 Cloneable 接口
- 由于 clone 可能不能使用，因此调用时要 trycatch
``` java
@Override public OceanReading clone() {
    OceanReading or = null;
    try {
        or =(OceanReading)super.clone();
    } catch(CloneNotSupportedException e) {
        throw new RuntimeException(e);
    }
    // 克隆并重新绑定引用
    or.depth = (DepthReading)or.depth.clone();
    or.temperature =(TemperatureReading)or.temperature.clone();
    return or;
}
```
<!--ID: 1709657368560-->
END