#ifndef _IMAGE
#define _IMAGE

#define Color math::Vec3<float>

#include "ppm.h"
#include "vec3.h"
#include "imageio.h"
#include "array2d.h"

#include <iostream>

using namespace std;

class Image : public math::Array2D<Color>, public image::ImageIO {
public:

	int width, height;
	float* data = NULL;
	math::Array2D<Color> pixeldata;

	Image() {}

	Image(const Image& src) {
		this->width = src.width;
		this->height = src.height;
		this->data = src.data;
		this->pixeldata = src.pixeldata;
	}


	bool check(const std::string& filename, const std::string& format) {
		string name = filename;
		string ext = format;
		string dot = ".";

		name.erase(0, name.find(dot) + dot.length());
		string extension = name.substr(0, name.find(dot));

		for (auto& c : extension) { c = tolower(c); }
		for (auto& c : ext) { c = tolower(c); }

		return extension == ext;
	}

	void setArray() {
		int size = width * height;

		Color* pixels = new Color[size];
		Color* pixel = new Color;

		int counter = 0;
		for (int i = 0; i < width * height * 3; i += 3) {
			pixel = &Color(data[i], data[i + 1], data[i + 2]);
			pixels[counter] = *pixel;
			counter += 1;
		}

		math::Array2D<Color> buffer(width, height, pixels);

		this->pixeldata = buffer;
	}

	bool load(const std::string& filename, const std::string& format) {

		if (check(filename, format)) {
			data = image::ReadPPM(filename.c_str(), &width, &height);

			setArray();
			return true;
		}
		else {
			cout << "Wrong format" << endl;
			return false;
		}
	}

	bool save(const std::string& filename, const std::string& format) {

		if (check(filename, format)) {
			image::WritePPM(data, width, height, filename.c_str());

			return true;
		}
		else {
			cout << "Wrong format" << endl;
			return false;
		}
	}

	Color operator () (unsigned int x, unsigned int y) {
		return this->pixeldata(x, y);
	}

};
#endif