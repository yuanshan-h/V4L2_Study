cmake_minimum_required(VERSION 3.10)

project(V4L2_Video_Test)

# 交叉编译工具链配置（CMake 语法）
set(CROSS_COMPILE "arm-linux-gnueabihf-")
set(ARCH "arm")

# 设置交叉编译器
set(CMAKE_C_COMPILER "${CROSS_COMPILE}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_COMPILE}g++")
set(CMAKE_AR "${CROSS_COMPILE}ar")
set(CMAKE_RANLIB "${CROSS_COMPILE}ranlib")

# 设置系统信息
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 可选：设置输出目录
set(OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

<<<<<<< HEAD
# 添加静态链接标志
set(CMAKE_EXE_LINKER_FLAGS "-static")

=======
>>>>>>> cadcbc78fade9f1e2088c26d6e072485c337c8ee
# 创建可执行文件
add_executable(video_test video_test.c)

# 设置输出目录
set_target_properties(video_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}"
)

# 添加自定义运行目标
add_custom_target(run COMMAND ${OUTPUT_PATH}/video_test /dev/video0 DEPENDS video_test)

# 清理目标
if(NOT TARGET clean-all)
    add_custom_target(clean-all
        COMMAND find "${CMAKE_BINARY_DIR}" -mindepth 1 -maxdepth 1 -exec rm -rf {} +
        COMMENT "Cleaning all generated files."
    )
endif()