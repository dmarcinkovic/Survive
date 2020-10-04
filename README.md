# Survive
Game engine.

## Building instructions
* Required packages and libraries
    * `pkg-config`: Used for managing compile and link flags for libraries.
    * `make`: A build automation tool that automatically builds executable.
    * `CMake`: Cross-platform software tool for managing the build 
        process of software using a compiler-independent method.  
        Make sure to download the version `3.15` or higher.
    * `libgl`: Free implementation of the OpenGL API
    * `glfw`: Library used for creating window and taking user input.  
    * `glew`: The OpenGL extension wrangler library. Used for determining 
    which OpenGL extensions are supported on the target platform. 
    * C++ compiler that supports c++20 standard
    * `openAL`: Cross-platform 3D audio API.
    * `glm`: C++ library for OpenGL GLSL type-base mathematics
    
 * ## Linux
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
        * ` $ dnf install gcc-c++`
        * ` $ dnf install freealut-devel`
        * ` $ dnf install glm-devel`