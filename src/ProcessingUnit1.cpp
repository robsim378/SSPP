#include <algorithm>
#include <array>

#include "ProcessingUnit1.hpp"

ProcessingUnit1::ProcessingUnit1(){}

void ProcessingUnit1::input(std::optional<ProcessingUnit1::InputType> newValues) {
	// Replace the existing values with the new ones
	if (newValues.has_value() && currentValues.has_value()) {
		std::copy(
				std::begin(newValues.value()), 
				std::end(newValues.value()), 
				std::begin(currentValues.value()));
	}
	else if (newValues.has_value()) {
		currentValues = newValues;
	}
	else {
		currentValues = std::nullopt;
	}
}
std::optional<ProcessingUnit1::OutputType> ProcessingUnit1::output() {
	if (currentValues.has_value()) {
		OutputType outputValues;
		outputValues = {};
		for (int i = 0; i < output_length; i++) {
			outputValues[i] = ((double)currentValues.value()[i] + (double)currentValues.value()[i + 1] + (double)currentValues.value()[i + 2]) / 3;
		}
		return outputValues;
	}
	else {
		return std::nullopt;
	}
}
