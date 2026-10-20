// ============================================================
// 01. 영상 입출력 - imread / imshow / imwrite / 창 다루기
//     (Chapter02)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// ---------- 영상 불러오기 ----------
	Mat img = imread("lenna.bmp", IMREAD_COLOR);   // 컬러 3채널 (기본값)
	// Mat gray = imread("lenna.bmp", IMREAD_GRAYSCALE);  // 그레이스케일 1채널
	// Mat any  = imread("lenna.bmp", IMREAD_UNCHANGED);  // 파일 그대로

	if (img.empty()) {                              // 반드시 확인할 것
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// ---------- 영상 정보 출력 ----------
	cout << "width  : " << img.cols << endl;
	cout << "height : " << img.rows << endl;
	cout << "channels : " << img.channels() << endl;

	if (img.type() == CV_8UC1)
		cout << "img is a grayscale image" << endl;
	else if (img.type() == CV_8UC3)
		cout << "img is a truecolor image" << endl;

	// ---------- 창 만들고 보여주기 ----------
	namedWindow("image");                 // 기본값 WINDOW_AUTOSIZE (크기 고정)
	// namedWindow("image", WINDOW_NORMAL);  // 창 크기 조절 가능

	moveWindow("image", 100, 100);        // 화면 (100,100) 위치로 창 이동
	// resizeWindow("image", 400, 300);   // WINDOW_NORMAL 창만 크기 변경 가능

	imshow("image", img);

	// ---------- 영상 저장하기 ----------
	imwrite("result.png", img);

	// JPEG 압축률 지정해서 저장하기
	// vector<int> params;
	// params.push_back(IMWRITE_JPEG_QUALITY);
	// params.push_back(95);
	// imwrite("result.jpg", img, params);

	waitKey(0);              // 0 이면 키를 누를 때까지 무한 대기
	destroyAllWindows();

	return 0;
}
