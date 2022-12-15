// Implement the virtual CPU.

#include "cpu.h"
#include "mem.h"

static int calc(struct pcb_t *proc)
{
	return ((unsigned long)proc & 0UL);
}

static int alloc(struct pcb_t *proc, uint32_t size, uint32_t reg_index)
{
	addr_t addr = alloc_mem(size, proc);
	if (addr == 0)
	{
		return 1;
	}
	else
	{
		proc->regs[reg_index] = addr;
		return 0;
	}
}

static int free_data(struct pcb_t *proc, uint32_t reg_index)
{
	return free_mem(proc->regs[reg_index], proc);
}

static int read(
		struct pcb_t *proc, // Process executing the instruction
		uint32_t source,		// Index of source register
		uint32_t offset,		// Source address = [source] + [offset]
		uint32_t destination)
{ // Index of destination register

	BYTE data;
	if (read_mem(proc->regs[source] + offset, proc, &data))
	{
		proc->regs[destination] = data;
		return 0;
	}
	else
	{
		return 1;
	}
}

static int write(
		struct pcb_t *proc,		// Process executing the instruction
		BYTE data,						// Data to be wrttien into memory
		uint32_t destination, // Index of destination register
		uint32_t offset)
{ // Destination address =
	// [destination] + [offset]
	return write_mem(proc->regs[destination] + offset, proc, data);
}

int run(struct pcb_t *proc)
{
	/* Check if Program Counter point to the proper instruction */
	if (proc->pc >= proc->code->size)
	{
		return 1;
	}

	struct inst_t ins = proc->code->text[proc->pc];
	proc->pc++;
	int stat = 1;
	switch (ins.opcode)
	{
	case CALC:
		// do some calculation using the CPU. This instruction does not have argument.
		// thực hiện một số tính toán bằng cách sử dụng CPU
		stat = calc(proc);
		break;
	case ALLOC:
		// Allocate some chunk of bytes on the main memory (RAM). Instruction’s syntax:
		// Phân bổ một số byte trên bộ nhớ chính (RAM). Cú pháp: alloc [size] [reg]
		//trong đó `size` là số byte mà quá trình muốn phân bổ từ RAM và reg là số của thanh ghi sẽ lưu địa chỉ của byte đầu tiên của vùng bộ nhớ được cấp phát. Ví dụ, lệnh alloc 124 7 sẽ phân bổ 124 byte từ HĐH và địa chỉ của byte đầu tiên trong số đó 124 byte được lưu trữ tại thanh ghi #7.
		stat = alloc(proc, ins.arg_0, ins.arg_1);
		break;
	case FREE:
	//Free allocated memory: bộ nhớ đc cấp phát tự do. Syntax: free [reg]
	//where reg is the number of the register which holds the address of the first byte of the memory region to be deallocated.- trong đó reg là số register chứa địa chỉ của byte đầu tiên của vùng bộ nhớ được giải phóng.
		stat = free_data(proc, ins.arg_0);
		break;
	case READ:
	//Read a byte from memory. syntax: read [source] [offset] [destination]
	//The instruction reads one byte memory at the address which equal to the value of register source + offset and saves it to destination. For example, assume that the value of register #1 is 0x123 then the instruction read 1 20 2 will read one byte memory at the address of 0x123 + 14 (14 is 20 in hexadecimal) and save it to register #2.
	//Lệnh đọc một byte bộ nhớ tại address bằng với giá trị của register nguồn + offset và lưu nó vào đích. Ví dụ, giả sử rằng giá trị của register #1 là 0x123 thì lệnh đọc 1 20 2 sẽ đọc một byte bộ nhớ ở địa chỉ 0x123 + 14 (14 là 20 trong hệ thập lục phân) và lưu nó vào register #2.
		stat = read(proc, ins.arg_0, ins.arg_1, ins.arg_2);
		break;
	case WRITE:
		stat = write(proc, ins.arg_0, ins.arg_1, ins.arg_2);
		break;
	default:
		stat = 1;
	}
	return stat;
}
