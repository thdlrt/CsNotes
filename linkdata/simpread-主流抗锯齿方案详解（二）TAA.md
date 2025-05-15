> 本文由 [简悦 SimpRead](http://ksria.com/simpread/) 转码， 原文地址 [zhuanlan.zhihu.com](https://zhuanlan.zhihu.com/p/425233743) [抗锯齿示例代码](https://link.zhihu.com/?target=https%3A//github.com/Raphael2048/AntiAliasing)

一、TAA 的原理
---------

前面我们讲过，[MSAA](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=MSAA&zhida_source=entity) 是通过添加次像素点，来实现抗锯齿效果，需要消耗额外的内存。

TAA 的原理和 [SSAA](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=SSAA&zhida_source=entity) 大致相同，都是每个像素点有多个采样点。但是不同与 SSAA 的方式，**TAA (Temporal Anti-Aliasing)** 综合历史帧的数据来实现抗锯齿，这样会将每个像素点的多次采样均摊到多个帧中，相对的开销要小得多。

### 1. 静态场景

首先来看处理静态场景的情况。在前面讲到 MSAA 时我们知道，实现抗锯齿要在一个像素中的多个位置进行采样。在 MSAA 中，我们在一帧中，在每个像素中放置了多个次像素采样点。在 TAA 中，我们实现的方式，就是在每帧采样时，将采样的点进行偏移，实现**抖动 (jitter)**。

采样点抖动的偏移，是和 MSAA 的次像素采样点放置是相同的，都需要使用低差异的采样序列，来实现更好的抗锯齿效果。TAA 中都会直接使用 [Halton 序列](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=Halton+%E5%BA%8F%E5%88%97&zhida_source=entity)，采样的点位置如下所示：

![](https://pic1.zhimg.com/v2-7585c87dde80b1f19b908d8c74724cfc_r.jpg)

要对采样点进行偏移，我们只需要稍微修改下我们的透视投影矩阵。这部分比较简单，只需要将偏移的 XY 分量分别写入到投影矩阵的 [2, 0] 和 [2, 1] 即可。这样，当左边的向量值乘以新的投影矩阵时，最终得到裁剪空间的坐标也会相应偏移。稍微需要注意下的就是需要将偏移的值转化到裁剪空间中。

![](https://pic4.zhimg.com/v2-143d0f5393f5c7b9d9b18eeba2ce66eb_r.jpg)

体现在代码中，这一步大致是这样的：

```
// 先将Halton序列的值转化为 -0.5~0.5范围的偏移；再除以屏幕长度，得到UV下的偏移值；最后乘以2，是转化到裁剪空间中的偏移值
ProjectionMatrix.m02 += (HaltonSequence[Index].x - 0.5f) / ScreenWidth * 2;
ProjectionMatrix.m12 += (HaltonSequence[Index].y - 0.5f) / ScreenHeight * 2;
```

接下来就是对历史的帧进行混合了，首先我们要确定 TAA 在图形管线中的位置，从结果上来看，如果使用 HDR 颜色作为输入，得到的抗锯齿效果不佳。所以需要把 TAA 放到 [Tonemapping](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=Tonemapping&zhida_source=entity) 之后。但是这样又会影响后续需要 HDR 的 Bloom 等特效的计算。因此我们需要先进行一次 Tonemapping，进行 TAA 后再将 Tonemapping 还原，然后处理需要 HDR 颜色输入的后处理，最终再进行一次 Tonemapping 计算。第一次的 Tonemapping 使用比较简单的 [Reinhard Tonemapping](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=Reinhard+Tonemapping&zhida_source=entity) 算法即可。这里的处理方式和前面我们讲过的 HDR 下 MSAA 的处理方式是一样的。

![](https://pica.zhimg.com/v2-c4ccc37c5541f7a7fe166bc7fafc36b8_r.jpg)

为了计算方便，我们不会将很多个历史帧保留下来做混合，而是直接使用当前帧的结果和上一帧得到的历史结果做混合。混合的方式，就是简单地使用百分比混合，即将历史帧数据，和当前帧数据进行 lerp。

```
float3 currColor = currBuffer.Load(pos);
float3 historyColor = historyBuffer.Load(pos);
return lerp(historyColor, currColor, 0.05f);
```

这里的取混合系数为 0.05，意味着最新的一帧渲染结果，只对最终结果产生了 5% 的贡献。

将累计的过程展开来看的话，可以看出当前帧 TAA 后的结果，是包含了所有的历史帧结果的，说明这种方式是合理的：

$$s_t = \alpha x_t + (1-\alpha)s_{t-1} = \alpha \sum_{k=0}^{\infty} (1-\alpha)^k x_{k-t}\\$$

s_t = \alpha x_t + (1-\alpha)s_{t-1} = \alpha \sum_{k=0}^{\infty} (1-\alpha)^k x_{k-t}\\

下图显示了 TAA 历史帧周期和混合系数，相对应的每像素超采样个数。例如当取混合系数 alpha = 0.1，混合周期 N = 5 时，相当于每个像素点进行了 2.2 个超采样， 混合周期 N = 10 时，相当于每个像素点进行了 5.1 次超采样。

![](https://pica.zhimg.com/v2-8d8a5aa106b1145ac7398723f7f01906_r.jpg)

到这里我们已经实现了静态场景和静态镜头的 TAA，下面就要开始考虑动态的部分了。

### 2. 重投影

首先要考虑的是镜头的移动，镜头移动后，原来投射到某个像素上的物体，现在很可能不在原来的位置上了。假设物体是不动的，我们就可以使用当前帧的深度信息，反算出世界坐标，使用上一帧的投影矩阵，在混合计算时做一次重投影 **Reprojection / 重投影**。

![](https://pic1.zhimg.com/v2-b68e86d6db5205544484fe1a6b910da0_r.jpg)

不过重投影只能适用于静态的物体，如果物体是移动的，我们就无法精确还原物体上一帧的投影位置了。

### 3. 动态物体

物体本身的移动比较复杂，包含了平移旋转缩放。再加上摄影机本身的移动，直接在混合时进行计算的话，计算起来非常困难。

要对历史数据进行混合，就要能够还原出当前物体在屏幕中投影的位置。为了能够精确地记录物体在屏幕空间中的移动，我们使用 **[Motion Vector](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=Motion+Vector&zhida_source=entity)** 贴图来记录物体在屏幕空间中的变化距离，表示当前帧和上一帧中，物体在屏幕空间投影坐标的变化值。因为 Motion Vector 的精度要求比较高，因此用 RG16 格式来存储。Motion Vector 可以作为延迟渲染的 GBuffer 的一部分，除了用了实现 TAA，还可以实现移动模糊 / Motion Blur 等效果。

在渲染物体时，我们需要用到上一帧的投影矩阵和上一帧该物体的位置信息，这样可以得到当前帧和上一帧的位置差，并写入到 Motion Vector。对于带蒙皮动画的物体，我们同时需要上一帧的骨骼的位置，来计算处上一帧中投影到的位置。计算上一帧位置和当前帧位置的方法是一样的，都是从 VS 中输出裁剪空间的齐次坐标，在 PS 中读取，然后就可以做差求得 Motion 值。为了使 Motion 的值比较精确，我们在计算 Motion 时，**不会**添加抖动。

另外一个需要考虑的地方是一些基于 UV 变化的动画效果，需要将偏移值转化为屏幕空间中的偏移。

还有就是平面反射的效果，需要小心翼翼地推导出反射时使用的矩阵和抖动，反射的位置信息等，这里的原理并不复杂，但是计算起来会非常麻烦。

![](https://pic4.zhimg.com/v2-efdfdc01553118b53699a638ba370905_r.jpg)

尽管理论上来说，所有的物体都应该有 Motion Vector 信息，但是有些物体却无法做到，比如：

*   带有复杂贴图动画的物体，粒子烟雾、水流等；
*   半透明物体，因为 Motion Vector 只有一层，因此无法写入。

不过因为这些物体往往都是很薄的一层，且都是很快消失的，因此抖动产生的误差比较不容易注意到，因此一般也不需要去特殊处理。

### 4. 使用 Motion Vector

接下来就是使用 Motion Vector 进行混合计算了，我们需要使用 Motion Vector 算出上一帧物体在屏幕空间中投射的坐标。在计算之前，我们先要移除当前像素采样的抖动偏移值，然后减去采样 Motion Vector 得到的 Motion 值，就可以算出上一帧中投影坐标的位置。然后就可以根据位置对历史数据进行采样了，因为我们得到的坐标往往不是正好在像素中心位置，因此这里使用双线性模式进行采样。

```
// 减去抖动坐标值，得到当前实际的像素中心UV值
uv -= _Jitter;
// 减去Motion值，算出上帧的投影坐标
float2 uvLast = uv - motionVectorBuffer.Sample(point, uv);
//使用双线性模式采样
float3 historyColor = historyBuffer.Sample(linear, uvLast);
```

当镜头的移动时，可能会导致物体的遮挡关系发生变化，比如一个远处的物体原来被前面的物体遮挡住，现在因为镜头移动而忽然出现，这时采样 Motion 偏移得到的位置，上帧中其实是没有渲染的数据的。因此为了得到更加平滑的数据，可以在当前像素点周围判断深度，取距离镜头最近的点位置，来采样 Motion Vector 的值，这样可以减弱遮挡错误的影响。

这一步的计算过程大致如下：

```
float2 GetClosestFragment(float2 uv)
{
    float2 k = _CameraDepthTexture_TexelSize.xy;
    //在上下左右四个点
    const float4 neighborhood = float4(
        SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, sampler_PointClamp, clamp(uv - k)),
        SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, sampler_PointClamp, clamp(uv + float2(k.x, -k.y))),
        SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, sampler_PointClamp, clamp(uv + float2(-k.x, k.y))),
        SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, sampler_PointClamp, clamp(uv + k))
    );
    // 获取离相机最近的点
    #if defined(UNITY_REVERSED_Z)
        #define COMPARE_DEPTH(a, b) step(b, a)
    #else
        #define COMPARE_DEPTH(a, b) step(a, b)
    #endif
    // 获取离相机最近的点，这里使用 lerp 是避免在shader中写分支判断
    float3 result = float3(0.0, 0.0, SAMPLE_DEPTH_TEXTURE(_CameraDepthTexture, sampler_PointClamp, uv));
    result = lerp(result, float3(-1.0, -1.0, neighborhood.x), COMPARE_DEPTH(neighborhood.x, result.z));
    result = lerp(result, float3( 1.0, -1.0, neighborhood.y), COMPARE_DEPTH(neighborhood.y, result.z));
    result = lerp(result, float3(-1.0,  1.0, neighborhood.z), COMPARE_DEPTH(neighborhood.z, result.z));
    result = lerp(result, float3( 1.0,  1.0, neighborhood.w), COMPARE_DEPTH(neighborhood.w, result.z));
    return (uv + result.xy * k);
}

//在周围像素中，寻找离相机最近的点
float2 closest = GetClosestFragment(uv);
//使用周围最近点，得到Velocity值，来计算上帧投影位置
float2 uvLast = uv - motionVectorBuffer.Sample(point, closest);
//...
```

这里的计算，是寻找周围 5 个像素点的最近点。如果想要更好的效果，可以将 周围 5 个点改成 9 个点。

因为使用了双线性采样，所以得到的值会混合周围像素的颜色，造成结果略微模糊。如果想要使得到的历史结果质量更好，也可以使用一些特殊的过滤方式进行处理。比如 UE4 中使用 Catmull–Rom 的方式进行锐化过滤。Catmull-Rom 方式的采样，会在目标点周围进行 5 次采样，然后根据相应权重进行过滤混合，额外的开销也非常大。

![](https://pic2.zhimg.com/v2-b1d1d38eca21e4794dea6f100b36a747_r.jpg)

### 5. 对历史结果进行处理

由于像素抖动，模型变化，渲染光照变化导致渲染结果发生变化时，会导致历史帧得到的像素值失效，就会产生 **鬼影 / ghosting** 和 **闪烁 /flicking** 问题。

![](https://pic4.zhimg.com/v2-6fce51deace9ef886f4077b610a74601_r.jpg)

为了缓解鬼影和闪烁的问题，我们还要对采样的历史帧和当前帧数据进行对比，将历史帧数据 **clamp / 截断** 在合理的范围内。

要确定当前帧目标像素的亮度范围，就需要读取当前帧数据目标像素周围 5 个或者 9 个像素点的颜色范围：

![](https://picx.zhimg.com/v2-9b19fd5c60b7a80d84a5cd63236d8c83_1440w.jpg)

比如现在要使用周围 9 个点像素作为 clamp 范围，AABBMin 和 AABBMax 形成了一个 AABB 的范围区域，为了使计算的结果更加准确，我们这里把色彩先转换到 YCgCo 色彩空间内。

简单的做法就是直接进行 clamp：

```
float3 AABBMin, AABBMax;
AABBMax = AABBMin = RGBToYCoCg(Color);
// 取得YCoCg色彩空间下，Clip的范围
for(int k = 0; k < 9; k++)
{
    float3 C = RGBToYCoCg(_MainTex.Sample(sampler_PointClamp, uv, kOffsets3x3[k]));
    AABBMin = min(AABBMin, C);
    AABBMax = max(AABBMax, C);
}
// 需要 Clip处理的历史数据
float3 HistoryYCoCg = RGBToYCoCg(HistoryColor);

// 简单地进行Clmap
float3 ResultYCoCg =  clmap(History, AABBMin, AABBMax);
//还原到RGB色彩空间，得到最终结果
HistoryColor.rgb = YCoCgToRGB(ResultYCoCg));
```

另外一种做法是进行 clip，clip 的效果会更好，计算量也会相对较大二者的差别可从下图看出：

![](https://pic2.zhimg.com/v2-54b001f4bf178d72cfe9fc4bd437ea57_1440w.jpg)

```
float3 AABBMin, AABBMax;
AABBMax = AABBMin = RGBToYCoCg(Color);
// 取得YCoCg色彩空间下，Clip的范围
for(int k = 0; k < 9; k++)
{
    float3 C = RGBToYCoCg(_MainTex.Sample(sampler_PointClamp, uv, kOffsets3x3[k]));
    AABBMin = min(AABBMin, C);
    AABBMax = max(AABBMax, C);
}
// 需要 Clip处理的历史数据
float3 HistoryYCoCg = RGBToYCoCg(HistoryColor);

// 下面是clip计算的过程
float3 Filtered = (AABBMin + AABBMax) * 0.5f;
float3 RayOrigin = History;
float3 RayDir = Filtered - History;
RayDir = abs( RayDir ) < (1.0/65536.0) ? (1.0/65536.0) : RayDir;
float3 InvRayDir = rcp( RayDir );

// 获取和Box相交的位置
float3 MinIntersect = (AABBMin - RayOrigin) * InvRayDir;
float3 MaxIntersect = (AABBMax - RayOrigin) * InvRayDir;
float3 EnterIntersect = min( MinIntersect, MaxIntersect );
float ClipBlend = max( EnterIntersect.x, max(EnterIntersect.y, EnterIntersect.z ));
ClipBlend = saturate(ClipBlend);

// 取得和 ClipBox 的相交点
float3 ResultYCoCg =  lerp(History, Filtered, ClipBlend);
//还原到RGB色彩空间，得到最终结果
HistoryColor.rgb = YCoCgToRGB(ResultYCoCg));
```

### 6. 混合得到结果

然后就可以混合历史颜色和当前的颜色了，不同于在静态场景中直接使用 0.05 作为混合系数，我们在这里使用一个可变化的混合系数值来平衡抖动和模糊的效果，当物体的 Motion Vector 值比较大时，就增大 blendFactor 的值，反之则减小：

```
// 与上帧相比移动距离越远，就越倾向于使用当前的像素的值
blendFactor = saturate(0.05 + length(motion) * 100);
return lerp(historyColor, currColor, blendFactor);
```

因为我们用到了很多双线性采样，会使得得到的结果有些模糊，因此我们根据情况选择是否对结果进行一次简单的锐化。

到这里为止，我们已经实现了 TAA 的整个流程，得到了不错的抗锯齿效果。

![](https://pica.zhimg.com/v2-48b08cc48d1bc5b0c8263aba60e82a08_r.jpg)

整个的流程可大致用下图归纳：

![](https://pica.zhimg.com/v2-4583e7ad58c15e08fe354a4d7e432566_r.jpg)

二、仅使用重投影的 TAA
-------------

在某些情况下，出于性能或其他方面的考虑，我们不能使用 Motion Buffer 来保存两帧之间的投影坐标差。这种方式没有使用 Motion Vector 来保存投影坐标，相对会比较节省性能。如果物体是快速运动的，就会产生错误的效果。

这种方式虽然结果不精确，但是性能开销小。非常适用于一些需要进行降噪处理的场合。比如对于 SSAO、SSR、Volumetric Fog、Raymarching Cloud 等这些开销很大的渲染效果，重投影的 TAA 能以非常低的开销实现降噪。而产生的渲染瑕疵，往往是可以接受的。

![](https://picx.zhimg.com/v2-d18d5c017de2738bb8a578583eb523b5_r.jpg)

三 、TAA 的小结
----------

因为 TAA 本质上是和 SSAA 类似的原理，所以完全不会有后处理抗锯齿的次像素问题，AA 效果可以和 MSAA 相当。由于 MSAA 在延迟渲染管线中无法使用，且使用 Motion Vector 也和延迟渲染比较契合，因此在 [Unreal 引擎](https://zhida.zhihu.com/search?content_id=182626622&content_type=Article&match_order=1&q=Unreal+%E5%BC%95%E6%93%8E&zhida_source=entity)的带领下，TAA 目前也逐渐成为现代 3A 游戏的标配。

当然其缺点也比较明显，虽然 TAA 实现的原理并不复杂，但是和渲染管线关系密切，需要改动的地方较多。可以说是牵一发而动全身，对于其他的每一项渲染功能，都需要考虑 TAA 的影响。

除此之外 TAA 中很容易出现一些闪烁，鬼影等问题，需要不同的应用场景进行处理。因为 TAA 和渲染管线是紧密相关的，在不同游戏引擎中，TAA 的很多细节处理方式都不太一样。

### 参考文献

[https://de45xmedrsdbp.cloudfront.net/Resources/files/TemporalAA_small-59732822.pdf](https://link.zhihu.com/?target=https%3A//de45xmedrsdbp.cloudfront.net/Resources/files/TemporalAA_small-59732822.pdf)

[http://advances.realtimerendering.com/s2016/s16_Ke.pptx](https://link.zhihu.com/?target=http%3A//advances.realtimerendering.com/s2016/s16_Ke.pptx)