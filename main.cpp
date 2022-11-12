#include <graphics.h>
#include <time.h>
#define height 700
#define width 1350

int i, X[100], Y[100], rx, ry, gm, gd, l, d = 2, s = 16;

void boundary();
void snakeinit();
void food();
void startGame();
void homeScreen();
void gameOver(int);

int main()
{
	initwindow(width, height);
	homeScreen();
	closegraph();
	getch();
	return 0;
}
void homeScreen()
{
	int i, j;
	int margin_x = 20;
	int margin_y = 20;

	int borderColor = 10;
	int fillColor = 10;
	setfillstyle(SOLID_FILL, fillColor);
	setcolor(borderColor);

	/// horizontall
	for (i = margin_x, j = margin_y; i < width - 50; i += 60)
	{

		rectangle(i, j, i + 50, j + 50);
		floodfill(i + 1, j + 1, borderColor);
		if (i == margin_x + (60 * 21))
		{
			for (int k = 0; k < 2; k++)
			{

				j += 60;
				rectangle(i, j, i + 50, j + 50);
				floodfill(i + 1, j + 1, borderColor);
			}
		}
	}

	// vertical
	for (i = margin_x, j = margin_y + 60; j <= height - 50; j += 60)
	{
		// setfillstyle(SOLID_FILL, BLUE);
		// setcolor(GREEN);
		rectangle(i, j, i + 50, j + 50);
		floodfill(i + 1, j + 1, borderColor);
		// 610 = current pos + (size * no of boxes)
		if (j == (margin_y + 60) + (60 * 9))
		{
			i += 60;
			rectangle(i, j, i + 50, j + 50);
			floodfill(i + 1, j + 1, borderColor);
		}
	}
	char ch;
	while (1)
	{

		setcolor(9);
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
		outtextxy((width / 2), 350, (char *)"Snake Game");

		settextjustify(CENTER_TEXT, CENTER_TEXT);
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
		outtextxy((width / 2), 450, (char *)"Press Space To Play");
		if (kbhit())
		{

			// 32 -- space
			// 13 -- enter
			// 27 -- esc
			ch = getch();
			if (int(ch) == 32)
			{
				printf("Enter pressed");
				startGame();
			}
		}
	}
}

void startGame()
{
	cleardevice();
	Sleep(300);
	srand(time(NULL));
	// detectgraph(&gd,&gm);
	// initgraph(&gd,&gm,NULL);

	// resolution to full screen

	// set boundary
	boundary();

	// fill initial snake body
	snakeinit();

	// food at random location
	food();
	delay(2000);

	while (1)
	{
		// updating the snake
		setfillstyle(1, 0);
		bar(X[l - 1] - s / 2, Y[l - 1] - s / 2, X[l - 1] + s / 2, Y[l - 1] + s / 2);
		for (i = l - 1; i > 0; i--)
		{
			X[i] = X[i - 1];
			Y[i] = Y[i - 1];
		}

		// updating the head
		if (d == 0)
			X[0] = X[0] - s;
		else if (d == 1)
			Y[0] = Y[0] - s;
		else if (d == 2)
			X[0] = X[0] + s;
		else if (d == 3)
			Y[0] = Y[0] + s;

		// terminating condition
		if (getpixel(X[0], Y[0]) == 1)
		{
			printf("game over");
			break;
		}

		// updating direction
		if ((GetAsyncKeyState(VK_RIGHT)) && (d != 0))
			d = 2;
		else if ((GetAsyncKeyState(VK_UP)) && (d != 3))
			d = 1;
		else if ((GetAsyncKeyState(VK_LEFT)) && (d != 2))
			d = 0;
		else if ((GetAsyncKeyState(VK_DOWN)) && (d != 1))
			d = 3;

		// food taken
		if (getpixel(X[0], Y[0]) == 2)
		{
			food();
			l = l + 1;
		}

		// displaying the snake
		setfillstyle(1, 1);
		for (i = 0; i < l; i++)
			bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
		delay(100);
	}

	// printing the score
	printf("score : %d", l - 5);
	printf("gameover");
	gameOver(l - 5);
	while (!GetAsyncKeyState(VK_RETURN))
		;
}
void gameOver(int score)
{
	char str[3];
	char scr[10] = "Score: ";
	sprintf(str, "%d", score);
	
	strcat(scr,str);
	setcolor(RED);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	outtextxy((width / 2), 150, (char *)"Game");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	outtextxy((width / 2), 250, (char *)"Over");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	outtextxy((width / 2), 450, (char *)"High Score: ");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	outtextxy((width / 2), 500, (char *)scr);
	// strcat("Score: ",str)

	// settextjustify(CENTER_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	// outtextxy((width / 2)+ 50, 500, (char *)sprintf(str,"%d",10));
}

void boundary()
{
	setfillstyle(4, 6);

	bar(8, 8, 1270, 24);
	bar(8, 8, 24, 684);
	bar(8, 668, 1270, 684);
	bar(1258, 8, 1274, 684);
}

void snakeinit()
{
	// noice
	setfillstyle(1, 1); // display snake when immediately game opens
	X[0] = s * (1270 / (2 * s));
	Y[0] = s * (680 / (2 * s));
	bar(X[0] - s / 2, Y[0] - s / 2, X[0] + s / 2, Y[0] + s / 2);
	l = 5;
	for (i = 1; i < l; i++)
	{
		X[i] = X[0] - (i * s);
		Y[i] = Y[0];
		bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
	}
}

void food()
{
	rx = s;
	ry = s;
	setfillstyle(1, 2);
	while (getpixel(rx, ry) != 0)
	{
		rx = s * (1 + rand() % (1270 / s - 1));
		ry = s * (1 + rand() % (680 / s - 1));
	}
	bar(rx - s / 2, ry - s / 2, rx + s / 2, ry + s / 2);
}
