#include "hook.h"
ID3DXFont * Font;
void DrawFillRect(IDirect3DDevice9 * device, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT Rect = { x, y, x + w, y + h };
	device->Clear(1, &Rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
}

void DrawString(int x, int y, D3DCOLOR color, LPD3DXFONT m_font, const char * format, ...)
{
	RECT Position;
	Position.left = x;
	Position.top = y;
	va_list vl;
	char buffer[256];
	va_start(vl, format);
	vsprintf(buffer, format, vl);
	va_end(vl);
	m_font->DrawTextA(0, buffer, strlen(buffer), &Position, DT_NOCLIP, color);
}
