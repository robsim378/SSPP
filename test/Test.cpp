#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <optional>

#include "SSPP.hpp"
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

TEST_CASE("Testing PU3 on simple valid input") {
	ProcessingUnit3 pu3;
	std::optional<ProcessingUnit3::InputType> input;
	input = {0, 1, 2};
	std::optional<ProcessingUnit3::OutputType> expectedOutput;
	expectedOutput = 1.0;

	pu3.input(input);
	std::optional<ProcessingUnit3::OutputType> result;
	result = pu3.output();

	REQUIRE(expectedOutput == result);
}

TEST_CASE("Testing PU3 on some more complex valid input") {
	ProcessingUnit3 pu3;
	std::optional<ProcessingUnit3::InputType> input;
	input = {-2.3, 1.5, 15};
	std::optional<ProcessingUnit3::OutputType> expectedOutput;
	expectedOutput = 14.2 / 3.0;

	pu3.input(input);
	std::optional<ProcessingUnit3::OutputType> result;
	result = pu3.output();

	REQUIRE(expectedOutput == Catch::Approx(result.value()).epsilon(1e-6));
}

TEST_CASE("Testing PU3 output with no input") {
	ProcessingUnit3 pu3;
	REQUIRE(!pu3.output().has_value());
}

TEST_CASE("Testing that inputting nothing clears PU3 output") {
	ProcessingUnit3 pu3;
	std::optional<ProcessingUnit3::InputType> input;
	input = {0, 1, 2};
	std::optional<ProcessingUnit3::OutputType> expectedOutput;
	expectedOutput = 1.0;

	pu3.input(input);
	std::optional<ProcessingUnit3::OutputType> result;
	result = pu3.output();

	REQUIRE(expectedOutput == result);

	pu3.input(std::nullopt);
	REQUIRE(pu3.output() == std::nullopt);
}

TEST_CASE("Testing SSPP") {
	ProcessingUnit1 pu1;
	ProcessingUnit2 pu2;
	ProcessingUnit3 pu3;

	SSPP<ProcessingUnit1,ProcessingUnit2,ProcessingUnit3> sspp(pu1, pu2, pu3);

	std::optional<ProcessingUnit1::InputType> input;
	std::optional<ProcessingUnit3::OutputType> expectedOutput;

	// We should not see any output until the 4th input.
	// First input. 
	input = {0, 1, 2, 3, 4};
	REQUIRE(!sspp.executeStep(input).has_value());

	// Second input
	input = {0, 2, 4, 6, 8};
	REQUIRE(!sspp.executeStep(input).has_value());

	// Third input
	input = {10, -3, 9, 0, -22};
	REQUIRE(!sspp.executeStep(input).has_value());

	// Fourth input. Here we should start seeing some output. We will also stop
	// providing input here to test that it correctly stops outputting.
	input = std::nullopt;
	expectedOutput = 2.0;
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Fifth input. Here we should start seeing the past data from PU2 kick in.
	expectedOutput = 3.0;
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Fifth input. Here we should start seeing the past data from PU2 kick in.
	expectedOutput = 21.0 / 9.0;
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Sixth input. Nothing should change here.
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Seventh input. Nothing should change here.
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Eigth input. The first input should be gone now.
	expectedOutput = 2.5;
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Ninth input. The first two inputs should be gone now.
	expectedOutput = 1;
	REQUIRE(sspp.executeStep(input).value() == Catch::Approx(expectedOutput.value()).epsilon(1e-6));

	// Tenth input. There should be no output here.
	REQUIRE(!sspp.executeStep(input).has_value());
}









