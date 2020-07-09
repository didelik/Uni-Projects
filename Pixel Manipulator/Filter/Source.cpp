#pragma warning( disable : 4244)

#include "FilterLinear.h"
#include "FilterGamma.h"

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		system("PAUSE");
		return 0;
	}

	unsigned int i = 1;
	Image* img = new Image();

	string name = argv[argc - 1];
	bool flag1 = img->load(name, "ppm");

	if (!flag1) {
		cerr << "There was a problem loading file..";
		system("PAUSE");
		return 0;
	}

	while (i < argc - 1) {

		if (!strcmp(argv[i++], "-f")) {
			if (!strcmp(argv[i], "linear")) {
				cout << "Applying Linear Filter..." << endl;
				i++;

				float a1, a2, a3, c1, c2, c3;
				a1 = atof(argv[i++]);
				a2 = atof(argv[i++]);
				a3 = atof(argv[i++]);
				c1 = atof(argv[i++]);
				c2 = atof(argv[i++]);
				c3 = atof(argv[i++]);
	
				imaging::FilterLinear filter(Color(a1, a2, a3), Color(c1, c2, c3));
				img = &(filter << *img);
			}

			else if (!strcmp(argv[i], "gamma")) {
				cout << "Applying Gamma Filter..." << endl;
				i++;

				imaging::FilterGamma filter(atof(argv[i++]));
				img = &(filter << *img);
				if (i == argc - 1) {
					return 0;
				}
			}
			else {
				cerr << "Invalid filter" << endl;
				system("PAUSE");
				return 0;
			}
		}
		else {
			cerr << "Invalid inputs" << endl;
			system("PAUSE");
			return 0;

		}

	}

	int pos = 1 + name.find_last_of("\\");
	name.insert(pos, "filtered_");

	bool flag2 = img->save(name, "ppm");
	if (!flag2) {
		cerr << "There was a problem saving file.." << endl;
		system("PAUSE");
		return 0;
	}

	system("PAUSE");
	return 0;

}
	