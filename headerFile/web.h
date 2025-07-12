//#ifndef WEB_H
//#define WEB_H
//#include <windows.h>
//#include <stdio.h>
//
//extern WINGDIAPI COLORREF WINAPI GetPixel(HDC hdc, int x, int y);
//
//POINT p;
//HWND hwnd = NULL;
//
//typedef struct {
//	int x, y;
//} pos;
//
//const pos positionOfNumberKeys[10] = {
//	{873, 549},
//	{476, 549},
//	{522, 549},
//	{566, 549},
//	{610, 549},
//	{654, 549},
//	{696, 549},
//	{741, 549},
//	{785, 549},
//	{827, 549}
//};
//const pos positionOfFunctionKeys[7] = {
//	{519, 603},
//	{561, 603},
//	{605, 603},
//	{649, 603},
//	{692, 603},
//	{749, 603},
//	{820, 603}
//};
//#define Plus 0
//#define Minus 1
//#define Multiplication 2
//#define Division 3
//#define Equal 4
//#define Enter 5
//#define Delete 6
//int blank_x[8] = {459, 519, 572, 629, 685, 741, 801, 854};
//int blank_y[6] = {203, 257, 314, 368, 424, 477};
//
//typedef struct {
//	BYTE R, G, B;
//} Color_;
//
//const Color_ color[4] = {
//	{0x16, 0x18, 0x03}, //Excluded
//	{0x82, 0x04, 0x58}, //Contained
//	{0x39, 0x88, 0x74}, //Proper
//	{0x98, 0x94, 0x84}, //NotJudged
//};
//
//const char colorToChar[4] = {'E', 'C', 'P', 'N'};
//
//
////46 44
//void click(pos p) {
//	SetCursorPos(p.x, p.y);
//	Sleep(10);
//	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
//	Sleep(30);
//	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
//
//	return ;
//}
//
//// 获取指定屏幕坐标位置的颜色
//char getColor(int x, int y) {
//	SetCursorPos(x, y);
//	Sleep(10);
//	HDC hdc = GetDC(NULL); // 获取整个屏幕的设备上下文
//	Sleep(10);
//	COLORREF colorIn = GetPixel(hdc, x, y); // 获取指定坐标的颜色
//	Sleep(10);
//	ReleaseDC(NULL, hdc); // 释放设备上下文
//	BYTE red = GetRValue(colorIn);   // 获取红色分量值
//	BYTE green = GetGValue(colorIn); // 获取绿色分量值
//	BYTE blue = GetBValue(colorIn);  // 获取蓝色分量值
////	printf("%02X %02X %02X\n",red,green,blue);
//	for (int i = 0; i < 4; i++) {
//		if (red == color[i].R && green == color[i].G && blue == color[i].B) return colorToChar[i];
//	}
//	if (red == 0xFF && green == 0xFF&& blue == 0xFF) return '1';
//	return '0';
//}
//
//#endif
