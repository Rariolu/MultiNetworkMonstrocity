#ifndef _INPUTCELL_H
#define _INPUTCELL_H

#include "Node.h"

class InputCell : public Node
{
	public:
		InputCell(int inpIndex);
		~InputCell();
		double GetNodeOutput(double inputs[]);
		Node* GetClone();
		InputCell* GetInputCellClone();
	private:
		int inputIndex;
};

#endif