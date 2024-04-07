#ifndef HEADER_PROCESSING_UNIT_2
#define HEADER_PROCESSING_UNIT_2

#include <array>

/* This is the first PU for this assignment. Input to the system, in the form of an std::array<int,5>,
   goes here, and its output goes to ProcessingUnit2. This processing unit goes through each element in the
   array and replaces them with a float average of its neighbours. */
class ProcessingUnit2 {
	public:
		// Constants for the input/output array sizes
		static constexpr int input_length = 3;
		static constexpr int output_length = input_length;
		using InputType = std::array<double,input_length>;
		using OutputType = std::array<double,output_length>;

		ProcessingUnit2();

		// Add two arrays together and return the resulting array
		template<typename T, std::size_t N>
		static std::array<T,N> addArrays(const std::array<T,N>& array1, const std::array<T,N>& array2);

		// Divide every element in an array by a divisor

		template <typename T, std::size_t N>
		static std::array<T, N> divideArray(const std::array<T, N>& a, T divisor);
		
		// Take a new array as input and replace the currently stored one with it.
		void input(InputType newValues);

		// Apply this PU's transformation to the current values and return the result

		OutputType output();
	private:
		static constexpr int num_past_values = 5;
		int numStoredValues;
		int currentIndex;
		std::array<InputType,num_past_values> currentValues = {}; 
};

#endif
