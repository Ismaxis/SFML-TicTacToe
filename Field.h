#pragma once
class Field
{
private:
	int** field;
	int fieldSize;
public:
	void createField(int fieldSize);

	int updateField(int x, int y, bool crossTurn);

	int** getField();
};




