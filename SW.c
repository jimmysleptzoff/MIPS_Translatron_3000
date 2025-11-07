/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
* Edits: James Sleptzoff
*/

#include "Instruction.h"

void sw_immd_assm(void) {
    // Checking that teh op code matches
    // strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "SW") != 0) {
        // If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return;
	}
    
    /*
        Checking the type of parameters
    */
    
    // Generally the first parameter should always be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
    
    // Param 2 needs to be an immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

    // Param3 needs to be a register
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
    
    // The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
    
    // Rs should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
    
    /*
        Putting the binary together
    */
    
    /*
       Encoding SW:
       opcode (6): 101011
       Rt (5): PARAM1
       offset (16): PARAM2
       Rs (5): PARAM3
   */

    // Set OpCode
	setBits_str(31, "101011");
    
    // Set Rt
	setBits_num(20, PARAM1.value, 5);
    
    // Set immediate
	setBits_num(15, PARAM2.value, 16);
    
    // Set Rs
	setBits_num(25, PARAM3.value, 5);

    // Tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // Check if the op code bits match
    // check_bits(start_bit, bit_string) returns 0 if the bit_string matches
    // any x will be skipped
    // If the manual shows (0), then the value of that bit doesn't matter
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

    // If the op code bits match, then the rest can be read as correctly
    
    /*
        Finding the values in the binary
    */
    // getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

    /*
        Setting Instuciton values
    */
    
	setOp("SW");
    //setCond_num(cond);
    //setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // Source data register
    setParam(2, IMMEDIATE, offset); // offset value
	setParam(3, REGISTER, Rs); // Register with data memory base address

    // Tell the system the decoding is done
	state = COMPLETE_DECODE;
}
