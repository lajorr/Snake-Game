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

	initwindow(width, height,"Snake Game");
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

			j = j + size;

			// boxes in the last column
			for (int k = 0; k < 3; k++)
			{

				setcolor(borderColor);
				rectangle(i, j, i + (size - 10), j + (size - 10));
				floodfill(i + 1, j + 1, borderColor);
				j += size;
			}

			// last crosshair box
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
	

		setcolor(9);
		// writes text in main screen
		text(10, (width / 2), 350, (char *)"Snake Game");
		text(5, (width / 2), 450, (char *)"Press Space To Play");

		// checks for keyboard entry
		// 32 -- space
		// 13 -- enter
		// 27 -- esc
		ch = getch();
		if (int(ch) == 32)
		{
			cleardevice();
			startGame();
		}
}

void startGame()
{

	score = 0;
	cleardevice();
	Sleep(300);
	srand(time(0));

	// fill initial snake body
	snakeinit();
	// set boundary
	boundary();

	// food at random location
	food();
	delay(1000);

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
		if (getpixel(X[0], Y[0]) == BLUE)
		{
			// printing the score
			// score = l - 5;
			gameOver();
			// break;
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
			score++;
		}

		// displaying the snake
		setfillstyle(1, 1);
		for (i = 0; i < l; i++)
			bar(X[i] - s / 2, Y[i] - s / 2, X[i] + s / 2, Y[i] + s / 2);
		delay(100);
	}

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

	cleardevice();

	fscanf(fptr, "%d", &hscore);
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

	if (score > hscore)
	{
		text(3, (width / 2), 500, (char *)"You have beaten the highscore !!!!");
		text(3, (width / 2) - 150, 600, (char *)"Press Space to play again.");
		text(3, (width / 2) + 200, 600, (char *)"Press Esc to quit the game.");
	}
	else
	{
		text(3, (width / 2) - 150, 550, (char *)"Press Space to play again.");
		text(3, (width / 2) + 200, 550, (char *)"Press Esc to quit the game.");
	}
	highScore();

	while (1)
	{
		ch = getch();
		if (ch == 32)
		{
			startGame();
		}
		else if (ch == 27)
		{
			exit(0);
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
