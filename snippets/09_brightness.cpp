// ============================================================
// 09. 영상의 밝기 조절
//     (Chapter05 코드 5-1 ~ 5-4)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 밝기 조절 수식
//     dst(x, y) = saturate( src(x, y) + n )
//   n > 0 이면 밝아지고, n < 0 이면 어두워진다
//   saturate : 0보다 작으면 0, 255보다 크면 255로 잘라내는 포화 연산

// ------------------------------------------------------------
// (1) 연산자로 간단히 (코드 5-1)
// ------------------------------------------------------------
void brightness1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst = src + 100;      // 포화 연산까지 알아서 해 준다
	// Mat dst = src - 100;   // 어둡게
	// src += 100;            // 원본을 직접 바꾸기

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (2) 직접 구현 - 포화 연산을 안 하면 어떻게 되는가 (코드 5-2)
// ------------------------------------------------------------
void brightness2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	// 결과 영상을 미리 만들어 두어야 한다.
	// 그냥 Mat dst; 로 두면 비어 있어서 at() 에서 에러가 난다.
	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = src.at<uchar>(j, i) + 100;
		}
	}
	// 255를 넘으면 uchar 가 넘쳐서(오버플로) 작은 값으로 돌아간다
	// -> 밝은 부분이 오히려 검게 나온다

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (3) 직접 구현 - 포화 연산 넣기 (코드 5-3)  ★ 이게 정답 형태
// ------------------------------------------------------------
void brightness3() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = saturate_cast<uchar>(src.at<uchar>(j, i) + 100);
		}
	}

	// 삼항 연산자로 직접 써도 같다
	// int v = src.at<uchar>(j, i) + 100;
	// dst.at<uchar>(j, i) = v > 255 ? 255 : v < 0 ? 0 : v;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (4) 트랙바로 밝기 조절 (코드 5-4)
// ------------------------------------------------------------
void on_brightness(int pos, void* userdata);

void brightness4() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	namedWindow("dst");                                      // 창을 먼저 만들고
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);     // 처음에 영상이 보이도록 강제로 한 번 호출

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;

	imshow("dst", dst);
}

// ------------------------------------------------------------
// 컬러 영상의 밝기를 직접 조절할 때 (채널 3개를 각각)
// ------------------------------------------------------------
void brightness_color() {
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			for (int c = 0; c < 3; c++) {
				dst.at<Vec3b>(j, i)[c] = saturate_cast<uchar>(src.at<Vec3b>(j, i)[c] + 50);
			}
		}
	}
	// 연산자로는 한 줄이다 : Mat dst = src + Scalar(50, 50, 50);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main() {
	// brightness1();
	// brightness2();
	brightness3();
	// brightness4();
	// brightness_color();

	return 0;
}
