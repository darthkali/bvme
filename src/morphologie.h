#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

#define WHITE 255
#define BLACK 0

using namespace bvme;

void getFirstImageValuesInTable(CImage imageOriginal, int size)
{
	for (int row = 0; row < size * 2; row++) {
		for (int column = 0; column < size; column++) {

			if (imageOriginal.getPointValue(row, column).getGrey() == 255)
			{
				std::cout << "| 1 | ";
			}else
			{
				std::cout << "| " << imageOriginal.getPointValue(row, column).getGrey() << " | ";
			}


		}
		std::cout << "\n" ;
	}

	
}

bool checkMatrixDilatation(CImage grayImage, int _row, int _column)
{
	for (int row = _row - 1; row <= _row + 1 ; row++) {
		for (int column = _column - 1; column <= _column + 1; column++) {
			if (grayImage.getPointValue(row, column).getGrey() == 255)
			{
				return true;
			}
		}
	}
	return false;
}

bool checkMatrixErosion(CImage grayImage, int _row, int _column)
{
	for (int row = _row - 1; row <= _row + 1; row++) {
		for (int column = _column - 1; column <= _column + 1; column++) {
			if (grayImage.getPointValue(row, column).getGrey() == BLACK)
			{
				return false;
			}
		}
	}
	return true;
}

CImage dilatation(CImage grayImage) {

	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);
	CColor whiteColor(WHITE);

	for (int row = 1; row < grayImage.getHeight() - 1; row++) {
		for (int column = 1; column < grayImage.getWidth() - 1; column++) {

			if(grayImage.getPointValue(row, column).getGrey() == WHITE){
				newImage.setPointValue(row, column, whiteColor);
				continue;
			}

			if (checkMatrixDilatation(grayImage, row, column)){
				newImage.setPointValue(row, column, whiteColor);
			}
		}
	}

	//grayImage.showImage();
	//newImage.showImage();
	//system("pause");
	return newImage;
}

CImage erosion(CImage grayImage) {

	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);
	CColor whiteColor(WHITE);
	CColor blackColor(BLACK);

	for (int row = 1; row < grayImage.getHeight() - 1; row++) {
		for (int column = 1; column < grayImage.getWidth() - 1; column++) {

			if (grayImage.getPointValue(row, column).getGrey() == BLACK) {
				newImage.setPointValue(row, column, blackColor);
				continue;
			}

			if (checkMatrixErosion(grayImage, row, column)) {
				newImage.setPointValue(row, column, whiteColor);
			}
			else
			{
				newImage.setPointValue(row, column, blackColor);
			}
		}
	}

	//grayImage.showImage();
	//newImage.showImage();
	//system("pause");
	return newImage;
}

void closing(CImage imageOriginal){
	CImage grayImage = createGrayValueImage(imageOriginal);

	CImage dilatationImage = dilatation(grayImage);
	CImage erosionImage = erosion(dilatationImage);

	//grayImage.showImage();
	erosionImage.showImage();
	system("pause");
}

void opening(CImage imageOriginal) {
	CImage grayImage = createGrayValueImage(imageOriginal);

	CImage erosionImage = erosion(grayImage);
	CImage dilatationImage = dilatation(erosionImage);

	//grayImage.showImage();
	dilatationImage.showImage();
	system("pause");
}
