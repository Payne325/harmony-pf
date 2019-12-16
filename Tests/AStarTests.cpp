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
