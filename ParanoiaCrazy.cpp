#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <tchar.h>
#include <shlwapi.h>
#include <commctrl.h>
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"msimg32.lib")
#define PI acos( -1.0 )

DWORD xs;
LPCSTR StrArray[36] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE unused;
	};
} *PRGBQUAD;

DWORD Xorshift32( VOID ){
	xs ^= xs << 13;
	xs ^= xs >> 17;
	xs ^= xs << 5;
	return xs;
}
double RadToDeg(double Rad){
    double Deg = Rad / PI * 180;
    return Deg;
}
double DegToRad(double Deg){
    double Rad = Deg / 180 * PI;
    return Rad;
}
double RtFunc(double Rad){
    double RadMod = fmod(Rad, 2 * PI);
    double Deg = RadToDeg(RadMod), DegMod = fmod(RadToDeg(RadMod), 90);
    double Value;
    if(RadMod < PI / 2){
        Value = (double)(DegMod / 90);
    }else if(RadMod < PI){
        Value = (double)(1.0 - (DegMod / 90));
    }else if(RadMod < PI / 2 * 3){
        Value = (double)(-1.0 * (DegMod / 90));
    }else{
        Value = (double)((DegMod / 90) - 1.0);
    }
    return Value;
}

/* ---------------------------------------------------------------------------------------------------- */

void WINAPI InitDPI( VOID ) {
	HMODULE hModUser32 = LoadLibrary((char *)"user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModUser32, "SetProcessDPIAware");
	if (SetProcessDPIAware){
		SetProcessDPIAware();
	}
	FreeLibrary(hModUser32);
	
    xs = (DWORD)(time(NULL));
}

DWORD WINAPI payload1A(LPVOID lpParam){
	for( ; ; ){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        POINT pos[3];
        pos[0].x = 50, pos[0].y = -50;
        pos[1].x = w + 50, pos[1].y = 50;
        pos[2].x = -50, pos[2].y = h - 50;
        PlgBlt(hdc, pos, hdc, -20, -20, w + 40, h + 40, 0, 0, 0);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(200);
    }
    return 0;
}

DWORD WINAPI payload1B(LPVOID lpParam){
	HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	
	for( ; ; ) {
    	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    	
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
    	for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++){
                int rgb = (prgbScreen[x + w * y].r + prgbScreen[x + w * y].g + prgbScreen[x + w * y].b) / 3;
                prgbScreen[x + w * y].r = rgb;
                prgbScreen[x + w * y].g = rgb;
                prgbScreen[x + w * y].b = rgb;
            }
    	}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(3000);
	}
	
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}

DWORD WINAPI payload2(LPVOID lpParam){
    for(int t = 0; ; t++){
    	HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
    	POINT pos[3];
    	int n = t % 10 <= 5 ? -1 : 1;
    	pos[0].x = n * 30, pos[0].y = -(n * 30);
    	pos[1].x = w + n * 30, pos[1].y = n * 30;
    	pos[2].x = -(n * 30), pos[2].y = h - (n * 30);
    	PlgBlt(hcdc, pos, hdc, 0, 0, w, h, NULL, 0, 0);
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, t % 20 < 10 ? 8913094 : 15597702);
		ReleaseDC(NULL, hdc);
    	ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
    	DeleteObject(hcdc);
    	DeleteObject(hBitmap);
    	Sleep(200);
    }
    return 0;
}

DWORD WINAPI payload3A(LPVOID lpParam){
    for( ; ; ){
    	HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        BitBlt(hdc, 1, 1, w, h, hdc, 0, 0, 6684742);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(200);
    }
    return 0;
}

DWORD WINAPI payload3B(LPVOID lpParam){
    for( ; ; ){
    	HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        SetBkColor(hdc, Xorshift32() % 0xffffff);
        SetTextColor(hdc, Xorshift32() % 0xffffff);
        TextOutA(hdc, Xorshift32() % w, Xorshift32() % h, TEXT("ParanoiaCrazy"), 13);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(1000);
    }
    return 0;
}

DWORD WINAPI payload4(LPVOID lpParam){
    for( ; ; ){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        int ropindex = Xorshift32() % 5;
        int rop = 0;
        if(ropindex == 0){
            rop = 8913094;
        }else if(ropindex == 1){
            rop = 15597702;
        }else{
            rop = 13369376;
        }
        int x = ((Xorshift32() % 2) == 0 ? -1 : 1) * 10, y = (Xorshift32() % 20) * (h / 20);
        BitBlt(hdc, x, y, w, h / 20, hdc, 0, y, rop);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
        Sleep(250);
    }
    return 0;
}

DWORD WINAPI payload5A(LPVOID lpParam){
	for( ; ; ){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        POINT pos[3];
        pos[0].x = 60, pos[0].y = 40;
        pos[1].x = w - 40, pos[1].y = 60;
        pos[2].x = 40, pos[2].y = h - 60;
		PlgBlt(hdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(250);
    }
    return 0;
}

DWORD WINAPI payload5B(LPVOID lpParam){
    int cx = 1, cy = 1;
    int x = 0, y = 0;
	for(int t = 0; ; t++){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    	PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
    	plf->lfWidth = 50;
    	plf->lfHeight = 50;
    	plf->lfWeight = 500;
    	plf->lfEscapement = 20 * t;
    	SelectObject(hdc, CreateFontIndirect(plf));
    	SetBkMode(hdc, TRANSPARENT);
    	SetTextColor(hdc, 0x0000ff);
    	TextOutA(hdc, x, y, _T("Be Lost"), 7);
    	LocalFree((LOCALHANDLE)plf);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		if(cx == 1){
		    if(x >= w - 175){
		        cx = -1;
		    }
		}else{
		    if(x <= -175){
		        cx = 1;
		    }
		}
		if(cy == 1){
		    if(y >= h - 25){
		        cy = -1;
		    }
		}else{
		    if(y <= -25){
		        cy = 1;
		    }
		}
		x += cx * 10, y += cy * 10;
		Sleep(250);
    }
    return 0;
}

DWORD WINAPI payload6(LPVOID lpParam){
    for( ; ; ){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        int blockW = w / 10, blockH = h / 10;
        int blockX = Xorshift32() % (w - blockW), blockY = Xorshift32() % (h - blockH);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
        SelectObject(hcdc, CreateSolidBrush(0x000000));
        Rectangle(hcdc, blockX, blockY, blockX + blockW, blockY + blockH);
    	BitBlt(hcdc, blockX + ((Xorshift32() % 2 == 0) ? (blockH / 10) : (-1 * (blockH / 10))), blockY + ((Xorshift32() % 2 == 0) ? (blockH / 10) : (-1 * (blockH / 10))), blockW, blockH, hdc, blockX, blockY, 13369376);
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
    	ReleaseDC(NULL, hdc);
    	DeleteObject(hdc);
    	ReleaseDC(NULL, hcdc);
    	DeleteObject(hcdc);
    	DeleteObject(hBitmap);
    	Sleep(500);
    }
    return 0;
}

DWORD WINAPI payload7A(LPVOID lpParam){
	for(int t = 0; ; t++){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        POINT pos[3];
        if(t % 200 < 100){
            pos[0].x = 50, pos[0].y = 50;
            pos[1].x = w, pos[1].y = 0;
            pos[2].x = 0, pos[2].y = h;
        }else{
            pos[0].x = 0, pos[0].y = 0;
            pos[1].x = w - 50, pos[1].y = 50;
            pos[2].x = 50, pos[2].y = h - 50;
        }
		PlgBlt(hdc, pos, hdc, 0, 0, w, h, 0, 0, 0);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(250);
    }
    return 0;
}

DWORD WINAPI payload7B(LPVOID lpParam){
	for(; ; ){
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        SelectObject(hdc, CreatePen(0, 5, 0x0000ff));
        MoveToEx(hdc, Xorshift32() % w, 0, NULL);
        LineTo(hdc, Xorshift32() % w, h);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(250);
    }
    return 0;
}

void ct(LPTHREAD_START_ROUTINE funcOne, LPTHREAD_START_ROUTINE funcTwo, int timer){
    if(funcOne != NULL){
        HANDLE handleOne = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(funcOne), NULL, 0, NULL);
        if(funcTwo != NULL){
            HANDLE handleTwo = CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(funcTwo), NULL, 0, NULL);
            Sleep(timer);
            TerminateThread(handleTwo, 0);
            CloseHandle(handleTwo);
        }else{
            Sleep(timer);
        }
        TerminateThread(handleOne, 0);
        CloseHandle(handleOne);
    }else{
        Sleep(timer);
    }
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

/* ---------------------------------------------------------------------------------------------------- */

DWORD WINAPI payloadStart(LPVOID lpParam){
    HWND hwnd = FindWindow(TEXT("Notepad"), NULL);
    int rx = -1, ry = -1;
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    for(int t = 0; ; t++){
        if(hwnd != NULL){
            RECT rect;
            GetWindowRect(hwnd, &rect);
            int cx = rect.left, cy = rect.top, cw = rect.right - rect.left, ch = rect.bottom - rect.top;
            if(cx >= w - cw || cx <= 0){
                rx *= -1;
            }
            if(cy >= h - ch || cy <= 0){
                ry *= -1;
            }
            cx += (rx * 2), cy += (ry * 5);
            cw = 0, ch = 0;
            SetWindowPos(hwnd, (hwnd)-2, cx, cy, cw, ch, 80);
            SetWindowTextA(hwnd, StrArray[t % 36]);
            Sleep(50);
        }else{
            return 0;
        }
    }
    return 0;
}

DWORD WINAPI payloadTurn1(LPVOID lpParam){
	HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	
	for(int t = 0; t < 10; t++) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
    	for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++){
                prgbScreen[x + w * y].rgb = (Xorshift32() % 100 == (DWORD)t ? 0xff0000: 0x000000);
            }
    	}
    	
        SetBkMode(hcdc, 1);
        SetTextColor(hcdc, 0x0000ff);
        HFONT font = CreateFont(100, 80, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, "Baby Kruffy");
        SelectObject(hcdc, font);
        TextOutA(hcdc, (w - 80) / 2, (h - 100) / 2, StrArray[35 - t], 1);
        
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(1000);
	}
	
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}

DWORD WINAPI payloadTurn2(LPVOID lpParam){
	HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	
	for(int t = 0; t < 20; t++) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
		int topY = Xorshift32() % h;
		int bottomY = (Xorshift32() % (h - topY)) + topY;
    	for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++){
                prgbScreen[x + w * y].rgb = ((y > topY && y < bottomY) ? 0xff0000 : 0x000000);
            }
    	}
    	
        SetBkMode(hcdc, 1);
        SetTextColor(hcdc, 0xffffff);
        HFONT font = CreateFont(50, 45, 0, 0, 500, 1, 0, 0, 0, 0, 0, 0, 0, "Baby Kruffy");
        SelectObject(hcdc, font);
        TextOutA(hcdc, (w - 270) / 2, (h - 50) / 2, TEXT("ENDING"), 6);
        
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(250);
	}
	
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}

DWORD WINAPI payloadCrazy1(LPVOID lpParam){
    int status = 0;
    for( ; ; ){
        HWND hwndTW = FindWindow("Shell_TrayWnd", NULL);
        if(hwndTW != NULL){
            ShowWindow(hwndTW, status);
            DeleteObject(hwndTW);
            status = 5 - status;
            Sleep(250);
        }else{
            return 0;
        }
    }
    return 0;
}

DWORD WINAPI payloadCrazy2(LPVOID lpParam){
    int MoveIndex = 0;
    for( ; ; ){
        int MoveX = ((MoveIndex == 0 || MoveIndex == 1) ? 1 : -1), MoveY = ((MoveIndex == 1 || MoveIndex == 2) ? 1 : -1);
        HWND hwndDsk = GetDesktopWindow();
        SetWindowPos(hwndDsk, (HWND)-2, MoveX * 50, MoveY * 50, 0, 0, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOSIZE);
        DeleteObject(hwndDsk);
        MoveIndex = ((MoveIndex < 3) ? MoveIndex + 1 : 0);
        Sleep(250);
    }
    return 0;
}

DWORD WINAPI payloadCrazy3(LPVOID lpParam){
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    for(int t = 0; ; t++){
        HWND hwndPM = FindWindowA("Progman", "Program Manager");
        if(hwndPM == NULL) return 0;
        HWND hwndSD = FindWindowExA(hwndPM, 0, "SHELLDLL_DefView", 0);
        if(hwndSD == NULL) return 0;
        HWND hwndSV = FindWindowExA(hwndSD, 0, "SysListView32", "FolderView");
        if(hwndSV == NULL) return 0;
        int linkNum = SendMessageA(hwndSV, LVM_GETITEMCOUNT, 0, 0);
        int x = (t % 2) * 100, y = 0;
        for(int nowLoop = 0; nowLoop < linkNum; nowLoop++){
            int tmpX = ((x + 100 >= w) ? 0 : x + 100), tmpY = ((y + 100 >= h) ? 0 : y + 100);
            SendMessageA(hwndSV, LVM_SETITEMPOSITION, nowLoop, (tmpX == 0 ? 0 : (tmpX << 16)) + tmpY);
            x = tmpX, y = tmpY;
        }
        Sleep(250);
    }
    return 0;
}

/* ---------------------------------------------------------------------------------------------------- */

DWORD getColor(int t){
    int rgb = 0x000000;
    switch(((t - (t % 16)) / 16) % 7){
        case 0:
            rgb = 0x110000;
            break;
        case 1:
            rgb = 0x111100;
            break;
        case 2:
            rgb = 0x001100;
            break;
        case 3:
            rgb = 0x001111;
            break;
        case 4:
            rgb = 0x000011;
            break;
        case 5:
            rgb = 0x110011;
            break;
        case 6:
            rgb = 0x111111;
            break;
    }
    return rgb;
}

DWORD WINAPI payloadFinal1(LPVOID lpParam){
    for(int t = 0;;t++){
    	HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        
    	BITMAPINFO bmi = { 0 };
    	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    	bmi.bmiHeader.biBitCount = 32;
    	bmi.bmiHeader.biPlanes = 1;
    	bmi.bmiHeader.biWidth = w;
    	bmi.bmiHeader.biHeight = h;
    	
    	PRGBQUAD prgbScreen;
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	
    	for(int y = 0; y < h; y++){
    	    for(int x = 0; x < w; x++){
    			bool isFount = false;
    			int rgb = getColor(t);
    			for(int side = 1; side < w; side *= 3){
    				int minSide = side / 3, maxSide = side / 3 * 2;
    				if((x % side >= minSide && x % side < maxSide) && (y % side >= minSide && y % side < maxSide)){
    					isFount = true;
    				}
    			}
    			if(isFount == true){
    			    prgbScreen[x + w * y].rgb = rgb * (t % 16);
    			}else{
    			    prgbScreen[x + w * y].rgb = 0x000000;
    			}
    	    }
    	}
    	
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(200);
    }
    return 0;
}

DWORD WINAPI payloadFinal2(LPVOID lpParam){
    for(int t = 0;;t++){
    	HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        
    	BITMAPINFO bmi = { 0 };
    	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    	bmi.bmiHeader.biBitCount = 32;
    	bmi.bmiHeader.biPlanes = 1;
    	bmi.bmiHeader.biWidth = w;
    	bmi.bmiHeader.biHeight = h;
    	
    	PRGBQUAD prgbScreen;
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	
    	for(int y = 0; y < h; y++){
    	    for(int x = 0; x < w; x++){
    			bool isFount = false;
    			int rgb = getColor(t);
    			for(int side = 1; side < w; side *= 4){
    				int minSide = side / 4, maxSide = side / 4 * 3;
    				if((x % side >= minSide && x % side < maxSide) && (y % side >= minSide && y % side < maxSide)){
    					isFount = true;
    				}
    			}
    			if(isFount == true){
    			    prgbScreen[x + w * y].rgb = rgb * (t % 16);
    			}else{
    			    prgbScreen[x + w * y].rgb = 0x000000;
    			}
    	    }
    	}
    	
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(200);
    }
    return 0;
}

DWORD WINAPI payloadFinal3(LPVOID lpParam){
    for(int t = 0;;t++){
    	HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        
    	BITMAPINFO bmi = { 0 };
    	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    	bmi.bmiHeader.biBitCount = 32;
    	bmi.bmiHeader.biPlanes = 1;
    	bmi.bmiHeader.biWidth = w;
    	bmi.bmiHeader.biHeight = h;
    	
    	PRGBQUAD prgbScreen;
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	
    	for(int y = 0; y < h; y++){
    	    for(int x = 0; x < w; x++){
    			bool isFount = false;
    			int rgb = getColor(t);
    			for(int side = 1; side < w; side *= 5){
    				int minSide = side / 5, maxSide = side / 5 * 4;
    				if((x % side >= minSide && x % side < maxSide) && (y % side >= minSide && y % side < maxSide)){
    					isFount = true;
    				}
    			}
    			if(isFount == true){
    			    prgbScreen[x + w * y].rgb = rgb * (t % 16);
    			}else{
    			    prgbScreen[x + w * y].rgb = 0x000000;
    			}
    	    }
    	}
    	
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(200);
    }
    return 0;
}

DWORD WINAPI payloadFinal4(LPVOID lpParam){
    for(int t = 0;;t++){
    	HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        
    	BITMAPINFO bmi = { 0 };
    	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    	bmi.bmiHeader.biBitCount = 32;
    	bmi.bmiHeader.biPlanes = 1;
    	bmi.bmiHeader.biWidth = w;
    	bmi.bmiHeader.biHeight = h;
    	
    	PRGBQUAD prgbScreen;
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	
    	int* lastArray = new int[w];
    	for(int y = 0; y < h; y++){
    	    int* tmpArray = new int[w];
			for(int n = 0; n < w; n++){
			    tmpArray[n] = lastArray[n];
    			if(n == 0 || n == y){
    			    lastArray[n] = 0;
    			}else if(n > y){
    			    lastArray[n] = 1;
    			}else{
    			    if((tmpArray[n - 1] + tmpArray[n]) % 2 == 0){
    			        lastArray[n] = 1;
    			    }else{
    			        lastArray[n] = 0;
    			    }
    			}
			}
			delete []tmpArray;
			
    	    for(int x = 0; x < w; x++){
    			int rgb = getColor(t);
    			if(lastArray[x] == 0){
    			    prgbScreen[x + w * y].rgb = rgb * (t % 16);
    			}else{
    			    prgbScreen[x + w * y].rgb = 0x000000;
    			}
    	    }
    	}
    	delete []lastArray;
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(200);
    }
    return 0;
}

/* ---------------------------------------------------------------------------------------------------- */

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    INT nCmdShow
){
    if(MessageBox(NULL, "This Malware will disturb you for some time,are you sure to run it?", "Warning", MB_YESNO+MB_ICONQUESTION) != IDYES) {
        ExitProcess(0);
    }
    if(MessageBox(NULL, "This is last warning,the malware author couldn't assume legal liability,so are you sure to run it?", "Warning", MB_YESNO+MB_ICONWARNING) != IDYES) {
        ExitProcess(0);
    }
    InitDPI();
    
    WinExec("notepad.exe", 5);
    CreateThread(NULL, 0, &payloadStart, NULL, 0, NULL);
    
    ct(&payload1A, &payload1B, 15000);
    ct(&payload2, NULL, 15000);
    ct(&payload3A, &payload3B, 15000);
    
    WinExec("taskkill /f /im notepad.exe", 0);
    payloadTurn1(NULL);
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    
    HANDLE Crazy1 = CreateThread(NULL, 0, &payloadCrazy1, NULL, 0, NULL);
    ct(&payload4, NULL, 15000);
    HANDLE Crazy2 = CreateThread(NULL, 0, &payloadCrazy2, NULL, 0, NULL);
    ct(&payload5A, &payload5B, 15000);
    HANDLE Crazy3 = CreateThread(NULL, 0, &payloadCrazy3, NULL, 0, NULL);
    ct(&payload6, NULL, 15000);
    ct(&payload7A, &payload7B, 15000);
    TerminateThread(Crazy1, 0);
    CloseHandle(Crazy1);
    TerminateThread(Crazy2, 0);
    CloseHandle(Crazy2);
    TerminateThread(Crazy3, 0);
    CloseHandle(Crazy3);
    
    // WinExec("taskkill /f /im explorer.exe", 0);
    // WinExec("explorer.exe", 0);
    
    payloadTurn2(NULL);
    
    int finalEffect = Xorshift32() % 4;
    switch(finalEffect){
        case 0:
            payloadFinal1(NULL);
            break;
        case 1:
            payloadFinal2(NULL);
            break;
        case 2:
            payloadFinal3(NULL);
            break;
        case 3:
            payloadFinal4(NULL);
            break;
    }
    return 0;
}