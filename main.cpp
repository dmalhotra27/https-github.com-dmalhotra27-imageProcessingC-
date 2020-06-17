
#include <opencv2/opencv.hpp>
#include<fstream>
#include <iostream>
#include <string>
#include "image.h"
#include <unordered_map>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat gray;
	
	const char* keys =
		"{ help  h     | | Print help message. }"
		"{ shape       | 256,256 | input image dimensions }";		
		
	CommandLineParser cmd(argc, argv, keys);
	
	// raise error if insufficient command line arguments passed
    if(argc == 1)
    {
        cout << "Usage : " << argv[0] << " <inputfile> [options]" << endl;
        cout << "Available options:" << endl;
        cmd.printMessage();
        return EXIT_SUCCESS;
    }
	
	// input file to be processed
	String infile = argv[1];
	int length = infile.size();

	//to determine type of fiel as binary or any other format
	String fformat = infile.substr(length - 3, length);
	
	//to capture width,height values from command line
	String dim = argv[3];
	
	int pos = dim.find(",");
	
	// parse dimensions into width & height separately
	string width = dim.substr(0, pos);
	string height = dim.substr(pos + 1);
	
	//initialize an image object
	Image image = Image(std::stoi(width), std::stoi(height));
	
	// binary file processing
	if (!fformat.compare("bin"))
	{
		// open the input file
		ifstream input(infile, std::ios::binary);

		// copies all data into bufferChar
		vector<unsigned char> bufferChar(std::istreambuf_iterator<char>(input), {});

		// converts the char data into unsigned int
		vector<unsigned int> buffer;
		for (int i = 0; i < bufferChar.size(); i++) {
			buffer.push_back(static_cast<unsigned int>(bufferChar[i]));
		}

		// initialise pixel data in the image object
		image.initPixels(buffer);
	}
	// other files processing
	else
	{
		// read an image
		Mat img = imread(argv[1], IMREAD_GRAYSCALE);

		// to raise error if image could not be read
		if (img.empty())
		{
			cout << "Could not read input image file: " << argv[1] << endl;
			cmd.printMessage();
			return -1;
		}

		if (!cmd.check())
		{
			cmd.printErrors();
			return 0;
		}

		gray = img;

		// convert image to gray scale if not already
		if (img.type() != CV_8UC1)
		{
			cout << "Inside type chk";
			cvtColor(img, gray, COLOR_BGR2GRAY);
		}

		// resize gray image generated to the width & height of input image
		Size size1(std::stoi(width), std::stoi(height));
		//resize(gray, gray, size1, 0, 0, INTER_LINEAR_EXACT);
		resize(gray, gray, size1, 0, 0, INTER_NEAREST);

		// initialise pixel data in the image object
		image.initPixels(gray);
		
		//imshow("Original Image", img); // Show our image inside the created window.
	}
		
	// count the numbers of areas of different shades of grey
	vector<unsigned int> countAreas;
	countAreas = image.countAreas();

	// output the results
	//cout << "Output Array::\n";
	for (int i = 0; i < countAreas.size(); i++) {
		cout << countAreas[i] << "\n";
	}
	
	return 0;
}