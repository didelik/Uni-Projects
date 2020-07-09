#include "FilterLinear.h"

namespace imaging {

	FilterLinear::FilterLinear(Color a, Color c) {
		this->a = a;
		this->c = c;
	}

	FilterLinear::FilterLinear(const FilterLinear& filter) {
		a = filter.a;
		c = filter.c;
	}

	Image FilterLinear::operator << (const Image& image) {
		Image* copy_image = new Image(image);
		Image& newImage = *copy_image;
		
		float* new_data = new float[newImage.width * newImage.height * 3];
		int counter = 0;
		
		for (int y = 0; y < (newImage.height); y++) {
			for (int x = 0; x < newImage.width; x++) {
					new_data[counter++] = (a * newImage(x, y) + c)[0];
					new_data[counter++] = (a * newImage(x, y) + c)[1];
					new_data[counter++] = (a * newImage(x, y) + c)[2];
				
			}
		}
		for (int i = 0; i < newImage.width * newImage.height * 3; i++) {
			newImage.data[i] = new_data[i];
		}
		newImage.setArray();
		
		return newImage;
	}
}