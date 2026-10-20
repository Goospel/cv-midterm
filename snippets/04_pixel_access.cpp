// ============================================================
// 04. 픽셀 값 참조 / 채널 분리·합성
//     (Chapter03 행렬의 원소 값 참조)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat gray = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat img = imread("lenna.bmp", IMREAD_COLOR);
	if (gray.empty() || img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	// ---------- at() 으로 픽셀 하나 읽고 쓰기 ----------
	// 첫 번째 인자가 "행 번호 = y", 두 번째가 "열 번호 = x" 이다. 순서 주의!
	uchar v = gray.at<uchar>(100, 50);           // (x=50, y=100) 위치의 밝기
	gray.at<uchar>(100, 50) = 255;

	Vec3b px = img.at<Vec3b>(100, 50);           // 컬러는 Vec3b
	int b = px[0];     // BLUE
	int g = px[1];     // GREEN
	int r = px[2];     // RED
	cout << "pixel B=" << b << " G=" << g << " R=" << r << endl;

	img.at<Vec3b>(100, 50)[0] = 0;               // BLUE  를 0 으로
	img.at<Vec3b>(100, 50)[1] = 255;             // GREEN 를 255 로
	img.at<Vec3b>(100, 50)[2] = 255;             // RED   를 255 로

	// ---------- 전체 픽셀 돌기 (가장 많이 쓰는 형태) ----------
	Mat dst = img.clone();
	for (int j = 0; j < dst.rows; j++) {         // j = y (세로)
		for (int i = 0; i < dst.cols; i++) {     // i = x (가로)
			dst.at<Vec3b>(j, i)[0] = 255 - img.at<Vec3b>(j, i)[0];
			dst.at<Vec3b>(j, i)[1] = 255 - img.at<Vec3b>(j, i)[1];
			dst.at<Vec3b>(j, i)[2] = 255 - img.at<Vec3b>(j, i)[2];
		}
	}
	imshow("inversed", dst);

	// 그레이스케일 전체 돌기
	Mat gdst = gray.clone();
	for (int j = 0; j < gdst.rows; j++)
		for (int i = 0; i < gdst.cols; i++)
			gdst.at<uchar>(j, i) = 255 - gray.at<uchar>(j, i);

	// ---------- ptr() 로 한 줄씩 접근 (at 보다 빠르다) ----------
	Mat pdst = gray.clone();
	for (int j = 0; j < pdst.rows; j++) {
		uchar* p = pdst.ptr<uchar>(j);           // j 번째 행의 첫 주소
		for (int i = 0; i < pdst.cols; i++)
			p[i] = 255 - p[i];
	}

	// ---------- 채널 분리 / 합성 ----------
	vector<Mat> planes;
	split(img, planes);        // planes[0]=B, planes[1]=G, planes[2]=R

	imshow("B plane", planes[0]);
	imshow("G plane", planes[1]);
	imshow("R plane", planes[2]);

	planes[0] = 0;             // 파란색 채널을 모두 0 으로
	Mat merged;
	merge(planes, merged);     // 다시 합치기
	imshow("B removed", merged);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
