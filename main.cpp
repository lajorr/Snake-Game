#include <graphics.h>
#include <time.h>
#include <stdlib.h>
#define height 700
#define width 1280

int i, X[100], Y[100], rx, ry, gm, gd, l, d = 2, s = 16;
int score;
int hscore;
FILE *fptr;

void boundary();
void snakeinit();
void food();
void highScore();
void startGame();
void homeScreen();
void gameOver();
void text(int, int, int, char *);

int main()
{
	fptr = fopen("highscore.txt", "r");
	if (fptr == NULL)
	{
		fptr = fopen("highscore.txt", "w");
		fprintf(fptr, "%d%d", 0, 0);
		fclose(fptr);
	}

	initwindow(width, height);
	homeScreen();
	closegraph();
	getch();
	return 0;
}
void homeScreen()
{
	int i, j, margin_x = 20, margin_y = 20, borderColor = 10, fillColor = 10, size = 50;

	score = 0;

	setfillstyle(SOLID_FILL, fillColor);

	/// horizontall boxes
	for (i = margin_x, j = margin_y; i < width - 50; i += size)
	{
		setcolor(borderColor);
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);

		// i = current pos + (size * no of boxes) this is the last box in the horizontal row
		if (i == margin_x + (size * 24))
		{
			for (int k = 0; k < 4; k++)
			{

				setcolor(borderColor);
				rectangle(i, j, i + (size - 10), j + (size - 10));
				floodfill(i + 1, j + 1, borderColor);
				j += size;
			}

			//
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

	// vertical boxes in home screen
	for (i = margin_x, j = margin_y + size; j <= height - 50; j += size)
	{
		rectangle(i, j, i + (size - 10), j + (size - 10));
		floodfill(i + 1, j + 1, borderColor);
		// j = current pos + (size * no of boxes) this is the last box in the vertical column

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
		// writes text in main screen
		text(10, (width / 2), 350, (char *)"Snake Game");
		text(5, (width / 2), 450, (char *)"Press Space To Play");

		// checks for keyboard entry
		if (kbhit())
		{

			// 32 -- space
			// 13 -- enter
			// 27 -- esc
			ch = getch();
			if (int(ch) == 32)
			{
				printf("Space pressed");
				startGame();
			}
		}
	}
}

void startGame()
{

	cleardevice();
	score = 0;
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
	highScore();
	gameOver();
	// while (!GetAsyncKeyState(VK_RETURN))
	// 	;
}
void gameOver()
{
	char ch;
	char str[3];
	char hstr[5];
	char scr[10] = "Score: ";
	char hscr[20] = "High Score: ";

	fscanf(fptr, "%d", &hscore);
	printf("\n\n This feom gameOver: %d \n\n", hscore);

	sprintf(str, "%d", score);
	sprintf(hstr, "%d", hscore);

	strcat(scr, str);
	strcat(hscr, hstr);

	setcolor(RED);
	/// Writes Text in game over screen
	text(10, (width / 2), 150, (char *)"GAME");
	text(10, (width / 2), 250, (char *)"OVER");
	text(5, (width / 2), 400, (char *)scr);
	text(5, (width / 2), 350, (char *)hscr);
	text(3, (width / 2) - 50, 550, (char *)"Press Space to play again.");
	text(3, (width / 2) + 100, 550, (char *)"Press Esc to quit the game.");

	// settextjustify(CENTER_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	// outtextxy((width / 2), 150, (char *)"Game");

	// settextjustify(CENTER_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 10);
	// outtextxy((width / 2), 250, (char *)"Over");

	// settextjustify(CENTER_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	// outtextxy((width / 2), 350, (char *)hscr);

	// settextjustify(CENTER_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
	// outtextxy((width / 2), 400, (char *)scr);

	// settextjustify(RIGHT_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	// outtextxy((width / 2) - 50, 550, (char *)"Press Space to play again.");

	// settextjustify(LEFT_TEXT, CENTER_TEXT);
	// settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	// outtextxy((width / 2) + 100, 550, (char *)"Press Esc to quit the game.");

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

void highScore()
{
	char fnum[5];

	fptr = fopen("highscore.txt", "r");
	// fscanf(fptr, "%d", &hscore);
	fgets(fnum, 5, fptr);
	hscore = atoi(fnum);
	fclose(fptr);
	if (score > hscore)
	{
		hscore = score;
		fptr = fopen("highscore.txt", "w");

		fprintf(fptr, "%d", hscore);
		fclose(fptr);
		printf("Highscore: %d", hscore);
	}
}

void text(int fontSize, int x_pos, int y_pos, char *str)
{
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, fontSize);
	outtextxy(x_pos, y_pos, str);
}
