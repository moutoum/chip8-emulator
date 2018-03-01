#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define MEMORY_LOCATION        0x1000 /* 4096 */
#define CHIP8_INTERPRETER_SIZE 0x200  /*  512 */
#define NREGISTERS             0x10   /*   16 */
#define STACK_SIZE             0x10   /*   16 */
#define GPU_WIDTH							 0x40   /*   64 */
#define GPU_HEIGHT             0x20   /*   32 */

typedef union Register {
	struct {
		uint8_t h : 4;
		uint8_t l : 4;
	};
	uint8_t r;
} chip8Register;

typedef struct CPU {
	chip8Register V[NREGISTERS];
	uint16_t I;
	uint16_t stack[STACK_SIZE];

	CPU();
} CPU;

typedef uint8_t GPU[GPU_WIDTH * GPU_HEIGHT];
typedef uint8_t RAM[MEMORY_LOCATION];

class Chip8 {
private:
	CPU cpu;
	GPU gpu;
	RAM ram;

public:
	Chip8();
	GPU const &getGraphics() const;
};

#endif
