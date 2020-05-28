#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>


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

//Size is 4 because I'm using at most 4 parts for a command
std::array<std::string,4> getInstruction(std::string line){
	std::istringstream string_stream(line);
	std::string curr;
	std::array<std::string,4> instruction;
	char delimiter = ' ';

	int i = 0;
	while(std::getline(string_stream, curr, delimiter)){
		instruction[i] = curr;
		i++;
	}
	return instruction;
}

//Store bitwise NAND if registers b and c to register a
void nand(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = ~(registers[rb] & registers[rc]);
}

//Add registers b and c to register a
void add(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + registers[rc];
}

//Add register b and a value to register a
void addi(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t imm = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + imm;
}

//Unconditional jump to instruction by index
int jmp(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	return(std::stoi(instruction->at(1)));
}

//Jump to instruction by index if register A is zero
int jz(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction, int i) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t line = std::stoi(instruction->at(1));
	if(registers[ra] != 0){
		return(line);
	}else{
		return i+1;
	}
}

//Decrement Register A by 1
void dec(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	registers[ra]--;
}

//Increment Register A by 1
void inc(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	registers[ra]++;
}


int main(){
	//TODO make this an argument
	std::vector<std::string> instructions = load_instruction("instruct.txt");

	//Registers for CPU
	std::array<uint8_t,256> registers;
	registers.fill(0);


	std::cout << "-----Instructions Start-----" << std::endl;

	int i=0;
	while(i<instructions.size()){
		std::array<std::string,4> instruction = getInstruction(instructions.at(i));
		std::cout << instructions[i] << std::endl;
		if(instruction[0].compare("ADDI") == 0){
			addi(registers, &instruction);
			i++;
		}else if (instruction[0].compare("ADD") == 0){
			add(registers, &instruction);
			i++;
		}else if (instruction[0].compare("NAND") == 0){
			nand(registers, &instruction);
			i++;
		}else if (instruction[0].compare("JMP") == 0){
			i = jmp(registers, &instruction);
		}else if (instruction[0].compare("JZ") == 0){
			i = jz(registers, &instruction,i);
		}else if (instruction[0].compare("DEC") == 0){
			dec(registers, &instruction);
			i++;
		}else if (instruction[0].compare("INC") == 0){
			inc(registers, &instruction);
			i++;
		}else{
			i++;
		}
	}

	std::cout << "-----Instructions End-----" << std::endl;

	std::cout << "-----Start Register States-----" << std::endl;

	for(int i = 0; i<registers.size(); i++) {
		//Print in format R0001 00001
		std::cout << "R"<< std::setw(3) << std::setfill('0') << i << " " <<  std::setw(3) << std::setfill('0') << std::to_string(registers[i]) << " ";
		if(i%10 == 0){ //Limit output width
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << "-----End Register States-----" << std::endl;
	return 0;
}
