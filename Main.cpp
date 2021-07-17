#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include"Field.h"

using namespace sf;
using namespace std;

RectangleShape** generateLines(int winSize, int fieldSize)
{
	int cageSize = winSize / fieldSize;
	int lineThick = 5;

	RectangleShape** linens = new RectangleShape * [2];
	for (size_t i = 0; i < 2; i++)
	{
		linens[i] = new RectangleShape[fieldSize];
	}

	for (size_t i = 1; i < fieldSize; i++)
	{
		RectangleShape vLine(Vector2f(lineThick, winSize));
		vLine.setFillColor(Color::Black);
		vLine.setPosition(i * cageSize - lineThick / 2, 0);

		RectangleShape hLine(Vector2f(winSize, lineThick));
		hLine.setFillColor(Color::Black);
		hLine.setPosition(0, i * cageSize - lineThick / 2);

		linens[0][i] = vLine;
		linens[1][i] = hLine;
	}

	return linens;
}

int main()
{
	srand(time(0));

	const int winSize = 600;
	const int fieldSize = 3;
	int cageSize = winSize / fieldSize;

	Field gameField;
	gameField.createField(fieldSize);

	// Texture
	Texture circleAndCross;
	circleAndCross.setSmooth(true);
	if (!circleAndCross.loadFromFile("Textures/circleAndCross.png"))
	{
		cout << "Texture load fail" << endl;
		return 0;
	}

	Vector2u circleAndCrossSize = circleAndCross.getSize();

	// Window setup
	RenderWindow window(VideoMode(winSize, winSize), "TicTacToe game", Style::Default);
	window.setFramerateLimit(60);

	bool crossTrun = false;
	int result = 0; // 0 - game continue, 1 - blue wins, -1 - red wins

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					Vector2i mousePos = Mouse::getPosition(window);
					int x = mousePos.x / cageSize;
					int y = mousePos.y / cageSize;

					// Check
					result = gameField.updateField(x, y, crossTrun);

					if (abs(result) == 1)
					{
						cout << "Game over" << endl;
						if (result == 1)
						{
							cout << "Blue win!" << endl;
						}
						else
						{
							cout << "Red win!" << endl;
						}
					}
					crossTrun = !crossTrun;
				}
			}
		}

		// Clear
		window.clear(Color::White);

		// Update
		Sprite** spritesField = new Sprite * [fieldSize];
		for (size_t i = 0; i < fieldSize; i++)
		{
			spritesField[i] = new Sprite[fieldSize];
		}

		int** field = gameField.getField();

		for (size_t i = 0; i < fieldSize; i++)
		{
			for (size_t j = 0; j < fieldSize; j++)
			{
				Sprite sprite;
				sprite.setPosition(Vector2f(i * cageSize, j * cageSize));
				switch (field[i][j])
				{
				case 1:
					sprite.setTexture(circleAndCross);
					sprite.setTextureRect(IntRect(0, 0, circleAndCrossSize.x / 2, circleAndCrossSize.y));
					break;
				case -1:
					sprite.setTexture(circleAndCross);
					sprite.setTextureRect(IntRect(circleAndCrossSize.x / 2, 0, circleAndCrossSize.x / 2, circleAndCrossSize.y));
					break;
				}
				spritesField[i][j] = sprite;
			}
		}

		// Draw block
		// Lines
		RectangleShape** lines = generateLines(winSize, fieldSize);
		for (size_t i = 0; i < fieldSize; i++)
		{
			window.draw(lines[0][i]);
			window.draw(lines[1][i]);
		}

		// Cages
		for (size_t i = 0; i < fieldSize; i++)
		{
			for (size_t j = 0; j < fieldSize; j++)
			{
				window.draw(spritesField[i][j]);
			}
		}

		// Display
		window.display();
		if (result != 0)
		{
			while (true)
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						break;
					}
				}
				break;
			}
		}
	}

	system("exit");
}

