
#include <cstdint>

[[gnu::section(".fopt")]]
[[gnu::used]]
const uint32_t my_fopt[] = {
	// flash configuration field
	// .word 0xFFFFFFFF    // backdoor comparison key
	// .word 0xFFFFFFFF    // backdoor comparison key
	// .word 0xFFFFFFFF    // program flash protection bytes FPROTO0-3
	// .word 0xFFFFFFFE    // FDPROT, FEPROT, FOPT, FSEC:unsecure
        0xffffffff,
        0xffffffff,
        0xffffffff,
        0xfffffffe,
};
