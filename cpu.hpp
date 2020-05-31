#ifndef CPU_H
#define CPU_H

const int NUM_REGISTERS = 256;
#define REG_TYPE uint16_t

class Cpu {
	public:
		std::array<REG_TYPE,NUM_REGISTERS> registers;
		Cpu(std::array<REG_TYPE,NUM_REGISTERS> &registers);
		std::array<std::string,4> getInstruction(std::string line);
		void nand(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void add(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void addi(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void sub(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void subi(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		int jmp(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		int jz(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int jl(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int eq(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		int jg(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction, int i);
		void dec(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
		void inc(std::array<REG_TYPE,NUM_REGISTERS> &registers, std::array<std::string,4> *instruction);
};
#endif
