#pragma once 
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "IAlgorithm.h"
#include "Node.h"
#include <vector>

class Map;

typedef std::vector<Node> Harmony;

namespace Algorithms
{
    MODULE_API class HarmonySearch : public IAlgorithm
    {
    public:
        HarmonySearch(
            const Map& map, 
            const Point2& startPosition, 
            const Point2& endPosition, 
            const float& harmonyMemoryConsiderationRate = 0.8, 
            const float& pitchAdjustmentRate = 0.25,
            const int maxIterations = 100, 
            const int harmonyMemorySize = 8);

        ~HarmonySearch();

        Point2 StartPosition() override;
        Point2 EndPosition() override;
        Metrics Run() override;
        bool MapContainsObsticles() override;

    private:
        const Map& m_map;
        Point2 m_startPosition;
        Point2 m_endPosition;
        std::vector<Harmony> m_harmonyMemory;
        float m_harmonyMemoryConsiderationRate;
        float m_pitchAdjustmentRate;
        int m_maxIterations;
        int m_harmonyMemorySize;

        Harmony getRandomHarmony();
        Harmony getNextHarmony();
        int quality(const Harmony& harmony);
    };
}
