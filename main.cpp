#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>


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
	while(std::getline(string_stream, curr, delimiter) && i<4){
		instruction[i] = curr;
		i++;
	}
	return instruction;
}

int main(){
	//TODO make this an argument
	std::vector<std::string> instructions = load_instruction("instruct.txt");

	//Memory for CPU I know that RiSC-16 is signed but I don't care
	int unsigned registers[64];


	for(int i = 0; i<instructions.size(); i++){
		std::array<std::string,4> instruction = getInstruction(instructions.at(i));

		if(instruction[0].compare("NOP") == 0){
			std::cout << "NOP" << std::endl;
		}else{
			std::cout << "Not NOP" << std::endl;
		}
	}
}
