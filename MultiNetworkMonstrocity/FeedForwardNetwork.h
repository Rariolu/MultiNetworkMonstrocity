#ifndef _FEEDFORWARDNETWORK_H
#define _FEEDFORWARDNETWORK_H

#include "Network.h"
#include "InputCell.h"
#include "HiddenCell.h"
#include "OutputCell.h"

class FeedForwardNetwork : public Network
{
	public:
		FeedForwardNetwork(int inputs, int hiddenlayers[], int outputs);
		~FeedForwardNetwork();
		double GetNodeOutput(double inputs[], int outputIndex);
		void ResetMemory();
		void Train(double inputs[], double outputs[]);
		int GetInputCount();
		int GetOutputCount();
	private:
		int inputCount;
		int outputCount;
		std::vector<Node*> nodes;
		std::vector<InputCell*> inputNodes;
		std::vector<std::vector<HiddenCell*>> intermediateNodes;
		std::vector<OutputCell*> outputNodes;
		static double minX;
		static double maxX;
		static double minY;
		static double maxY;
		static double XRange();
		static double YRange();
};

#endif