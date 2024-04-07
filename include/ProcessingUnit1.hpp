#ifndef HEADER_PROCESSING_UNIT_1
#define HEADER_PROCESSING_UNIT_1

#include <array>

/* This is the first PU for this assignment. Input to the system, in the form of an std::array<int,5>,
   goes here, and its output goes to ProcessingUnit2. This processing unit goes through each element in the
   array and replaces them with a float average of its neighbours. */
class ProcessingUnit1 {
	public:
		// Constants for the input/output array sizes
		static constexpr int input_length = 5;
		static constexpr int output_length = input_length - 2;
		using InputType = std::array<int,input_length>;
		using OutputType = std::array<double,output_length>;

		ProcessingUnit1();

		// Take a new array as input and replace the currently stored one with it.
		void input(InputType newValues);

		// Return an array containing the averages of the neighbours of each element in the input array, with the 
		// first and last elements being ignored.
		OutputType output();

	private:
		InputType currentValues = {}; 
};

#endif
