# ray_tracing
开始想完全自己实现，发现因为对phong模型理解不够，实现出来怪怪的。
刚刚根据http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml修改了部分代码，目前完成了diffusion部分。

需要外链opencv的vs2015库。

things to note:
Color 和 Vec3 中只声明了Vec3 * Double的形式，所以如果出现倒过来的情况，一定几率是不会报错的，而是会得出错误的结果。

Jun15：加入了折射代码，发现了求shadow中的一个bug，解决了。
