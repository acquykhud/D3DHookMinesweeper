// dllmain.cpp : Defines the entry point for the DLL application.
#include "hook.h"
HMODULE hMod;
LPD3DXFONT Directx_Font;
uintptr_t Base = 0, EndSceneAdd = 0;
int row = 0, col = 0;
BYTE cell[MAX_COL][MAX_ROW]; // cell[i][j] = 1 mean the cell at (i, j) has bomb, otherwise, = 0
typedef HRESULT (__stdcall *tEndScene)(LPDIRECT3DDEVICE9 pDevice); 
tEndScene oriEndScene; // Original EndScene Function
HRESULT __stdcall  myEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	// Read row:

	row = *(int*)(Base + 0xAAA38);
	row = *(int*)(row + 0x18);
	row = *(int*)(row + 0xC);
	// Read col:
	col = *(int*)(Base + 0xAAA38);
	col = *(int*)(col + 0x18);
	col = *(int*)(col + 0x10);

	D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Directx_Font);
	DrawString(0, 7, D3DCOLOR_XRGB(255, 0, 0), Directx_Font, "Author = fb.com/Trung149");

	// row is at [[base + 0xAAA38] + 0x18] + 0xC]
    // col is at [[base + 0xAAA38] + 0x18] + 0x10]
    // row and col can be found by looking around "Time" in CE

	// printf("row = %d, col = %d\n", row, col); // For debugging
	// Read each column
	// The game stores the board as an array, go in Y direction
	// Column[i] is at [[[[[[[base + 0xAAA38] + 0x18] + 0x58] + 0x10] + (0x8 * i)] + 0x10] + 0x0]
	// this can be found by looking for AOB in CE, 0 means no bomb and 1 means bomb
	for (int i = 0; i < col; i++)
	{
		uintptr_t tmp = *(uintptr_t*)(Base + 0xAAA38);
		tmp = *(uintptr_t*)(tmp + 0x18);
		tmp = *(uintptr_t*)(tmp + 0x58);
		tmp = *(uintptr_t*)(tmp + 0x10);
		tmp = *(uintptr_t*)(tmp + 0x8 * i);
		tmp = *(uintptr_t*)(tmp + 0x10);
		tmp += 0x0;
		memcpy(cell[i], (void*)tmp, row); // copy (row) elements to Column[i]
	}
	for (int j = 0; j < row; ++j)
	{
		for (int i = 0; i < col; ++i)
		{
			if (cell[i][j] == 1 && Directx_Font)
				DrawString(35 + 18 * i, 32 + 18 * j, D3DCOLOR_XRGB(255, 0, 0), Directx_Font, "X");
		}
	}
	Directx_Font->Release(); // free memory, prevent memory leak
	return oriEndScene(pDevice);
}

void Init()
{
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);
	Base = (uintptr_t)GetModuleHandleA(NULL); // Base = Minesweeper.exe
	memset(cell, 0x0, sizeof(cell));
	// EndSceneAddress is at [[[[base + 0xAAC30] + 0x50] + 0x0] + 0x150]
	// Get this address by debugging the game
	EndSceneAdd = *(uintptr_t*)(Base + 0xAAC30);
	EndSceneAdd = *(uintptr_t*)(EndSceneAdd + 0x50);
	EndSceneAdd = *(uintptr_t*)(EndSceneAdd + 0x0); // Get vTable
	EndSceneAdd = *(uintptr_t*)(EndSceneAdd + 0x150); // 0x150 = 336 = 8 * 42 = sizeof(pointer) * EndSceneIndex
	oriEndScene = (tEndScene)(EndSceneAdd);
	// BeginHook
	Mhook_SetHook((PVOID*)&oriEndScene, myEndScene);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		hMod = hModule;
		DisableThreadLibraryCalls(hMod);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL);
		break;
    case DLL_THREAD_ATTACH:
		break;
    }
    return TRUE;
}

