#define VOLK_IMPLEMENTATION
#include <volk.h>
#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stbimage.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader.h>


VkResult Application::initVolk() {
    return volkInitialize();
}


void Application::loadVolk(VkInstance instance) {
    volkLoadInstance(instance);
}


int main() {
    try {
        Application::run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}