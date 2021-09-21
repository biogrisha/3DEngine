#pragma once
#include <vector>
#include <iostream>

class ThreeDObject
{
public:
	struct ThreeDPixel
	{
		int X;
		int Y;
		int Z;
		int Brightness = 0;
	};

	ThreeDObject();
	~ThreeDObject();

	void AddPixel(ThreeDPixel pixel);
	const std::vector<ThreeDPixel>* GetPixels()const;
protected:
	std::vector<ThreeDPixel>* pixels;
};

