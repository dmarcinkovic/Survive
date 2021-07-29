# Survive

## Download repository

    $ git clone --recurse-submodules https://github.com/dmarcinkovic/Survive.git

## Required packages and libraries

* `pkg-config`: Used for managing compile and link flags for libraries.
* `make`: A build automation tool that automatically builds executable.
* `CMake`: Cross-platform software tool for managing the build process of software using a compiler-independent
  method.  
  Make sure to download the version `3.15` or higher.
* `libgl`: Free implementation of the OpenGL API
* `glfw`: Library used for creating window and taking user input.
* `glew`: The OpenGL extension wrangler library. Used for determining which OpenGL extensions are supported on the
  target platform.
* `C++` compiler that supports c++20 standard
* `openAL`: Cross-platform 3D audio API.
* `glm`: C++ library for OpenGL GLSL type-base mathematics

## Linux

### Download dependencies
* On Linux you can use `clang` or `gcc` compiler.
    - ##### Ubuntu
        * ` $ apt install pkg-config`
        * ` $ apt install make`
        * ` $ apt install cmake`
        * ` $ apt install libgl1-mesa-dev`
        * ` $ apt install libglfw3-dev`
        * ` $ apt install libglew-dev`
        * ` $ apt install libclang-dev clang` or ` $ apt install g++`
        * ` $ apt install libalut-dev`
        * ` $ apt install libglm-dev`

    - ##### Gentoo
        * ` $ emerge dev-util/pkgconfig`
        * ` $ emerge sys-devel/make`
        * ` $ emerge dev-util/cmake`
        * ` $ emerge media-libs/mesa`
        * ` $ emerge media-libs/glfw`
        * ` $ emerge media-libs/glew`
        * ` $ emerge sys-devel/llvm sys-devel/clang` or ` $ emerge sys-devel/gcc`
        * ` $ emerge media-libs/freealut`
        * ` $ emerge media-libs/glm`

    - ##### Archlinux
        * ` $ pacman -S pkg-config`
        * ` $ pacman -S make`
        * ` $ pacman -S cmake`
        * ` $ pacman -S mesa`
        * ` $ pacman -S glfw-x11`
        * ` $ pacman -S glew`
        * ` $ pacman -S llvm clang` or ` $ pacman -S gcc`
        * ` $ pacman -S freealut`
        * ` $ pacman -S glm`

    - ##### Fedora
        * ` $ dnf install pkgconf-pkg-config`
        * ` $ dnf install make`
        * ` $ dnf install cmake`
        * ` $ dnf install mesa-libGL`
        * ` $ dnf install glfw-devel`
        * ` $ dnf install glew-devel`
        * ` $ dnf install llvm clang` or ` $ dnf install gcc-c++`
        * ` $ dnf install freealut-devel`
        * ` $ dnf install glm-devel`

### Build and run

* Create build directory with: ` mkdir build && cd build`
  

* Build the executable: ` cmake .. && make`


* Run: ` ./build/Survive`

## Windows

### Download dependencies

* `CMake`: CMake can be downloaded from the [CMake Official Website](https://cmake.org/download/). Choose the latest *CMake*
  release and download the CMake installer. Put the *CMake/bin* directory in the **PATH**
  environment variable.


* `C++ compiler`: On Windows you can use [MinGW](http://www.mingw.org/) or
  [Visual Studio](https://visualstudio.microsoft.com/vs/features/cplusplus/) compiler.
  Make sure to download the compiler that supports c++20 standard


*  Download [conan](https://conan.io/) C/C++ Package Manager from the official
   website. We will be using it to take care of installing required libraries
   as it can be very challenging to set up everything manually.

### Build and run

* Create build directory with: ` mkdir build && cd build`


* Download required libraries: 
 ```
conan install -s compiler="Visual Studio" -s build_type=Release -s compiler.version=16 --build=missing ..
```

* Build the executable: ` cmake .. -G "Visual Studio 16" && cmake --build . --config Release`


* Run: ` build\bin\Survive.exe`