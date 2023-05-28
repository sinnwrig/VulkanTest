#pragma once

#define GLFW_INCLUDE_VULKAN
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
#include <glm/glm.hpp>


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
    glm::vec2 pos;
    glm::vec3 color;


    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }


    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions {};
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};


struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};



class Application {
public:
    static void run() {
        if (isRunning) {
            throw std::runtime_error("application is already running!");
        }

        isRunning = true;

        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

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


    static inline VkBuffer vertexBuffer;
    static inline VkDeviceMemory vertexBufferMemory;
    static inline VkBuffer indexBuffer;
    static inline VkDeviceMemory indexBufferMemory;


    static inline std::vector<VkBuffer> uniformBuffers;
    static inline std::vector<VkDeviceMemory> uniformBuffersMemory;
    static inline std::vector<void*> uniformBuffersMapped;

    static inline VkDescriptorPool descriptorPool;
    static inline std::vector<VkDescriptorSet> descriptorSets;



    static inline bool framebufferResized = false;

    static inline bool isRunning = false;


    static void initWindow();

    static void initVulkan();

    static void createInstance();

    static void mainLoop();

    static void cleanup();

    static void cleanupSwapChain();

    static void recreateSwapChain();

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

    static void createCommandBuffers();

    static void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

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

    static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};