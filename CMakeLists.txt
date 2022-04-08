cmake_minimum_required(VERSION 3.15)
project (MotaSDL)
# https://blog.csdn.net/afei__/article/details/81201039

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/SDL2-2.0.16/include) # SDL的Include
include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/SDL2_image-2.0.5/include) # SDL-IMAGE的Include
include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src) # 项目的Include
set(SDL2_HOME ${PROJECT_SOURCE_DIR}/SDL2-2.0.16)
set(SDL2_IMAGE_HOME ${PROJECT_SOURCE_DIR}/SDL2_image-2.0.5)
message(${SDL2_HOME})

if (BUILD_WIN32) # Windows32位
	set(SDL2_LIBRARY ${SDL2_HOME}/lib/x86/SDL2.lib) # SDL的lib
	set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_HOME}/lib/x86/SDL2_image.lib) #SDL-IMAGE的lib
	file(COPY ${SDL2_HOME}/lib/x86/SDL2.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/libjpeg-9.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/libpng16-16.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/libtiff-5.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/libwebp-7.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/SDL2_image.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x86/zlib1.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
else() # 64位
	set(SDL2_LIBRARY ${SDL2_HOME}/lib/x64/SDL2.lib) # SDL的lib
	set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_HOME}/lib/x64/SDL2_image.lib) #SDL-IMAGE的lib
	file(COPY ${SDL2_HOME}/lib/x64/SDL2.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/libjpeg-9.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/libpng16-16.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/libtiff-5.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/libwebp-7.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/SDL2_image.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
	file(COPY ${SDL2_IMAGE_HOME}/lib/x64/zlib1.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()


# 主程序
file(GLOB_RECURSE ALLCPP ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${ALLCPP})

# 素材
file(COPY ${PROJECT_SOURCE_DIR}/src/resources DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

# lib库连接
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}) #SDL
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY}) #SDL-IMAGE