#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

#define WHITE 255
#define BLACK 0

using namespace bvme;


double calcMatrix(CImage grayImage, int _row, int _column){
	double innerValue = (double)grayImage.getPointValue(_row, _column).getGrey();
	double result = 0;
	for (int row = _row - 1; row <= _row + 1; row++) {
		for (int column = _column - 1; column <= _column + 1; column++) {
			result += abs(grayImage.getPointValue(row, column).getGrey() - innerValue)/8;
		}
	}
	return result;
}


CImage moravec(CImage _grayImage) {

	CImage grayImage = createGrayValueImage(_grayImage);
	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);
	CColor newColor(0);

	for (int row = 1; row < grayImage.getHeight() - 1; row++) {
		for (int column = 1; column < grayImage.getWidth() - 1; column++) {
			newColor.setGrey(calcMatrix(grayImage, row, column));

			if(newColor.getGrey() > 96){
				newImage.setPointValue(row, column, newColor);
			}
		}
	}

	grayImage.showImage();
	newImage.showImage();
	system("pause");
	return newImage;
}
