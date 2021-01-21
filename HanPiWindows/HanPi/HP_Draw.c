// HP_Draw.c : 
//
#include "HanPi_PCH.h"
void HP_DrawLine(HDC hdc, COLORREF color, int lWidth, int x0, int y0, int x1, int y1) {
    if (lWidth <= 0)return;

    HBRUSH hBrush = (HBRUSH)CreatePen(PS_SOLID, lWidth, color);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x1, y1);
    DeleteObject(hBrush);
    DeleteObject(hOldBrush);
}
void HP_DrawDOTLine(HDC hdc, COLORREF color, int lWidth, int x0, int y0, int x1, int y1) {
    if (lWidth <= 0)return;
    HBRUSH hBrush = (HBRUSH)CreatePen(PS_DOT, lWidth, color);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x1, y1);
    DeleteObject(hBrush);
    DeleteObject(hOldBrush);
}
void HP_DrawRect(HDC hdc, COLORREF color, int left, int top, int right, int bottom)
{
    RECT rc;
    rc.left = left;
    rc.top = top;
    rc.right = right;
    rc.bottom = bottom;
    HBRUSH hbrush = CreateSolidBrush(color);
    FillRect(hdc, &rc, hbrush);
    DeleteObject(hbrush);
}
void HP_DrawRoundRect(HDC hdc, COLORREF color, int r, int x0, int y0, int x1, int y1)
{
    HBRUSH hbrush = CreateSolidBrush(color);
    HRGN hrgn = CreateRoundRectRgn(x0, y0, x1, y1, r, r);
    FillRgn(hdc, hrgn, hbrush);
    DeleteObject(hbrush);
}
void HP_DrawRoundBorder(HDC hdc, COLORREF color, int r, int x0, int y0, int x1, int y1)
{
    HBRUSH hbrush = (HBRUSH)CreatePen(PS_SOLID, 2, color);
    HGDIOBJ hburshOld = SelectObject(hdc, hbrush);
    //SetStretchBltMode(hdc, STRETCH_HALFTONE);
    RoundRect(hdc, x0, y0, x1, y1, r, r);
    SelectObject(hdc, hburshOld);
    DeleteObject(hbrush);
}

void HP_DrawBorder(HDC hdc, COLORREF color, int lWidth, int left, int top, int right, int bottom) {
    if (lWidth <= 0)return;
    HP_DrawRect(hdc, color, left, top, right, top + lWidth);
    HP_DrawRect(hdc, color, left, bottom - lWidth, right, bottom);
    HP_DrawRect(hdc, color, left, top + lWidth, left + lWidth, bottom - lWidth);
    HP_DrawRect(hdc, color, right - lWidth, top + lWidth, right, bottom - lWidth);
}
void HP_DrawDOTBorder(HDC hdc, COLORREF color, int lWidth, int left, int top, int right, int bottom) {
    if (lWidth <= 0)return;
    HP_DrawDOTLine(hdc, color, lWidth, left, top, right, top);
    HP_DrawDOTLine(hdc, color, lWidth, left, bottom, right, bottom);
    HP_DrawDOTLine(hdc, color, lWidth, left, top, left, bottom);
    HP_DrawDOTLine(hdc, color, lWidth, right, top, right, bottom);

}

void HP_DrawText(HDC hdc, COLORREF txtColor, HFONT hFont, RECT* rect, DWORD style, LPCWSTR lpText)
{
    COLORREF crOld = SetTextColor(hdc, txtColor);
    int nOldMode = SetBkMode(hdc, TRANSPARENT);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    DrawText(hdc, lpText, lstrlen(lpText), rect, style);
    SetBkMode(hdc, nOldMode);
    SetTextColor(hdc, crOld);
    SelectObject(hdc, hOldFont);
}