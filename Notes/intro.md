## Introduction to Cpp Under Linux System

### 1. 编译与调试


#### 1.1 编译过程
`预处理 --> 编译 --> 汇编 --> 链接`

<div style="text-align: center;">
    <img src="Figures/f1.png" style="width: 80%; max-width: 600px; height: auto;">
</div>

- **预处理:** 只进行预处理步骤, 而不进行编译. 这意味着它会处理所有的宏定义,包含文件(#include), 以及条件编译指令(如 #ifdef), 并生成预处理后的源代码.

- **编译:**  预处理代码转换为汇编语言

- **汇编:** 目标文件通常是二进制格式，包含机器代码，但尚未链接成可执行文件

- **链接:** 将目标文件链接成一个可执行文件

```
# Pre-Processing
# -E选项指示编译器只对输入文件进行预处理
g++ -E test.cpp -o test.i  //  得到.i文件

# Compiling
g++ -S test.i -o test.s 

# Assembling
# -c选项告诉g++将源代码编译为机器语言的目标文件
g++ -c test.s -o test.o

# Linking
#生成bin文件, test 是生成的可执行文件名
g++ test.o -o test

```

- 一步到位的编译: `g++ test.cpp -o test`, `./test  `


#### 1.2 g++重要的编译参数

- **-g:**  编译带调试信息的可执行文件

```
# -g告诉GCC产生能被GNU调试器GDB使用的调试信息, 以调试程序
# 产生带调试信息的可执行文件test

g++ -g test.cpp -o test
```


- **-O[n]:** 优化源代码

```
# 所谓优化, 例如省略代码中从未使用过的变量, 直接将常量表达式用结果值代替等等
g++  inefficient_test.cpp -O2 efficient_test 
```


- **-l / -L** 指定库文件 / 指定库文件路径

```
# -l参数指定程序要链接的库, -l参数后跟的就是库名
# 在/lib和 /usr/lib和 /usr/local/lib里的库直接用-l参数就能链接
#链接mytest库 (mytest库在上述的三个目录之一)
g++ -lmytest test.cpp

# -L参数指定库文件所在的目录
#链接mytest库
g++ -L/home/being/mytestlibfolder -lmytest test.cpp
```

- **-I:** 指定头文件搜索目录

```
# /usr/include目录一般是不用指定的, gcc知道去哪里找. 
# 但是如果头文件不在/usr/include里我们就要用 -I 去指定了. 
# 比如头文件放在 /myinclude 文件夹里, 就要 -I/myinclude去指定. 
# -I可以用相对路径

g++ -I/myinclude test.cpp
```

- **-Wall:** 打印警告信息. `g++ -Wall test.cpp`
- **-w:** 关闭警告信息. `g++ -w test.cpp`
<p>

- **-std=c++11**: 设置编译标准 `g++ -std=c++11 test.cpp`

- **-o** 指定即将产生的文件名


#### 1.3 静态链接库与动态链接库

- 链接就是把目标文件与一些库文件生成可执行文件的一个过程



- **静态链接:** `静态链接库`在程序**编译**时被连接到**目标代码**中参与**编译**; **链接**时将库**完整**地拷贝至可**执行文件**中, 被多次使用就有多份冗余拷贝;生成可执行程序之后, 静态链接库**不需要**(因已将函数拷贝到可执行文件中). `静态链接库`, Windows下以`.lib`为后缀, Linux下以`.a`为后缀.

- **动态链接:** `动态链接(Dynamic Linking)`, 把链接这个过程推迟到了运行时再进行, 在可执行文件装载时或运行时, 由操作系统的装载程序加载库. 系统只加载一次, 多个程序共用, 节省内存. `动态链接库`, Windows下以`.dll`为后缀, Linux下以`.so`为后缀.


- **静态链接的优点:**
  - 代码装载速度快, 执行速度略比动态链接库快;
  - 只需保证在开发者的计算机中有正确的`.lib文件`, 在以二进制形式发布程序时不需考虑在用户的计算机上`.lib`文件是否存在及版本问题.

- **静态链接的缺点:**
  - 使用静态链接生成的可执行文件体积较大, 包含相同的公共代码, 造成浪费.
  - 如果静态库进行更新则应用该库的所有程序都需要重新编译

<p>

- **动态链接的优点:**
  - 生成的可执行文件较静态链接生成的可执行文件小;
  - 适用于大规模的软件开发, 使开发过程独立,耦合度小; 便于不同开发者和开发组织之间进行开发和测试;
  - 不同编程语言编写的程序只要按照函数调用约定就可以调用同一个DLL函数；
  - `DLL`文件与`EXE`文件独立, 只要输出接口不变(即名称/参数/返回值类型和调用约定不变), 更换`DLL`文件不会对`EXE`文件造成任何影响, 因而极大地提高了可维护性和可扩展性;
  - 动态链接库可以包含其他动态链接库
<p>

- **动态链接的缺点:**
  - 使用动态链接库的应用程序`不是自完备的`, 它依赖的`DLL模块`也要存在, 如果使用载入时动态链接,程序启动时发现DLL不存在, 系统将终止程序并给出错误信息;
  - 速度比静态链接慢;


#### 1.4 g++命令行编译(  实战)

```
# 目录结构
.
├── include
│   └── Swap.h
├── main.cpp
└── src
    └── Swap.cpp

```

- **直接编译**
  - **简单编译:**  `g++ main.cpp src/Swap.cpp -Iinclude -o test`
  <p>

  - **加参数编译:**  `g++ main.cpp src/Swap.cpp -Iinclude -Wall -std=c++11 -o test`

- **生成库文件并编译**
  - **链接静态库生成可执行文件**

```
## 进入src目录下
cd src

# 汇编, 生成Swap.o文件
g++ Swap.cpp -c -I../include

# 生成静态库libSwap.a
ar rs libSwap.a Swap.o

## 回到上级目录
cd ..

# 链接  , 编译器会自动寻找 libSwap.a ( lib 前缀省略)
g++ main.cpp -Iinclude -Lsrc -lSwap -o staticmain
```

**运行可执行文件:** ` ./staticmain`

<p>

  - **链接动态库生成可执行文件**

```
## 进入src目录下
cd src

# 生成动态库libSwap.so
g++ Swap.cpp -I../include -fPIC -shared -o libSwap.so

## 回到上级目录
cd ..

# 链接
g++ main.cpp -Iinclude -Lsrc -lSwap -o sharemain
```

**运行可执行文件:** `LD_LIBRARY_PATH=src ./sharemain`



#### 1.5 GDB调试器

- **GDB (GNU Debugger)** 是一个强大的 C/C++ 调试器, 常用于 Linux 开发环境.程序员可以使用 GDB 追踪程序中的错误, 减少工作量.

- 在 **VSCode** 中, 可以调用 GDB 来进行 C/C++ 调试. 在 **Windows** 上, **VS/CLion** 等 IDE 内置了相应的调试器.


- **GDB 主要功能**
  - 设置断点,让程序在指定代码处暂停执行

  - 单步执行

  - 查看程序变量值变化

  - 动态修改程序执行环境

  - 分析崩溃程序生成的 `core` 文件


### 2. CMake

#### 2.1 What is CMake?

- **CMake:** `CMake` 是 **跨平台**的**安装编译**工具，可以用 简单的语法 描述 所有平台 的安装(编译)过程

- **简化C/C++第三方库的引入与使用流程**

- **跨平台开发( Cross-platform development)**: `CMake` 允许在**不同平台**上共享 C++ 代码, 并使用不同的 **构建工具(Build Tools)** 进行编译.
  
  - Windows 平台使用 Visual Studio

  - macOS 使用 Xcode

  - Linux 使用 Makefile

  - **构建流程** : **Build Tools**(Visual Studio / Xcode / Makefile) -> **Build Commands**(msbuild / xcodebuild / make) -> **Binaries**(最终可执行文件)

<div style="text-align: center;">
    <img src= "Figures/cmakeworkflow.jpg" style="width: 80%; max-width: 600px; height: auto;">
</div>


#### 2.2 CMake语法特点

- **基本语法格式:** 指令(参数1 参数2)
  - 参数之间使用**空格**或者**分号**分开
  - 指令是**大小无关**的, 即大小写字母一样, 但是**参数**是大小写有关的
  - **变量使用`${}`取值, 但是在IF控制语句中是直接使用变量名**

#### 2.3 CMake重要指令

- 1 **cmake_minimum_required(指定 CMake 最小版本要求)**
```
cmake_minimum_required(VERSION 2.8.3)
```
<p>

- 2 **project(projectname [CXX][C][Java])**
```
# 指定工程名为HELLOWORLD
project(HELLOWORLD)
```

<p>

- 3 **set(定义变量)**: 用于显式定义变量, 例如指定源文件列表.

```
# 定义SRC变量, 其值为sayhello.cpp 和 hello.cpp
set(SRC sayhello.cpp hello.cpp)

```

- 4 **include_directories( 向工程添加多个特定的头文件搜索路径)**: 相当于 g++ 的 `-I` 选项
```
# 将 /usr/include/myincludefolder 和./include 添加为头文件搜索路径
include_directories(/usr/include/myincludefolder ./include)
```

- 5 **link_directories:** 指定链接器搜索库文件的目录路径___(相当于指定g++编译器的-L参数)
```
#语法
link_directories(dir1 dir2 ...)

# example
link_directories(/usr/lib/my/libfolder /lib)
```

- 6 **add_library:** 生成一个库文件.

```
# 语法
add_library(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] source1 source2 ...)

# Example
# 通过变量SRC 生成libhello.so 共享库
add_library(hello SHARED ${SRC})

```


- 7 **add_compile_options:** 添加编译选项
```
add_compile_options(-Wall -std=c++11 -O2)
```

- 8 **add_executable:** 生成可执行文件

```
# 编译main.cpp生成可执行文件main
add_executable(main main.cpp)
```


- 9 **target_link_libraries:** 指定目标需要链接的库, 相当于g++编译器的`-l`参数
```
# 将hello动态库文件链接到可执行文件main
target_link_libraries(main hello)
```

- 10 **add_subdirectory:** 向当前的工程添加存放源文件的子目录.
```
# 添加src子目录, src中需要有一个CMakeLists.txt文件
add_subdirectory(src)
```

- 11 **aux_source_directory**
```
#定义SRC变量, 其值为当前目录下所有的源代码文件
aux_source_directory(. SRC)

# 编译SRC变量所代表的源代码文件, 生成main可执行文件
add_executable(main ${SRC})
```


#### 2.4 CMake常用变量

- **CMAKE_C_FLAGS**: gcc 编译器选项
- **CMAKE_CXX_FLAGS**: g++编译器选项

```
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
```

- **CMAKE_BUILD_TYPE** 编译类型(Debug调试, Release发布)
```
set( CMAKE_BUILD_TYPE Debug)
```

- **CMAKE_BINARY_DIR** / **PROJECT_BINARY_DIR** / **<projectname>_BINARY_DIR**: 都是定义项目的二进制目录, 通常是构建文件(build files)生成的位置 **(build目录的位置, 比如 /root/CppBasic/Code/build)**. 如果是 `in source build` 就是工程顶层目录, 如果是`out source build`就是工程编译发生的目录

- **CMAKE_SOURCE_DIR**: 定义项目的源代码目录 (即工程的顶层目录)，通常是包含CMakeLists.txt文件的目录.


- **CMAKE_C_COMPILER:** 指定C语言的编译器.
- **CMAKE_CXX_COMPILER:** 指定C++语言的编译器.
- **EXECUTABLE_OUTPUT_PATH:** 指定生成的可执行文件的输出路径.
- **LIBRARY_OUTPUT_PATH:** 指定生成库文件的输出路径.


#### 2.5 CMake项目的编译流程

- CMake项目的主要目录存在一个 `CMakeLists.txt` 文件. 我们有两种方式设置编译规则:

  - 包含源文件的子文件夹包含 `CMakeLists.txt` 文件, 主目录的 `CMakeLists.txt` 通过 `add_subdirectory` 添加子目录即可.
  - 包含源文件的子文件夹未包含 `CMakeLists.txt` 文件, 子目录编译规则体现在主目录的 `CMakeLists.txt` 文件

<p>

- 在 Linux 平台下使用 CMake 构建 C/C++ 工程的流程如下：

  - 编写 `CMakeLists.txt` 规则
  - 执行 `cmake PATH` 生成 `Makefile` (`PATH` 是`CMakeLists.txt` 所在的顶层目录)
  - 执行命令` make` 进行编译

- CMake的两种构建方式
  - **内部构建 (in-source build)**:**不推荐使用**. 内部构建会产生很多中间文件, 这些文件并不是我们最终想要的, 和工程源代码文件放在一起会显得杂乱无章.

```shell
# 内部构建示例

# 在项目源代码根目录下，使用  cmake 指令解析 CMakeLists.txt ，生成 Makefile 和其他文件
cmake .
# 执行 make 命令，生成 target
make
```
  - **外部构建 (out-of-source build)**: **推荐使用**.  将编译的目录和源代码目录区分开来, 放在不同目录中


```shell
# 外部编译示例

# 1. 在当前目录下，创建 build 文件夹
mkdir build
# 2. 进入build目录
cd build
# 3. 解析上级目录的 CMakeLists.txt ，生成 Makefile 和其他文件
cmake ..
# 4. 执行 make ，生成 target
make
```



### 3. VSCode 构建完整 C++ 过程

```
# 项目目录结构
.
├── include
├── main.cpp
├── CMakeLists.txt
└── src
```

- Linux 下:
```
mkdir build
cd build
cmake
make
./CppBasic

```

- Windows 下:
```
mkdir build
cd build
cmake -G "MinGw Makefiles" ..
mingw32-make
./CppBasic.exe

```






### 参考

- [Linux 之基于VSCode和CMake实现C/C++开发与调试 环境配置 GDB 多文件开发](https://www.bilibili.com/video/BV1fy4y1b7TC/?spm_id_from=333.1387.favlist.content.click&vd_source=ea310d614abfa357560d43c5ecb9fcfd)

- [什么是动态链接与静态链接？](https://zhuanlan.zhihu.com/p/604962547)

- [C++知识点14：静态链接库和动态链接库区别](https://blog.csdn.net/htt789/article/details/81454832)

