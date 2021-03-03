#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;

int sharpen(CImage imageOriginal) {

	CImage grayImage = createGrayValueImage(imageOriginal);
	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);
	int x = 0;
	int y = 0;

	float newValue = 0.0;
	double matrix[3][3] = {
		{ -1, -1, -1},
		{ -1, 8, -1},
		{ -1, -1, -1}
	};

	//double matrix[3][3] = {
	//{ 0, -1, 0},
	//{ -1, 4, -1},
	//{ 0, -1,0}
	//};

	int sizeMatrix = sizeof(matrix) / sizeof(matrix[0]);
	int border = sizeMatrix / 2;

	float FloatColor = 0.0;
	float newFloatColor = 0.0;
	int grayValue = 0;
	int mX = 0;
	int mY = 0;

	for (x = border; x < grayImage.getHeight() - border; x++) {
		for (y = border; y < grayImage.getWidth() - border; y++) {
			newValue = 0;
			mX = 0;

			for (int i = x - border; i <= x + border; i++) {
				mY = 0;
				for (int k = y - border; k <= y + border; k++) {
					newValue += (float)(grayImage.getPointValue(i, k).getGrey()) * matrix[mY][mX];
					mY++;
				}
				mX++;
			}
			
			newValue = abs(grayImage.getPointValue(x, y).getGrey() + newValue);
			CColor newColor(newValue);
			newImage.setPointValue(x, y, newColor);

		}

	}
	grayImage.showImage();
	newImage.showImage();
	system("pause");
	return 0;
}
