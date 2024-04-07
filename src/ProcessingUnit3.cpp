#include <array>
#include <numeric>

#include "ProcessingUnit3.hpp"

ProcessingUnit3::ProcessingUnit3(){}

void ProcessingUnit3::input(std::optional<ProcessingUnit3::InputType> newValues) {
	// this function implements basic exception safety guarantee even without doing anything
	// special, because there are no invalid intermediate states. 
	currentValues = newValues;
}

std::optional<ProcessingUnit3::OutputType> ProcessingUnit3::output() {
	if (currentValues.has_value()) {
		double sum = std::accumulate(currentValues.value().begin(), currentValues.value().end(), 0.0);
		return sum / 3.0;
	}
	else {
		return std::nullopt;
	}
}
