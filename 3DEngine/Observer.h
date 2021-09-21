#pragma once
#include<vector>
#include <Unknwn.h>
#include <windows.h>
#include <gdiplus.h>
#include "ThreeDObject.h"
class Observer
{
public:
	class SpherePoint
	{
	public:
		unsigned char back = 0;
		unsigned char front = 0;
		bool IsInCircle = false;
	};

	Observer(int diameter, const ThreeDObject * object);
	~Observer();

	Gdiplus::Bitmap * GetImage();

	void Rotate(bool direction);
	void Move(bool direction);
private:
	SpherePoint** SphereMatrix;//[x][y]

	const std::vector<ThreeDObject::ThreeDPixel>* pixels;

	std::vector<SpherePoint*> *usedPixels = new std::vector<SpherePoint*>();

	Gdiplus::Color* col = new Gdiplus::Color(255, 50, 0);
	Gdiplus::Bitmap * image = new Gdiplus::Bitmap(L"BITMAP2.bmp");

	int diameter;
	int radius;
	int radiusSquare;

	float angle = 0;

	int x_forvard = 0;
	int z_forvard = 10;

	int x = 0;
	int y = 0;
	int z = 0;
	
	void CreateSphereMatrix();
	void DeleteSphereMatrix();

	void SetPixel(int x, int y, int z, unsigned char brightness);

	unsigned char GetPixel(int x, int y);

	void Refresh();
};