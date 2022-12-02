#include <WINDOWS.H>
#include <CMATH>
#include <CSTDLIB>
#include <CTIME>
#define PI 3.141
#define nTime 10

void payload1(){
    int dwStartTime = ((unsigned)time(NULL));
	HDC hdc;
	int tmpw, tmph;
	__int64 icnty;
	int hlfsw;
	int rndw, rndh;
	int icncs;
	int flwlng;
	double radius;
	HICON icnld;
	float flww, flwh;
	int sw, sh;
	hdc = GetDC(0i64);
	sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	tmpw = sw, tmph = sh;
	icnty = 32518i64;
	if (NULL != 1){
		hlfsw = sw / 2;
		for (int t = 0; ((unsigned)time(NULL)) < (dwStartTime + nTime); t++) {
		    Sleep(250);
			RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
			rndw = rand() % tmpw;
			rndh = rand() % tmph;
			icncs = rand() % 4;
			if (icncs){
				if (icncs == 1){
				    icnty = 32515i64;
				}else if (icncs == 3){
					icnty = 32516i64;
				}
			}else{
				icnty = 32513i64;
			}
			flwlng = 0;
			if (hlfsw > 0){
				do{
					radius = (double)(flwlng + 300);
					icnld = LoadIconW(0i64, (LPCWSTR)icnty);
					flww = sin(radius) * (double)flwlng + 100.0;
					flwh = cos(radius) * (double)flwlng + 100.0;
					DrawIcon(hdc, rndw + (int)flwh, rndh + (int)flww, icnld);
					if (NULL == 1){break;}
					flwlng += 2;
				}while(flwlng < hlfsw);
				tmpw = sw;
				tmph = sh;
			}
			InvalidateRect(0i64, 0i64, 0);
			Sleep(100);
		}
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload2(){
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    int cx, cy, sgn;
    sgn = 0;
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++){
        HDC hdc = GetDC(NULL);
        for(cy = 0; cy < h; ){
            for(cx = 0; cx < w; ){
                DrawIcon(hdc, cx, cy, LoadIcon(NULL, MAKEINTRESOURCE(32512 + sgn)));
                cx += 20;
                Sleep(10);
            }
            cy += 20;
            if(sgn >= 6){
                sgn = 0;
            }else{
                sgn++;
            }
        }
        ReleaseDC(NULL, hdc);
        DeleteObject(hdc);
    }
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload3(){
    int x,y,dx,dy,angle,i;
	double xx,yy;
	POINT cp;
    int ts=0;
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++){
        HDC hdc = GetDC(NULL);
    	for (i = 45; i <= 405; i++){
        	cp.x=0,cp.y=0;
        	x = cp.x-ts, y = cp.y-ts;
        	dx = cp.x, dy = cp.y;
        	angle = i;
        	xx = (x-dx)*cos(angle * PI / 180) - (y-dy)*sin(angle * PI / 180) - 15 + (double)(GetSystemMetrics(SM_CXSCREEN) / 2);//¼ÆËã+ 
        	yy = (y-dy)*cos(angle * PI / 180) + (x-dx)*sin(angle * PI / 180) - 15 + (double)(GetSystemMetrics(SM_CYSCREEN) / 2);//¼ÆËã 
        	DrawIcon(hdc,(int)xx,(int)yy,LoadIcon(NULL,IDI_ERROR));
    	}
		ts+=20;
    	ReleaseDC(NULL, hdc);
    	DeleteObject(hdc);
    	Sleep(100);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload4(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++){
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
	    DrawIcon(hdc, rand()%w, rand()%h, LoadIcon(NULL, MAKEINTRESOURCE(32512 + (rand() % 6))));
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload5(){
    int dwStartTime = time(NULL);
	for (int t = 0; time(NULL) < (dwStartTime + nTime); t++){
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
    	int icnsz = GetSystemMetrics(SM_CXICON);
    	POINT p;
    	int x = rand()%2;
    	if(x){
    		p.x = 0;
    		p.y = rand()%h;
    	}else{
    		p.x = rand()%w;
    		p.y = 0;
    	}
    	for(;;){
    		if(p.x >= w - icnsz || p.y >= h - icnsz){
    			break;
    		}
    		DrawIcon(hdc, p.x, p.y, LoadIcon(NULL, IDI_ERROR));
    		p.x += icnsz;
    		p.y += icnsz;
    		Sleep(50);
    	}
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
    }
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload6(){
    int dwStartTime = time(NULL);
	for (int sgn = 0; time(NULL) < (dwStartTime + nTime); sgn+=20){
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
	    for (float x = 0; x < (float)w; x += 10){
	        float y = (float)((sin(x / (w / 20)) * (h / 20)) + sgn - (h / 20));
    		DrawIcon(hdc, x, y, LoadIcon(NULL, IDI_ERROR));
    		Sleep(1);
	    }
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

void payload7(){
    int dwStartTime = time(NULL);
    int status = 3;
    int icnNum = 32516;
    POINT p;
    p.x = 0, p.y = 0;
	for ( ; time(NULL) < (dwStartTime + nTime); ){
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        HDC hdc = GetDC(NULL);
        DrawIcon(hdc, p.x, p.y, LoadIcon(NULL, MAKEINTRESOURCE(icnNum)));
	    switch(status){
	        case 0: //¨I
	            icnNum = 32513;
	            p.x -= 20;
	            p.y -= 20;
	            if(p.x < 0 || p.y < 0){
    	            if(p.x < 0){
        	            status = 1;
    	            }
    	            if(p.y < 0){
        	            status = 2;
    	            }
    	        }
    	        break;
	        case 1: //¨J
	            icnNum = 32514;
	            p.x += 20;
	            p.y -= 20;
	            if(p.x >= w - 20 || p.y < 0){
    	            if(p.x >= w - 20){
        	            status = 0;
    	            }
    	            if(p.y < 0){
        	            status = 3;
    	            }
    	        }
    	        break;
	        case 2: //¨L
	            icnNum = 32515;
	            p.x -= 20;
	            p.y += 20;
	            if(p.x < 0 || p.y >= h - 20){
    	            if(p.x < 0){
        	            status = 3;
    	            }
    	            if(p.y >= h - 20){
        	            status = 0;
    	            }
    	        }
    	        break;
	        case 3: //¨K
	            icnNum = 32516;
	            if(p.x >= w - 20 && p.y >= h - 20){
                	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
                	return;
	            }
	            p.x += 20;
	            p.y += 20;
	            if(p.x >= w - 20 || p.y >= h - 20){
    	            if(p.x >= w - 20){
        	            status = 2;
    	            }
    	            if(p.y >= h - 20){
        	            status = 1;
    	            }
    	        }
    	        break;
	    }
	    Sleep(10);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, INT nCmdShow){
    int mb = MessageBox(NULL, "This Malware will disturb you for some time,are you sure to run it?", "Warning", MB_YESNO+MB_ICONQUESTION);
    if(mb == IDYES){
        int mba = MessageBox(NULL, "This is last warning,the malware author couldn't assume legal liability,so are you sure to run it?", "Warning", MB_YESNO+MB_ICONWARNING);
        if(mba == IDYES){
            payload1();
            payload2();
            payload3();
            payload4();
            payload5();
            payload6();
            payload7();
        }
    }
    return 0;
}