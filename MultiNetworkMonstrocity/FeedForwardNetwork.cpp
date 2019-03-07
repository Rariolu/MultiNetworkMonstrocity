#include "FeedForwardNetwork.h"

double FeedForwardNetwork::minX = 0;
double FeedForwardNetwork::maxX = 10000;
double FeedForwardNetwork::minY = 0;
double FeedForwardNetwork::maxY = 10000;

FeedForwardNetwork::FeedForwardNetwork(int inputs,int hiddenlayers[],int outputs) : Network(inputs,outputs)
{
	inputCount = inputs;
	outputCount = outputs;
	for (int i = 0; i < inputs; i++)
	{
		InputCell* inp = new InputCell(i);
		inp->SetXValue(minX);
		nodes.push_back(inp);
		inputNodes.push_back(inp);
	}
	for (int i = 0; i < outputs; i++)
	{
		OutputCell* out = new OutputCell();
		out->SetXValue(maxX);
		nodes.push_back(out);
		outputNodes.push_back(out);
	}
	int hLayers = Operations::ArrayLength(hiddenlayers);
	for (int x = 0; x < hLayers; x++)
	{
		std::vector<HiddenCell*> layer;
		for (int y = 0; y < hiddenlayers[x]; y++)
		{
			HiddenCell* hidden = new HiddenCell();
			hidden->SetPosition(((x+1)/(hLayers+2))*XRange(), y*YRange());
			if (x == 0)
			{
				for (int i = 0; i < inputs; i++)
				{
					hidden->AddInput(inputNodes[i]);
				}
			}
			else
			{
				for (int i = 0; i < hiddenlayers[x - 1]; i++)
				{
					hidden->AddInput(intermediateNodes[x - 1][i]);
				}
			}
			nodes.push_back(hidden);
			layer.push_back(hidden);
		}
		intermediateNodes.push_back(layer);
	}
}

FeedForwardNetwork::~FeedForwardNetwork()
{
	int nSize = nodes.size();
	for (int i = 0; i < nSize; i++)
	{
		delete nodes[i];
		nodes[i] = NULL;
	}
}

double FeedForwardNetwork::GetNodeOutput(double inputs[], int outputIndex)
{
	if (outputNodes.size() < 1)
	{
		return 0;
	}
	return outputNodes[outputIndex % outputNodes.size()]->GetNodeOutput(inputs);
}

void FeedForwardNetwork::ResetMemory()
{
	Node::ResetMemory();
	for (Node* n : nodes)
	{
		n->ResetMemory();
	}
}

void FeedForwardNetwork::Train(double inputs[], double outputs[])
{
	ResetMemory();
	for (int i = 0; i < GetOutputCount(); i++)
	{
		outputNodes[i]->GetNodeOutput(inputs);
	}
	for (int i = 0; i < GetOutputCount(); i++)
	{
		outputNodes[i]->Train(inputs, outputs[i]);
	}
}

int FeedForwardNetwork::GetInputCount()
{
	return inputCount;
}

int FeedForwardNetwork::GetOutputCount()
{
	return outputCount;
}

double FeedForwardNetwork::XRange()
{
	return maxX - minX;
}

double FeedForwardNetwork::YRange()
{
	return maxY - minY;
}