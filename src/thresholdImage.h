#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;

int thresholdImage(CImage colorImage) {
	
	int averageGrayValue = 0;
	int arrLowerAverage = 0;
	int arrHigherAverage = 0;
	int countLowerAverage = 0;
	int countHigherAverage = 0;
	int oldAverageGrayValue = 0;
	float diff = 0;
	int count = 0;
	
	CColor blackColor(0);
	CColor whiteColor(255);
	
	CImage grayImage = createGrayValueImage(colorImage);

	// calculates the averageGrayValue from the whole image
	for (int x = 0; x < grayImage.getHeight(); x++) {
		for (int y = 0; y < grayImage.getWidth(); y++) {
			averageGrayValue += grayImage.getPointValue(x, y).getGrey();
		}
	}
	averageGrayValue = averageGrayValue / (grayImage.getHeight() * grayImage.getWidth());


	// calculates the averageGrayValue from pixel below and above the threshold
	do{
		oldAverageGrayValue = averageGrayValue;
		arrLowerAverage = 0;
		arrHigherAverage = 0;
		countLowerAverage = 0;
		countHigherAverage = 0;
		
		for (int x = 0; x < grayImage.getHeight(); x++) {
			for (int y = 0; y < grayImage.getWidth(); y++) {

				int _grayPoint = grayImage.getPointValue(x, y).getGrey();
				if (grayImage.getPointValue(x, y).getGrey() < averageGrayValue) {
					arrLowerAverage += grayImage.getPointValue(x, y).getGrey();
					countLowerAverage++;
				}
				else {
					arrHigherAverage += grayImage.getPointValue(x, y).getGrey();
					countHigherAverage++;
				}
			}
		}
		
		arrLowerAverage = arrLowerAverage / countLowerAverage;
		arrHigherAverage = arrHigherAverage / countHigherAverage;
		averageGrayValue = (arrLowerAverage + arrHigherAverage) / 2;
		diff = (float)abs(oldAverageGrayValue - averageGrayValue);

	} while (diff > 0.1);

	
	// generate the black white image
	for (int x = 0; x < grayImage.getHeight(); x++) {
		for (int y = 0; y < grayImage.getWidth(); y++) {

			if (grayImage.getPointValue(x, y).getGrey() < averageGrayValue) {
				grayImage.setPointValue(x, y, blackColor);
			}
			else {
				grayImage.setPointValue(x, y, whiteColor);
			}
		}
	}
	
	grayImage.showImage();

	system("pause");
	return 0;
}
