#include <iostream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"

using namespace bvme;

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}


int noiseRemove(CImage imageOriginal) {

	CImage grayImage = createGrayValueImage(imageOriginal);
	CImage newImage(grayImage.getWidth(), grayImage.getHeight(), true);

	
	int windowSize = 3;
	int n = windowSize * windowSize;
	int Smax = 9;
	int kreuz = windowSize / 2;
	int k = 0;

	int zMed = 0;
	int zMin = 0;
	int zMax = 0;
	int a1 = 0;
	int a2 = 0;

	int b1 = 0;
	int b2 = 0;

	bool check = true;
	int borderCheck = 0;
	int count = 0;

	int *arrZ = new int(Smax * Smax);

	int newValue = 0;
	
	for (int x = kreuz; x < grayImage.getHeight() - kreuz; x++){
		for (int y = kreuz; y < grayImage.getWidth() - kreuz; y++){

			check = true;
			windowSize = 3;
			kreuz = windowSize / 2;
			while (check){
				
				for (int xi = 0; xi < windowSize; xi++) {
					for (int yi = 0; yi < windowSize; yi++) {
						arrZ[k] = grayImage.getPointValue(x + xi - kreuz, y + yi - kreuz).getGrey();
						k++;
					}
				}
				k = 0;

				qsort(arrZ, n, sizeof(int), compare);
				zMed = arrZ[n / 2];
				zMin = arrZ[0];
				zMax = arrZ[n - 1];
				a1 = zMed - zMin;
				a2 = zMed - zMax;

				if (a1 > 0 && a2 < 0) {

					b1 = grayImage.getPointValue(x , y ).getGrey() - zMin;
					b2 = grayImage.getPointValue(x , y ).getGrey() - zMax;
					if (b1 > 0 && b2 < 0) {
						newValue = grayImage.getPointValue(x, y).getGrey();
						break;
					}else{
						newValue = zMed;
						break;
					}
				}else {
					windowSize += 2;
					kreuz = windowSize / 2;
				}

				borderCheck = true;
				(x - kreuz < 0 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(y - kreuz < 0 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(x - kreuz < 0 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(y + kreuz > grayImage.getWidth() - 1 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(x + kreuz > grayImage.getHeight() - 1 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(y - kreuz < 0 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(x + kreuz > grayImage.getHeight() - 1 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				(y + kreuz > grayImage.getWidth() - 1 || borderCheck == false) ? borderCheck = false : borderCheck = true;
				
				if(windowSize < Smax && borderCheck){
					check = true;
				}else{
					check = false;
					newValue = grayImage.getPointValue(x, y).getGrey();
				}
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

