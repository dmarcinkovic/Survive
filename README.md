# Survive
Game engine.

## Building instructions
* Required packages and libraries
    * `pkg-config`: Used for managing compile and link flags for libraries.
    * `libgl`: Free implementation of the OpenGL API
    * `glfw`: Library used for creating window and taking user input.  
    * `glew`: The OpenGL extension wrangler library. Used for determining 
    which OpenGL extensions are supported on the target platform. 
    * C++ compiler that supports c++20 standard
    * `openAL`: Cross-platform 3D audio API.
    * `CMake`: Cross-platform software tool for managing the build 
    process of software using a compiler-independent method.  
    Make sure to download the version `3.15` or higher.
    * `glm`: C++ library for OpenGL GLSL type-base mathematics
    
 * ## Linux
 * On Linux you can use `clang` or `gcc` compiler. 
   - ##### Ubuntu 
        * ` $ sudo apt install pkg-config`
        * ` $ sudp apt install libgl1-mesa-dev`
        * ` $ sudo apt install libglfw3-dev`
        * ` $ sudo apt install libglew-dev`
        * ` $ sudo apt install clang` or ` $ sudo apt install g++`
        * ` $ sudo apt install libalut-dev`
        * ` $ sudo apt install cmake`
        * ` $ sudo apt install libglm-dev`
    
    - ##### Gentoo
        * ` $ sudo emerge dev-util/pkgconfig`
        * ` $ sudo emerge media-libs/mesa`
        * ` $ sudo emerge media-libs/glfw`
        * ` $ sudo emerge media-libs/glew`
        * ` $ sudo emerge sys-devel/llvm sys-devel/clang` or `sudo emerge sys-devel/gcc`
        * ` $ sudo emerge media-libs/freealut`
        * ` $ sudo emerge dev-util/cmake`
        * ` $ sudo emerge media-libs/glm`
