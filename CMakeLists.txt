cmake_minimum_required(VERSION 3.12)

project(VulkanTest)

set(EXE_NAME VulkanTest_x86-64)
file(GLOB SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${EXE_NAME} ${SRC})

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set(IMPORTED_LIB_DIR ${EXTERNAL_INSTALL_LOCATION}/lib)


ExternalProject_Add(VULKAN
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers
    GIT_TAG main
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

# TODO : Make this correctly download sometime
#ExternalProject_Add(VULKAN_VALIDATION
#    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers
#    GIT_TAG master
#    CMAKE_ARGS -DBUILD_TESTS=Off -DBUILD_DEMOS=Off -DBUILD_WSI_MIR_SUPPORT=Off -DBUILD_WSI_WAYLAND_SUPPORT=Off -DBUILD_WSI_XLIB_SUPPORT=Off -DBUILD_WSI_XCB_SUPPORT=Off -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#)

ExternalProject_Add(GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

ExternalProject_Add(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

add_dependencies(${EXE_NAME} VULKAN)
#add_dependencies(${EXE_NAME} VULKAN_VALIDATION)
add_dependencies(${EXE_NAME} GLFW)
add_dependencies(${EXE_NAME} GLM)

# set include directory
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty ${EXTERNAL_INSTALL_LOCATION}/include)

if(WIN32)
  set(suffix ".lib")
elseif(APPLE)
  set(suffix ".a")
else()
  set(suffix ".a")
endif()

# TODO : Find out how to identify the proper glfw libraries
set(GLFW_LIB "${IMPORTED_LIB_DIR}/libglfw3${suffix}")
target_link_libraries(${EXE_NAME} ${GLFW_LIB})


file(COPY resources DESTINATION shaders)
file(COPY shaders DESTINATION shaders)