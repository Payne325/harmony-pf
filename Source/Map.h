#pragma once
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "Point2.h"
#include <vector>
#include <memory>

typedef std::unique_ptr<char[]> charArr;

MODULE_API class Map
{
public:
    Map(
        int sizeX,
        int sizeY,
        const std::vector<Point2>& obsticles = std::vector<Point2>());

    ~Map();

    bool ContainsObsticles() const;

    Point2 Size() const;

    bool IsObsticle(const Point2& point) const;

private:
    int m_sizeX;
    int m_sizeY;

    std::unique_ptr<charArr[]> m_mapSpace;
};
