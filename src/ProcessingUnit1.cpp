#include <array>
#include <iostream>

#include "ProcessingUnit1.hpp"

ProcessingUnit1::ProcessingUnit1(){}

void ProcessingUnit1::input(std::optional<ProcessingUnit1::InputType> newValues) {
	// Create a copy of the currentValues in case an exception occurs
	std::optional<InputType> tempCurrentValues = currentValues;

	// Replace the stored input with the new input.
	try{
		currentValues = newValues;
	}
	catch(...){
		// Restore the initial value of currentValues on all exceptions, ensuring 
		// a strong exception safety guarantee.
		currentValues = tempCurrentValues;

		std::cerr << "Unknown error occured when inputting to PU1" << std::endl;

		// Rethrow the excepton
		throw;
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
