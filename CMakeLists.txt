cmake_minimum_required(VERSION 3.12)

project(VulkanTest)

set(EXE_NAME VulkanTest_x86-64)
file(GLOB SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${EXE_NAME} ${SRC})

include(ExternalProject)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set(IMPORTED_LIB_DIR ${EXTERNAL_INSTALL_LOCATION}/lib)


ExternalProject_Add(GLFW
    GIT_REPOSITORY https://github.com/glfw/glfw
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

ExternalProject_Add(GLM
    GIT_REPOSITORY https://github.com/g-truc/glm
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

add_dependencies(${EXE_NAME} GLFW)
add_dependencies(${EXE_NAME} GLM)

# set include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty ${EXTERNAL_INSTALL_LOCATION}/include)

if(WIN32)
  set(suffix ".lib")
elseif(APPLE)
  set(suffix ".a")
else()
  set(suffix ".a")
endif()

set(GLFW_LIB "${IMPORTED_LIB_DIR}/libglfw3${suffix}")
target_link_libraries(${EXE_NAME} ${GLFW_LIB})


file(COPY resources DESTINATION resources)
file(COPY shaders DESTINATION shaders)