//Bradley Beltran
//CS3432

//GitHub
//jamesb5959/Lab2
//https://github.com/jamesb5959/Lab2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

bool equals(char str1[], char str2[]){
	int index=0;
    while(str1[index]==str2[index]){
    	if(str1[index]=='\0' || str2[index]=='\0')
            break;
        index++;
    }
	if(str1[index]=='\0' && str2[index]=='\0')
        return true;
    else
        return false;
}

long strToInt(char str1[]){
    long num = 0;
    int index = 0;
    while (str1[index]){
        if(str1[index] >= '0' && str1[index] <= '9'){
            num = num * 10 + (str1[index] - '0');
        }
        index++;
    }
    return num;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){

	char** tok = tokenize(instr, ' ');
	char* mem_file = "mem.txt";

	if(equals(tok[0], "ADD")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		int32_t tok3 = strToInt(tok[3]);
		if(tok1 > 31 || tok2 > 31 || tok3 > 31)
			return false;
		reg[tok1]=reg[tok2]+reg[tok3];
	}
	else if(equals(tok[0], "ADDI")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		int32_t tok3 = strToInt(tok[3]);
		if(tok1 > 31 || tok2 > 31)
			return false;
		reg[tok1]=reg[tok2]+tok3;
	}
	else if(equals(tok[0], "LW")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = 0;
		char** tokTemp = tokenize(tok[2], '(');
		if(tok1 > 31)
			return false;
		if (tokTemp[1] == '\0'){
			tok2=reg[strToInt(tokTemp[0])];
		}
		else if (tokTemp[1] != '\0'){
			tok2=strToInt(tokTemp[0])+reg[strToInt(tokTemp[1])];
		}
    	reg[tok1] = read_address(tok2, "mem.txt");;
	}
	else if(equals(tok[0], "SW")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		char** tokTemp = tokenize(tok[2], '(');
		if(tok1 > 31)
			return false;
		if (tokTemp[1] == '\0'){
			tok2=reg[strToInt(tokTemp[0])];
		}
		else if (tokTemp[1] != '\0'){
			tok2=strToInt(tokTemp[0])+reg[strToInt(tokTemp[1])];
		}
		int32_t write = write_address(reg[tok1], tok2, "mem.txt");
		if(write == (int32_t) NULL)
			printf("ERROR: Unsucessful write to address %0X\n", 0x40);
			return false;
	}
	else if(equals(tok[0], "AND")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		int32_t tok3 = strToInt(tok[3]);
		if(tok1 > 31 || tok2 > 31 || tok3 > 31)
			return false;
		int32_t read = read_address(tok1, mem_file);
		reg[tok1]=reg[tok2]&reg[tok3];
	}
	else if(equals(tok[0], "OR")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		int32_t tok3 = strToInt(tok[3]);
		if(tok1 > 31 || tok2 > 31 || tok3 > 31)
			return false;
		int32_t read = read_address(tok1, mem_file);
		reg[tok1]=reg[tok2]|reg[tok3];
	}
	else if(equals(tok[0], "XOR")){
		int32_t tok1 = strToInt(tok[1]);
		int32_t tok2 = strToInt(tok[2]);
		int32_t tok3 = strToInt(tok[3]);
		if(tok1 > 31 || tok2 > 31 || tok3 > 31)
			return false;
		int32_t read = read_address(tok1, mem_file);
		reg[tok1]=reg[tok2]^reg[tok3];
	}
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");


	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}