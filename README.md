# s4-gui

实时接收和展示APEX L2 UDP行情

## 依赖库：
- S4libLite: https://github.com/fpga2u/s4-libLite.git
- QT: 5.12

## 安装:
### Windows:
*以Visual Studio 2019 + Qt5.12.9为例*
1. 安装依赖库 (若已安装，可忽略)

```bat
git clone https://github.com/fpga2u/s4-libLite.git
cd s4-libLite
git submodule update --init --recursive

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
.\tool\install.bat
```
2. 安装QT，过程略，下以安装到C:\Qt\Qt5.12.9为例。
3. 安装本工程
```bat
git clone https://github.com/fpga2u/L2live.git
cd L2live

mkdir build
cd build

cmake -D_QT_PATH=C:\Qt\Qt5.12.9\5.12.9\msvc2017_64 -DS4libLite_ROOT=..\..\s4-libLite\install_release ..
cmake --build .  --config Release

.\Release\L2live-qt_L2Viewer.exe
```

### Linux:
*以CentOS8Stream + Qt5.12.9为例*
1. 安装依赖库 (若已安装，可忽略)

```shell
git clone https://github.com/fpga2u/s4-libLite.git
cd s4-libLite
git submodule update --init --recursive
mkdir build
cd build
cmake ..
sudo cmake --build . --target install --config Release
```
2. 安装QT，过程略，下以安装到/opt/Qt5.12.9为例。
3. 编译本工程
```shell
git clone https://github.com/fpga2u/L2live.git
cd L2live

mkdir build
cd build

cmake -D_QT_PATH=/opt/Qt5.12.9/5.12.9/gcc_64 ..
cmake --build .  --config Release

# test run
./L2live-qt_L2Viewer.exe
```

4. 使用linuxdeployqt打包发布
进入工程根目录L2live
```shell
export PATH=/opt/Qt5.12.9/5.12.9/gcc_64/bin:$PATH
mkdir pack
cd pack
cp ../L2live-qt_L2Viewer ./
../tools/linux/linuxdeployqt L2live-qt_L2Viewer -verbose=2 -bundle-non-qt-libs
```


5. trouble shoot
 * 若Linux 出现 Failed to find "GL/gl.h" in "/usr/include/libdrm" :
  sudo yum install mesa-libGL-devel mesa-libGLU-devel
