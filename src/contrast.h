#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;

CImage contrast(CImage contrastImage){
	
	//CImage grayImage = createGrayValueImage(contrastImage);
	CImage grayImage = contrastImage;

	int arrhistogram[256] = {0};
	int arrCumulativeHistogram[256] = {0};
	int amountPixel = grayImage.getHeight() * grayImage.getWidth();

	// generate the histogram from the image
	for (int x = 0; x < grayImage.getHeight(); x++) {
		for (int y = 0; y < grayImage.getWidth(); y++) {
			arrhistogram[grayImage.getPointValue(x, y).getGrey()]++;
		}
	}
	
	// generate the cumulative histogram from the image
	int value = amountPixel;
	for (int i = 255; i >= 0; i--) {
		value = value - arrhistogram[i];
		arrCumulativeHistogram[i] = value;
	}

	// set the new grayValues for the image
	for (int x = 0; x < grayImage.getHeight(); x++) {
		for (int y = 0; y < grayImage.getWidth(); y++) {
			int newColor = (arrCumulativeHistogram[grayImage.getPointValue(x, y).getGrey()] / (float) amountPixel) * 255;
			CColor blackColor(newColor);
			
			grayImage.setPointValue(x, y, blackColor);
		}
	}
	
	//grayImage.showImage();

	//system("pause");
	return grayImage;
}


void histogramLinearizationRGB(CImage image){

	/*Aufteilen des Bildes in 3 Bilder
	uebergeben an funktion zum umwandeln
	zusammensetzen der ruckgabebilder
	ausgabe des Bildes*/



	CImage pictureRed(image.getWidth(), image.getHeight(), true);
	CImage pictureGreen(image.getWidth(), image.getHeight(), true);
	CImage pictureBlue(image.getWidth(), image.getHeight(), true);

	CImage newPictureRed(image.getWidth(), image.getHeight(), true);
	CImage newPictureGreen(image.getWidth(), image.getHeight(), true);
	CImage newPictureBlue(image.getWidth(), image.getHeight(), true);
	
	CImage newPicture(image.getWidth(), image.getHeight(), false);

	CColor red;
	CColor green;
	CColor blue;
	
	
	for (int x = 0; x < image.getHeight(); x++) {
		for (int y = 0; y < image.getWidth(); y++) {
			
			CColor red = CColor(image.getPointValue(x, y).getRed());
			CColor green = CColor(image.getPointValue(x, y).getGreen());
			CColor blue = CColor(image.getPointValue(x, y).getBlue());
		
			pictureRed.setPointValue(x,y, red);
			pictureGreen.setPointValue(x,y, green);
			pictureBlue.setPointValue(x,y, blue);

			
		}
	}

	newPictureRed = contrast(pictureRed);
	newPictureGreen = contrast(pictureGreen);
	newPictureBlue = contrast(pictureBlue);

	for (int x = 0; x < image.getHeight(); x++) {
		for (int y = 0; y < image.getWidth(); y++) {

			CColor color = CColor(pictureRed.getPointValue(x, y).getGrey(), pictureGreen.getPointValue(x, y).getGrey(), pictureBlue.getPointValue(x, y).getGrey());
			newPicture.setPointValue(x, y, color);

		}
	}

	newPicture.showImage();
	image.showImage();
	system("pause");
	
}
