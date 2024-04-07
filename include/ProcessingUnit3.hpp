#ifndef HEADER_PROCESSING_UNIT_3
#define HEADER_PROCESSING_UNIT_3

#include <array>
#include <optional>

/* This is the first PU for this assignment. Input to the system, in the form of an optional std::array<int,5>,
   goes here, and its output goes to ProcessingUnit2. This processing unit goes through each element in the
   array and replaces them with a float average of its neighbours. */
class ProcessingUnit3 {
	public:
		// Constants for the input/output array sizes
		static constexpr int input_length = 3;
		using InputType = std::array<double,input_length>;
		using OutputType = double;

		ProcessingUnit3();

		// Take a new array as input and replace the currently stored one with it.
		void input(std::optional<InputType> newValues);

		// Return the average of all elements in the array
		std::optional<OutputType> output();

	private:
		std::optional<InputType> currentValues = std::nullopt; 
};

#endif
