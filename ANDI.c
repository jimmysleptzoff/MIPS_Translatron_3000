#include "Instruction.h"

// File edited by Zachary Jeckering

void andi_immd_assm(void) {

	// Check that the opcode matches
	if (strcmp(OP_CODE, "ANDI") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// // This is ANDI, so param 1 needs to be a register (rt)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is ANDI, so param 2 needs to be a register (rs)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// This is ANDI, so param 3 needs to be an immediate value
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}


	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// imm16 should be 0 to 65535
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode
	setBits_str(31, "001100");

    // Set rs (bits 25–21)
	setBits_num(25, PARAM2.value, 5);

	// Set rt (bits 20–16)
	setBits_num(20, PARAM1.value, 5);

	// Set immediate (bits 15–0)
	setBits_num(15, PARAM3.value, 16);

	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	// Check that opcode bits match ANDI (001100)
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// get binary values
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instuciton values
	*/
	
	setOp("ANDI");
	setParam(1, REGISTER, Rt); // destination
	setParam(2, REGISTER, Rs); // source
	setParam(3, IMMEDIATE, imm16); // immediate value
	
	// tell the system when the decoding is done
	state = COMPLETE_DECODE;
}



