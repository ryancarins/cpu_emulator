#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>
#include "cpu.hpp"

Cpu::Cpu(std::array<uint8_t,NUM_REGISTERS> &registers){
	this->registers = registers;
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

//Store bitwise NAND of registers b and c in register a
void Cpu::nand(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = ~(registers[rb] & registers[rc]);
}

//Add registers b and c and store in register a
void Cpu::add(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + registers[rc];
}

//Add register b and a value and store in register a
void Cpu::addi(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t imm = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + imm;
}

//Subtract register b from c and store in register a
void Cpu::sub(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] - registers[rc];
}

//Subtract a value from register b and store in register a
void Cpu::subi(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t imm = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] - imm;
}

//Unconditional jump to instruction by index
int Cpu::jmp(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	return(std::stoi(instruction->at(1)));
}

//Jump to instruction by index if register A is zero
int Cpu::jz(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t line = std::stoi(instruction->at(2));
	if(registers[ra] != 0){
		return(line);
	}else{
		return i+1;
	}
}

//Jump to instruction by index if register A is less than register B
int Cpu::jl(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t line = std::stoi(instruction->at(3));
	if(registers[ra] < registers[rb]){
		return(line);
	}else{
		return i+1;
	}
}

//Jump to instruction by index if register A is equal to imm
int Cpu::eq(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t imm = std::stoi(instruction->at(2));
	uint8_t line = std::stoi(instruction->at(3));
	if(registers[ra] == imm) {
		return(line);
	}else{
		return i+1;
	}
}


//Jump to instruction by index if register A is greater than register B
int Cpu::jg(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t line = std::stoi(instruction->at(3));
	if(registers[ra] > registers[rb]){
		return(line);
	}else{
		return i+1;
	}
}

//Decrement Register A by 1
void Cpu::dec(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	registers[ra]--;
}

//Increment Register A by 1
void Cpu::inc(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	registers[ra]++;
}
