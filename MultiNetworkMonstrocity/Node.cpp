#include "Node.h"

Node::Node()
{

}

Node::~Node()
{
	int iLength = inputs.size();
	int oLength = outputs.size();
	for (int i = 0; i < iLength; i++)
	{
		delete inputs[i];
		inputs[i] = NULL;
	}
	inputs.clear();
	for (int i = 0; i < oLength; i++)
	{
		delete outputs[i];
		outputs[i] = NULL;
	}
	outputs.clear();
}

double Node::GetSigmoid(double inputVals[])
{
	double sum = 0;
	for (Link* inputLink : inputs)
	{
		sum += inputLink->GetSource()->GetNodeOutput(inputVals) * inputLink->GetWeight();
	}
	return Operations::Sigmoid(sum);
}

double Node::GetNodeOutput(double inputs[])
{
	if (Memorised())
	{
		return MemorisedValue();
	}
	return Memorise(GetSigmoid(inputs));
}

double Node::GetNodeOutput(double inputs[], int outputIndex)
{
	return GetNodeOutput(inputs);
}

void Node::ResetMemory()
{
	memorised = false;
}

Node* Node::GetClone()
{
	if (!clone)
	{
		clone = new Node();
		clone->SetPosition(xValue, yValue);
		for (Link* l : outputs)
		{
			l->GetClone();
		}
	}
	return clone;
}

void Node::AddInput(Node* inputNode)
{
	Link* link = new Link(inputNode, this);
	AddInput(link);
	inputNode->AddOutput(link);
}

void Node::AddInput(Link* input)
{
	if (!inputLimit || inputs.size() < inputLimit)
	{
		inputs.push_back(input);
	}
}

void Node::AddOutput(Node* outputNode)
{
	Link* link = new Link(this, outputNode);
	AddOutput(link);
	outputNode->AddInput(link);
}

void Node::AddOutput(Link* output)
{
	if (!outputLimit || outputs.size() < outputLimit)
	{
		outputs.push_back(output);
	}
}

double Node::GetXValue()
{
	return xValue;
}

void Node::SetXValue(double val)
{
	xValue = val;
}

double Node::GetYValue()
{
	return yValue;
}

void Node::SetYValue(double val)
{
	yValue = val;
}

void Node::SetPosition(double x, double y)
{
	xValue = x;
	yValue = y;
}

std::vector<Node::Link*> Node::GetInputs()
{
	return inputs;
}

std::vector<Node::Link*> Node::GetOutputs()
{
	return outputs;
}

void Node::Train(double inputs[], double desiredOutput)
{
	std::vector<Link*> inputLinks = GetInputs();
	double output = GetNodeOutput(inputs);
	double error = desiredOutput - output;
	double delta = error * output;
	for (int i = 0; i < inputLinks.size(); i++)
	{
		inputLinks[i]->Train(delta, inputs);
	}
}

bool Node::Memorised()
{
	return memorised;
}

double Node::MemorisedValue()
{
	return memorisedValue;
}

double Node::Memorise(double value)
{
	memorised = true;
	return memorisedValue = value;
}