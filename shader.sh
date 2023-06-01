#!/bin/bash

glslc=/usr/local/glslc/bin/glslc

echo "Compiling Vertex Shader"
$glslc shaders/source/triangle.vert -o shaders/SPIR-V/vert.spv
echo "Compiling Fragment Shader"
$glslc shaders/source/triangle.frag -o shaders/SPIR-V/frag.spv