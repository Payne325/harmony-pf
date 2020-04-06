#include "Map.h"
#include <stdexcept>

Map::Map(
    int sizeX,
    int sizeY,
    const std::vector<Point2>& obsticles)
{
    for (const Point2& point : obsticles)
    {
        if (point.X > sizeX ||
            point.X < 0 ||
            point.Y > sizeY ||
            point.Y < 0)
        {
            throw std::invalid_argument(
                "Obsticle out of bounds! Map Construction Failed!");
        }
    }

    m_sizeX = sizeX;
    m_sizeY = sizeY;

    m_mapSpace = std::unique_ptr<nodeArr[]>(new nodeArr[m_sizeX]);

    for (size_t i = 0; i < m_sizeX; ++i)
    {
        m_mapSpace[i] = nodeArr(new Node[m_sizeY]);

        for (size_t j = 0; j < m_sizeY; ++j)
        {
            m_mapSpace[i][j] = Node();
            m_mapSpace[i][j].position = Point2(i, j);
            m_mapSpace[i][j].isObsticle = false;
        }
    }

    for (const Point2& point : obsticles)
    {
        m_mapSpace[point.X][point.Y].isObsticle = true;
    }

}

Map::~Map()
{
}

bool Map::ContainsObsticles() const
{
    for (int i = 0; i < m_sizeX; ++i)
    {
        for (int j = 0; j < m_sizeY; ++j)
        {
            if (m_mapSpace[i][j].isObsticle) 
                return true;
        }
    }

    return false;
}

Point2 Map::Size() const
{
    return Point2(m_sizeX, m_sizeY);
}

bool Map::IsObsticle(const Point2& point) const
{
    return m_mapSpace[point.X][point.Y].isObsticle;
}

Node* Map::GetNode(const Point2& point) const
{
    return &(m_mapSpace[point.X][point.Y]);
}

std::vector<Node*> Map::GetNodesAdjacentTo(const Point2& point) const
{
    std::vector<Node*> adjacentNodes;
    auto target = GetNode(point);

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == j && j == 0) continue;

            Point2 pos(target->position.X + i, target->position.Y + j);
            if (!PointLiesWithinMap(pos)) continue;

            auto adjacentNode = GetNode(pos);
            adjacentNodes.push_back(adjacentNode);
        }
    }

    return adjacentNodes;
}

bool Map::PointLiesWithinMap(const Point2& p) const
{
    if (p.X < 0 || p.Y < 0) return false;
    if (p.X >= m_sizeX || p.Y >= m_sizeY) return false;

    return true;
}
