#ifndef _NODE_H
#define _NODE_H

#include "Resources.h"

class Node
{
	public:
		class Link
		{
			public:
				Link(Node* s, Node* d) : Link(s,d,Operations::randd->NextDouble(-10,10))
				{

				}
				Link(Node* s, Node* d, double w) : source(s), destination(d), weight(w)
				{

				}
				~Link()
				{

				}
				Node* GetSource()
				{
					return source;
				}
				Node* GetDestination()
				{
					return destination;
				}
				double GetWeight()
				{
					return weight;
				}
				void SetWeight(double w)
				{
					weight = w;
				}
				virtual Link* GetClone()
				{
					if (!clone)
					{
						if (source && destination)
						{
							if (source->GetClone() && destination->GetClone())
							{
								clone = new Link(source->GetClone(), destination->GetClone(), weight);
								source->GetClone()->AddOutput(clone);
								destination->GetClone()->AddInput(clone);
								return clone;
							}
						}
					}
					return clone;
				}
				virtual void Train(double prevDelta, double inputs[])
				{
					double output = weight * source->GetNodeOutput(inputs);
					double error = prevDelta * weight;
					double delta = error * output;
					weight += output * delta;
					std::vector<Link*> sourceInputs = source->GetInputs();
					for (int i = 0; i < sourceInputs.size(); i++)
					{
						sourceInputs[i]->Train(delta, inputs);
					}
				}
			private:
				Link* clone;
				Node* source;
				Node* destination;
				double weight;
		};
		Node();
		~Node();
		double GetSigmoid(double inputs[]);
		virtual double GetNodeOutput(double inputs[]);
		virtual double GetNodeOutput(double inputs[], int outputIndex);
		virtual void ResetMemory();
		virtual Node* GetClone();
		void AddInput(Node* inputNode);
		void AddInput(Link* input);
		void AddOutput(Node* outputNode);
		void AddOutput(Link* output);
		double GetXValue();
		void SetXValue(double val);
		double GetYValue();
		void SetYValue(double val);
		void SetPosition(double x, double y);
		std::vector<Link*> GetInputs();
		std::vector<Link*> GetOutputs();
		virtual void Train(double inputs[], double desiredOutput);
	protected:
		bool Memorised();
		double MemorisedValue();
		double Memorise(double value);
		int inputLimit = 0;
		int outputLimit = 0;
		Node* clone;
	private:
		std::vector<Link*> inputs;
		std::vector<Link*> outputs;
		double memorisedValue = 0;
		bool memorised = false;
		double xValue;
		double yValue;
};

#endif