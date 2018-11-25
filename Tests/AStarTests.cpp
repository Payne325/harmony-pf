//#pragma once
#include "AStar.h"
#include <stdexcept>
#include <cstring>
#include <gtest/gtest.h>

using namespace Algorithms;

char** ConstructMapWithNoObsticles(int size)
{
	char** map = new char*[size];

	for(int i = 0; i < size; ++i)
	{
		map[i] = new char[size];
	}

	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			map[i][j] = 'E';
		}
	}

	return map;
}

char** ConstructMapWithOneObsticle(int size)
{
	char** map = new char*[size];

	for(int i = 0; i < size; ++i)
	{
		map[i] = new char[size];
	}

	int obsticleXYPosition = 2;

	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if (i == obsticleXYPosition && 
				j == obsticleXYPosition)
			{
				map[i][j] = 'O';
			}
			else
			{
				map[i][j] = 'E';
			}
		}
	}

	return map;
}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }

TEST(AStarSpecification, AStarIsConstructedWithEmptyMap)
{
	char** map = ConstructMapWithNoObsticles(32);
	Point2 startPosition(0, 0);
	Point2 endPosition(31, 31);

	IAlgorithm* pathFinder = new AStar(map, startPosition, endPosition);
	
	EXPECT_FALSE(pathFinder->MapContainsObsticles());
	EXPECT_TRUE(pathFinder->StartPosition() == startPosition);
	EXPECT_TRUE(pathFinder->EndPosition() == endPosition);

	delete pathFinder;
}

TEST(AStarSpecification, AStarIsConstructedWithNotEmptyMap)
{
	char** map = ConstructMapWithOneObsticle(32);
	Point2 startPosition(0, 0);
	Point2 endPosition(31, 31);

	IAlgorithm* pathFinder = new AStar(map, startPosition, endPosition);
	
	EXPECT_TRUE(pathFinder->MapContainsObsticles());
	EXPECT_TRUE(pathFinder->StartPosition() == startPosition);
	EXPECT_TRUE(pathFinder->EndPosition() == endPosition);

	delete pathFinder;
}

TEST(AStarSpecification, AStarIsConstructedWithNonZeroStartPosition)
{
	char** map = ConstructMapWithOneObsticle(32);
	Point2 startPosition(10, 25);
	Point2 endPosition(31, 31);

	IAlgorithm* pathFinder = new AStar(map, startPosition, endPosition);
	
	EXPECT_TRUE(pathFinder->MapContainsObsticles());
	EXPECT_TRUE(pathFinder->StartPosition() == startPosition);
	EXPECT_TRUE(pathFinder->EndPosition() == endPosition);

	delete pathFinder;
}

TEST(AStarSpecification, AStarIsNotConstructedWithNegativeStartPosition)
{
	char** map = ConstructMapWithOneObsticle(32);
	Point2 startPosition(-1, -1);
	Point2 endPosition(31, 31);

	IAlgorithm* pathFinder;
	try
	{
		pathFinder = new AStar(map, startPosition, endPosition);
		EXPECT_TRUE(false);
	}
	catch(const std::invalid_argument& e)
	{
		EXPECT_TRUE(strcmp(e.what(),
			"StartPosition out of bounds! Algorithm Construction Failed!") == 0);
	}
}

TEST(AStarSpecification, AStarIsNotConstructedWithNegativeEndPosition)
{
	char** map = ConstructMapWithOneObsticle(32);
	Point2 startPosition(0, 0);
	Point2 endPosition(-14, -21);

	IAlgorithm* pathFinder;
	try
	{
		pathFinder = new AStar(map, startPosition, endPosition);
		EXPECT_TRUE(false);
	}
	catch(const std::invalid_argument& e)
	{	
		EXPECT_TRUE(strcmp(e.what(),
			"EndPosition out of bounds! Algorithm Construction Failed!") == 0);
	}
}