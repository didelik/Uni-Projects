#ifndef _FILTER
#define _FILTER

#include "image.cpp"

namespace imaging {
	class Filter {

	public:
		virtual Image operator << (const Image & image) = 0;
	};
}

#endif
