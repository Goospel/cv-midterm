// ============================================================
// 02. Mat 기본 - 생성 / 초기화 / 정보 / 복사 / 타입·크기 변환
//     (Chapter03)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	// ---------- 행렬 생성 ----------
	Mat img1(480, 640, CV_8UC1);                      // 그레이스케일 (쓰레기값)
	Mat img2(480, 640, CV_8UC3);                      // 컬러
	Mat img3(Size(640, 480), CV_8UC3);                // Size(가로, 세로) 주의

	Mat img4(480, 640, CV_8UC1, Scalar(128));         // 회색으로 초기화
	Mat img5(480, 640, CV_8UC3, Scalar(0, 0, 255));   // 빨강 (B, G, R 순서)

	Mat mat_zero = Mat::zeros(3, 3, CV_32SC1);        // 0으로 채움
	Mat mat_one = Mat::ones(3, 3, CV_32FC1);          // 1로 채움
	Mat mat_eye = Mat::eye(3, 3, CV_32FC1);           // 단위 행렬

	// 값을 직접 넣어 만들기
	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat_data(2, 3, CV_32FC1, data);
	cout << "mat_data:\n" << mat_data << endl;

	// 이미 만든 행렬을 한 가지 값으로 채우기
	Mat img6(480, 640, CV_8UC3);
	img6 = Scalar(255, 0, 0);     // 파랑
	img6.setTo(Scalar(0, 255, 0));  // 초록 (setTo 도 같은 역할)

	// ---------- 행렬 정보 참조 ----------
	Mat img = imread("lenna.bmp");
	if (img.empty()) { cerr << "Image load failed!" << endl; return -1; }

	cout << "rows : " << img.rows << endl;          // 세로 크기(행 개수)
	cout << "cols : " << img.cols << endl;          // 가로 크기(열 개수)
	cout << "size : " << img.size() << endl;        // [가로 x 세로]
	cout << "channels : " << img.channels() << endl;
	cout << "type : " << img.type() << endl;        // CV_8UC3 이면 16
	cout << "depth : " << img.depth() << endl;
	cout << "total : " << img.total() << endl;      // 전체 픽셀 개수
	cout << "elemSize : " << img.elemSize() << endl;  // 한 픽셀의 바이트 수
	cout << "empty? " << img.empty() << endl;

	// ---------- 복사 : 얕은 복사 vs 깊은 복사 ----------
	Mat shallow1 = img;         // 얕은 복사 - 같은 픽셀을 가리킴
	Mat shallow2;
	shallow2 = img;             // 이것도 얕은 복사

	Mat deep1 = img.clone();    // 깊은 복사 - 픽셀까지 새로 복사
	Mat deep2;
	img.copyTo(deep2);          // 이것도 깊은 복사

	// 원본을 바꿔 보면 차이를 알 수 있다
	// img.setTo(Scalar(0, 255, 255));
	// shallow1 도 같이 노랗게 변하고, deep1 은 그대로다

	// ---------- 타입 변환 ----------
	Mat gray = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat fimg;
	gray.convertTo(fimg, CV_32FC1);           // uchar -> float
	// gray.convertTo(dst, CV_8UC1, alpha, beta);  // dst = src * alpha + beta

	// ---------- 크기 변환 ----------
	Mat small_img;
	resize(gray, small_img, Size(320, 240));            // 크기를 직접 지정
	// resize(gray, small_img, Size(), 0.5, 0.5);       // 비율로 지정 (절반)

	imshow("img", img);
	imshow("small", small_img);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
