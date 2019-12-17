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
        AStar(const Map& map, const Point2& startPosition, const Point2& endPosition);
        ~AStar();

        Point2 StartPosition() override;
        Point2 EndPosition() override;
        Metrics Run() override;
        bool MapContainsObsticles() override;

    private:
        const Map& m_map;
        Point2 m_startPosition;
        Point2 m_endPosition;
    };
}
