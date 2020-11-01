# chain-3d

计划表 http://uu.rs/posts/note20201101/

## 构建环境  
### 开发环境
目前开发在Windows-msys2-mingw64-GCC/CLang和MacOS环境下，每次封版才会打包Linux-GCC/CLang和VisualStudio依赖库到master分支，所以你需要下载msys2或者xcode
IDE使用的clion，当然也支持其他支持gcc的IDE，例如：QT，CB，Eclipse，vscode等

## 编译发布
### pc
修改./chain-3d/CMakeLists.txt确保变量IOS=0  
修改./chain-3d/code/Config.h  
确保#define IOSX  
确保#define __EMSCRIPTEN__X  
修改#define PROJECT_ROOT_DIR "Z:/chain-3d/"为你的项目目录  

ide直接点锤子就编译成功了  
不使用IDE的话就执行：
``` sh
cd ./chain-3d
mkdir build
cd build
cmake .. -G "Ninja" #没有Ninja自己安装个，很小很好安装。或者使用cmake .. -G "MinGW Makefiles"
cmake --build . -j8
```
### web
修改./chain-3d/CMakeLists.txt确保变量IOS=0  
修改./chain-3d/code/Config.h  
确保#define IOSX  
确保#define __EMSCRIPTEN__X  
修改#define PROJECT_ROOT_DIR "Z:/chain-3d/"为你的项目目录  

生成html需要自行安装Emscripten，Emscripten官方不支持VS，Windows下只能是用WSL或者MSYS2，官方教程写的WSL安装Linux来跑,但是Msys2也可以跑，而且可以跑的更好。  
安装好了之后，在shel里执行 em++看看环境有没有加上，没有找到程序，就回到官方教程看如何添加环境。  
配置好环境后执行：
``` sh
cd ./chain-3d
mkdir build
cd build
cp ../data.0 ./
emcmake cmake ..
make -j 16
python -m http.server
```
运行就是打开Firefox或者Chrome浏览http://localhost:8000/

### Android
编译安卓需要Android Studio或者IDEA，Android Studio是基于IDEA开发的，各人推荐使用IDEA，编译所需的Android SDK，使用的是Android 10, 安装IDE的时候会自动下载，但是国内环境很难自动下载下来，特别是在MacOS，翻墙都难下，Windows下比较顺利Linux下未测试。  
下载好了再安装个NDK,后续我没有再搞，手里没有安卓设备，有设备的自己研究下。

### iOS
修改./chain-3d/CMakeLists.txt确保变量IOS=1  
修改./chain-3d/code/Config.h  
确保#define IOS  
确保#define __EMSCRIPTEN__X  
修改#define PROJECT_ROOT_DIR "/home/abc/chain-3d/"为你的项目目录  

编译iOS需要买个Macbook, 然后安装Xcode cmake，不管开发什么iOS APP都需要Xcode，苹果的硬规定。注册苹果id，到商店xcode直接商店安装就可以。  
安装好执行：  
``` sh
cd ./chain-3d
mkdir build
cd build
cmake .. -DCMAKE_SYSTEM_NAME=iOS #没有Ninja自己安装个，很小很好安装。或者使用cmake .. -G "MinGW Makefiles"
```
执行完build目录下会有xcode项目，打开后进入IDE项目设置中登录你的Apple ID，然后点签证，签证好可以编译运行，过去签证要钱，现在免费了，不过想上架APP需要交钱申请年费开发证书，800RMB/年。



