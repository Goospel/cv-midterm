// ============================================================
// 12. 유용한 기능 - 시간 측정 / 통계 함수 / 데이터 파일 입출력
//     (Chapter04 코드 4-18, 4-19 및 유용한 함수들)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// ------------------------------------------------------------
// (1) 연산 시간 측정 - TickMeter (코드 4-19)
// ------------------------------------------------------------
void time_inverse() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	Mat dst(src.rows, src.cols, src.type());

	TickMeter tm;
	tm.start();

	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			dst.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}

	tm.stop();
	cout << "Image inverse took " << tm.getTimeMilli() << "ms." << endl;
	// tm.getTimeMicro()  마이크로초 / tm.getTimeSec()  초
	// tm.reset()         0으로 초기화

	// ※ Debug 모드는 아주 느리다. 시간 측정은 Release 모드로 할 것.
}

// 틱 카운트로 직접 재는 방법
void time_tickcount() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) { cerr << "Image load failed!" << endl; return; }

	int64 t1 = getTickCount();

	Mat dst = ~src;                   // 재고 싶은 작업

	int64 t2 = getTickCount();
	double ms = (t2 - t1) * 1000 / getTickFrequency();
	cout << "took " << ms << "ms." << endl;
}

// ------------------------------------------------------------
// (2) 통계 함수 - sum / mean / minMaxLoc / normalize / cvRound
// ------------------------------------------------------------
void useful_functions() {
	Mat img = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (img.empty()) { cerr << "Image load failed!" << endl; return; }

	// 합과 평균 : 반환형이 Scalar 라서 [0] 으로 꺼낸다 (컬러면 [0]=B [1]=G [2]=R)
	cout << "Sum: " << (int)sum(img)[0] << endl;
	cout << "Mean: " << (int)mean(img)[0] << endl;

	// 최솟값 / 최댓값과 그 위치
	double minVal, maxVal;
	Point minPos, maxPos;
	minMaxLoc(img, &minVal, &maxVal, &minPos, &maxPos);
	cout << "minVal: " << minVal << " at " << minPos << endl;
	cout << "maxVal: " << maxVal << " at " << maxPos << endl;
	// 필요 없는 인자는 0 을 준다 : minMaxLoc(img, 0, &maxVal);

	// 정규화 : 값의 범위를 0 ~ 255 로 맞춘다
	Mat src = Mat_<float>({ 1, 5 }, { -1.f, -0.5f, 0.f, 0.5f, 1.f });
	Mat dst;
	normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	cout << "src: " << src << endl;
	cout << "dst: " << dst << endl;      // [0, 64, 128, 191, 255]

	// 반올림 : 0.5 는 가까운 짝수로 간다 (cvRound(2.5)==2, cvRound(3.5)==4)
	cout << "cvRound(2.5): " << cvRound(2.5) << endl;
	cout << "cvRound(2.51): " << cvRound(2.51) << endl;
	cout << "cvRound(3.5): " << cvRound(3.5) << endl;
	// cvCeil() 올림, cvFloor() 내림
}

// ------------------------------------------------------------
// (3) 데이터 파일 입출력 - FileStorage (코드 4-14, 4-15)
// ------------------------------------------------------------
String filename = "mydata.json";      // .xml / .yml 로 바꾸면 그 형식으로 저장된다

void writeData() {
	String name = "Jane";
	int age = 10;
	Point pt1(100, 200);
	vector<int> scores = { 80, 90, 50 };
	Mat mat1 = (Mat_<float>(2, 2) << 1.0f, 1.5f, 2.0f, 3.2f);

	FileStorage fs(filename, FileStorage::WRITE);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs << "name" << name;        // "이름" << 값  순서로 쓴다
	fs << "age" << age;
	fs << "point" << pt1;
	fs << "scores" << scores;
	fs << "data" << mat1;

	fs.release();                // 꼭 닫아야 파일에 반영된다
}

void readData() {
	String name;
	int age;
	Point pt1;
	vector<int> scores;
	Mat mat1;

	FileStorage fs(filename, FileStorage::READ);

	if (!fs.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	fs["name"] >> name;          // 이름으로 찾아 꺼낸다
	fs["age"] >> age;
	fs["point"] >> pt1;
	fs["scores"] >> scores;
	fs["data"] >> mat1;

	fs.release();

	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "point: " << pt1 << endl;
	cout << "scores: " << Mat(scores).t() << endl;
	cout << "data:\n" << mat1 << endl;
}

int main() {
	time_inverse();
	useful_functions();
	writeData();
	readData();

	return 0;
}
