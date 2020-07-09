#include "FilterGamma.h"

namespace imaging {

	FilterGamma::FilterGamma(float gamma) {
		this->gamma = gamma;
	}

	FilterGamma::FilterGamma(const FilterGamma& filter) {
		gamma = filter.gamma;
	}

	Image FilterGamma::operator << (const Image& image) {
		Image* copy_image = new Image(image);
		Image& newImage = *copy_image;
		float* new_data = new float[newImage.width * newImage.height * 3];
		int counter = 0;
		for (int y = 0; y < (newImage.height); y++) {
			for (int x = 0; x < newImage.width; x++) {
				new_data[counter++] = powf(newImage(x, y).x, gamma);
				new_data[counter++] = powf(newImage(x, y).y, gamma);
				new_data[counter++] = powf(newImage(x, y).z, gamma);
			}
		}
		for (int i = 0; i < newImage.width * newImage.height * 3; i++) {
			newImage.data[i] = new_data[i];
		}
		newImage.setArray();
		return newImage;
	}
}