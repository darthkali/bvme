#pragma once
#include <iostream>
#include "CImage.h"
#include "CColor.h"

using namespace bvme;

CImage createGrayValueImage(CImage colorImage){

	CImage grayImage(colorImage.getWidth(), colorImage.getHeight(), true);
	
	for (int x = 0; x < colorImage.getHeight(); x++){
		for (int y = 0; y < colorImage.getWidth(); y++){
			CColor test ((colorImage.getPointValue(x, y).getGreen() + colorImage.getPointValue(x, y).getBlue() + colorImage.getPointValue(x, y).getRed()) / 3);
			grayImage.setPointValue(x, y, test);
		}
	}

	return grayImage;
	
}

