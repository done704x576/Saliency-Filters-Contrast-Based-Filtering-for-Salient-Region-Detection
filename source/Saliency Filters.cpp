// Saliency Filters.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream> 
#include <opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include "saliency.h"

using namespace cv;  
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char input_image_name[100];
	int image_num = 10000;
	for (int i = 1; i <= image_num; i++)
	{
		sprintf(input_image_name,"../%s\\%d.jpg","image",i); 
		cv::Mat input_image = cv::imread(input_image_name);

		if (input_image.empty())
		{
			continue;
		}

		Saliency saliency;
		Mat_<float> sal = saliency.saliency( input_image );

		double adaptive_T = 2.0 * sum( sal )[0] / (sal.cols * sal.rows);
		while (sum( sal > adaptive_T )[0] == 0)
		{
			adaptive_T /= 1.2;
		}

		imshow( "source image", input_image );
		imshow( "saliency image", sal );
		imshow("threshold image", sal > adaptive_T );
		waitKey(1);
	}

	return 0;
}

