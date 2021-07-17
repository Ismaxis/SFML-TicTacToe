#include<cmath>
#include "Field.h"

void Field::createField(int givenFieldSize)
{
	fieldSize = givenFieldSize;
	field = new int* [fieldSize];
	for (size_t i = 0; i < fieldSize; i++)
	{
		field[i] = new int[fieldSize];
	}
}

int Field::updateField(int x, int y, bool crossTurn)
{
	// Update part
	if (crossTurn)
	{
		field[x][y] = -1;
	}
	else
	{
		field[x][y] = 1;
	}

	// Check part
	int majDiag = 0, minDiag = 0;
	for (size_t i = 0; i < fieldSize; i++)
	{
		int vSum = 0, hSum = 0;
		for (size_t j = 0; j < fieldSize; j++)
		{
			vSum += field[j][i];
			hSum += field[i][j];
		}

		// Check ver lines
		if (abs(vSum) == 3)
		{
			if (vSum > 0)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		// Check hor lines
		if (abs(hSum) == 3)
		{
			if (hSum > 0)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

		majDiag += field[i][i];
		minDiag += field[i][fieldSize - i - 1];
	}

	//Check maj diag
	if (abs(majDiag) == 3)
	{
		if (majDiag > 0) {
			return 1;
		}
		else
		{
			return -1;
		}
	}

	//Check min diag
	if (abs(minDiag) == 3)
	{
		if (minDiag > 0) {
			return 1;
		}
		else
		{
			return -1;
		}
	}

	// Default
	return 0;
}

int** Field::getField()
{
	return field;
}
