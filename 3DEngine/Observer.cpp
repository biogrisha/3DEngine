#define _USE_MATH_DEFINES
#include<math.h>
#include<array>
#include <Unknwn.h>
#include <windows.h>
#include <gdiplus.h>
#include "Observer.h"
#include "ThreeDObject.h"
using namespace Gdiplus;

using namespace std;
Observer::Observer(int diameter, const ThreeDObject * object)
{
	pixels = object->GetPixels();
	this->diameter = diameter;
	radius = diameter / 2;
	radiusSquare = radius * radius;
	CreateSphereMatrix();
}

Observer::~Observer()
{
	DeleteSphereMatrix();
	delete usedPixels;
	DeleteObject(col);

}

Gdiplus::Bitmap * Observer::GetImage()
{

	Refresh();
	delete image;
	image = new Gdiplus::Bitmap(L"BITMAP2.bmp");
	for(int x = 0; x< diameter; x++)
		for (int y = 0; y < diameter;y++)
		{
			

			if(GetPixel(x,y) == 10)
			image->SetPixel(x, y, *col);
		}
	return image;
}

void Observer::Refresh()
{
	for (auto pix : *usedPixels)
	{
		pix->back = 0;
		pix->front = 0;
	}
	usedPixels->clear();

	for (auto pix : *pixels)
	{
		SetPixel(pix.X, pix.Y, pix.Z, 10);
	}
}



void Observer::SetPixel(int x, int y, int z, unsigned char brightness)
{
	int x_vec = this->x - x;
	int y_vec = this->y - y;
	int z_vec = this->z - z;
	float distance = sqrt(x_vec * x_vec + y_vec * y_vec + z_vec * z_vec)/radius/2;
	int x_sph = (float(x_vec) / distance);
	int y_sph = (float(y_vec) / distance)+ radius;
	int z_sph = (float(z_vec) / distance);

	float radius_rel = sqrt(x_sph * x_sph + z_sph * z_sph);
	float angle_new;
	if(z_sph<0)
		angle_new = acos(x_sph / radius_rel) + angle;
	else
		angle_new = acos(x_sph / radius_rel)*(-1) + angle;

	int x_rotated = (radius_rel * cos(angle_new)) + radius;
	int z_rotated = (radius_rel * sin(angle_new));

	if (x_rotated < diameter && y_sph < diameter && x_rotated >=0 && y_sph>=0)
	{
		SpherePoint sp;
		if(z_rotated >0)
			SphereMatrix[x_rotated][y_sph].front = brightness;
		else
			SphereMatrix[x_rotated][y_sph].back = brightness;

		usedPixels->push_back(&(SphereMatrix[x_rotated][y_sph]));
	}
	
}


unsigned char Observer::GetPixel(int x, int y)
{
	if(x<diameter && x>=0 && y< diameter && y >=0)
	return SphereMatrix[x][y].front;
}

void Observer::Rotate(bool direction)
{
	if (direction)
	{
		angle -= M_PI / 20;
	}
	else
		angle += M_PI / 20;

	z_forvard = sin(90.0 + angle) * 10;
	x_forvard = cos(90.0 + angle) * 10;
}

void Observer::Move(bool direction)
{
	if (direction)
	{
		x += x_forvard;
		z += z_forvard;
	}
	else
	{
		x -= x_forvard;
		z -= z_forvard;
	}
}



void Observer::CreateSphereMatrix()
{
	SphereMatrix = new SpherePoint *[diameter];
	for (int i = 0; i < diameter; i ++)
	{
		SphereMatrix[i] = new SpherePoint[diameter];
	}

}

void Observer::DeleteSphereMatrix()
{
	for (int i = 0; i < diameter; i++)
	{
		delete []SphereMatrix[i];
	}
	delete []SphereMatrix;

}
