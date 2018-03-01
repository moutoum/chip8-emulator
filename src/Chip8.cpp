#include "Chip8.hpp"
#include <cstring>
#include <iostream>

Chip8::Chip8() {
	memset(gpu, 0, sizeof(GPU));
	memset(ram, 0, sizeof(RAM));
}

GPU const &Chip8::getGraphics() const {
	return gpu;
}

CPU::CPU() {
	memset(V, 0, sizeof(V));
	memset(stack, 0, sizeof(stack));
}
