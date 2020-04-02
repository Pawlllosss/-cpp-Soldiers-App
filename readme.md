**Prerequisites**

To run this project you need to have QT5 library.

Project is declared in CMake to run in C++17 standard.

Project was built with *gcc 7.4.0*

**Configuration**

You need to set proper path to your Qt library, below an example is included:

`set(Qt5_DIR "~/Qt/5.9.9/gcc_64/lib/cmake/Qt5")`

If you want to specify path to compilers you need to do it in the following way.

`SET(CMAKE_C_COMPILER "/usr/bin/gcc")
 SET(CMAKE_CXX_COMPILER "/usr/bin/g++")`

**Possible problems**

You may stumble upon following error when configuring cmake project.
`Failed to find "GL/gl.h" in "/usr/include/libdrm"`

You can fix it by the following command:
`sudo apt install mesa-common-dev libglu1-mesa-dev`
