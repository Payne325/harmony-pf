#pragma once
#include "HarmonySearch.h"
#include "Map.h"
#include <stdexcept>
#include <cstring>
#include <gtest/gtest.h>

using namespace Algorithms;

TEST(HarmonySpecification, HarmonySearchIsConstructedWithEmptyMap)
{
   Map map(32, 32);
   Point2 startPosition(0, 0);
   Point2 endPosition(31, 31);

   HarmonySearch pathFinder(map, startPosition, endPosition);

   EXPECT_FALSE(pathFinder.MapContainsObsticles());
   EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
   EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(HarmonySpecification, HarmonySearchIsConstructedWithNotEmptyMap)
{
   std::vector<Point2> obsticles;
   obsticles.push_back(Point2(2, 2));

   Map map(32, 32, obsticles);

   Point2 startPosition(0, 0);
   Point2 endPosition(31, 31);

   HarmonySearch pathFinder(map, startPosition, endPosition);

   EXPECT_TRUE(pathFinder.MapContainsObsticles());
   EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
   EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(HarmonySpecification, HarmonySearchIsConstructedWithNonZeroStartPosition)
{
   Map map(32, 32);

   Point2 startPosition(10, 25);
   Point2 endPosition(31, 31);

   HarmonySearch pathFinder(map, startPosition, endPosition);

   EXPECT_FALSE(pathFinder.MapContainsObsticles());
   EXPECT_TRUE(pathFinder.StartPosition() == startPosition);
   EXPECT_TRUE(pathFinder.EndPosition() == endPosition);
}

TEST(HarmonySpecification, HarmonySearchIsNotConstructedWithNegativeStartPosition)
{
   Map map(32, 32);

   Point2 startPosition(-1, -1);
   Point2 endPosition(31, 31);

   try
   {
      HarmonySearch pathFinder(map, startPosition, endPosition);
      EXPECT_TRUE(false);
   }
   catch (const std::invalid_argument & e)
   {
      EXPECT_TRUE(strcmp(e.what(),
         "StartPosition out of bounds! Algorithm Construction Failed!") == 0);
   }
}

TEST(HarmonySpecification, HarmonySearchIsNotConstructedWithNegativeEndPosition)
{
   Map map(32, 32);

   Point2 startPosition(0, 0);
   Point2 endPosition(-14, -21);

   try
   {
      HarmonySearch pathFinder(map, startPosition, endPosition);
      EXPECT_TRUE(false);
   }
   catch (const std::invalid_argument & e)
   {
      EXPECT_TRUE(strcmp(e.what(),
         "EndPosition out of bounds! Algorithm Construction Failed!") == 0);
   }
}

TEST(HarmonySpecification, HarmonySearchReturnsPathWhenRun)
{
   Map map(6, 6);

   Point2 startPosition(2, 2);
   Point2 endPosition(4, 4);

   HarmonySearch pathFinder(map, startPosition, endPosition);

   auto metrics = pathFinder.Run();

   EXPECT_TRUE(metrics.calculated_route.size() > 0);
}
