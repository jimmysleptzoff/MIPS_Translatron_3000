/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// File edited by Zachary Jeckering

#include "Instruction.h"

void div_reg_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "DIV") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// Generally the first parameter should always be a register (rs)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Generally the first parameter should always be a register (rt)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
        Checking the value of parameters
    */

    // Rs should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}


	/*
		Putting the binary together
	*/

	// set the opcode
	setBits_str(31, "000000");

	// set the funct
	setBits_str(5, "011010");

	// set the Rt
	setBits_num(20, PARAM2.value, 5);

	// set the Rs
	setBits_num(25, PARAM1.value, 5);

	// Set the rd
	setBits_num(15, 0, 5);

	// Set the shamt
    setBits_num(10, 0, 5);
	
	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	/*
		Setting Instuciton values
	*/

	setOp("DIV");
	setParam(1, REGISTER, Rs); //first source register operand
	setParam(2, REGISTER, Rt); //second source register operand

	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


