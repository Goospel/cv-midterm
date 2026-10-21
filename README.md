# 컴퓨터비전 중간고사 — 실기 대비 코드 모음

호서대 2026-2학기 「컴퓨터비전(02)」 중간고사(2026-10-21 수 15:00~17:30) 오픈북 대비 자료.
**시험 범위: Chapter 01 ~ 05 (1주차 ~ 7주차)**

## 바로 쓰기

| 상황 | 할 일 |
|---|---|
| 기능별로 코드를 찾고 싶다 | **[index.html](index.html)** 을 브라우저로 연다 |
| **VS + OpenCV 설정을 처음부터 해야 한다** | **[docs/VS-OPENCV-SETUP.md](docs/VS-OPENCV-SETUP.md)** — 교재 화면 캡처 넣은 따라하기 |
| 설정은 알고 빠른 요약만 필요하다 | [SETUP.md](SETUP.md) |
| 코드 파일만 필요하다 | [`snippets/`](snippets) 폴더 |
| 실습 이미지가 없다 | [`data/`](data) 폴더를 프로젝트 폴더에 복사 |

학교 컴퓨터에서 받는 법: 이 페이지 위쪽 초록색 **Code** 버튼 → **Download ZIP**

## 폴더

```
index.html                 기능 → 코드 찾아보기 (여기서 시작)
docs/VS-OPENCV-SETUP.md    VS + OpenCV 설정 따라하기 (교재 화면 캡처 포함)
docs/images/               교재 설정 화면 캡처
SETUP.md                   같은 내용의 짧은 요약판
snippets/                  주제별 코드 (각 파일에 main() 이 들어 있어 그대로 빌드됨)
data/                      실습용 이미지·동영상 (lenna, cat, dog, airplane, field, mask, hawkes, stopwatch)
```

## snippets 목록

| 파일 | 내용 | 교재 |
|---|---|---|
| `01_image_io.cpp` | imread / imshow / imwrite, 창 다루기 | Ch02 |
| `02_mat_basics.cpp` | Mat 생성·초기화·정보·복사·타입/크기 변환 | Ch03 |
| `03_roi_mask.cpp` | 부분 영상(ROI), 반전, 마스크 연산 | Ch03·04 |
| `04_pixel_access.cpp` | at / ptr 픽셀 접근, split·merge | Ch03 |
| `05_drawing.cpp` | line·rectangle·circle·ellipse·polylines·putText | Ch04 |
| `06_video_camera.cpp` | VideoCapture(카메라·파일), VideoWriter | Ch04 |
| `07_keyboard_mouse.cpp` | 키보드·마우스 이벤트 | Ch04 |
| `08_trackbar.cpp` | 트랙바 (기본 / RGB 3개) | Ch04 |
| `09_brightness.cpp` | 밝기 조절, 직접 구현, 트랙바 밝기 | Ch05 |
| `10_contrast.cpp` | 명암비 조절 (기본 / 효과적인 방법) | Ch05 |
| `11_histogram.cpp` | 히스토그램 구하기·그리기, 스트레칭, 평활화 | Ch05 |
| `12_utils.cpp` | 연산 시간 측정, sum·mean·minMaxLoc·normalize, FileStorage | Ch04 |

## 쓰는 법

각 `.cpp` 에는 `main()` 이 들어 있다. **한 프로젝트에 하나만** 넣고 빌드한다.
여러 개를 넣으면 `LNK2005: main이 이미 정의되어 있습니다` 가 난다 —
안 쓰는 파일은 우클릭 → 속성 → **빌드에서 제외: 예**.

필요한 부분만 뽑아 쓸 때는 함수 단위로 복사해 쓰면 된다.

## 주의

- 플랫폼은 **x64**, 구성은 **Debug** 로 맞춘다.
- 추가 종속성에는 `.lib` 만 넣는다 (`.dll` 넣으면 LNK1104).
- `imread("lenna.bmp")` 는 **`.vcxproj` 가 있는 폴더**에서 파일을 찾는다.
- OpenCV 버전에 따라 lib 이름의 숫자가 다르다 → SETUP.md 0번 참고.
