#ifndef CPU_H
#define CPU_H

const int NUM_REGISTERS = 256;

class Cpu {
	public:
		std::array<uint8_t,NUM_REGISTERS> registers;
		Cpu(std::array<uint8_t,NUM_REGISTERS> &registers);
		std::array<std::string,4> getInstruction(std::string line);
		void nand(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void add(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void addi(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void sub(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void subi(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		int jmp(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		int jz(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int jl(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int eq(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int jg(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		void dec(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void inc(std::array<uint8_t,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
};
#endif
