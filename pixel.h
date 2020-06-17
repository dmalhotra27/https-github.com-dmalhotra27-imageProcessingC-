#include <iostream>

// class representing a single pixel in an image
class Pixel
{
private:
	unsigned int x;       //horizontal co-ordinate
	unsigned int y;       // vertical co-ordinate
	unsigned int shade;   // shade of grey
	bool is_marked;       // variable indicating whether pixel has been considered for calculating neighbours
public:
	Pixel(unsigned int X, unsigned int Y, unsigned int Shade, bool marked = false)
	{
		this->x = X;
		this->y = Y;
		this->shade = Shade;
		this->is_marked = marked;
	}
	unsigned int getX() const
	{
		return x;
	}
	unsigned int getY() const
	{
		return y;
	}
	unsigned int getShade() const
	{
		return shade;
	}
	bool getMarked() const
	{
		return is_marked;
	}
	void setMarked(bool marked)
	{
		is_marked = marked;
	}
};