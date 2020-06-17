#include "Image.h"
#include <unordered_map>

//constructor
Image::Image(unsigned int width, unsigned int height)
{
	Pixels.resize(width);
	for (int i = 0; i < Pixels.size(); i++)
		Pixels[i].resize(height);

	//setting all pixels to NULL
	for (int i = 0; i < Pixels.size(); i++)
	{
		for (int j = 0; j < Pixels[i].size(); j++)
		{
			Pixels[i][j] = nullptr;
		}
	}
}

// destructor
Image::~Image()
{
	// Dynamically delete the pixels allocated earlier
	for (int i = 0; i < Pixels.size(); i++)
	{
		for (int j = 0; j < Pixels[i].size(); j++)
		{
			if (Pixels[i][j] != nullptr)
			{
				delete Pixels[i][j];
			}
		}
	}
}

/**
* set pixels from the buffer read from file
* @param buffer data read from file (used for binary images)
*/
void Image::initPixels(const vector<unsigned int>& buffer)
{
	unordered_map<unsigned int, int> umap;
	for (int i = 0; i < Pixels.size(); i++)
	{
		for (int j = 0; j < Pixels[i].size(); j++)
		{
			Pixels[i][j] = new Pixel(i, j, buffer[i + j * Pixels[i].size()]);
			umap[buffer[i + j * Pixels.size()]]++;
		}
	}
	
	// uncomment to check different shades of grey with frequency
	/*for (auto it = umap.begin(); it != umap.end(); it++)
		cout << it->first << "," << it->second << ")\n";*/

}

/**
* set pixels from the Mat object read from file
* @param Mat object read from file (used for non binary images)
*/
void Image::initPixels(Mat &gray)
{
	unordered_map<unsigned int, int> umap;
	
	for (int r = 0; r < gray.rows; r++)
	{
		for (int c = 0; c < gray.cols; c++)
		{
			unsigned int val = (unsigned int)gray.at<uchar>(r, c);
			Pixels[r][c] = new Pixel(r, c, val); 
			umap[val]++;
		}
	}

	// uncomment to check different shades of grey with frequency
	/*for (auto it = umap.begin(); it != umap.end(); it++)
		cout << "\n(" <<it->first << "," << it->second << ")\n";*/

}

/**
* get adjacent neighbour pixels around the specified pixel
* @param pixel co-ordinates (x,y) aroungd which neighbour pixels are to be determined, shade to be considered, 
*        count of pixels corresponding to this shade
* @returns none, except count of pixels in a region with specified shade value
*/
void Image::identifyNeighbours(unsigned int x, unsigned int y, unsigned int &shade_value, unsigned int &count)
{
	int width = Pixels[0].size();
	int height = Pixels.size();
	int xoleft, xoright, yoabove, yobelow;
	vector<Pixel*> neighbours;
	
	if (Pixels[x][y]->getMarked())
		return;

	Pixels[x][y]->setMarked(true);
	count++;

	// calculate neighbour offsets
	xoleft = (y == 0) ? 0 : -1;
	xoright = (y == (width - 1)) ? 0 : 1;
	yoabove = (x == 0) ? 0 : -1;
	yobelow = (x == (height - 1)) ? 0 : 1;

	if ((xoleft != 0) && !Pixels[x][y-1]->getMarked() && Pixels[x][y-1]->getShade() == shade_value)
	{
		neighbours.push_back(Pixels[x][y-1]);
	}
		
	if ((xoright != 0) && !Pixels[x][y+1]->getMarked() && Pixels[x][y + 1]->getShade() == shade_value)
	{
		neighbours.push_back(Pixels[x][y+1]);
	}
		
	if ((yoabove != 0) && !Pixels[x-1][y]->getMarked() && Pixels[x-1][y]->getShade() == shade_value)
	{
		neighbours.push_back(Pixels[x-1][y]);
	}
		
	if ((yobelow != 0) && !Pixels[x+1][y]->getMarked() && Pixels[x+1][y]->getShade() == shade_value)
	{
		neighbours.push_back(Pixels[x+1][y]);
	}

	for (int i = 0; i < neighbours.size(); i++)
	{
		identifyNeighbours(neighbours[i]->getX(), neighbours[i]->getY(), shade_value, count);
	}
	
}

/**
* count the numbers of areas of different shades of grey
* @returns a vector of unsigned int representing the count of different areas per grey shade
*/
vector<unsigned int> Image::countAreas()
{
	vector<unsigned int> countAreas;
	countAreas.resize(256);
	unsigned int count;          // the count of pixels in the target area
	unsigned int shade_value; // the shade of gray
	vector<Pixel*> neighbours; //neighbour cells with same shade value

	// visit all pixels to find different areas
	for (int i = 0; i < Pixels.size(); i++)
	{
		for (int j = 0; j < Pixels[i].size(); j++)
		{
			count = 0;          
			shade_value = Pixels[i][j]->getShade();

			// find the area that the target pixel belongs to
			identifyNeighbours(i, j, shade_value, count);
			if (count)
			{
				countAreas[shade_value]++;
			}
		}
	}

	return countAreas;
}
