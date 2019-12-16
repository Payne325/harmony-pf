#include "AStar.h"
#include "Map.h"
#include "Node.h"
#include <stdexcept>
#include <algorithm>

namespace Algorithms
{
    AStar::AStar(
        const Map& map,
        const Point2& startPosition,
        const Point2& endPosition)
        :
        m_map(map),
        m_startPosition(startPosition),
        m_endPosition(endPosition)
    {
        if (startPosition.X < 0 ||
            startPosition.Y < 0)
        {
            throw std::invalid_argument(
                "StartPosition out of bounds! Algorithm Construction Failed!");
        }

        if (endPosition.X < 0 ||
            endPosition.Y < 0)
        {
            throw std::invalid_argument(
                "EndPosition out of bounds! Algorithm Construction Failed!");
        }
    }

    AStar::~AStar()
    {
    }

    Point2 AStar::StartPosition()
    {
        return m_startPosition;
    }

    Point2 AStar::EndPosition()
    {
        return m_endPosition;
    }

    Metrics AStar::Run()
    {
        //A Star Algorithm 

        std::vector<Node> openList;
        std::vector<Node> closedList;

        Node startNode;
        startNode.position = m_startPosition;
        startNode.cost = 0.0;
        startNode.parent = nullptr;

        openList.push_back(startNode);

        Node goalNode;

        while (!openList.empty())
        {
            auto currentNodeIt = std::min_element(openList.begin(), openList.end(),
                [](const Node& first, const Node& second)
                {
                    return first.cost < second.cost;
                });

            if (currentNodeIt->position == m_endPosition)
            {
                //TODO: record time taken here
                goalNode = *currentNodeIt;
                break;
            }
            else
            {
                Node currentNode = *currentNodeIt;
                closedList.push_back(currentNode);
                openList.erase(currentNodeIt);

                std::vector<Node> adjacentNodes;

                for (int i = -1; i <= 1; ++i)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        if (i == j == 0) continue;

                        Node node;
                        node.position = Point2(currentNode.position.X + i, currentNode.position.Y + j);
                        node.parent = &(currentNode);
                        adjacentNodes.push_back(node);
                    }
                }

                for (auto& node : adjacentNodes)
                {
                    auto notInOpenList = std::find_if(openList.begin(), openList.end(),
                        [&currentNode](const Node& node)
                        {
                            return node.position == currentNode->position;
                        }) == openList.end();

                    auto notInClosedList = std::find_if(closedList.begin(), closedList.end(),
                        [&currentNode](const Node& node)
                        {
                            return node.position == currentNode->position;
                        }) == closedList.end();

                    if (notInOpenList && notInClosedList)
                    {
                        if (m_map.IsObsticle(node.position))
                        {
                            closedList.push_back(node);
                        }
                        else
                        {
                            float h_cost = std::abs(node.position.X + m_endPosition.X) + std::abs(node.position.Y + m_endPosition.Y);
                            node.cost = node.parent->cost + h_cost;
                            openList.push_back(node);
                        }
                    }
                }
            }
        }

        Metrics met;
        met.calculated_route.push_back(goalNode.position);

        Node* pathNode = &goalNode;
        while (pathNode->parent != nullptr)
        {
            met.calculated_route.insert(met.calculated_route.begin(), pathNode->parent->position);
            pathNode = pathNode->parent;
        }

        return met;
    }

    bool AStar::MapContainsObsticles()
    {
        return m_map.ContainsObsticles();
    }
}
