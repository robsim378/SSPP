#include <optional>
#include "ProcessingUnit1.hpp"

// Concept used to validate that the output type of one PU 
// is a valid input type to another.
template<typename PU1, typename PU2>
concept ValidPUSequence = requires(PU1 pu1, PU2 pu2) {
	{ pu2.input(pu1.output()) };
};

// Class containing a Simplified Signal Processing Pipeline
class SSPP {
	public:

		SSPP();

		std::optional<int> executeStep(ProcessingUnit1::InputType);
	private:
};
