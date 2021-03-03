#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"
#include <cmath>


using namespace bvme;

int hough(CImage imageOriginal) {

	double PI = 3.14159265358979323846;
	
	CImage binaryPicture = createGrayValueImage(imageOriginal);
	double m = binaryPicture.getWidth();
	double n = binaryPicture.getHeight();
	double o = 180;//TODO What
	double p = sqrt(pow(m, 2) + pow(n, 2)); //TODO: WHat

	
	CImage houghPicture(p, o, true);

	double dTeta = PI / o;

	double xr = m / 2;
	double yr = n / 2;
	double r = 0.0;
	double j0 = (p / 2);
	double j = 0.0;
	double x = 0.0;
	double y = 0.0;

		for (int u = 0; u < m; u++) {
			for (int v = 0; v < n; v++) {
				if (binaryPicture.getPointValue(u, v).getGrey() > 0){
					x = u - xr;
					y = v - yr;
					
					for (int i = 0; i < 180; i++){
						dTeta = (PI / o) * i;
						r = x * cos(dTeta) + y * sin(dTeta);
						j = j0 + round(r);

						int actualColor = houghPicture.getPointValue(i, j).getGrey();
						CColor white(actualColor + 1);
						houghPicture.setPointValue(i, j, white);
						
					}
					
				}
			
			}
		}



	binaryPicture.showImage();
	houghPicture.showImage();
	system("pause");
	return 0;
}
