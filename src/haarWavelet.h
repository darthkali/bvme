#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"


using namespace bvme;

int g(CImage image, int column  , int row){
	return (image.getPointValue(row, 2 * column).getGrey() + image.getPointValue(row, 2 * column + 1).getGrey())/2;
}

int gFail(CImage image, int column, int row) {
	return (image.getPointValue(row, 2 * column).getGrey() - image.getPointValue(row, 2 * column + 1).getGrey()) / 2 + 128;
}


int gSenkrecht(CImage image, int column, int row) {
	return (image.getPointValue(2 * row, column).getGrey() + image.getPointValue(2 * row + 1, column).getGrey()) / 2;
}

int gFailSenkrecht(CImage image, int column, int row) {
	return (image.getPointValue(2 * row, column).getGrey() - image.getPointValue(2 * row + 1,  column).getGrey()) / 2 +128;
}

int haarWavelet(CImage imageOriginal) {

	CImage grayImage = createGrayValueImage(imageOriginal);
	CImage newImageSenkrecht(grayImage.getWidth(), grayImage.getHeight(), true);
	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);



	int m = grayImage.getWidth();

	while(m > 32){
		for (int row = 0; row < m; row++) {
			for (int column = 0; column < m / 2; column++) {

				CColor color(g(grayImage, column, row));
				newImageSenkrecht.setPointValue(row, column, color);

				CColor colorFail(gFail(grayImage, column, row));
				newImageSenkrecht.setPointValue(row, column + m / 2, colorFail);
			}
		}

		for (int column = 0; column < m; column++) {
			for (int row = 0; row < m / 2; row++) {

				CColor color(gSenkrecht(newImageSenkrecht, column, row));
				newImage.setPointValue(row, column, color);
				grayImage.setPointValue(row, column, color);

				CColor colorFail(gFailSenkrecht(newImageSenkrecht, column, row));
				newImage.setPointValue(row + m / 2, column, colorFail);
				grayImage.setPointValue(row + m / 2, column, colorFail);
			}
		}
		m = m / 2;
	}
	
	//grayImage.showImage();
	newImage.showImage();
	system("pause");
	return 0;
}
