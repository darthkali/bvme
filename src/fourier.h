#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;


void multiFilter(CImage& fourierImage, CImage& filterImage){

	Complex fourierPoint = 0.0;
	Complex filterPoint = 0.0;
	Complex newComplexPoint = 0.0;
	double xValue;
	double iValue;
	double rValue;
	for (int x = 0; x < fourierImage.getHeight(); x++) {
		for (int y = 0; y < fourierImage.getWidth(); y++) {

			fourierPoint = fourierImage.getComplexPointValue(x, y);
			filterPoint = filterImage.getComplexPointValue(x, y);
			//newComplexPoint = filterPoint * fourierPoint;
			rValue = fourierPoint.real();
			iValue = fourierPoint.imag();
			xValue = filterPoint.real();
			newComplexPoint.real(rValue * xValue);
			newComplexPoint.imag(iValue * xValue);
			fourierImage.setComplexPointValue(x, y, newComplexPoint);
		}
	}
}

CImage generateSimpleFilter(int width, int height){

	Complex black(0.0);
	Complex white(1.0);

	CImage filterImage(width, height, true);
	CImage fourierFilterImage = filterImage.FourierTransformation(false);

	// Filter
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			fourierFilterImage.setComplexPointValue(x, y, white);
		}
	}

	fourierFilterImage.setComplexPointValue(height / 2, width / 2, black);
	fourierFilterImage.setComplexPointValue(height / 2, width / 2 + 1, black);
	fourierFilterImage.setComplexPointValue(height / 2 + 1, width / 2, black);
	fourierFilterImage.setComplexPointValue(height / 2 + 1, width / 2 + 1, black);

	return fourierFilterImage;
}

CImage generateLowHighPassFilter(int width, int height, double radius, bool lowpass) {


	Complex complexPointLow(0.0);
	Complex complexPointHigh(0.0);
	if(lowpass){
		 complexPointLow = 0.0;
		 complexPointHigh = 1.0;
	}else
	{
		 complexPointLow = 1.0;
		 complexPointHigh = 0.0;
	}


	CImage filterImage(width, height, true);
	CImage fourierFilterImage = filterImage.FourierTransformation(false);

	double D = 0.0;

	// Filter
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			D = sqrt((pow((y - width / 2), 2)) + (pow((x - height / 2), 2)));

			if(D < radius){
				fourierFilterImage.setComplexPointValue(x, y, complexPointHigh);
			}else{
				fourierFilterImage.setComplexPointValue(x, y, complexPointLow);
			}
		}
	}

	fourierFilterImage.showImage();
	return fourierFilterImage;
}

CImage generateButterworthFilter(int width, int height, double radius, bool lowpass) {
	Complex H(0.0);

	CImage filterImage(width, height, true);
	CImage fourierFilterImage = filterImage.FourierTransformation(false);

	double D = 0.0;
	H = 0.0;

	// Filter
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {

			D = sqrt((pow((y - width / 2), 2)) + (pow((x - height / 2), 2)));
			H = 1 / (1 + pow((D / radius), 2 * 1));

			if (!lowpass) {
				H = 1 - H.real();
			}

			fourierFilterImage.setComplexPointValue(x, y, H);
		}
	}

	fourierFilterImage.showImage();
	return fourierFilterImage;
}


int fourierTransformation(CImage imageOriginal) {

	CImage grayImage = createGrayValueImage(imageOriginal);
	CImage fourierImage = grayImage.FourierTransformation(false);

	int width = fourierImage.getWidth();
	int height = fourierImage.getHeight();


	//Filter
	//CImage filterImage = generateSimpleFilter(width, height);
	//multiFilter(fourierImage, filterImage);
	//
	//CImage filterLowHighPassImage = generateLowHighPassFilter(width, height, 50.0, false);
	//multiFilter(fourierImage, filterLowHighPassImage);

	CImage generateButterworthImage = generateButterworthFilter(width, height, 50.0, false);
	multiFilter(fourierImage, generateButterworthImage);
	

	
	CImage reverseFourierImage = fourierImage.FourierTransformation(true);



	reverseFourierImage.showImage();

	
	system("pause");
	return 0;
}




