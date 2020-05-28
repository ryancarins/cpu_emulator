#include <fstream>
#include <iostream>
#include <vector>


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
	std::vector<std::string> instructions = load_instruction("instruct.txt");
	for(int i = 0; i<instructions.size(); i++){
		std::cout << instructions.at(i) << std::endl;
	}
}

