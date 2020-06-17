#pragma once

#include <iostream>
#include <vector>
#include "pixel.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// class representing Pixels in an image in the form of 2D vector
class Image
{
private:
	vector<vector<Pixel*>> Pixels;   //2D vector to store pixels in an image

	/**
	* identfiy neighbour pixels around the specified pixel
	* @param pixel coordinates (x & y) around which neighbours are to be computed, shade to be compared, count of pixels with same shade
	* @returns none except count of pixels in an area (pass by reference)
	*/
	void identifyNeighbours(unsigned int x, unsigned int y, unsigned int &shade, unsigned int &count);
	
public:
	// constructor
	Image(unsigned int width, unsigned int height);
	//destructor
	~Image();

	/**
	* count the numbers of areas of different shades of grey
	* @returns a vector of unsigned int representing count of each area per grey shade
	*/
	vector<unsigned int> countAreas();

	/**
	* initialize pixels from the buffer read from binary file
	* @param buffer data read from file
	*/
	void initPixels(const vector<unsigned int>& buffer);

	/**
	* set pixels from the Mat object read from file (in case of non binary files)
	* @param Mat object data read from file
	*/
	void initPixels(Mat &obj);
};

