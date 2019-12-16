#pragma once
#include "Map.h"
#include <stdexcept>
#include <cstring>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(MapSpecification, EmptyMapIsConstructed)
{
	Map map(32, 32);

	ASSERT_FALSE(map.ContainsObsticles());
	ASSERT_TRUE(map.Size() == Point2(32, 32));
}

TEST(MapSpecification, MapWithObsticlesIsConstructed)
{
	std::vector<Point2> obsticles;

	obsticles.push_back(Point2(13, 13));

	Map map(32, 32, obsticles);

	ASSERT_TRUE(map.ContainsObsticles());
	ASSERT_TRUE(map.IsObsticle(Point2(13, 13)));
}

TEST(MapSpecification, MapWithObsticlesOutsideSpaceIsInvalid)
{
	std::vector<Point2> obsticles;

	obsticles.push_back(Point2(130, 13));

	try
	{
		Map map(32, 32, obsticles);
		ASSERT_TRUE(false);
	}
	catch(const std::invalid_argument& e)
	{	
		EXPECT_TRUE(strcmp(e.what(),
			"Obsticle out of bounds! Map Construction Failed!") == 0);
	}
}

TEST(MapSpecification, MapWithObsticleInNegativeSpaceIsInvalid)
{
	std::vector<Point2> obsticles;

	obsticles.push_back(Point2(-1, -34));

	try
	{
		Map map(32, 32, obsticles);
		ASSERT_TRUE(false);
	}
	catch(const std::invalid_argument& e)
	{	
		EXPECT_TRUE(strcmp(e.what(),
			"Obsticle out of bounds! Map Construction Failed!") == 0);
	}
}

