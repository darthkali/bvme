#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;

int sobel(CImage imageOriginal) {


	CImage grayImage = createGrayValueImage(imageOriginal);
	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);
	int x = 0;
	int y = 0;

	double newValue = 0.0;
	double newValueX = 0.0;
	double newValueY = 0.0;
	double newValueXTop = 0.0;
	double newValueXBottom = 0.0;
	double newValueYLeft = 0.0;
	double newValueYRight = 0.0;
	
	double matrixX[3][3] = {
		{ -1, -2, -1},
		{ 0, 0, 0},
		{ 1, 2, 1}
	};

	double matrixY[3][3] = {
	{ -1, 0, 1},
	{ -2, 0, 2},
	{ -1, 0, 1}
	};

	int sizeMatrix = 3;
	int border = sizeMatrix / 2;

	//float FloatColor = 0.0;
	//float newFloatColor = 0.0;
	//int grayValue = 0;
	//int mX = 0;
	//int mY = 0;

	for (x = border; x < grayImage.getHeight() - border; x++) {
		for (y = border; y < grayImage.getWidth() - border; y++) {

			newValueXTop =  (double)grayImage.getPointValue(x - 1, y - 1).getGrey();
			newValueXTop += (double)grayImage.getPointValue(x - 1, y).getGrey() *2;
			newValueXTop += (double)grayImage.getPointValue(x - 1, y + 1).getGrey();

			newValueXBottom =  (double)grayImage.getPointValue(x + 1, y - 1).getGrey()	;
			newValueXBottom += (double)grayImage.getPointValue(x + 1, y).getGrey() * 2;
			newValueXBottom += (double)grayImage.getPointValue(x + 1, y + 1).getGrey()	;



			newValueYLeft =  (double)grayImage.getPointValue(x - 1, y - 1).getGrey();
			newValueYLeft += (double)grayImage.getPointValue(x, y - 1).getGrey() * 2;
			newValueYLeft += (double)grayImage.getPointValue(x + 1, y - 1).getGrey();

			newValueYRight =  (double)grayImage.getPointValue(x - 1, y + 1).getGrey();
			newValueYRight += (double)grayImage.getPointValue(x, y + 1).getGrey() * 2;
			newValueYRight += (double)grayImage.getPointValue(x + 1, y + 1).getGrey();

			newValueX = newValueXBottom - newValueXTop;
			newValueY = newValueYRight - newValueYLeft;
			
			newValue = (abs(newValueX) + abs(newValueY))  / 2;

			if (false) {
				std::cout << "Horizontal:" << "\n";
				std::cout << "TOP" << "\n";

				std::cout << "gray 0|0: " << grayImage.getPointValue(x - 1, y - 1).getGrey() << "\n";
				std::cout << "gray 0|1: " << grayImage.getPointValue(x - 1, y).getGrey() << "\n";
				std::cout << "gray 0|2: " << grayImage.getPointValue(x - 1, y + 1).getGrey() << "\n";

				std::cout << "Bottom" << "\n";

				std::cout << "gray 2|0: " << grayImage.getPointValue(x + 1, y - 1).getGrey() << "\n";
				std::cout << "gray 2|1: " << grayImage.getPointValue(x + 1, y).getGrey() << "\n";
				std::cout << "gray 2|2: " << grayImage.getPointValue(x + 1, y + 1).getGrey() << "\n";

				std::cout << "Vertikal:" << "\n";
				std::cout << "Links" << "\n";

				std::cout << "gray 0|0: " << grayImage.getPointValue(x - 1, y - 1).getGrey() << "\n";
				std::cout << "gray 1|0: " << grayImage.getPointValue(x, y - 1).getGrey() << "\n";
				std::cout << "gray 2|0: " << grayImage.getPointValue(x + 1, y - 1).getGrey() << "\n";

				std::cout << "Rechts" << "\n";

				std::cout << "gray 0|2: " << grayImage.getPointValue(x - 1, y + 1).getGrey() << "\n";
				std::cout << "gray 1|2: " << grayImage.getPointValue(x, y + 1).getGrey() << "\n";
				std::cout << "gray 2|2: " << grayImage.getPointValue(x + 1, y + 1).getGrey() << "\n";

				std::cout << "NewValues" << "\n";
				std::cout << "newValueX: " << newValueX << "\n";
				std::cout << "newValueY: " << newValueY << "\n";

			}

			
			CColor newColor(newValue);
			newImage.setPointValue(x, y, newColor);

		}

	}
	grayImage.showImage();
	newImage.showImage();
	system("pause");
	return 0;
}
