#include "MIPS_Interpreter.h"
#include <stdio.h>

int main(void) {
	// inializes everything
	initAll();

	// buffer for reading/writing
	char buffer[BUFF_SIZE] = { '\0' };

	// startup message
	puts("Welcome to the MIPS-Translatron 3000 Tool");
	puts("ByteForge Systems ©2012");

	// loopps forever
	while (1) {
		// prompts and takes input
		puts("\nPlease enter an option:");
		puts("\t(1) Assembly to Machine Code");
		puts("\t(2) Machine Code to Assembly");
		puts("\t(3) Quit");
		printf("\n> ");

		memset(buffer, '\0', BUFF_SIZE);
		gets(buffer, BUFF_SIZE);

		// either calls the assembly menu, the machine menu, or exits the program
		if (strcmp(buffer, "1") == 0) {
			assembly2machine(buffer);
		}
		else if (strcmp(buffer, "2") == 0) {
			machine2assembly(buffer);
		}
		else if (strcmp(buffer, "3") == 0) {
			return 0;
		}
		else if (strcmp(buffer, "test") == 0) {
			test();
		}
	}
	return 0;
}

/*
	Purpose: Test benchmark, run through the test_assem.txt file and test each line
	Params: none
	Return: none
*/
void test(void) {

	// Pointer to our test file
	FILE *test_file_ptr;
	test_file_ptr = fopen("test_assem.txt", "r");

	// Check if file opened successfully
	if (test_file_ptr == NULL) {
		printf("Error: Could not open test file.\n");
		return; // Exit
	}

	// reading line by line
	// test each assembly code line
	char line[BUFF_SIZE];
	int tests_passed = 0;
	int test_failed = 0;

	while (fgets(line, sizeof(line), test_file_ptr) != NULL) {
		// Remove trailing newline character if present
		line[strcspn(line, "\n")] = '\0';
		char pass_fail = line[0]; // First character indicates pass/fail
		memmove(line, line + 2, strlen(line) - 1); // Shift line to remove pass/fail indicator
		printf("Testing line: %s, Result [%c]\n", line, pass_fail);

		// parse the instruction
		parseAssem(line);
		// checks if there was an error, and encodes if there wasn't
		if (state == NO_ERROR) {
			encode();
			printResult();
			if (state == COMPLETE_ENCODE) {
				printAssm();
			} else {
				printf("Test failed during encoding.\n");
				if (pass_fail == 'P') {
					test_failed++;
				} else {
					tests_passed++;
				}
			}
		} else {
			if (pass_fail == 'P') {
				test_failed++;
			} else {
				tests_passed++;
			}
			printf("Error encountered during parsing.\n");
		}
		printf("\n");
		
	}
	// print results
	printf("Tests Passed: %d, Tests Failed: %d\n", tests_passed, test_failed);

	fclose(test_file_ptr);
}

/*
	Purpose: initializes anything that needs to be initialized
	Params: none
	Return: none
*/
void initAll(void) {
	initInstructs();
}


/*
	Purpose: menu for assembly to machine conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void assembly2machine(char* buff) {
	// loops forever
	while (1) {
		// prompts and takes input
		puts("\nEnter a line of assembly:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the instruction
		parseAssem(buff);

		// checks if there was an error, and encodes if there wasn't
		if (state == NO_ERROR) {
			encode();
		}

		// either prints an error message or the encoded instruction
		printResult();
	}
}


/*
	Purpose: menu for machine to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void machine2assembly(char* buff) {
	while (1) {
		while (1) {
			// prompts and takes input
			puts("\nPlease select an option:");
			puts("\t(1) Hexadecimal to Assembly");
			puts("\t(2) Binary to Assembly");
			puts("\t[3] Main Menu");
			printf("\n> ");

			memset(buff, '\0', BUFF_SIZE);
			gets(buff, BUFF_SIZE);


			// either calls the hex menu or binary menu
			// otherwise exist back tot he previous menu
			if (strcmp(buff, "1") == 0) {
				hex2assembly(buff);
			}
			else if (strcmp(buff, "2") == 0) {
				binary2assembly(buff);
			}
			else {
				return;
			}
		}
	}
}


/*
	Purpose: menu for binary to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void binary2assembly(char* buff) {
	while (1) {
		// prompts and takes input
		puts("\nEnter Binary:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the number
		parseBin(buff);

		// checks if there was an error, and decodes if there wasn't
		if (state == NO_ERROR) {
			decode();
		}

		// either prints an error message or the encoded instruction
		printResult();
	}
}


/*
	Purpose: menu for hex to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void hex2assembly(char* buff) {
	while (1) {
		// prompts and takes input
		puts("\nEnter Hex:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the number
		parseHex(buff);

		// checks if there was an error, and decodes if there wasn't
		if (state == NO_ERROR) {
			decode();
		}

		// either prints an error message or the encoded instruction
		printResult();
	}
}