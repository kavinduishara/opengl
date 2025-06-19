#include "Polygon.h"
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>

void Polygon::GenerateCircle(float centerX, float centerY, float radius, int segments,
    std::vector<float>& outVertices,
    std::vector<unsigned int>& outIndices) {
    outVertices.clear();
    outIndices.clear();

    // Center vertex
    outVertices.push_back(centerX);
    outVertices.push_back(centerY);

    // Outer vertices
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        outVertices.push_back(centerX + std::cos(angle) * radius);
        outVertices.push_back(centerY + std::sin(angle) * radius);
    }

    // Triangle fan indices
    for (int i = 0; i < segments; ++i) {
        outIndices.push_back(0);
        outIndices.push_back(i + 1);
        outIndices.push_back((i + 2 > segments) ? 1 : i + 2);
    }
}
