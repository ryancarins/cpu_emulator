#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>
#include "cpu.hpp"

Cpu::Cpu(){
	this->registers.fill(0);
}


//Size is 4 because I'm using at most 4 parts for a command
std::array<std::string,4> Cpu::getInstruction(std::string line){
	std::istringstream string_stream(line);
	std::string curr;
	std::array<std::string,4> instruction;
	char delimiter = ' ';

	int i = 0;
	while(std::getline(string_stream, curr, delimiter) && i<4){
		instruction[i] = curr;
		i++;
	}
	return instruction;
}

//Store bitwise NAND of this->registers b and c in register a
void Cpu::nand(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE rc = std::stoi(instruction->at(3));
	this->registers[ra] = ~(registers[rb] & registers[rc]);
}

//Add this->registers b and c and store in register a
void Cpu::add(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE rc = std::stoi(instruction->at(3));
	this->registers[ra] = registers[rb] + registers[rc];
}

//Add register b and a value and store in register a
void Cpu::addi(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE imm = std::stoi(instruction->at(3));
	this->registers[ra] = registers[rb] + imm;
}

//Subtract register b from c and store in register a
void Cpu::sub(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE rc = std::stoi(instruction->at(3));
	this->registers[ra] = registers[rb] - registers[rc];
}

//Subtract a value from register b and store in register a
void Cpu::subi(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE imm = std::stoi(instruction->at(3));
	this->registers[ra] = registers[rb] - imm;
}

//Unconditional jump to instruction by index
int Cpu::jmp(std::array<std::string,4> *instruction) {
	return(std::stoi(instruction->at(1)));
}

//Jump to instruction by index if register A is zero
int Cpu::jz(std::array<std::string,4> *instruction, int i) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE line = std::stoi(instruction->at(2));
	if(this->registers[ra] != 0){
		return(line);
	}else{
		return i+1;
	}
}

//Jump to instruction by index if register A is less than register B
int Cpu::jl(std::array<std::string,4> *instruction, int i) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE line = std::stoi(instruction->at(3));
	if(this->registers[ra] < registers[rb]){
		return(line);
	}else{
		return i+1;
	}
}

//Jump to instruction by index if register A is equal to imm
int Cpu::eq(std::array<std::string,4> *instruction, int i) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE imm = std::stoi(instruction->at(2));
	REG_TYPE line = std::stoi(instruction->at(3));
	if(this->registers[ra] == imm) {
		return(line);
	}else{
		return i+1;
	}
}


//Jump to instruction by index if register A is greater than register B
int Cpu::jg(std::array<std::string,4> *instruction, int i) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	REG_TYPE rb = std::stoi(instruction->at(2));
	REG_TYPE line = std::stoi(instruction->at(3));
	if(this->registers[ra] > registers[rb]){
		return(line);
	}else{
		return i+1;
	}
}

//Decrement Register A by 1
void Cpu::dec(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	this->registers[ra]--;
}

//Increment Register A by 1
void Cpu::inc(std::array<std::string,4> *instruction) {
	REG_TYPE ra = std::stoi(instruction->at(1));
	this->registers[ra]++;
}

void Cpu::print_states(){
	for(int i = 0; i<this->registers.size(); i++) {
		//Print in format R0001 00001
		std::cout << "R"<< std::setw(3) << std::setfill('0') << i << " "
			<< std::setw(5) << std::setfill('0') << std::to_string(this->registers[i]) << " ";
		if(i%9 == 0){ //Limit output width
			std::cout << std::endl;
		}
	}

}
