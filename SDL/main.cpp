#include "Project.h"

// ������ ����. ������ ��������� � ������� ������ ���� 128x128 ��������
const int GRID_SIZE = 512;

class FreezerScreen : public Screen
{
private:
	Input* input;
	Graphics* graphics;

	// ����������� ����, ��������� � �������
	Image* back;
	Image* position[2];

	// ������, ������������ ����, � ������� �����
	int grid[4][4];

	void StartSettings()
	{
		// ����� ������� Graphics � Input � ������������� ��������� ����

		input = game->GetInput();
		graphics = game->GetGraphics();
		srand(time(NULL));
		SDL_WM_SetCaption("Freezer", 0);
	}

	void LoadingImage()
	{
		// �������� �����������

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
		// -1 - ���� �� ��������; 0 - �����; 1 - �������� ��������; 2 - �������� ������


		
			// �� �����������
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
		// ��������� ����� ����


		if (!over) return;
		LPCWSTR message = L"�� ��������! ������� ������� ���?";

		// ���������� ������������, ����� �� �� ������� ��� ���
		if (MessageBox(0, message, L"���� ��������", MB_YESNO) == IDYES)
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
		// ���� ����� ������� ������� � ����
		if (input->IsExit())
			game->Exit();

		// ���� ������ ����� ������ ����
		// P.S. 1 - ���, 2 - ���, 3 - ���
		if (input->IsMouseButtonDown(1))
		{
			// ����� ���������� ������� ������
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
				// ������ ������
				graphics->DrawImage(back, 0, 0);

				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						graphics->DrawImage(position[grid[i][j]], i * GRID_SIZE / 4, j* GRID_SIZE / 4);
					

				// ������� �� �����
				graphics->Flip();

				// ������������ ����� ����
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