#include <algorithm>
#include <array>
#include <numeric>

#include "ProcessingUnit3.hpp"

ProcessingUnit3::ProcessingUnit3(){}

void ProcessingUnit3::input(std::optional<ProcessingUnit3::InputType> newValues) {
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
std::optional<ProcessingUnit3::OutputType> ProcessingUnit3::output() {
	if (currentValues.has_value()) {
		return std::accumulate(currentValues.value().begin(), currentValues.value().end(), 0) / 3;
	}
	else {
		return std::nullopt;
	}
}
