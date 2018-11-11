#include "Point2.h"

namespace Algorithms
{
	class IAlgorithm
	{
		public:

		virtual Point2 StartPosition() = 0;
		virtual Point2 EndPosition() = 0;

		virtual bool MapContainsObsticles() = 0;
	};
}