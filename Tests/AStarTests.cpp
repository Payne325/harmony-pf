#pragma once
#include "AStar.h"
#include "Map.h"
#include <stdexcept>
#include <cstring>
#include <gtest/gtest.h>

using namespace Algorithms;

TEST(AStarSpecification, AStarIsConstructedWithEmptyMap)
{
    Map map(32, 32);
    Point2 startPosition(0, 0);
    Point2 endPosition(31, 31);

    AStar pathFinder(map, startPosition, endPosition);

    EXPECT_FALSE(pathFinder.MapContainsObsticles());
    EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
    EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(AStarSpecification, AStarIsConstructedWithNotEmptyMap)
{
    std::vector<Point2> obsticles;
    obsticles.push_back(Point2(2, 2));

    Map map(32, 32, obsticles);

    Point2 startPosition(0, 0);
    Point2 endPosition(31, 31);

    AStar pathFinder(map, startPosition, endPosition);

    EXPECT_TRUE(pathFinder.MapContainsObsticles());
    EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
    EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(AStarSpecification, AStarIsConstructedWithNonZeroStartPosition)
{
    Map map(32, 32);

    Point2 startPosition(10, 25);
    Point2 endPosition(31, 31);

    AStar pathFinder(map, startPosition, endPosition);

    EXPECT_FALSE(pathFinder.MapContainsObsticles());
    EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
    EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(AStarSpecification, AStarIsNotConstructedWithNegativeStartPosition)
{
    Map map(32, 32);

    Point2 startPosition(-1, -1);
    Point2 endPosition(31, 31);

    try
    {
        AStar pathFinder(map, startPosition, endPosition);
        EXPECT_TRUE(false);
    }
    catch (const std::invalid_argument & e)
    {
        EXPECT_TRUE(strcmp(e.what(),
            "StartPosition out of bounds! Algorithm Construction Failed!") == 0);
    }
}

TEST(AStarSpecification, AStarIsNotConstructedWithNegativeEndPosition)
{
    Map map(32, 32);

    Point2 startPosition(0, 0);
    Point2 endPosition(-14, -21);

    try
    {
        AStar pathFinder(map, startPosition, endPosition);
        EXPECT_TRUE(false);
    }
    catch (const std::invalid_argument & e)
    {
        EXPECT_TRUE(strcmp(e.what(),
            "EndPosition out of bounds! Algorithm Construction Failed!") == 0);
    }
}

TEST(AStarSpecification, AStarReturnsPathWhenRun)
{
    Map map(6, 6);

    Point2 startPosition(2, 2);
    Point2 endPosition(4, 4);

    std::vector<Point2> expectedPath = { Point2(2,2), Point2(3, 3), Point2(4, 4) };
    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}

TEST(AStarSpecification, AStarNavigatesAroundAnObsticle)
{
    std::vector<Point2> obsticles = { Point2(0, 1)};
    Map map(2, 3, obsticles);

    Point2 startPosition(0, 0);
    Point2 endPosition(0, 2);

    std::vector<Point2> expectedPath = { Point2(0,0), Point2(1, 1), Point2(0, 2) };
    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}

TEST(AStarSpecification, AStarNavigatesAroundTwoObsticles)
{
    std::vector<Point2> obsticles = { Point2(3, 3), Point2(4, 3) };
    Map map(6, 6, obsticles);

    Point2 startPosition(2, 2);
    Point2 endPosition(4, 4);

    std::vector<Point2> expectedPath = { Point2(2,2), Point2(2, 3), Point2(3, 4), Point2(4, 4) };
    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}

TEST(AStarSpecification, AStarNavigatesAroundThreeObsticles)
{
    std::vector<Point2> obsticles = { Point2(3, 3), Point2(4, 3), Point2(2, 2) };
    Map map(6, 6, obsticles);

    Point2 startPosition(4, 4);
    Point2 endPosition(0, 1);

    std::vector<Point2> expectedPath = { Point2(4, 4), Point2(3, 4), Point2(2, 3), Point2(1, 2), Point2(0, 1) };
    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}

TEST(AStarSpecification, AStarCanNotMoveWhenTrapped)
{
    std::vector<Point2> obsticles = { Point2(4, 5), Point2(4, 4), Point2(5, 4) };
    Map map(6, 6, obsticles);

    Point2 startPosition(5, 5);
    Point2 endPosition(0, 1);

    std::vector<Point2> expectedPath = { };
    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}

TEST(AStarSpecification, AStarCanNotMoveToPointOutsideOfTheMap)
{
    Map map(6, 6);

    Point2 startPosition(5, 5);
    Point2 endPosition(7, 7);

    try
    {
        AStar pathFinder(map, startPosition, endPosition);
        EXPECT_TRUE(false);
    }
    catch (const std::invalid_argument & e)
    {
        EXPECT_TRUE(strcmp(e.what(),
            "EndPosition out of bounds! Algorithm Construction Failed!") == 0);
    }
}

TEST(AStarSpecification, AStarCanTraverseAMaze)
{
    /*
        LEGEND
        ------
        S = Start
        E = End
        0 = Traversable Node
        X = Blocked by obsticle

        MAP
        ---
        |0|0|0|0|0|0|
        |X|X|X|0|X|0|
        |E|0|0|0|X|0|
        |X|X|X|X|X|0|
        |S|0|0|0|0|0|
    */
    std::vector<Point2> obsticles = 
    { 
        Point2(0, 1), 
        Point2(1, 1), 
        Point2(2, 1), 
        Point2(3, 1), 
        Point2(4, 1), 
        Point2(4, 2), 
        Point2(4, 3), 
        Point2(0, 3), 
        Point2(1, 3), 
        Point2(2, 3) };

    Map map(6, 5, obsticles);

    Point2 startPosition(0, 0);
    Point2 endPosition(0, 2);

    std::vector<Point2> expectedPath = 
    {
        Point2(0, 0),
        Point2(1, 0),
        Point2(2, 0), 
        Point2(3, 0),
        Point2(4, 0), 
        Point2(5, 1),
        Point2(5, 2), 
        Point2(5, 3), 
        Point2(4, 4), 
        Point2(3, 3), 
        Point2(2, 2), 
        Point2(1, 2),
        Point2(0, 2)
    };

    AStar pathFinder(map, startPosition, endPosition);

    auto metrics = pathFinder.Run();

    EXPECT_TRUE(expectedPath.size() == metrics.calculated_route.size());
    EXPECT_TRUE(std::equal(expectedPath.begin(), expectedPath.end(), metrics.calculated_route.begin()));
}
