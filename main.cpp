#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#define height 700
#define width 1280

int i, X[100], Y[100], rx, ry, gm, gd, l, d = 2, s = 16;

void boundary();
void snakeinit();
void food();
int highScore(int);
void startGame();
void homeScreen();
void gameOver(int, int);

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
	int size = 50;

	setfillstyle(SOLID_FILL, fillColor);
	// setcolor(borderColor);

	/// horizontall
	for (i = margin_x, j = margin_y; i < width - 50; i += size)
	{
		setcolor(borderColor);
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);

		if (i == margin_x + (size * 24))
		{
			for (int k = 0; k < 4; k++)
			{

				setcolor(borderColor);
				rectangle(i, j, i + (size - 10), j + (size - 10));
				floodfill(i + 1, j + 1, borderColor);
				j += size;
			}

			rectangle(i + 14, j, i + (size - 10) - 13, j + (size - 10) - 28);
			floodfill(i + 15, j + 1, borderColor);

			rectangle(i, j + (size - 10) - 27, i + 13, j + (size - 10) - 14);
			floodfill(i + 2, j + 14, borderColor);

			rectangle(i + 28, j + (size - 10) - 27, i + (size - 10), j + (size - 10) - 14);
			floodfill(i + 29, j + 14, borderColor);

			rectangle(i + 14, j + (size - 12) - 11, i + (size - 10) - 13, j + (size - 12));
			floodfill(i + 15, j + 30, borderColor);
		}
	}

	// vertical
	for (i = margin_x, j = margin_y + size; j <= height - 50; j += size)
	{
		// setfillstyle(SOLID_FILL, BLUE);
		// setcolor(GREEN);
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);
		// 610 = current pos + (size * no of boxes)
		if (j == (margin_y + size) + (size * 11))
		{
			i += size;
			rectangle(i, j, i + (size - 10), j + (size - 10));
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
	int score;
	int hscore;

	cleardevice();
	Sleep(300);
	srand(time(NULL));
	// detectgraph(&gd,&gm);
	// initgraph(&gd,&gm,NULL);

	// resolution to full screen

	// fill initial snake body
	snakeinit();
	// set boundary
	boundary();

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
	score = l - 5;
	printf("score : %d", score);
	// printf("gameover");
	hscore = highScore(score);
	gameOver(score, hscore);
	// while (!GetAsyncKeyState(VK_RETURN))
	// 	;
}
void gameOver(int score, int hscore)
{
	char ch;
	char str[3];
	char hstr[5];
	char scr[10] = "Score: ";
	char hscr[20] = "High Score: ";
	sprintf(str, "%d", score);
	sprintf(hstr, "%d", hscore);

	strcat(scr, str);
	strcat(hscr, hstr);

	setcolor(RED);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	outtextxy((width / 2), 150, (char *)"Game");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	outtextxy((width / 2), 250, (char *)"Over");

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	outtextxy((width / 2), 350, (char *)hscr);

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	outtextxy((width / 2), 400, (char *)scr);

	settextjustify(RIGHT_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtextxy((width / 2) - 50, 550, (char *)"Press Space to play again.");

	settextjustify(LEFT_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtextxy((width / 2) + 100, 550, (char *)"Press Esc to quit the game.");

	while (1)
	{
		if (kbhit())
		{
			ch = getch();
			if (int(ch) == 32)
			{
				printf("Enter pressed");
				startGame();
			}
			else if (int(ch) == 27)
			{
				exit(0);
			}
		}
	}
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
		rx = s * (1 + rand() % (1268 / s - 1));
		ry = s * (1 + rand() % (678 / s - 1));
	}
	bar(rx - s / 2, ry - s / 2, rx + s / 2, ry + s / 2);
}

int highScore(int score)
{
	FILE *fptr;
	int hscore = 0;
	int fscore;

	fptr = fopen("highscore.txt", "r");
	if (fptr == NULL)
	{
		fptr = fopen("highscore.txt", "w");
	}

	if (score > hscore)
	{
		hscore = score;
		printf("Highscore: %d", hscore);
		fprintf(fptr, "%d", hscore);
	}
	fscanf(fptr, "%d", &fscore);
	return fscore;
}
