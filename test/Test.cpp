#include <iostream>
#include <optional>
#define CATCH_CONFIG_MAIN

#include <array>

#include <catch2/catch_test_macros.hpp>
#include "ProcessingUnit1.hpp"
#include "ProcessingUnit2.hpp"
#include "ProcessingUnit3.hpp"



TEST_CASE("Testing PU1 on simple valid input") {
	ProcessingUnit1 pu1;
	std::optional<ProcessingUnit1::InputType> input;
	input = {0, 1, 2, 3, 4};
	std::optional<ProcessingUnit1::OutputType> expectedOutput;
	expectedOutput = {1.0, 2.0, 3.0};

	pu1.input(input);
	std::optional<ProcessingUnit1::OutputType> result;
	result = pu1.output();

	REQUIRE(expectedOutput == result);
}

TEST_CASE("Testing PU1 on more complex valid input") {
	ProcessingUnit1 pu1;
	std::optional<ProcessingUnit1::InputType> input;
	input = {4, 2, 6, -10, 0};
	// For non-whole numbered values, perform a caluclation instead of a hardcoded decimal since
	// floats are sometimes a bit off and may not like that.
	std::optional<ProcessingUnit1::OutputType> expectedOutput;
	expectedOutput = {4, -2.0/3, -4.0/3};

	pu1.input(input);
	std::optional<ProcessingUnit1::OutputType> result;
	result = pu1.output();

	REQUIRE(expectedOutput == result);
}

TEST_CASE("Testing PU1 output with no input") {
	ProcessingUnit1 pu1;
	REQUIRE(!pu1.output().has_value());
}

TEST_CASE("Testing that inputting nothing clears PU1 output") {
	// Input something to have an output
	ProcessingUnit1 pu1;
	std::optional<ProcessingUnit1::InputType> input;
	input = {0, 1, 2, 3, 4};
	std::optional<ProcessingUnit1::OutputType> expectedOutput;
	expectedOutput = {1.0, 2.0, 3.0};

	pu1.input(input);
	std::optional<ProcessingUnit1::OutputType> result;
	result = pu1.output();

	REQUIRE(expectedOutput == result);

	// Check that inputting nothing results in no output
	pu1.input(std::nullopt);
	result = pu1.output();
	REQUIRE(!result.has_value());
}

// PU2 operates on the past 5 inputs, so we must input multiple times to properly test it.
// We verify that the output is correct after each input to ensure it works while its past
// inputs fill up.
TEST_CASE("Testing PU2 on a series of valid inputs") {
	ProcessingUnit2 pu2;
	std::optional<ProcessingUnit2::InputType> input;
	input = {};
	std::optional<ProcessingUnit2::OutputType> expectedOutput;
	expectedOutput = {};
	// Sum of all inputs so far. This will be used to calculate expectedOutput at each step.
	std::optional<ProcessingUnit2::InputType> inputTotal;
	inputTotal = {};


	// First input
	input = {1.0, 2.0, 3.0};
	// For the first input, we can just make inputTotal equal to input. this also
	// means we don't have to deal with initializing inputTotal.
	inputTotal = input;
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 1.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Second input
	input = {3.0, 5.0, 7.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), input.value());
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 2.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Third input
	input = {25.0, 0.00001, -70.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), input.value());
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 3.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Fourth input
	input = {0.0, 0.0, 0.0};
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), input.value());
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 4.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Fifth input
	input = {1000.0, -5000.0, 75.23534};
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), input.value());
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 5.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Sixth input. This one is a bit different from the others, because the first
	// input should now be overwritten.
	input = {1000.0, -5000.0, 75.23534};
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), input.value());
	// This removes the first input from the total since it should now be overwritten
	inputTotal = ProcessingUnit2::addArrays(inputTotal.value(), {-1.0, -2.0, -3.0});
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 5.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());
}

TEST_CASE("Testing PU2 output with no input") {
	ProcessingUnit2 pu2;
	REQUIRE(!pu2.output().has_value());
}

TEST_CASE("Testing that inputting nothing clears PU2 output") {
	// Input something to have an output
	ProcessingUnit2 pu2;
	std::optional<ProcessingUnit2::InputType> input;
	input = {};
	std::optional<ProcessingUnit2::OutputType> expectedOutput;
	expectedOutput = {};
	// Sum of all inputs so far. This will be used to calculate expectedOutput at each step.
	std::optional<ProcessingUnit2::InputType> inputTotal;
	inputTotal = {};


	// First input
	input = {1.0, 2.0, 3.0};
	// For the first input, we can just make inputTotal equal to input. this also
	// means we don't have to deal with initializing inputTotal.
	inputTotal = input;
	expectedOutput = ProcessingUnit2::divideArray(inputTotal.value(), 1.0);
	pu2.input(input);
	REQUIRE(expectedOutput == pu2.output());

	// Input nothing a few times. Expected output should remain unchanged until the sixth input.

	// second input
	pu2.input(std::nullopt);
	REQUIRE(expectedOutput == pu2.output());

	// third input
	pu2.input(std::nullopt);
	REQUIRE(expectedOutput == pu2.output());

	// fourth input
	pu2.input(std::nullopt);
	REQUIRE(expectedOutput == pu2.output());

	// fifth input
	pu2.input(std::nullopt);
	REQUIRE(expectedOutput == pu2.output());

	// sixth input. This time, the output should be nothing.
	pu2.input(std::nullopt);
	REQUIRE(!pu2.output().has_value());

}
