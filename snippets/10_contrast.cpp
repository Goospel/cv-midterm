// ============================================================
// 10. 영상의 명암비(contrast) 조절
//     (Chapter05 코드 5-5, 5-6)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// 명암비 : 밝은 곳과 어두운 곳의 밝기 차이가 얼마나 큰가
//   낮으면 흐릿하고, 높으면 선명하다

// ------------------------------------------------------------
// (1) 기본적인 방법 - 그냥 곱하기 (코드 5-5)
//     dst(x, y) = saturate( s * src(x, y) )
//     s > 1 이면 명암비 증가, 0 < s < 1 이면 감소
//     단점 : 전체가 밝아져서 밝은 쪽이 다 하얗게 날아간다
// ------------------------------------------------------------
void contrast1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (2) 효과적인 방법 - 128을 기준으로 벌리기 (코드 5-6)  ★ 이게 정답 형태
//     dst(x, y) = saturate( src(x, y) + (src(x, y) - 128) * alpha )
//
//     항상 (128, 128) 을 지나는 직선이라, 밝은 픽셀은 더 밝게
//     어두운 픽셀은 더 어둡게 되어 전체 밝기는 유지된다
//       alpha > 0        -> 명암비 증가
//       -1 <= alpha <= 0 -> 명암비 감소
// ------------------------------------------------------------
void contrast2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (3) 트랙바로 명암비 조절하기 (코드 5-4 와 5-6 을 합친 형태)
// ------------------------------------------------------------
Mat g_src;

void on_contrast(int pos, void* userdata) {
	// 트랙바 0~100 을 alpha -1.0 ~ +1.0 으로 바꿔 쓴다
	float alpha = (pos - 50) / 50.f;
	Mat dst = g_src + (g_src - 128) * alpha;

	imshow("dst", dst);
}

void contrast_trackbar() {
	g_src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (g_src.empty()) { cerr << "Image load failed!" << endl; return; }

	namedWindow("dst");
	createTrackbar("Contrast", "dst", 0, 100, on_contrast);
	setTrackbarPos("Contrast", "dst", 50);     // 가운데 = alpha 0 = 원본

	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (4) 직접 구현 (픽셀을 하나씩 돌면서)
// ------------------------------------------------------------
void contrast_manual() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	float alpha = 1.f;
	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			int v = src.at<uchar>(j, i);
			dst.at<uchar>(j, i) = saturate_cast<uchar>(v + (v - 128) * alpha);
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main() {
	// contrast1();
	contrast2();
	// contrast_trackbar();
	// contrast_manual();

	return 0;
}
