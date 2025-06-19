#pragma once

#include <vector>

class Polygon {
public:
    static void GenerateCircle(float centerX, float centerY, float radius, int segments,
        std::vector<float>& outVertices,
        std::vector<unsigned int>& outIndices);
};
