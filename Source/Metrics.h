#pragma once 
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "Point2.h"
#include <chrono>
#include <vector>

MODULE_API struct Metrics
{
    Metrics()
    {
        time_taken = std::chrono::duration<double>(0.0);
    }

    //bool operator== (const Metrics& rhs)
    //{
    //    return
    //        this->time_taken == rhs.time_taken &&
    //        this->calculated_route == rhs.calculated_route;
    //}

    std::chrono::duration<double> time_taken;
    std::vector<Point2> calculated_route;
};
