#include <conio.h> 
#include <iostream> 
#include <windows.h> 

using namespace std;
const int width = 80, height = 20; // поле
int x, y, // координаты тела змейки
	fruitx, fruity, // координаты еды
	score, // счетчик очков
	tailx[100], taily[100], // массив для хранения хвоста змейки
	taillength; // длина хвоста 
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN }; // движение
direction dir; // переменная snakesDirection
bool gameover; // бул для чека, окончена игра уже или нет

void game()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}

void render() // создание игрового поля и рендеринг
{
	system("cls"); // очистка консоли

	for (int i = 0; i < width + 2; i++) // верхняя стена
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) 
		{
			if (j == 0 || j == width) 
				cout << "|"; // левая и правая стены
			if (i == y && j == x)
				cout << "O"; // бошка
			else if (i == fruity && j == fruitx)
				cout << "#"; // еда
			else {
				bool prTail = false;
				for (int k = 0; k < taillength; k++) {
					if (tailx[k] == j
						&& taily[k] == i) {
						cout << "o"; // хвост
						prTail = true;
					}
				}
				if (!prTail)
					cout << " "; // пустое пространство
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) // нижняя стена
		cout << "-";
	cout << endl;
	cout << "SCORE: " << score << endl;
}

void update() // апдейт
{
	int prevx = tailx[0],
		prevY = taily[0],
		prev2X, prev2Y;
	tailx[0] = x;
	taily[0] = y;

	for (int i = 1; i < taillength; i++) {
		prev2X = tailx[i];
		prev2Y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevY;
		prevx = prev2X;
		prevY = prev2Y;
	}

	switch (dir) 
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
 
	if (x >= width || x < 0 || y >= height || y < 0) // столкновение со стеной
		gameover = true;

	for (int i = 0; i < taillength; i++)  // столкновение с хвостом
	{
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}

	if (x == fruitx && y == fruity) // столкновение с едой
	{
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		taillength++;
	}
}

void input() // движение
{
	if (_kbhit())  
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}


int main()
{
	game();
	while (!gameover)
	{
		render();
		input();
		update();
		Sleep(100); // приостановка текущего потока на 100 миллисек 
	}
	return 0;
}