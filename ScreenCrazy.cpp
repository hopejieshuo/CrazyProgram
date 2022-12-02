#include <CSTDLIB>
#include <CTIME>
#include <CMATH>
#include <WINDOWS.H>
#pragma comment(lib,"SHLWAPI.LIB")
#pragma comment(lib,"MSIMG32.LIB")
#define nTime 10
#define PI 3.141

void MoveRight(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w / 20, h, hdc, w / 20 * 19, 0, SRCCOPY);
    	BitBlt(hcdc, w / 20, 0, w / 20 * 19, h, hdc, 0, 0, SRCCOPY);
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(10);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void RandLeft(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	BitBlt(hcdc, -10, (rand() % 50) - 25, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(50);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ColorScreenMove(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	    BitBlt(hcdc, 0, 0, w - 20, h - 20, hdc, 20, 20, NOTSRCERASE);
    	SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
    	PatBlt(hcdc, 0, 0, w, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void PixelationScreen(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for(int x = 0; x <= w; x += 10){
            for(int y = 0; y <= h; y += 10){
                StretchBlt(hcdc, x, y, 10, 10, hcdc, x, y, 1, 1, SRCCOPY);
            }
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void TwistScreen(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        int y = rand() % h;
        int v1 = rand() % 5;
        if (v1){
            if (v1 == 1){
                BitBlt(hdc, 0, y, w, 15, hdc, 5, y, SRCCOPY);
            }
        }else{
            BitBlt(hdc, 5, y, w, 15, hdc, 0, y, SRCCOPY);
        }
		ReleaseDC(NULL, hdc);
    	DeleteObject(hdc);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void PositionError(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        POINT pos[2];
        pos[0].x = (w / 10) * (rand() % 10);
        pos[0].y = (h / 10) * (rand() % 10);
        pos[1].x = (w / 10) * (rand() % 10);
        pos[1].y = (h / 10) * (rand() % 10);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, pos[0].x, pos[0].y, w / 10, h / 10, hcdc, pos[1].x, pos[1].y, SRCCOPY);
        BitBlt(hdc, pos[1].x, pos[1].y, w / 10, h / 10, hcdc, pos[0].x, pos[0].y, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ColorLineBlock(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        int cho = rand() % 2;
        if(cho == 0){
        	PatBlt(hcdc, 0, (h / 20) * (rand() % 20), w, h / 20, PATINVERT);
        }else{
        	PatBlt(hcdc, (w / 20) * (rand() % 20), 0, w / 20, h, PATINVERT);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenWind(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	BLENDFUNCTION blf = { 0 };
    	blf.BlendOp = AC_SRC_OVER;
    	blf.BlendFlags = 0;
    	blf.SourceConstantAlpha = 128;
    	blf.AlphaFormat = 0;
    	AlphaBlend(hdc, 0 + t % 200 + 10, 0 - t % 25, w, h, hcdc, 0, 0, w, h, blf);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(20);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenMelt(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	    int rndx = rand() % (w - 10);
	    int rndy = rand() % 50;
        BitBlt(hcdc, rndx, rndy, 10, h, hdc, rndx, 0, SRCCOPY);
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
    	DeleteObject(hBitmap);
    	DeleteObject(hcdc);
    	Sleep(50);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenBlackBlock(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int x = rand() % (w - 2), y = rand() % (h / 2);
    	BitBlt(hcdc, x, y, rand() % (w - 2), rand() % (h - 2), hdc, x, y, NOTSRCERASE);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(50);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenCrazyMove(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        t *= 3;
    	int x = rand() % w;
    	int y = rand() % h;
    	BitBlt(hcdc, x, y, t % w, t % h, hdc, (x + t / 2) % w, y % h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(50);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenPaper(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	    int _w = rand() % 100 + 400, _h = rand() % 100 + 400;
		int x = rand() % (w - _w), y = rand() % (h - _h);
		StretchBlt(hcdc, x + (5 - rand() % 10), y + (5 - rand() % 10), _w + (5 - rand() % 10), _h + (5 - rand() % 10), hdc, x, y, _w, _h, SRCCOPY);
		StretchBlt(hcdc, x + (5 - rand() % 10), y + (5 - rand() % 10), _w + (5 - rand() % 10), _h + (5 - rand() % 10), hdc, x, y, _w, _h, SRCCOPY);
		StretchBlt(hcdc, x + (5 - rand() % 10), y + (5 - rand() % 10), _w + (5 - rand() % 10), _h + (5 - rand() % 10), hdc, x, y, _w, _h, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenSkew(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        POINT ps[3];
        ps[0].x = 0, ps[0].y = h / 8;
        ps[1].x = w - (w / 8), ps[1].y = 0;
        ps[2].x = w / 8, ps[2].y = h;
		PlgBlt(hcdc, ps, hdc, 0, 0, w, h, 0, 0, 0);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenRotate(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        POINT ps[3];
        ps[0].x = 0, ps[0].y = 0;
        ps[1].x = w, ps[1].y = 0;
        ps[2].x = sin(PI / 18) * h, ps[2].y = cos(PI / 18) * h;
		PlgBlt(hcdc, ps, hdc, 0, 0, w, h, 0, 0, 0);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenShake(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SelectObject(hcdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
        BitBlt(hcdc, 10 * ((rand() % 3) - 1), 10 * ((rand() % 3) - 1), w, h, hdc, 0, 0, SRCCOPY);
        PatBlt(hcdc, 0, 0, w, h, PATINVERT);
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(50);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void BlackDown(){
    int dwStartTime = time(NULL);
    int tmp = 0;
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        if(tmp > h){
            tmp = 0;
        }
        StretchBlt(hcdc, 0, 0, w, tmp, hdc, 0, 0, 1, 1, SRCAND);
		tmp += 10;
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void ScreenWave(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++) {
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
		HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for(int y = 0; y <= h; y ++){
            BitBlt(hcdc, y % (h / 5), y, w, 1, hdc, 0, y, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
    	Sleep(1000);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void MainPart(){
    MoveRight();
    RandLeft();
    ColorScreenMove();
    PixelationScreen();
    TwistScreen();
    PositionError();
    ColorLineBlock();
    ScreenWind();
    ScreenMelt();
    ScreenBlackBlock();
    ScreenCrazyMove();
    ScreenPaper();
    ScreenSkew();
    ScreenRotate();
    ScreenShake();
    BlackDown();
    ScreenWave();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, INT nCmdShow){
    int mb = MessageBox(NULL, "This Malware will disturb you for some time,are you sure to run it?", "Warning", MB_YESNO+MB_ICONQUESTION);
    if(mb == IDYES){
        int mba = MessageBox(NULL, "This is last warning,the malware author couldn't assume legal liability,so are you sure to run it?", "Warning", MB_YESNO+MB_ICONWARNING);
        if(mba == IDYES){
            MainPart();
        }
    }
    return 0;
}