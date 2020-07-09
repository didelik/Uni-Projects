#include "ppm.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace image {

	float* ReadPPM(const char* filename, int* w, int* h) {

		string header[4];
		char junk[1];

		string name = filename;
		cout << name << endl;
		string file = "C:\\Users\\dimit\\Desktop\\Images\\" + name;

		ifstream ppm_file(file, ios::binary);
		if (!ppm_file) {
			cerr << "File could not be opened" << endl;

		}
		for (int i = 0; i < 4; i++) {
			ppm_file >> header[i];
		}

		*w = stoi(header[1]);
		*h = stoi(header[2]);
		ppm_file.get(junk[0]);

		const int size = *w * *h * 3;

		char* store = new char[size];
		float* pixeldata = new float[size];

		for (int i = 0; i < size; i += 1) {
			ppm_file.get(store[i]);
			pixeldata[i] = (int)((unsigned char)(store[i])) / 255.f;
		}
		return pixeldata;
	}


	bool WritePPM(const float* data, int w, int h, const char* filename) {

		int size = w * h * 3;
		string name = filename;
		cout << name << endl;

		string file1 = "C:\\Users\\dimit\\Desktop\\Images\\" + name;

		ofstream newfile(file1, ios::binary);
		newfile << "P6" << "\n" << w << "\n" << h << "\n" << 255 << endl;

		for (int i = 0; i < size; i++) {
			newfile.put((char)(data[i] * 255));
		}
		return true;
	}
}