#pragma once
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "Node.h"
#include <vector>
#include <memory>

typedef std::unique_ptr<Node[]> nodeArr;

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

    Node* GetNode(int x, int y) const;

    std::vector<Node*> GetNodesAdjacentTo(int x, int y) const;

private:
    int m_sizeX;
    int m_sizeY;

    std::unique_ptr<nodeArr[]> m_mapSpace;

    bool isValidPosition(int x, int y) const;
};
