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

//Size is 4 because I'm implementing RiSC-16 instruction set so there will be
//a max of 4 parts i.e ADD RA, RB, RC https://user.eng.umd.edu/~blj/RiSC/RiSC-isa.pdf
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

void add(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t rc = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + registers[rc];
}


void addi(std::array<uint8_t,256> &registers, std::array<std::string,4> *instruction) {
	uint8_t ra = std::stoi(instruction->at(1));
	uint8_t rb = std::stoi(instruction->at(2));
	uint8_t imm = std::stoi(instruction->at(3));
	registers[ra] = registers[rb] + imm;
	std::cout << std::to_string(registers[ra]) << std::endl;
}

int main(){
	//TODO make this an argument
	std::vector<std::string> instructions = load_instruction("instruct.txt");

	//Registers for CPU I know that RiSC-16 is signed but I don't care
	std::array<uint8_t,256> registers;
	registers.fill(0);



	for(int i = 0; i<instructions.size(); i++){
		std::array<std::string,4> instruction = getInstruction(instructions.at(i));

		if(instruction[0].compare("ADDI") == 0){
			std::cout << "ADDI" << std::endl;
			addi(registers, &instruction);
		}
		else if (instruction[0].compare("ADD") == 0){
			std::cout << "ADD" << std::endl;
			add(registers, &instruction);
		}else{
			std::cout << "Not ADD" << std::endl;
		}
	}
	std::cout << "Register states" << std::endl;

	for(int i = 0; i<registers.size(); i++) {
		//Print in format R0001 00001
		std::cout << "R"<< std::setw(3) << std::setfill('0') << i << " " <<  std::setw(3) << std::setfill('0') << std::to_string(registers[i]) << " ";
		if(i%10 == 0){ //Limit output width
			std::cout << std::endl;
		}
	}
}
