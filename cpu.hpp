#ifndef CPU_H
#define CPU_H

const int NUM_REGISTERS = 256;
#define REG_TYPE uint16_t //Must be unsigned for a sensible output

class Cpu {
	public:
		std::array<REG_TYPE,NUM_REGISTERS> registers;
		Cpu(std::array<REG_TYPE,NUM_REGISTERS> &registers);
		std::array<std::string,4> getInstruction(std::string line);
		void nand(std::array<std::string,4> *instruction);
		void add(std::array<std::string,4> *instruction);
		void addi(std::array<std::string,4> *instruction);
		void sub(std::array<std::string,4> *instruction);
		void subi(std::array<std::string,4> *instruction);
		int jmp(std::array<std::string,4> *instruction);
		int jz(std::array<std::string,4> *instruction, int i);
		int jl(std::array<std::string,4> *instruction, int i);
		int eq(std::array<std::string,4> *instruction, int i);
		int jg(std::array<std::string,4> *instruction, int i);
		void dec(std::array<std::string,4> *instruction);
		void inc(std::array<std::string,4> *instruction);
		void print_states();
};
#endif
