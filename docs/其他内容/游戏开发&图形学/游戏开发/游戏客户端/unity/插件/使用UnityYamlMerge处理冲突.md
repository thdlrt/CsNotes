- unity 提供的更智能的冲突处理工具
### 手动使用工具进行处理
```bash
git show ':1:./Suntail Village/Demo/Suntail Village Navigation.scene' > './Suntail Village/Demo/Suntail Village Navigation base.scene'
git show ':2:./Suntail Village/Demo/Suntail Village Navigation.scene' > './Suntail Village/Demo/Suntail Village Navigation ours.scene'
git show ':3:./Suntail Village/Demo/Suntail Village Navigation.scene' > './Suntail Village/Demo/Suntail Village Navigation theirs.scene'

$yamlexe = 'C:\Program Files\Tuanjie\Hub\Editor\2022.3.38t2\Editor\Data\Tools\TuanjieYAMLMerge.exe'
# 三路合并所需的文件
$base    = '.\Suntail Village Navigation.base.unity'
$ours    = '.\Suntail Village Navigation.ours.unity'
$theirs  = '.\Suntail Village Navigation.theirs.unity'
$merged  = '.\Suntail Village Navigation.merged.unity'
& $yamlexe merge $base $ours $theirs $merged --force-txt

$LASTEXITCODE # =0表示没有问题
Move-Item -Force '.\Suntail Village Navigation merged.scene' '.\Suntail Village Navigation.scene'
```