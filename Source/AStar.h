#pragma once 
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "IAlgorithm.h"

class Map;

namespace Algorithms
{
    MODULE_API class AStar : public IAlgorithm
    {
    public:
        AStar(Map* map, Point2 startPosition, Point2 endPosition);
        ~AStar();

        Point2 StartPosition();
        Point2 EndPosition();

        bool MapContainsObsticles();

    private:

        Map* m_map;
        Point2 m_startPosition;
        Point2 m_endPosition;
    };
}