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
        * ` $ apt install pkg-config`
        * ` $ apt install libgl1-mesa-dev`
        * ` $ apt install libglfw3-dev`
        * ` $ apt install libglew-dev`
        * ` $ apt install clang` or ` $ sudo apt install g++`
        * ` $ apt install libalut-dev`
        * ` $ apt install cmake`
        * ` $ apt install libglm-dev`
    
    - ##### Gentoo
        * ` $ emerge dev-util/pkgconfig`
        * ` $ emerge media-libs/mesa`
        * ` $ emerge media-libs/glfw`
        * ` $ emerge media-libs/glew`
        * ` $ emerge sys-devel/llvm sys-devel/clang` or `sudo emerge sys-devel/gcc`
        * ` $ emerge media-libs/freealut`
        * ` $ emerge dev-util/cmake`
        * ` $ emerge media-libs/glm`
