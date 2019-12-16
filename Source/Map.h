#pragma once
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "Point2.h"
#include <vector>

MODULE_API class Map
{
public:
    Map(
        int sizeX,
        int sizeY,
        const std::vector<Point2>& obsticles = std::vector<Point2>());

    ~Map();

    bool ContainsObsticles();

    Point2 Size();

    bool IsObsticle(const Point2& point);

private:
    int m_sizeX;
    int m_sizeY;

    char** m_mapSpace;
};