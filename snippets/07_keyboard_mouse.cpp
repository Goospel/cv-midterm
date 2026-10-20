// ============================================================
// 07. 키보드 이벤트 / 마우스 이벤트
//     (Chapter04 이벤트 처리)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// ------------------------------------------------------------
// (1) 키보드 이벤트 - waitKey() 의 반환값이 누른 키의 아스키 코드
// ------------------------------------------------------------
void keyboard_event() {
	Mat img = imread("lenna.bmp");
	if (img.empty()) { cerr << "Image load failed!" << endl; return; }

	namedWindow("img");
	imshow("img", img);

	while (true) {
		int keycode = waitKey(0);

		if (keycode == 'i' || keycode == 'I') {      // 반전
			img = ~img;
			imshow("img", img);
		}
		else if (keycode == 27 || keycode == 'q') {  // ESC 또는 q 면 종료
			break;
		}
	}
	destroyAllWindows();
}

// ------------------------------------------------------------
// (2) 마우스 이벤트 - 드래그해서 그림 그리기
// ------------------------------------------------------------
Mat img;
Point ptOld;

void on_mouse(int event, int x, int y, int flags, void*);

void mouse_event() {
	img = imread("lenna.bmp");
	if (img.empty()) { cerr << "Image load failed!" << endl; return; }

	namedWindow("img");
	setMouseCallback("img", on_mouse);   // 콜백 등록 (창을 먼저 만들 것)

	imshow("img", img);
	waitKey(0);
	destroyAllWindows();
}

void on_mouse(int event, int x, int y, int flags, void*) {
	switch (event) {
	case EVENT_LBUTTONDOWN:                  // 왼쪽 버튼 누름
		ptOld = Point(x, y);
		cout << "EVENT_LBUTTONDOWN : " << x << ", " << y << endl;
		break;

	case EVENT_LBUTTONUP:                    // 왼쪽 버튼 뗌
		cout << "EVENT_LBUTTONUP : " << x << ", " << y << endl;
		break;

	case EVENT_MOUSEMOVE:                    // 마우스 움직임
		if (flags & EVENT_FLAG_LBUTTON) {    // 왼쪽 버튼을 누른 채 움직일 때만
			line(img, ptOld, Point(x, y), Scalar(0, 255, 255), 2);
			imshow("img", img);
			ptOld = Point(x, y);
		}
		break;

	default:
		break;
	}
}

// 자주 쓰는 이벤트 값
//   EVENT_LBUTTONDOWN / EVENT_LBUTTONUP / EVENT_LBUTTONDBLCLK
//   EVENT_RBUTTONDOWN / EVENT_RBUTTONUP
//   EVENT_MOUSEMOVE   / EVENT_MOUSEWHEEL
// flags 비트 값
//   EVENT_FLAG_LBUTTON / EVENT_FLAG_RBUTTON / EVENT_FLAG_CTRLKEY / EVENT_FLAG_SHIFTKEY

int main() {
	// keyboard_event();
	mouse_event();

	return 0;
}
