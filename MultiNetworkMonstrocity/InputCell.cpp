#include "InputCell.h"

InputCell::InputCell(int inpIndex)
{
	inputIndex = inpIndex;
}

InputCell::~InputCell()
{
	
}

double InputCell::GetNodeOutput(double inputs[])
{
	return inputs[inputIndex];
}

Node* InputCell::GetClone()
{
	if (!clone)
	{
		clone = new InputCell(inputIndex);
	}
	return clone;
}

InputCell* InputCell::GetInputCellClone()
{
	return (InputCell*)GetClone();
}