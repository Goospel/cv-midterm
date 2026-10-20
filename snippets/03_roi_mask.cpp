// ============================================================
// 03. 부분 영상(ROI) / 영상 반전 / 마스크 연산
//     (Chapter03 부분행렬, Chapter04 마스크)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("lenna.bmp");
	if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	// ---------- ROI : 영상의 일부만 잘라내기 ----------
	// 잘라낸 결과는 원본을 "가리키는" 부분 행렬이다 (복사가 아니다)
	Mat roi = img(Rect(100, 100, 200, 150));   // Rect(x, y, width, height)

	// ROI 를 고치면 원본도 같이 바뀐다 -> ROI 만 반전시키는 방법
	roi = ~roi;                                 // 또는 bitwise_not(roi, roi);
	imshow("roi inversed", img);

	// 원본을 지키고 싶으면 clone() 으로 복사본을 만든 뒤 자른다
	Mat img2 = imread("lenna.bmp");
	Mat copy = img2.clone();
	Mat roi2 = copy(Rect(100, 100, 200, 150));
	roi2 = ~roi2;                               // img2 는 그대로, copy 만 바뀐다

	// 행 / 열 단위로 자르기
	// Mat row10 = img.row(10);
	// Mat col5  = img.col(5);
	// Mat rows  = img.rowRange(10, 20);
	// Mat cols  = img.colRange(5, 15);

	// ---------- 영상 전체 반전 ----------
	Mat inversed = ~img2;          // 255 - 픽셀값
	imshow("inversed", inversed);

	// ---------- 마스크 연산 ----------
	// mask 는 CV_8UC1 이고, 값이 0이 아닌 위치에만 복사된다
	Mat src = imread("airplane.bmp", IMREAD_COLOR);
	Mat mask = imread("mask_plane.bmp", IMREAD_GRAYSCALE);
	Mat dst = imread("field.bmp", IMREAD_COLOR);

	if (!src.empty() && !mask.empty() && !dst.empty()) {
		src.copyTo(dst, mask);     // 비행기 모양 부분만 들판 위에 옮겨 붙인다
		imshow("mask copyTo", dst);
	}

	// 마스크 위치에만 한 가지 색 칠하기
	Mat img3 = imread("lenna.bmp");
	Mat smile = imread("mask_smile.bmp", IMREAD_GRAYSCALE);
	if (!smile.empty()) {
		img3.setTo(Scalar(0, 255, 255), smile);   // 마스크 부분만 노랗게
		imshow("mask setTo", img3);
	}

	waitKey(0);
	destroyAllWindows();

	return 0;
}
