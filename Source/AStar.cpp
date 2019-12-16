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

        std::vector<Node*> openList;
        std::vector<Node*> closedList;

        Node* startNode = m_map.GetNode(m_startPosition);

        openList.push_back(startNode);

        Node* goalNode = nullptr;

        while (!openList.empty())
        {
            auto currentNodeIt = std::min_element(openList.begin(), openList.end(),
                [](const Node* first, const Node* second)
                {
                    return first->cost < second->cost;
                });

            if ((*currentNodeIt)->position == m_endPosition)
            {
                //TODO: record time taken here
                goalNode = *currentNodeIt;
                break;
            }
            else
            {
                Node* currentNode = *currentNodeIt;
                closedList.push_back(currentNode);
                openList.erase(currentNodeIt);

                auto adjacentNodes = m_map.GetNodesAdjacentTo(currentNode->position);

                for (auto& adjacentNode : adjacentNodes)
                {
                    auto notInOpenList = std::find_if(openList.begin(), openList.end(),
                        [&adjacentNode](const Node* node)
                        {
                            return node->position == adjacentNode->position;
                        }) == openList.end();

                    auto notInClosedList = std::find_if(closedList.begin(), closedList.end(),
                        [&adjacentNode](const Node* node)
                        {
                            return node->position == adjacentNode->position;
                        }) == closedList.end();

                    if (notInOpenList && notInClosedList)
                    {
                        if (m_map.IsObsticle(adjacentNode->position))
                        {
                            closedList.push_back(adjacentNode);
                        }
                        else
                        {
                            float h_cost = 
                                std::abs(adjacentNode->position.X - m_endPosition.X) +
                                std::abs(adjacentNode->position.Y - m_endPosition.Y);

                            adjacentNode->parent = currentNode;
                            adjacentNode->cost = adjacentNode->parent->cost + h_cost;
                            openList.push_back(adjacentNode);
                        }
                    }
                }
            }
        }

        if (goalNode == nullptr) 
            return Metrics();

        Metrics met;
        met.calculated_route.push_back(goalNode->position);

        while (goalNode->parent != nullptr)
        {
            met.calculated_route.insert(met.calculated_route.begin(), goalNode->parent->position);
            goalNode = goalNode->parent;
        }

        return met;
    }

    bool AStar::MapContainsObsticles()
    {
        return m_map.ContainsObsticles();
    }
}
