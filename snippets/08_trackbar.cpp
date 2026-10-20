// ============================================================
// 08. 트랙바
//     (Chapter04 트랙바 사용하기)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// createTrackbar(트랙바이름, 창이름, 위치변수주소, 최대위치, 콜백함수, 사용자데이터)
//   - 위치 변수 주소에는 보통 0 을 준다
//   - 최대 위치가 255 이면 0 ~ 255 (256 단계)
// getTrackbarPos(트랙바이름, 창이름)              -> 현재 위치
// setTrackbarPos(트랙바이름, 창이름, 위치)        -> 위치를 강제로 옮김 (콜백이 불린다)

// ------------------------------------------------------------
// (1) 트랙바 하나로 밝기 조절
// ------------------------------------------------------------
Mat src;

void on_level_change(int pos, void* userdata) {
	Mat img = *(Mat*)userdata;          // 사용자 데이터로 넘긴 Mat
	img.setTo(pos * 16);
	imshow("image", img);
}

void trackbar_basic() {
	Mat img = Mat::zeros(400, 400, CV_8UC1);

	namedWindow("image");
	createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img);

	imshow("image", img);
	waitKey(0);
	destroyAllWindows();
}

// ------------------------------------------------------------
// (2) 트랙바 3개로 R, G, B 채널 조절 (콜백 하나를 함께 쓴다)
// ------------------------------------------------------------
void on_rgb_change(int pos, void* userdata) {
	int r = getTrackbarPos("R", "image");
	int g = getTrackbarPos("G", "image");
	int b = getTrackbarPos("B", "image");

	Mat dst = src.clone();

	for (int j = 0; j < dst.rows; j++) {
		for (int i = 0; i < dst.cols; i++) {
			dst.at<Vec3b>(j, i)[0] = src.at<Vec3b>(j, i)[0] * b / 100;   // BLUE
			dst.at<Vec3b>(j, i)[1] = src.at<Vec3b>(j, i)[1] * g / 100;   // GREEN
			dst.at<Vec3b>(j, i)[2] = src.at<Vec3b>(j, i)[2] * r / 100;   // RED
		}
	}
	imshow("image", dst);
}

void trackbar_rgb() {
	src = imread("lenna.bmp", IMREAD_COLOR);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	namedWindow("image");
	imshow("image", src);

	createTrackbar("R", "image", 0, 100, on_rgb_change);
	createTrackbar("G", "image", 0, 100, on_rgb_change);
	createTrackbar("B", "image", 0, 100, on_rgb_change);

	setTrackbarPos("R", "image", 100);     // 처음엔 원본 그대로
	setTrackbarPos("G", "image", 100);
	setTrackbarPos("B", "image", 100);

	waitKey(0);
	destroyAllWindows();
}

int main() {
	// trackbar_basic();
	trackbar_rgb();

	return 0;
}
