// ============================================================
// 06. 카메라 / 동영상 파일 / 동영상 저장
//     (Chapter04 카메라와 동영상 파일 다루기)
// ============================================================
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

// ------------------------------------------------------------
// (1) 카메라 입력 처리
// ------------------------------------------------------------
void camera_in() {
	VideoCapture cap(0);           // 0번 카메라 (기본 웹캠)

	if (!cap.isOpened()) {
		cerr << "Camera open failed!" << endl;
		return;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;

	Mat frame, inversed;
	while (true) {
		cap >> frame;              // 한 프레임 읽기 (cap.read(frame) 과 같다)
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(10) == 27)     // ESC 를 누르면 종료
			break;
	}
	destroyAllWindows();
}

// ------------------------------------------------------------
// (2) 동영상 파일 처리
// ------------------------------------------------------------
void video_in() {
	VideoCapture cap("stopwatch.avi");

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return;
	}

	cout << "Frame width : " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
	cout << "Frame height : " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
	cout << "Frame count : " << cvRound(cap.get(CAP_PROP_FRAME_COUNT)) << endl;

	double fps = cap.get(CAP_PROP_FPS);
	cout << "FPS : " << fps << endl;

	int delay = cvRound(1000 / fps);    // 원래 속도로 재생하려면 이 간격으로

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
}

// ------------------------------------------------------------
// (3) 동영상 파일로 저장하기
// ------------------------------------------------------------
void camera_in_video_out() {
	VideoCapture cap(0);
	if (!cap.isOpened()) { cerr << "Camera open failed!" << endl; return; }

	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = cap.get(CAP_PROP_FPS);
	if (fps <= 0) fps = 30;                     // 카메라가 FPS 를 안 알려줄 때

	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');   // 코덱 지정
	int delay = cvRound(1000 / fps);

	VideoWriter outputVideo("output.avi", fourcc, fps, Size(w, h));

	if (!outputVideo.isOpened()) {
		cerr << "File open failed!" << endl;
		return;
	}

	Mat frame, inversed;
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		inversed = ~frame;
		outputVideo << inversed;      // 한 프레임 쓰기

		imshow("frame", frame);
		imshow("inversed", inversed);

		if (waitKey(delay) == 27)
			break;
	}
	destroyAllWindows();
}

int main() {
	// 필요한 것 하나만 주석을 풀어 쓴다
	video_in();
	// camera_in();
	// camera_in_video_out();

	return 0;
}
