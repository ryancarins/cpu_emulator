#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>
#include "cpu.hpp"

std::vector<std::string> load_instruction(std::string filename) {
	std::ifstream instruction_file;
	std::string line;
	std::vector<std::string> instructions;
	instruction_file.open(filename);
	if(instruction_file.is_open()){
		while (getline(instruction_file,line)) {
			instructions.push_back(line);
		}
	}
	return instructions;
}

int main(){
	//TODO make this an argument
	std::vector<std::string> instructions = load_instruction("instruct.txt");

	//Registers for CPU
	std::array<REG_TYPE,NUM_REGISTERS> registers;
	registers.fill(0);
	Cpu cpu = Cpu(registers);

	std::cout << "-----Instructions Start-----" << std::endl;

	int i=0;
	bool debug = cpu.getInstruction(instructions.at(0))[0].compare("DEBUG") == 0;

	if(!debug){
		std::cout << "-----Debugging Is Off-----" << std::endl;
	}

	while(i<instructions.size()){
		std::array<std::string,4> instruction = cpu.getInstruction(instructions.at(i));

		if(debug){
			std::cout << instructions[i] << std::endl;
		}

		//Not a switch because C++ doesn't allow strings in switches
		//and code for an enum would be longer anyway
		if(instruction[0].compare("ADDI") == 0){
			cpu.addi(&instruction);
			i++;
		}else if (instruction[0].compare("ADD") == 0){
			cpu.add(&instruction);
			i++;
		}else if (instruction[0].compare("NAND") == 0){
			cpu.nand(&instruction);
			i++;
		}else if (instruction[0].compare("SUB") == 0){
			cpu.sub(&instruction);
			i++;
		}else if (instruction[0].compare("SUBI") == 0){
			cpu.subi(&instruction);
			i++;
		}else if (instruction[0].compare("JMP") == 0){
			i = cpu.jmp(&instruction);
		}else if (instruction[0].compare("JZ") == 0){
			i = cpu.jz(&instruction,i);
		}else if (instruction[0].compare("JL") == 0){
			i = cpu.jl(&instruction,i);
		}else if (instruction[0].compare("JG") == 0){
			i = cpu.jg(&instruction,i);
		}else if (instruction[0].compare("EQ") == 0){
			i = cpu.eq(&instruction,i);
		}else if (instruction[0].compare("DEC") == 0){
			cpu.dec(&instruction);
			i++;
		}else if (instruction[0].compare("INC") == 0){
			cpu.inc(&instruction);
			i++;
		}else{
			i++;
		}
	}
	std::cout << "-----Instructions End-----" << std::endl;

	
	std::cout << "-----Start Register States-----" << std::endl;
	cpu.print_states();
	std::cout << std::endl << "-----End Register States-----" << std::endl;

	
	return 0;
}
