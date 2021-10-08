//64010846
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y); printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	setcolor(2, 0);
	gotoxy(x, y);	printf("       ");

}

void draw_star(int x, int y)
{
	setcolor(7+(rand()%2), 0);
	gotoxy(x, y); printf("*");
}

void erase_star(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y); printf(" ");
}

void draw_bullet(int x, int y)
{
	setcolor(1, 0);
	gotoxy(x, y);	printf("|");
}

void erase_bullet(int x, int y)
{
	setcolor(1, 0);
	gotoxy(x, y);	printf(" ");
}

void display_score(int score,int x ,int y)
{
	gotoxy(80-13, 0);
	setcolor(0, 15);
	printf("SCORE : %.5d", score);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}


int main()
{
	int score=0;
	char ch = '.';
	int x = 38, y = 20;
	int dx = 0, dy = 0;
	//set up srand
	srand(time(NULL));

	//int for bullet
	int ammo = 5;
	int dbx[5] = { 0,0,0,0,0 };
	int dby[5] = { 19,19,19,19,19 };
	setcursor(0);
	draw_ship(x, y);

	//creating star	
	for (int i = 0; i < 20; i++)
	{
		draw_star((rand() % 60) + 10, (rand() % 4) + 1);
	}
	display_score(score,x,y);
	//loop game
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { dy = 0; dx = 1; }
			if (ch == 'd') { dx = 0; dy = 1; }
			if (ch == 's') { dx = 0; dy = 0; draw_ship(x, y); }
			if (ch == ' ') {
				if (ammo > 0)
				{
					
					for (int i = 0; i < 5; i++)
					{
						if (dbx[i] == 0)
						{
							dbx[i] = x + 3;
							dby[i] = 19;
							break;
						}
					}
				}
			}
			fflush(stdin);
		}

		//for ship
		if (dx != 0 || dy != 0)
		{
			erase_ship(x, y);
			if (dx == 1)
			{
				draw_ship(--x, y);
			}
			if (dy == 1)
			{
				draw_ship(++x, y);
			}
			if (x == 0 || x == 80 - 7)
			{
				dx = 0; dy = 0;
				draw_ship(x, y);
			}
		}

		//for bullet
		for (int i = 0; i < 5; i++)
		{
			if (dbx[i] != 0)
			{
				erase_bullet(dbx[i], dby[i]);
				if (dby[i] == 0)
				{
					dby[i] = 19;
					dbx[i] = 0;
				}
				else
				{
					if (cursor(dbx[i], dby[i]-1) == '*')
					{
						Beep(1250 + (rand() % 50), 250);
						erase_star(dbx[i], dby[i] - 1);
						score += 50;
						display_score(score, x, y);
						draw_star((rand() % 60) + 10, (rand() % 4) + 1);
						dby[i] = 19;
						dbx[i] = 0;
					}
					else
					{
						draw_bullet(dbx[i], --dby[i]);
					}
				}
			}
		}

		Sleep(100);
	} while (ch != 'x');

	return 0;
}
