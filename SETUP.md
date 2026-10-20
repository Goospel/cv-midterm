# 시험장 세팅 — Visual Studio + OpenCV 프로젝트 만들기

> 처음 보는 컴퓨터에서 5분 안에 빌드되는 상태까지 만드는 순서.

## 0. 먼저 확인할 것 — OpenCV가 어디에 깔려 있나

탐색기나 명령 프롬프트에서 확인한다.

```bat
echo %OPENCV_DIR%
```

- 뭔가 나오면 → 그 경로가 `build` 폴더다. (예: `C:\opencv\build`)
- 아무것도 안 나오면 → `C:\opencv`, `C:\opencv\build`, `C:\Program Files\opencv` 를 직접 찾아본다.

**그리고 lib 파일 이름을 눈으로 확인한다.** 이게 제일 중요하다.

```
<OpenCV>\build\x64\vc16\lib\
```

폴더 안에 `opencv_world4120.lib`, `opencv_world4120d.lib` 같은 파일이 있다.
**끝에 `d`가 붙은 게 Debug용, 없는 게 Release용이다.** 숫자는 버전마다 다르다.

| 본 것 | Debug에 쓸 이름 |
|---|---|
| `opencv_world460.lib` | `opencv_world460d.lib` |
| `opencv_world4120.lib` | `opencv_world4120d.lib` |
| `opencv_world500.lib` | `opencv_world500d.lib` |

`vc16` 대신 `vc17`, `vc15` 폴더일 수도 있다. 있는 걸 쓰면 된다.

---

## 1. 프로젝트 만들기

1. Visual Studio → **새 프로젝트 만들기**
2. **빈 프로젝트**(C++) 선택 → 이름 아무거나 → 만들기
3. 위쪽 툴바에서 **Debug / x64** 로 맞춘다 ← **x86(Win32)이면 안 된다**
4. 솔루션 탐색기 → **소스 파일** 우클릭 → 추가 → **새 항목** → `main.cpp`

## 2. 속성 3곳 설정

솔루션 탐색기에서 **프로젝트 이름 우클릭 → 속성**.
창 위쪽에서 **구성: Debug, 플랫폼: x64** 인지 다시 확인한다.

| 위치 | 넣을 값 |
|---|---|
| C/C++ → 일반 → **추가 포함 디렉터리** | `C:\opencv\build\include` |
| 링커 → 일반 → **추가 라이브러리 디렉터리** | `C:\opencv\build\x64\vc16\lib` |
| 링커 → 입력 → **추가 종속성** | `opencv_world500d.lib` |

- 경로는 0번에서 확인한 실제 경로로 바꾼다.
- 추가 종속성에는 **`.lib`만** 넣는다. `.dll`을 넣으면 `LNK1104`로 빌드가 깨진다.
- Release로도 빌드할 거면 구성을 Release로 바꿔 `d` 없는 이름(`opencv_world500.lib`)으로 같은 작업을 한 번 더 한다.

## 3. 빌드해 보기

```cpp
#include "opencv2/opencv.hpp"
#include <iostream>
int main() {
    std::cout << CV_VERSION << std::endl;
    cv::Mat img = cv::imread("lenna.bmp");
    if (img.empty()) { std::cerr << "Image load failed!" << std::endl; return -1; }
    cv::imshow("img", img);
    cv::waitKey(0);
    return 0;
}
```

버전이 찍히면 설정은 끝난 것이다.

## 4. 이미지 파일은 어디에 두나

`imread("lenna.bmp")` 처럼 파일명만 쓰면 **`.vcxproj` 가 있는 폴더**에서 찾는다.
(`.sln` 폴더가 아니다.)

```
MyProject\
  MyProject.sln
  MyProject\          ← 여기에 이미지를 둔다
    MyProject.vcxproj
    main.cpp
    lenna.bmp
```

이 저장소의 `data/` 폴더 파일들을 거기에 복사하면 된다.

---

## 자주 나는 오류

### `LNK1104: opencv_world500d.lib 파일을 열 수 없습니다`
라이브러리 디렉터리 경로가 틀렸거나, lib 이름의 버전 숫자가 틀렸다.
0번으로 돌아가 lib 폴더의 **실제 파일 이름**을 확인한다.

### 빌드는 되는데 실행하면 `opencv_world500d.dll을 찾을 수 없습니다`
DLL 경로가 PATH에 없다. 둘 중 하나로 해결한다.

- **(빠름)** 프로젝트 속성 → **디버깅** → **환경** 에 이 한 줄을 넣는다
  ```
  PATH=C:\opencv\build\x64\vc16\bin;%PATH%
  ```
- 또는 `bin` 폴더의 DLL을 `.exe`가 생기는 폴더(`x64\Debug`)에 복사한다.

(환경 변수 PATH를 방금 고쳤다면 **Visual Studio를 완전히 껐다 켜야** 적용된다.)

### `error C4716: 값을 반환해야 합니다`
`int` 함수인데 `return` 이 없다. `void` 로 바꾸거나 `return 0;` 을 넣는다.

### `error LNK2019: 확인할 수 없는 외부 기호`
선언과 정의의 **이름 철자(대소문자)나 반환형**이 다르다. 글자 하나까지 맞춘다.

### `error LNK2005: main이 이미 정의되어 있습니다`
`main()` 이 들어있는 .cpp가 두 개 이상 프로젝트에 들어가 있다.
안 쓰는 파일은 우클릭 → 속성 → **빌드에서 제외: 예** 로 둔다.

### 한글 주석이 깨지거나 `C4819` 경고
파일을 **UTF-8(BOM 포함)** 으로 저장한다.
(파일 → 다른 이름으로 저장 → 저장 버튼 옆 화살표 → 인코딩을 지정하여 저장)
경고일 뿐이라 빌드는 된다.

### 실행했는데 창이 바로 닫힌다
`waitKey(0);` 이 없다. `imshow` 뒤에는 꼭 `waitKey`가 있어야 그림이 그려진다.
