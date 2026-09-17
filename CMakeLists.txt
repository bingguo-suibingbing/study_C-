cmake_minimum_required(VERSION 3.16)

# -----------------------------------------------------------------------------
#  CMake 是什么，为什么真实项目几乎都用它
# -----------------------------------------------------------------------------
#  .vcxproj 是 Visual Studio 私有格式：换到 Linux/GCC、Clang、CI 机器上就废了。
#  CMake 用一份 CMakeLists.txt 描述工程，可以生成 VS 工程、Makefile、Ninja 等
#  任何平台的构建文件。跨平台、可脚本化、能集成第三方库，是事实标准。
#
#  用法（PowerShell）：
#      cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#      cmake --build build --config Release
#      ./build/cpp_learning            # 或用 -B build 下的实际路径
#
#  调试版带符号：
#      cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# -----------------------------------------------------------------------------

project(cpp_learning
        VERSION 1.0
        DESCRIPTION "C++ 学习工程：从基础语法到工程实践"
        LANGUAGES CXX)

# C++20：需要 concepts、ranges、<format>、三路比较等新特性
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)        # 关闭编译器私有扩展，保证可移植

# 默认构建类型。不写的话 MSVC 下会得到"无优化无调试信息"的奇怪组合。
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

# -----------------------------------------------------------------------------
#  源文件收集
# -----------------------------------------------------------------------------
#  【取舍】GLOB 的经典问题是"新增文件后 CMake 不会自动重新配置"。
#      学习工程用 CONFIGURE_DEPENDS 缓解：每次构建都会检查目录变化。
#      生产工程更推荐显式列文件，改动了什么一目了然、code review 也能看到。
file(GLOB_RECURSE CPP_LEARNING_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(cpp_learning ${CPP_LEARNING_SOURCES})

# 让 #include "common/lesson.h" 这种写法生效
target_include_directories(cpp_learning PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# -----------------------------------------------------------------------------
#  编译选项：按编译器区分
# -----------------------------------------------------------------------------
#  【工程习惯】不要用全局的 CMAKE_CXX_FLAGS 硬塞选项，
#      用 target_xxx 系列命令把选项绑在具体 target 上。
#      全局变量会污染所有依赖，"改一个地方炸一片"。
if(MSVC)
    target_compile_options(cpp_learning PRIVATE
        /W4            # 高告警等级
        /utf-8         # 源码与执行字符集都是 UTF-8，中文才不会乱码
        /permissive-   # 关闭 MSVC 非标准扩展
        /EHsc          # 标准异常模型
        /Zc:__cplusplus  # 让 __cplusplus 报告真实标准版本
        /MP)           # 多核并行编译
else()
    target_compile_options(cpp_learning PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
        -fno-omit-frame-pointer)
endif()

# 中文 Windows 控制台需要 UTF-8 代码页；由 main.cpp 在运行时设置，
# 这里只是提醒：Linux 下终端本来就是 UTF-8，无需处理。
