BOOL Line(HDC hdc, int x1, int y1, float x2, float y2);
BOOL Box(HDC hdc, float x1, float y1, int size);


BOOL Line(HDC hdc, int x1, int y1, float x2, float y2)
{
	MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
	return LineTo(hdc, (int)x2, (int)y2); //нарисовать линию
}

BOOL Box(HDC hdc, float x1, float y1, int size)
{
	MoveToEx(hdc, (int)x1 + size, (int)y1 + size, NULL);
	LineTo(hdc, (int)x1 + size, (int)y1 - size);
	LineTo(hdc, (int)x1 - size, (int)y1 - size);
	LineTo(hdc, (int)x1 - size, (int)y1 + size);
	LineTo(hdc, (int)x1 + size, (int)y1 + size);
	return 0;
}

BOOL Rotate(HDC hDC,float rotate_buf, float draw_x, float draw_y)
{
if (22.5 < rotate_buf & rotate_buf < 67.5)
	Line(hDC, draw_x, draw_y, draw_x - 75, draw_y - 75);
if (67.5 < rotate_buf & rotate_buf < 112.5)
	Line(hDC, draw_x, draw_y, draw_x, draw_y - 75);
if (112.5 < rotate_buf & rotate_buf < 157.5)
	Line(hDC, draw_x, draw_y, draw_x + 75, draw_y - 75);
if (157.5 < rotate_buf & rotate_buf < 202.5)
	Line(hDC, draw_x, draw_y, draw_x + 75, draw_y);
if (202.5 < rotate_buf & rotate_buf < 247.5)
	Line(hDC, draw_x, draw_y, draw_x + 75, draw_y + 75);
if (247.5 < rotate_buf & rotate_buf < 292.5)
	Line(hDC, draw_x, draw_y, draw_x, draw_y + 75);
if (292.5 < rotate_buf & rotate_buf < 337.5)
	Line(hDC, draw_x, draw_y, draw_x - 75, draw_y + 75);
if (337.5 < rotate_buf & rotate_buf < 360.0)
	Line(hDC, draw_x, draw_y, draw_x - 75, draw_y);
if (0 < rotate_buf & rotate_buf < 22.5)
	Line(hDC, draw_x, draw_y, draw_x - 75, draw_y);
return 0;
}