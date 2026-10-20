// ============================================================
// 11. 히스토그램 - 구하기 / 그리기 / 스트레칭 / 평활화
//     (Chapter05 코드 5-7 ~ 5-10)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// ------------------------------------------------------------
// (1) 히스토그램 구하기 (코드 5-7)
// ------------------------------------------------------------
Mat calcGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);

	Mat hist;
	int channels[] = { 0 };            // 0번 채널 (그레이스케일은 하나뿐)
	int dims = 1;                      // 1차원 히스토그램
	const int histSize[] = { 256 };    // 빈(bin) 개수 256개
	float graylevel[] = { 0, 256 };    // 값의 범위 0 이상 256 미만
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;    // CV_32FC1, 원소 256개
}

// ------------------------------------------------------------
// (2) 히스토그램 그래프 그리기 (코드 5-8)
//
//  ※ 교재는 hist.at<float>(i, 0) 과 CV_Assert(hist.size() == Size(1, 256))
//     을 쓰는데, OpenCV 5.x 에서는 결과가 1 x 256 모양이라
//     그대로 쓰면 Assert 에서 멈추거나 값이 전부 0 으로 읽힌다.
//     아래처럼 hist.at<float>(i) 로 쓰면 4.x / 5.x 양쪽에서 다 맞는다.
// ------------------------------------------------------------
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.total() == 256);

	double histMax;
	minMaxLoc(hist, 0, &histMax);      // 가장 큰 빈도수를 찾는다

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));   // 흰 바탕 256 x 100
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i) * 100 / histMax)), Scalar(0));
	}

	return imgHist;
}

void histogram_show() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (3) 히스토그램 스트레칭 (코드 5-9)
//
//     dst(x, y) = (src(x, y) - Gmin) * 255 / (Gmax - Gmin)
//
//     영상이 쓰는 밝기 구간을 0~255 전체로 쭉 늘려 명암비를 높인다.
//     OpenCV 에 전용 함수가 없어서 직접 쓴다.
// ------------------------------------------------------------
void histogram_stretching() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);      // 최솟값 / 최댓값 찾기

	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (4) Ends-In Search 스트레칭
//
//     하한(low) 아래는 전부 0, 상한(high) 위는 전부 255 로 만들고
//     그 사이만 늘린다. 아주 어둡거나 밝은 소수의 픽셀 때문에
//     스트레칭 효과가 안 나는 경우에 쓴다.
// ------------------------------------------------------------
void histogram_ends_in(int low = 40, int high = 200) {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst(src.rows, src.cols, src.type());

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			int v = src.at<uchar>(j, i);

			if (v <= low)
				dst.at<uchar>(j, i) = 0;
			else if (v >= high)
				dst.at<uchar>(j, i) = 255;
			else
				dst.at<uchar>(j, i) = saturate_cast<uchar>((v - low) * 255 / (high - low));
		}
	}

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (5) 히스토그램 평활화 (코드 5-10)
//
//     dst(x, y) = round( H(src(x, y)) * Lmax / N )
//       H  : 누적 히스토그램,  Lmax = 255,  N = 전체 픽셀 수
//
//     픽셀 값 분포를 전 구간에 고르게 퍼뜨린다.
//     ※ equalizeHist 는 CV_8UC1 (그레이스케일) 만 받는다. 컬러를 넣으면 에러.
// ------------------------------------------------------------
void histogram_equalization() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst;
	equalizeHist(src, dst);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));
	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

// ------------------------------------------------------------
// (6) 컬러 영상을 평활화하고 싶을 때
//     세 채널을 각각 평활화하면 색이 변한다.
//     밝기 채널(Y) 만 평활화해야 색이 유지된다.
// ------------------------------------------------------------
void histogram_equalization_color() {
	Mat src = imread("lenna.bmp", IMREAD_COLOR);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat src_ycrcb;
	cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb);

	vector<Mat> planes;
	split(src_ycrcb, planes);
	equalizeHist(planes[0], planes[0]);     // Y(밝기) 채널만

	Mat dst_ycrcb, dst;
	merge(planes, dst_ycrcb);
	cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR);

	imshow("src", src);
	imshow("dst", dst);
	waitKey();
	destroyAllWindows();
}

int main() {
	// histogram_show();
	// histogram_stretching();
	// histogram_ends_in();
	histogram_equalization();
	// histogram_equalization_color();

	return 0;
}
