#pragma once 

#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif


#include "Point2.h"

namespace Algorithms
{
    MODULE_API class IAlgorithm
    {
    public:
        virtual ~IAlgorithm() {};
        virtual Point2 StartPosition() = 0;
        virtual Point2 EndPosition() = 0;

        virtual bool MapContainsObsticles() = 0;
    };
}