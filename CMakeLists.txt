cmake_minimum_required(VERSION 3.12)

# Always required :
#     A CMake installation
#     Git on the system

# Compiling CMake on windows requires a MinGW installation on the PATH. 
#     MinGW can be downloaded from here : [https://sourceforge.net/projects/mingw/]
#     When running the installer, make sure to add mingw32-base (for mingw32-make), and mingw-gcc-g++ (for compilation)
#     To add MinGW to PATH, search for environment variables in settings, edit PATH, then add the MinGW/bin directory
#     When running CMake, specify using MinGW files with '-G "MinGW Makefiles"' in the command line.
#     Compiling the makefile will be 'mingw32-make' instead of just 'make'

# Linux normally has GCC installed for compilation, but if not, you can use a package manager to get it.
#     Make sure to have 'make' installed for makefile compilation. 
#     CMake should handle the rest. Probably. Just run cmake -Bbuild
#     To compile, run make -Cbuild

# I have no clue about Mac. Probably more finicky as you'll need MoltenVK for Vulkan, and I don't know about CMake on Apple either.

project(VulkanTest)

set(EXE_NAME VulkanTest_x86-64)
file(GLOB SRC CONFIGURE_DEPENDS "*.cpp")

add_executable(${EXE_NAME} ${SRC})

include(FetchContent)
set(EXTERNAL ${CMAKE_BINARY_DIR}/external)
set(EXTERNAL_PACKAGE_LOCATION ${EXTERNAL}/packages)
set(EXTERNAL_INSTALL_LOCATION ${EXTERNAL}/install)
set(IMPORTED_LIB_DIR ${EXTERNAL_INSTALL_LOCATION}/lib)

set(INSTALL_COMMAND -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION})

message("Downloading external libraries")
set(FETCHCONTENT_QUIET FALSE)
set(FETCHCONTENT_BASE_DIR ${EXTERNAL_PACKAGE_LOCATION}/vulkan)
FetchContent_Declare(vulkan
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers
    GIT_TAG main
)
FetchContent_MakeAvailable(vulkan)

# TODO : Make this correctly download sometime
#FetchContent_Declare(VULKAN_VALIDATION
#    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers
#    GIT_TAG master
#    CMAKE_ARGS -DBUILD_TESTS=Off -DBUILD_DEMOS=Off -DBUILD_WSI_MIR_SUPPORT=Off -DBUILD_WSI_WAYLAND_SUPPORT=Off -DBUILD_WSI_XLIB_SUPPORT=Off -DBUILD_WSI_XCB_SUPPORT=Off -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#)

set(FETCHCONTENT_BASE_DIR ${EXTERNAL_PACKAGE_LOCATION}/glfw)
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

set(FETCHCONTENT_BASE_DIR ${EXTERNAL_PACKAGE_LOCATION}/glm)
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG master
)
FetchContent_MakeAvailable(glm)

message("Installing packages")
#execute_process(
#  COMMAND mingw32-make
#  WORKING_DIRECTORY ${BOTAN_LIB_REPOS_DIR}
#  COMMAND_ECHO      STDOUT
#)


# set include directory
target_include_directories(${EXE_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty ${EXTERNAL_INSTALL_LOCATION})

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


file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})