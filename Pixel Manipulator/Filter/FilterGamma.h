#ifndef _GAMMAFILTER
#define _GAMMAFILTER

#include "Filter.h"

namespace imaging {

	class FilterGamma : public Filter {
		float gamma;
	public:
		FilterGamma(float gamma);
		FilterGamma(const FilterGamma& filter);
		Image operator << (const Image& image);

	};
}

#endif;