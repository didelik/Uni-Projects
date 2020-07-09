#ifndef _FILTERLINEAR
#define _FILTERLINEAR
#include "Filter.h"

namespace imaging {

	class FilterLinear : public Filter {
		Color a, c;
	public:
		FilterLinear(Color a, Color c);
		FilterLinear(const FilterLinear &filter);
		Image operator << (const Image & image);

	};
}

 
#endif;