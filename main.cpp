#define VOLK_IMPLEMENTATION
#include "volk.h"
#include "Application.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stbimage.h"

int main() {
    try {
        Application::run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}