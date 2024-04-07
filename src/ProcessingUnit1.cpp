#include <algorithm>
#include <array>

#include "ProcessingUnit1.hpp"

ProcessingUnit1::ProcessingUnit1(){}

void ProcessingUnit1::input(ProcessingUnit1::InputType newValues) {
	// Replace the existing values with the new ones
	std::copy(std::begin(newValues), std::end(newValues), std::begin(currentValues));
}

ProcessingUnit1::OutputType ProcessingUnit1::output() {
	// Iterative solution for now, look into more efficient std generic options.
	OutputType outputValues;
	for (int i = 0; i < output_length; i++) {
		outputValues[i] = ((double)currentValues[i] + (double)currentValues[i + 1] + (double)currentValues[i + 2]) / 3;
	}
	return outputValues;
}
