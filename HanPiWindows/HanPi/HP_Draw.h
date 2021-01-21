// HP_Draw.h :
//
#ifndef _HP_DRAW_H
#define _HP_DRAW_H

void HP_DrawLine(HDC hdc, COLORREF color, int lwidth, int x0, int y0, int x1, int y1);
void HP_DrawDOTLine(HDC hdc, COLORREF color, int lwidth, int x0, int y0, int x1, int y1);
void HP_DrawRect(HDC hdc, COLORREF color, int x0, int y0, int x1, int y1);
void HP_DrawRoundRect(HDC hdc, COLORREF color, int r, int x0, int y0, int x1, int y1);
void HP_DrawRoundBorder(HDC hdc, COLORREF color, int r, int x0, int y0, int x1, int y1);
void HP_DrawBorder(HDC hdc, COLORREF color, int lwidth, int x0, int y0, int x1, int y1);
void HP_DrawDOTBorder(HDC hdc, COLORREF color, int lwidth, int x0, int y0, int x1, int y1);
void HP_DrawText(HDC hdc, COLORREF txtColor, HFONT hFont, RECT* rect, DWORD style, LPCWSTR lpText);

#endif