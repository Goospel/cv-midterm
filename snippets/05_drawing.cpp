// ============================================================
// 05. 그리기 함수 - 선 / 도형 / 문자열
//     (Chapter04 다양한 그리기 함수)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img(500, 700, CV_8UC3, Scalar(255, 255, 255));   // 흰 도화지

	// ---------- 직선 ----------
	// line(영상, 시작점, 끝점, 색, 두께, 선타입, shift)
	line(img, Point(50, 50), Point(200, 50), Scalar(0, 0, 255));           // 빨강
	line(img, Point(50, 70), Point(200, 70), Scalar(255, 0, 255), 3);      // 두께 3
	line(img, Point(50, 90), Point(200, 90), Scalar(255, 0, 0), 5, LINE_AA);  // 부드럽게

	// 화살표
	arrowedLine(img, Point(50, 120), Point(200, 120), Scalar(0, 0, 255), 2);

	// 마커(십자, X 등)
	drawMarker(img, Point(50, 160), Scalar(0, 0, 255), MARKER_CROSS);
	drawMarker(img, Point(100, 160), Scalar(0, 0, 255), MARKER_TILTED_CROSS);
	drawMarker(img, Point(150, 160), Scalar(0, 0, 255), MARKER_STAR);

	// ---------- 사각형 ----------
	// rectangle(영상, Rect, 색, 두께, ...)  두께에 FILLED(-1) 를 주면 채워진다
	rectangle(img, Rect(250, 50, 150, 100), Scalar(0, 0, 255), 2);
	rectangle(img, Rect(250, 170, 150, 100), Scalar(0, 0, 255), FILLED);
	// rectangle(img, Point(250,50), Point(400,150), Scalar(0,0,255), 2);  // 두 점으로도 가능

	// ---------- 원 ----------
	// circle(영상, 중심, 반지름, 색, 두께, ...)
	circle(img, Point(500, 100), 50, Scalar(255, 0, 0), 2, LINE_AA);
	circle(img, Point(500, 220), 50, Scalar(255, 0, 0), FILLED, LINE_AA);

	// ---------- 타원 ----------
	// ellipse(영상, 중심, Size(장축/2, 단축/2), 회전각, 시작각, 끝각, 색, 두께, ...)
	ellipse(img, Point(620, 100), Size(60, 30), 0, 0, 360, Scalar(255, 0, 0), 2, LINE_AA);
	ellipse(img, Point(620, 220), Size(60, 30), 45, 0, 180, Scalar(0, 128, 0), FILLED, LINE_AA);

	// ---------- 다각형 ----------
	vector<Point> pts;
	pts.push_back(Point(250, 300));
	pts.push_back(Point(300, 350));
	pts.push_back(Point(250, 400));
	pts.push_back(Point(150, 400));
	pts.push_back(Point(100, 350));
	polylines(img, pts, true, Scalar(255, 0, 255), 2);   // true = 닫힌 도형

	// ---------- 문자열 ----------
	// putText(영상, 문자열, 왼쪽아래 좌표, 폰트, 크기, 색, 두께, ...)
	putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 450),
		FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 1, LINE_AA);
	putText(img, "FONT_HERSHEY_PLAIN", Point(20, 480),
		FONT_HERSHEY_PLAIN, 1.0, Scalar(255, 0, 0), 1, LINE_AA);
	// 기울임꼴은 FONT_ITALIC 을 더한다
	// putText(img, "ITALIC", Point(20,480), FONT_HERSHEY_SIMPLEX | FONT_ITALIC, 1.0, Scalar(0,0,0));

	imshow("canvas", img);
	waitKey(0);

	// ---------- 문자열 가운데 정렬하기 ----------
	Mat img2(200, 640, CV_8UC3, Scalar(255, 255, 255));

	const String text = "Hello, OpenCV";
	int fontFace = FONT_HERSHEY_TRIPLEX;
	double fontScale = 2.0;
	int thickness = 1;

	int baseline = 0;
	Size sizeText = getTextSize(text, fontFace, fontScale, thickness, &baseline);

	// 영상 한가운데에 오도록 좌표를 계산한다
	Point org((img2.cols - sizeText.width) / 2, (img2.rows + sizeText.height) / 2);

	putText(img2, text, org, fontFace, fontScale, Scalar(255, 0, 0), thickness, LINE_AA);
	rectangle(img2, org + Point(0, baseline),
		org + Point(sizeText.width, -sizeText.height), Scalar(0, 255, 0), 1);

	imshow("center text", img2);
	waitKey(0);
	destroyAllWindows();

	return 0;
}
