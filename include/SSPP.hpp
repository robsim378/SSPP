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
template<typename PU1, typename PU2>
requires(ValidPU<PU1> && ValidPU<PU2> && ValidPUSequence<PU1, PU2>)
class SSPP {
	public:
		SSPP(PU1 a_pu1, PU2 a_pu2) {
			pu1 = a_pu1;
			pu2 = a_pu2;
		}

		std::optional<typename PU2::OutputType> executeStep(std::optional<typename PU1::InputType> input) {
			
		}
	private:
		PU1 pu1;
		PU2 pu2;

		// Value that was last output by PU1. This is mostly used to handle the 
		// early stages of operation, when not all PUs have received input yet.
		std::optional<typename PU1::InputType> last_input = std::nullopt;
		std::optional<typename PU1::OutputType> pu1Out = std::nullopt;
		std::optional<typename PU2::OutputType> pu2Out = std::nullopt;

		
		
};
