#include <iostream>
#include "CImage.h"
#include "CColor.h"
#include "createGrayValueImage.h"
#include "thresholdImage.h"
#include "contrast.h"
#include "blur.h"
#include "sharpen.h"
#include "fourier.h"
#include "noiseRemove.h"
#include "Sobel.h"
#include "haarWavelet.h"
#include "morphologie.h"
#include "segmentierung.h"
#include "hough.h"

using namespace bvme;

int main()
{
	CImage colorImage("Images/text1.bmp");
	CImage rose_flauImage("Images/rose_flau.bmp");
	CImage rose_Image("Images/rose.bmp");
	CImage flower_Image("Images/flower.bmp");
	CImage rose_RGBflauImage("Images/rose_rgb_flau.bmp");
	CImage mondImage("Images/mond.bmp");
	CImage fourierImage("Images/rose_fourier.bmp");
	CImage butterflyImage("Images/schmetterling_saltpepper.bmp");
	CImage calvinImage("Images/calvin.bmp");
	CImage bla("Images/HaarwaveletGrey.bmp");
	CImage reis("Images/reis.bmp");
	CImage schachbrett("Images/schachbrett.bmp");
	CImage linien("Images/linien.bmp");
	CImage linienkreis("Images/linienkreis.bmp");


	//bla.showImage();

	//for (int x = 0; x < calvinImage.getWidth(); x++)
	//{
	//	for (int y = 0; y < calvinImage.getWidth(); y++)
	//	{
	//		std::cout << "x: " << x << " y: " << y << " gray: " << calvinImage.getPointValue(x, y).getGrey() << "\n";
	//	}
	//}
	//system("pause");

	
	//thresholdImage(colorImage);

	//contrast(rose_flauImage);

	//blur(mondImage);
	//sharpen(mondImage);
	//fourierTransformation(fourierImage);
	//noiseRemove(butterflyImage);
	//histogramLinearizationRGB(rose_RGBflauImage);
	//sobel(rose_Image);
	//haarWavelet(calvinImage);
	//dilatation(reis);
	//erosion(reis);


	//reis.showImage();
	//opening(reis);
	//closing(reis);

	//moravec(schachbrett);

	hough(linien);
	hough(linienkreis);

	return 0;
}