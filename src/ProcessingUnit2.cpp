#include <algorithm>
#include <array>
#include <functional>
#include <optional>

#include "ProcessingUnit2.hpp"

ProcessingUnit2::ProcessingUnit2() {
	currentIndex = 0;
}

template<typename T, std::size_t N>
std::array<T,N> ProcessingUnit2::addArrays(const std::array<T,N>& array1, const std::array<T,N>& array2) {
	std::array<T,N> result = {};
	std::transform(array1.begin(), array1.end(), array2.begin(), result.begin(), std::plus<T>());
	return result;
}

template <typename T, std::size_t N>
std::array<T, N> ProcessingUnit2::divideArray(const std::array<T, N>& a, T divisor) {
	// Use a lambda to divide every element in an array by a given value of the same type as the array elements
	std::array<T, N> result;
	std::transform(a.begin(), a.end(), result.begin(), [divisor](T element) { return element / divisor; });
	return result;
}

void ProcessingUnit2::input(std::optional<ProcessingUnit2::InputType> newValues) {
	// this function implements basic exception safety guarantee even without doing anything
	// special, because there are no invalid intermediate states.
	currentValues[currentIndex] = newValues;

	// Instead of shifting all the past stored values over, we just maintain the index of the next value to 
	// be overwritten by new input. This saves a good amount of copying.
	currentIndex = (currentIndex + 1) % num_past_values;
}

std::optional<ProcessingUnit2::OutputType> ProcessingUnit2::output() {
	OutputType result = {};

	// Loop over all the stored input arrays and calculate the element-wise sum of all of them
	int numStoredValues = 0;
	for (int i = 0; i < num_past_values; i++) {
		if (currentValues[i].has_value()) {
			result = addArrays(result, currentValues[i].value());
			numStoredValues++;
		}
	}

	// If there are no stored values, output nothing.
	if (numStoredValues == 0) {
		return std::nullopt;
	}

	// Divide each element of the result by the total number of stored inputs,
	// giving the average stored input for each element.
	result = divideArray(result, (double)numStoredValues);

	return result;
}
