/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edits: James Sleptzoff
*/

#include "Instruction.h"

void lw_immd_assm(void) {
    // Checking that the op code matches
    // strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
        // If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}
	
    /*
        Checking the type of parameters
    */
	
    // Parameter 1 is the register in which to load data memory into
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
    
    // Parameter 2 is the imm16 value given as an "immediate" or constant
    // integer value in MIPS
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}
    
    // Parameter 3 is the register that holds the base data memory address
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
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
	if ( PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
    
    // The immediate value is limited to 16 bits, this is 0xFFFF
	if ( PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	
    /*
       Encoding LW:
       opcode (6): 100011
       Rt (5): PARAM1
       imm16 (16: PARAM2
       Rs (5): PARAM3
    */
    
	// Set OpCode
	setBits_str(31, "100011");
    
    // Set Rt
	setBits_num(20, PARAM1.value, 5);
    
    // Set Rs
	setBits_num(25, PARAM3.value, 5);
    
    // Set immediate
	setBits_num(15, PARAM2.value, 16);

    // Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {
	// Check if the op code bigs match
    // check_bits(start_bit, bit_string) returns 0 if the bit_string matches
    //  any x will be skipped
    // If the manual shows (0), then teh value of that bit doesn't matter
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

    // If the op code bits match, then the rest can be read as correctly
    
    /*
        Finding values in the binary
    */
    // getBits(start_bit , width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

    /*
        Setting Instruction values
    */
    
	setOp("LW");
    // setCond_num(cond);
    // setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // Destination
    setParam(2, IMMEDIATE, imm16); // imm16 immediate value
	setParam(3, REGISTER, Rs); // Register with data memory base address

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;

}
