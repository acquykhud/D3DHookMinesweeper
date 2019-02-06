#pragma once
#include <Windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "mhook-lib/mhook.h"
#define MAX_ROW 24
#define MAX_COL 30
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma warning (disable : 4312)

void DrawFillRect(IDirect3DDevice9*, int, int, int, int, D3DCOLOR);
void DrawString(int x, int y, D3DCOLOR color, LPD3DXFONT m_font, const char *format, ...);
extern 	ID3DXFont * Font;