#include "SSPP.hpp"
#include "ProcessingUnit1.hpp"
#include "ProcessingUnit2.hpp"

int main (int argc, char *argv[]) {
	ProcessingUnit1 pu1;
	std::array<int,ProcessingUnit1::input_length> input = {0, 1, 2, 3, 4};
	std::array<double,ProcessingUnit1::output_length> expectedOutput = {1.0, 2.0, 3.0};
	pu1.input(input);
	std::array<double,ProcessingUnit1::output_length> result = pu1.output();
	return 0;
}
