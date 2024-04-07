#include <iostream>
#define CATCH_CONFIG_MAIN

#include <array>

#include <catch2/catch_test_macros.hpp>
#include "ProcessingUnit1.hpp"
#include "ProcessingUnit2.hpp"
#include "ProcessingUnit3.hpp"


TEST_CASE("Testing PU1 on simple valid input") {
	ProcessingUnit1 pu1;
	std::array<int,ProcessingUnit1::input_length> input = {0, 1, 2, 3, 4};
	std::array<double,ProcessingUnit1::output_length> expectedOutput = {1.0, 2.0, 3.0};

	pu1.input(input);
	std::array<double,ProcessingUnit1::output_length> result = pu1.output();

	REQUIRE(expectedOutput == result);
}

TEST_CASE("Testing PU1 on more complex valid input") {
	ProcessingUnit1 pu1;
	std::array<int,ProcessingUnit1::input_length> input = {4, 2, 6, -10, 0};
	// For non-whole numbered values, perform a caluclation instead of a hardcoded decimal since
	// floats are sometimes a bit off and may not like that.
	std::array<double,ProcessingUnit1::output_length> expectedOutput = {4, -2.0/3, -4.0/3};

	pu1.input(input);
	std::array<double,ProcessingUnit1::output_length> result = pu1.output();

	REQUIRE(expectedOutput == result);
}

// PU2 operates on the past 5 inputs, so we must input multiple times to properly test it.
// We verify that the output is correct after each input to ensure it works while its past
// inputs fill up.
TEST_CASE("Testing PU2 on a series of valid inputs") {
	ProcessingUnit2 pu2;
	std::array<double,ProcessingUnit2::input_length> input = {};
	std::array<double,ProcessingUnit2::output_length> expectedOutput = {};
	// Sum of all inputs so far. This will be used to calculate expectedOutput at each step.
	std::array<double,ProcessingUnit2::output_length> inputTotal = {};

	// First input
	input = {1.0, 2.0, 3.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 1.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Second input
	input = {3.0, 5.0, 7.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 2.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Third input
	input = {25.0, 0.00001, -70.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 3.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Fourth input
	input = {0.0, 0.0, 0.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 4.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Fifth input
	input = {1000.0, -5000.0, 75.23534};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 5.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Sixth input. This one is a bit different from the others, because the first
	// input should now be overwritten.
	input = {1000.0, -5000.0, 75.23534};
	inputTotal = ProcessingUnit2::addArrays(inputTotal, input);
	// This removes the first input from the total since it should now be overwritten
	inputTotal = ProcessingUnit2::addArrays(inputTotal, {-1.0, -2.0, -3.0});
	expectedOutput = ProcessingUnit2::divideArray(inputTotal, 5.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());
}
