#include "ThreeDObject.h"

ThreeDObject::ThreeDObject()
{
	pixels = new std::vector<ThreeDPixel>();
}

ThreeDObject::~ThreeDObject()
{
	delete pixels;
}

void ThreeDObject::AddPixel(ThreeDPixel pixel)
{
	pixels->push_back(pixel);
}

const std::vector<ThreeDObject::ThreeDPixel>* ThreeDObject::GetPixels()const
{
	return pixels;
}
