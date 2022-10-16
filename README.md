# 有限元课程作业

1. 项目语言 `C++`，请确保你的编译器支持 `C++14`及以上标准
2. 请安装 `Xmake`，是本项目的编译系统
   > 请访问[https://xmake.io/#/zh-cn/getting_started](https://xmake.io/#/zh-cn/getting_started)获得更多帮助
   >
3. `lab*`目录为第 `*`次作业，目录下的 `main.cpp`一般是主程序文件
4. 请访问指定文件夹后首先运行 `xmake build`命令进行构建，再运行 `xmake run`命令去运行
5. 如有疑问请联系<axccjqh@qq.com>

运行示例（Codespace中）

```bash
@DawnMagnet ➜ /workspaces/FEA-cpp (master) $ bash <(curl -fsSL https://xmake.io/shget.text)
(省略安装Xmake的输出)
@DawnMagnet ➜ /workspaces/FEA-cpp (master) $ ls
lab1  README.md  xmake.lua
@DawnMagnet ➜ /workspaces/FEA-cpp (master) $ xmake
checking for platform ... linux
checking for architecture ... x86_64
updating repositories .. ok
note: install or modify (m) these packages (pass -y to skip confirm)?
in xmake-repo:
  -> boost 1.80.0 [from:numcpp]
  -> numcpp 2.4.2 
please input: y (y/n/m)
y
  => download https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.bz2 .. ok
  => install boost 1.80.0 .. ok
  => download https://github.com/dpilger26/NumCpp/archive/refs/tags/Version_2.4.2.tar.gz .. ok
  => install numcpp 2.4.2 .. ok
[ 25%]: cache compiling.release lab1/main.cpp
[ 50%]: linking.release lab1
[100%]: build ok!
@DawnMagnet ➜ /workspaces/FEA-cpp (master) $ xmake run
[[7042.11, 2688.16, -5250, 0, -1792.11, -2688.16, ]
[2688.16, 4032.24, 0, 0, -2688.16, -4032.24, ]
[-5250, 0, 7042.11, -2688.16, -1792.11, 2688.16, ]
[0, 0, -2688.16, 4032.24, 2688.16, -4032.24, ]
[-1792.11, -2688.16, -1792.11, 2688.16, 3584.22, 9.09495e-13, ]
[-2688.16, -4032.24, 2688.16, -4032.24, 9.09495e-13, 8064.49, ]]
[[0.00111111, ]
[0.00195056, ]
[-0.00161037, ]]
@DawnMagnet ➜ /workspaces/FEA-cpp (master) $ 
```
