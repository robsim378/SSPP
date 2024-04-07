#include <optional>
#include <concepts>
#include <utility>
#include "ProcessingUnit1.hpp"

// Concept used to validate that the output type of one PU 
// is a valid input type to another.
template<typename PU1, typename PU2>
concept ValidPUSequence = requires(PU1 pu1, PU2 pu2) {
	{ pu2.input(pu1.output()) };
};

// Concept used to validate that a PU has certain requirements
template<typename PU>
concept ValidPU = requires (PU pu) {
	typename PU::InputType;
	typename PU::OutputType;
	{ pu.input(PU::InputType) } -> std::same_as<void>;
	{ pu.output() } -> std::same_as<typename PU::OutputType>;
};


// Class containing a Simplified Signal Processing Pipeline
template<typename PU1, typename PU2, typename PU3>
requires(ValidPU<PU1> && ValidPU<PU2> && ValidPU<PU3> && ValidPUSequence<PU1, PU2> && ValidPUSequence<PU2, PU3>)
class SSPP {
	public:
		SSPP(PU1 a_pu1, PU2 a_pu2, PU3 a_pu3) {
			pu1 = a_pu1;
			pu2 = a_pu2;
			pu3 = a_pu3;
		}

		std::optional<typename PU2::OutputType> executeStep(std::optional<typename PU1::InputType> input) {
			// Calculate the outputs first, then do inputs. This way we don't have to
			// care about the order the PUs are executed in.
			std::optional<typename PU1::OutputType> pu1Output;
			pu1Output = pu1.output();
			std::optional<typename PU2::OutputType> pu2Output;
			pu2Output = pu2.output();
			std::optional<typename PU3::OutputType> pu3Output;
			pu3Output = pu3.output();

			// Now that we have all the outputs, plug them in as inputs to the next PU.
			pu1.input(input);
			pu2.input(pu1Output);
			pu3.input(pu2Output);
			return pu3.output();
		}
	private:
		PU1 pu1;
		PU2 pu2;
		PU3 pu3;

		// Value that was last output by PU1. This is mostly used to handle the 
		// early stages of operation, when not all PUs have received input yet.
		std::optional<typename PU1::InputType> last_input = std::nullopt;
		std::optional<typename PU1::OutputType> pu1Out = std::nullopt;
		std::optional<typename PU2::OutputType> pu2Out = std::nullopt;
};
