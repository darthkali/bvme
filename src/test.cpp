#include <iostream>
#include "CImage.h"
#include "CColor.h"

using namespace bvme;

int test()
{
	// relativ ausgehend von main.cpp, absolute Pfadangaben sind auch möglich
	CImage imageRose("Images/rose.bmp");


	imageRose.showImage();
	CImage imageText("Images/text1.bmp");


	imageText.showImage();

	system("pause");
	return 0;
}