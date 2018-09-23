#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <TlHelp32.h>
#include <cstdlib>
#include <math.h>

#include "ReadWrite.h" 
#include "SimpleDraw.h"

HANDLE hProcess;
DWORD pID;
HANDLE hHandle;
HWND hWindow;  // дефолтные для работы с окнами

// offsets
DWORD players_list;
DWORD players_list_offset = 0x38;
DWORD players_offset = 0x04035C0;
DWORD player_size = 0x140;
DWORD hp_offset = 0x24;
DWORD side_offset = 0x20; //1 spectractor , 2 T side , 3 ct side
DWORD x_offset = 0x28;
DWORD y_offset = 0x2C;
DWORD z_offset = 0x30;
DWORD rotate_offset = 0x38;
DWORD my_coord_offset = 0x039D4F0;
DWORD my_coord_list;
DWORD my_coord_x = 0x64;
DWORD my_coord_y = 0x68;
DWORD my_coord_z = 0x6C;

int main()
{
	SetConsoleTitle("SSCR");	//титул
	hWindow = FindWindow(0, "Counter-Strike Source");	// нашел окно ебаное
	GetWindowThreadProcessId(hWindow, &pID);			//дай пид плес
	hHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);	//хендл мне гони, сучара

	DWORD ClientDLL = FindModule(pID, "client.dll");
	DWORD EngineDLL = FindModule(pID, "engine.dll");
	
	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);
	HPEN red_pen = CreatePen(PS_SOLID, 6, RGB(255, 0, 0));
	HPEN blude_pen = CreatePen(PS_SOLID, 6, RGB(0, 0, 255));
	HPEN white_pen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	HPEN yellow_pen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));

	SetMapMode(hDC, MM_LOMETRIC);
	SetViewportOrgEx(hDC, 600, 450, NULL);

	ReadProcessMemory(hHandle, (LPCVOID)(ClientDLL + players_offset), &players_list, sizeof(players_list), 0);
	ReadProcessMemory(hHandle, (LPCVOID)(ClientDLL + my_coord_offset), &my_coord_list, sizeof(my_coord_list), 0);

	while (true)
	{
		system("cls");
		for (int i = 0; i < 64; i++)
		{
				int hp_buf, side_buf;
				float x_buf, y_buf, z_buf, rotate_buf, my_x, my_y, my_z;
				float draw_x, draw_y;
				char name_buf[24];
				
				ReadProcessMemory(hHandle, (LPCVOID)(players_list + players_list_offset + player_size * i), &name_buf, sizeof(name_buf), 0);

				hp_buf = RPM_int(hHandle, (players_list + players_list_offset + hp_offset + player_size * i));
				side_buf = RPM_int(hHandle, (players_list + players_list_offset + side_offset + player_size * i));
				rotate_buf = RPM_float(hHandle, (players_list + players_list_offset + rotate_offset + player_size * i))+180.0;

				if (hp_buf > 0 && side_buf != 1)
				{
					x_buf = RPM_float(hHandle, players_list + players_list_offset + x_offset + player_size * i);
					y_buf = RPM_float(hHandle, (players_list + players_list_offset + y_offset + player_size * i));
					z_buf = RPM_float(hHandle, (players_list + players_list_offset + z_offset + player_size * i));

					my_x = RPM_float(hHandle, my_coord_list + my_coord_x);
					my_y = RPM_float(hHandle, my_coord_list + my_coord_y);
					my_z = RPM_float(hHandle, my_coord_list + my_coord_z);

					draw_x = (x_buf - my_x) / 1.6;
					draw_y = (y_buf - my_y) / 1.6;

					char hp[4];
					_itoa_s(hp_buf, hp, 10);

					if (side_buf == 2)
					{
						SelectObject(hDC, red_pen);
						Box(hDC, draw_x, draw_y, 20);
						SelectObject(hDC, white_pen);

						TextOut(hDC, draw_x + 25, draw_y + 25, name_buf, sizeof(name_buf));
						TextOut(hDC, draw_x - 20, draw_y - 20, hp, sizeof(hp));
					}
					if (side_buf == 3)
					{
						SelectObject(hDC, blude_pen);
						Box(hDC, draw_x, draw_y, 20);
						SelectObject(hDC, white_pen);
	
						TextOut(hDC, draw_x + 25, draw_y + 25, name_buf, sizeof(name_buf));
						TextOut(hDC, draw_x - 20, draw_y - 20, hp, sizeof(hp));
					}
					SelectObject(hDC, yellow_pen);
					Rotate(hDC, rotate_buf, draw_x, draw_y);
				}
		}
		Sleep(100);
	}
	return 0;
}

