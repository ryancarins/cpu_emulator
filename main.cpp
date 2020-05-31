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
			cpu.addi(registers, &instruction);
			i++;
		}else if (instruction[0].compare("ADD") == 0){
			cpu.add(registers, &instruction);
			i++;
		}else if (instruction[0].compare("NAND") == 0){
			cpu.nand(registers, &instruction);
			i++;
		}else if (instruction[0].compare("SUB") == 0){
			cpu.sub(registers, &instruction);
			i++;
		}else if (instruction[0].compare("SUBI") == 0){
			cpu.subi(registers, &instruction);
			i++;
		}else if (instruction[0].compare("JMP") == 0){
			i = cpu.jmp(registers, &instruction);
		}else if (instruction[0].compare("JZ") == 0){
			i = cpu.jz(registers, &instruction,i);
		}else if (instruction[0].compare("JL") == 0){
			i = cpu.jl(registers, &instruction,i);
		}else if (instruction[0].compare("JG") == 0){
			i = cpu.jg(registers, &instruction,i);
		}else if (instruction[0].compare("EQ") == 0){
			i = cpu.eq(registers, &instruction,i);
		}else if (instruction[0].compare("DEC") == 0){
			cpu.dec(registers, &instruction);
			i++;
		}else if (instruction[0].compare("INC") == 0){
			cpu.inc(registers, &instruction);
			i++;
		}else{
			i++;
		}
	}

	std::cout << "-----Instructions End-----" << std::endl;

	std::cout << "-----Start Register States-----" << std::endl;

	for(int i = 0; i<cpu.registers.size(); i++) {
		//Print in format R0001 00001
		std::cout << "R"<< std::setw(3) << std::setfill('0') << i << " "
			<< std::setw(5) << std::setfill('0') << std::to_string(registers[i]) << " ";
		if(i%9 == 0){ //Limit output width
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << "-----End Register States-----" << std::endl;
	return 0;
}
