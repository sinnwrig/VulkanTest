CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
GLSLC = /usr/local/glslc/bin/glslc

.PHONY: VulkanTest test clean shader

VulkanTest:
	g++ $(CFLAGS) -o VulkanTest_x86_64 source/*.cpp $(LDFLAGS) -I include

test: VulkanTest
	./VulkanTest_x86_64

clean:
	rm -f VulkanTest

shader: 
	$(GLSLC) shaders/source/triangle.vert -o shaders/SPIR-V/vert.spv
	$(GLSLC) shaders/source/triangle.frag -o shaders/SPIR-V/frag.spv 
