#include "Harmony.h"
#include "Map.h"
#include <stdexcept>
#include <random>

const int NUM_OF_INSTRUMENTS = 50;

using namespace Algorithms;

float randomNumber()
{
    // To Do, do not construct random device every call. See video for ref (questions section).
    // https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
    std::random_device rd; 
    std::mt19937 e(rd());
    std::uniform_real_distribution<> dist(0, 1);

    return dist(e);
}

HarmonySearch::HarmonySearch(
    const Map& map,
    const Point2& startPosition,
    const Point2& endPosition,
    const float& harmonyMemoryConsiderationRate,
    const float& pitchAdjustmentRate,
    const int maxIterations,
    const int harmonyMemorySize)
    :
    m_map(map),
    m_startPosition(startPosition),
    m_endPosition(endPosition),
    m_harmonyMemoryConsiderationRate(harmonyMemoryConsiderationRate),
    m_pitchAdjustmentRate(pitchAdjustmentRate),
    m_maxIterations(maxIterations),
    m_harmonyMemorySize(harmonyMemorySize)
{
    //TODO: Code repeated in A*. This could live in some shared place.
    if (!m_map.PointLiesWithinMap(startPosition))
    {
        throw std::invalid_argument(
            "StartPosition out of bounds! Algorithm Construction Failed!");
    }

    if (!m_map.PointLiesWithinMap(endPosition))
    {
        throw std::invalid_argument(
            "EndPosition out of bounds! Algorithm Construction Failed!");
    }
}

HarmonySearch::~HarmonySearch()
{
}

Point2 HarmonySearch::StartPosition()
{
    return m_startPosition;
}

Point2 HarmonySearch::EndPosition()
{
    return m_endPosition;
}

Metrics HarmonySearch::Run()
{
    const int BEST_HARMONY_INDEX = m_harmonyMemorySize - 1;
    const int WORST_HARMONY_INDEX = 0;

    // Initialise Harmony Memory
    for (int i = 0; i < m_harmonyMemorySize; ++i)
    {
        m_harmonyMemory.push_back(getRandomHarmony());
    }

    std::sort(m_harmonyMemory.begin(), m_harmonyMemory.end(), 
        [&](const Harmony& a, const Harmony& b) 
        {
            return cost(a) > cost(b);
        });

    //Harmony Search Meta-Heuristic
    for (int i = 0; i < m_maxIterations; ++i)
    {
        auto newHarmony = getNextHarmony();

        auto worstHarmonyInMemory = m_harmonyMemory[WORST_HARMONY_INDEX];

        if (cost(newHarmony) < cost(worstHarmonyInMemory))
        {
            // TODO
            // Remove worst harmony in memory
            // Add new harmony to memory

            std::sort(m_harmonyMemory.begin(), m_harmonyMemory.end(),
                [&](const Harmony& a, const Harmony& b)
                {
                    return cost(a) > cost(b);
                });
        }
    }

    // Return Best Harmony
    auto bestHarmony = m_harmonyMemory[BEST_HARMONY_INDEX];

    Metrics metrics;

    for (const auto& node : bestHarmony)
    {
        metrics.calculated_route.push_back(node.position);
    }

    return metrics;
}

bool HarmonySearch::MapContainsObsticles()
{
    return m_map.ContainsObsticles();
}

Harmony HarmonySearch::getRandomHarmony()
{
    Harmony newHarmony;

    //Function to generate a random harmony
    for (int i = 0; i < NUM_OF_INSTRUMENTS; ++i)
    {
        int randX = static_cast<int>(floor(randomNumber() * m_map.Size().X));
        int randY = static_cast<int>(floor(randomNumber() * m_map.Size().Y));

        Node node;
        node.position = Point2(randX, randY);
        newHarmony.push_back(node);
    }

    return newHarmony;
}

Harmony HarmonySearch::getNextHarmony()
{
    Harmony nextHarmony;

    for (int i = 0; i < NUM_OF_INSTRUMENTS; ++i)
    {
        Node newNote;

        if (randomNumber() < m_harmonyMemoryConsiderationRate)
        {
            int randomIndex = floor(randomNumber() * m_harmonyMemorySize);

            Harmony randomInMemoryHarmony = m_harmonyMemory[randomIndex];

            newNote = randomInMemoryHarmony[i];

            if (randomNumber() < m_pitchAdjustmentRate)
            {
                float adjustmentX = randomNumber() > 0.5 ? 1 : -1;
                float adjustmentY = randomNumber() > 0.5 ? 1 : -1;

                newNote.position.X += adjustmentX;
                newNote.position.Y += adjustmentY;
            }
        }
        else
        {
            int randomIndex = floor(randomNumber() * NUM_OF_INSTRUMENTS);
            newNote = getRandomHarmony()[randomIndex];
        }

        nextHarmony.push_back(newNote);
    }

    return nextHarmony;
}

int HarmonySearch::cost(const Harmony& harmony)
{
    // Function to detemine the quality of a harmony
    // lower value == better
    // if path contains a node that cannot be traversed then give it the maximum cost
    // if path is not connected (i.e. gaps between nodes) then give it the maximum cost
    // else cost == number of nodes.

    // TODO: Compare this version of harmony search to the one implemented in the dissertation.
    // This is a different way of doing it as I construct a full path as a harmony, rather than finding one node 
    // at a time like the dissertation version. Maybe I should provide both implementations?

    return 0;
}
