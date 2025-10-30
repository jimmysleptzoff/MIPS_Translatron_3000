#include "Instruction.h"

// will do later

void mult_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "MULT") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// MULT requires two registers
	if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	 /*
        Encoding MULT:
        opcode (6): 000000
        rs (5): PARAM2
        rt (5): PARAM1
        rd (5): 00000
        shamt (5): 00000
        funct (6): 011000
    */

	/*
		Putting the binary together
	*/

	// Set the opcode, which is 000000 for R-Format instructions
	setBits_num(31, 0, 6);

	// set Rs
	setBits_num(25, PARAM1.value, 5);

	// set Rt
	setBits_num(20, PARAM2.value, 5);

	// set Rd
	setBits_num(15, 0, 5);

	// set shamt
	setBits_num(10, 0, 5);

	// set funct (0b = binary literal)
	setBits_num(5, 0b011000, 6);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	// Checking that the binary matches MULT 
	// checkBits(position, "bitstring") returns 0 if they match
	// funct is the last 6 for R-Format
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("MULT");
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt);

	state = COMPLETE_DECODE;
}

