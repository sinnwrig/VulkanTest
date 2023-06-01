#pragma once

#include "volk.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>
#include <array>

#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <unordered_map>
#include <chrono>


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};


struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;


    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }


    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions {};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

    bool operator==(const Vertex& other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};


namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^
                   (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}


struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};



class Application {
public:
    static void run();

private:
    static inline GLFWwindow* window;


    static inline VkInstance instance;
    static inline VkDebugUtilsMessengerEXT debugMessenger;
    static inline VkSurfaceKHR surface;


    static inline VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    static inline VkDevice device;


    static inline VkQueue graphicsQueue;
    static inline VkQueue presentQueue;


    static inline VkSwapchainKHR swapChain;
    static inline std::vector<VkImage> swapChainImages;
    static inline VkFormat swapChainImageFormat;
    static inline VkExtent2D swapChainExtent;
    static inline std::vector<VkImageView> swapChainImageViews;
    static inline std::vector<VkFramebuffer> swapChainFramebuffers;


    static inline VkRenderPass renderPass;
    static inline VkDescriptorSetLayout descriptorSetLayout;
    static inline VkPipelineLayout pipelineLayout;
    static inline VkPipeline graphicsPipeline;


    static inline VkCommandPool commandPool;
    static inline std::vector<VkCommandBuffer> commandBuffers;


    static inline std::vector<VkSemaphore> imageAvailableSemaphores;
    static inline std::vector<VkSemaphore> renderFinishedSemaphores;
    static inline std::vector<VkFence> inFlightFences;
    static inline uint32_t currentFrame = 0;


    static inline std::vector<Vertex> vertices;
    static inline std::vector<uint32_t> indices;
    static inline VkBuffer vertexBuffer;
    static inline VkDeviceMemory vertexBufferMemory;
    static inline VkBuffer indexBuffer;
    static inline VkDeviceMemory indexBufferMemory;


    static inline std::vector<VkBuffer> uniformBuffers;
    static inline std::vector<VkDeviceMemory> uniformBuffersMemory;
    static inline std::vector<void*> uniformBuffersMapped;

    static inline VkDescriptorPool descriptorPool;
    static inline std::vector<VkDescriptorSet> descriptorSets;

    static inline VkImage textureImage;
    static inline VkDeviceMemory textureImageMemory;
    static inline VkImageView textureImageView;
    static inline VkSampler textureSampler;

    static inline VkImage depthImage;
    static inline VkDeviceMemory depthImageMemory;
    static inline VkImageView depthImageView;

    static inline glm::mat4 cameraMatrix = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    static inline glm::mat4 modelMatrix = glm::mat4(1.0f);

    static inline std::unordered_map<int, bool> keyStates{};


    static inline bool firstMouse = true;
    static inline glm::vec2 mouseDelta;


    static inline bool framebufferResized = false;

    static inline bool isRunning = false;

    static inline std::chrono::time_point startTime = std::chrono::high_resolution_clock::now();
    static inline std::chrono::time_point lastTime = std::chrono::high_resolution_clock::now();
    static inline float deltaTime;



    static void mouseMove();

    static void camMove();

    static void rotateCamera(float amount, glm::vec3 axis);

    static void moveCamera(glm::vec3 moveVector);


    static VkResult initVolk();

    static void loadVolk(VkInstance instance);

    static void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

    static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) ;

    static void initWindow();

    static void loadModel();

    static void initVulkan();

    static void createInstance();

    static void mainLoop();

    static void cleanup();

    static void cleanupSwapChain();

    static void recreateSwapChain();

    static void createDepthResources();

    static VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    static VkFormat findDepthFormat();

    static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    static void setupDebugMessenger();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    static void createSurface();

    static void pickPhysicalDevice();

    static void createLogicalDevice();

    static void createSwapChain();

    static void createImageViews();

    static void createRenderPass();

    static void createGraphicsPipeline();

    static void createVertexBuffer();

    static void createIndexBuffer();

    static void createUniformBuffers();

    static void createDescriptorPool();

    static void createDescriptorSets();

    static void updateUniformBuffers(uint32_t currentImage);

    static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    static void createFramebuffers();

    static void createCommandPool();

    static void createTextureImage();

    static void createTextureSampler();

    static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

    static void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

    static void createCommandBuffers();

    static void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    static VkCommandBuffer beginSingleTimeCommands();

    static void endSingleTimeCommands(VkCommandBuffer commandBuffer);

    static void createSyncObjects();

    static void drawFrame();

    static void createDescriptorSetLayout();

    static VkShaderModule createShaderModule(const std::vector<char>& code);

    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    static bool isDeviceSuitable(VkPhysicalDevice device);

    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    static std::vector<const char*> getRequiredExtensions();

    static bool checkValidationLayerSupport();

    static bool enableValidation();

    static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};