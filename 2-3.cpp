#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


int main()
{
	Mat img_color;


	img_color = imread("cat on laptop.jpg", IMREAD_COLOR);
	if (img_color.empty())
	{
		cout << "이미지 파일을 읽을 수 없습니다." << endl;
		return -1;
	}


	namedWindow("Color");
	imshow("Color", img_color);

	waitKey(0);


	Mat img_gray;

	cvtColor( img_color, img_gray, COLOR_BGR2GRAY);


	imshow("Grayscale", img_gray);

	imwrite("grayscale.jpg", img_gray);

	waitKey(0);
	destroyAllWindows();
}