#include "Project.h"

// Размер поля. Размер крестиков и ноликов должен быть 128x128 пикселей
const int GRID_SIZE = 512;

class FreezerScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;

	// Изображения фона, крестиков и ноликов
	Image* back;
	Image* position[2];

	// Массив, обозначающий поле, и текущий игрок
	int grid[4][4];

	void StartSettings()
	{
		// Берем объекты Graphics и Input и устанавливаем заголовок окна

		input = game->GetInput();
		graphics = game->GetGraphics();
		srand(time(NULL));
		SDL_WM_SetCaption("Freezer", 0);
	}

	void LoadingImage()
	{
		// Загрузка изображений

		back = graphics->NewImage("background.bmp");
		position[0] = graphics->NewImage("position0.bmp", 255, 255, 255);
		position[1] = graphics->NewImage("position1.bmp", 255, 255, 255);
	}

	void Reset()
	{
		
		graphics->DrawImage(back, 0, 0);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				grid[i][j] = rand() % 2;
				graphics->DrawImage(position[grid[i][j]], i * GRID_SIZE / 4, j* GRID_SIZE / 4);
			}
		graphics->Flip();
	}

	int GameOver()
	{
		// -1 - игра не окончена; 0 - ничья; 1 - победили крестики; 2 - победили нолики


		
			// По горизонтали
			if ((grid[0][0] == grid[1][0]) && (grid[0][0] == grid[1][1]) &&
				(grid[0][0] == grid[2][0]) && (grid[0][0] == grid[3][0]) &&
				(grid[0][0] == grid[2][1]) && (grid[0][0] == grid[3][1]) &&
				(grid[0][0] == grid[0][2]) && (grid[0][0] == grid[0][1]) &&
				(grid[0][0] == grid[1][2]) && (grid[0][0] == grid[2][2]) &&
				(grid[0][0] == grid[3][2]) && (grid[0][0] == grid[0][3]) &&
				(grid[0][0] == grid[1][3]) && (grid[0][0] == grid[2][3]) &&
				(grid[0][0] == grid[3][3]))

				return 1;

		return 0;
	}

	void GameOverHandle(int over)
	{
		// Обработка конца игры


		if (!over) return;
		LPCWSTR message = L"Вы победили! Желаете сыграть еще?";

		// Спрашиваем пользователя, хочет ли он сыграть еще раз
		if (MessageBox(0, message, L"Игра окончена", MB_YESNO) == IDYES)
			Reset();
		else
			game->Exit();
	}

public:
	void Start()
	{
		StartSettings();
		LoadingImage();
		Reset();
	}

	void Update()
	{
		// Если нажат красный крестик в окне
		if (input->IsExit())
			game->Exit();

		// Если нажата левая кнопка мыши
		// P.S. 1 - ЛКМ, 2 - СКМ, 3 - ПКМ
		if (input->IsMouseButtonDown(1))
		{
			// Берем координаты нажатой клетки
			int x = input->GetButtonDownCoords().x / (GRID_SIZE / 4),
				y = input->GetButtonDownCoords().y / (GRID_SIZE / 4);

			for (int i = 0; i < 4; ++i)
			{
				if (grid[i][y]) grid[i][y] = 0;
				else grid[i][y] = 1;
				if (grid[x][i]) grid[x][i] = 0;
				else grid[x][i] = 1;
			}
			if (grid[x][y]) grid[x][y] = 0;
			else grid[x][y] = 1;
				// Рисуем задник
				graphics->DrawImage(back, 0, 0);

				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						graphics->DrawImage(position[grid[i][j]], i * GRID_SIZE / 4, j* GRID_SIZE / 4);
					

				// Выводим на экран
				graphics->Flip();

				// Обрабатываем конец игры
				GameOverHandle(GameOver());
				SDL_Delay(250);
		}
	}
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game;
	return game.Execute(new FreezerScreen(), GRID_SIZE, GRID_SIZE);
}