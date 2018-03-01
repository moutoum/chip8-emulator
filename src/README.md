# Virtual Machine Description

## Memory

CHIP-8 was most commonly implemented on 4K systems, such as the Cosmac VIP and the Telmac 1800. These machines had `4096 (0x1000) memory locations`, all of which are 8 bits (a byte) which is where the term CHIP-8 originated. However, the CHIP-8 interpreter itself occupies the first 512 bytes of the memory space on these machines. For this reason, most programs written for the original system begin at memory location 512 (0x200) and do not access any of the memory below the location 512 (0x200). The uppermost 256 bytes (0xF00-0xFFF) are reserved for display refresh, and the 96 bytes below that (0xEA0-0xEFF) were reserved for call stack, internal use, and other variables.

In modern CHIP-8 implementations, where the interpreter is running natively outside the 4K memory space, there is no need for any of the lower 512 bytes memory space to be used, but it is common to store font data in those lower 512 bytes (0x000-0x200).

## Registers
CHIP-8 has 16 8-bit data registers named from V0 to VF. The VF register doubles as a flag for some instructions, thus it should be avoided. In addition operation VF is for carry flag. While in subtraction, it is the "no borrow" flag. In the draw instruction the VF is set upon pixel collision.

The address register, which is named I, is 16 bits wide and is used with several opcodes that involve memory operations.

## The stack
The stack is only used to store return addresses when subroutines are called. The original 1802 version allocated 48 bytes for up to 24 levels of nesting; modern implementations normally have at least 16 levels.

## Timers
CHIP-8 has two timers. They both count down at 60 hertz, until they reach 0.

Delay timer: This timer is intended to be used for timing the events of games. Its value can be set and read.
Sound timer: This timer is used for sound effects. When its value is nonzero, a beeping sound is made.

## Input
Input is done with a hex keyboard that has 16 keys which range from 0 to F. The '8', '4', '6', and '2' keys are typically used for directional input. Three opcodes are used to detect input. One skips an instruction if a specific key is pressed, while another does the same if a specific key is not pressed. The third waits for a key press, and then stores it in one of the data registers.

## Graphics and sound
Original CHIP-8 Display resolution is 64×32 pixels, and color is monochrome. Graphics are drawn to the screen solely by drawing sprites, which are 8 pixels wide and may be from 1 to 15 pixels in height. Sprite pixels are XOR'd with corresponding screen pixels. In other words, sprite pixels that are set flip the color of the corresponding screen pixel, while unset sprite pixels do nothing. The carry flag (VF) is set to 1 if any screen pixels are flipped from set to unset when a sprite is drawn and set to 0 otherwise. This is used for collision detection.

As previously described, a beeping sound is played when the value of the sound timer is nonzero.

## Opcode table
CHIP-8 has 35 opcodes, which are all two bytes long and stored big-endian. The opcodes are listed below, in hexadecimal and with the following symbols:

* NNN: address
* NN: 8-bit constant
* N: 4-bit constant
* X and Y: 4-bit register identifier
* PC : Program Counter
* I : 16bit register (For memory address) (Similar to void pointer)

Opcode | Type | C Pseudo | Explanation
:-----:|------|----------|------------
0NNN   | Call |          | Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
00E0   | Display | disp_clear() | Clears the screen.
00EE   | Flow |	return;	 | Returns from a subroutine.
1NNN   | Flow	| goto NNN;| Jumps to address NNN.
2NNN   | Flow	| *(0xNNN)() | Calls subroutine at NNN.
3XNN   | Cond	| if(Vx==NN) | Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
4XNN   | Cond	| if(Vx!=NN) | Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
5XY0	Cond	if(Vx==Vy)	Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
6XNN	Const	Vx = NN	Sets VX to NN.
7XNN	Const	Vx += NN	Adds NN to VX. (Carry flag is not changed)
8XY0	Assign	Vx=Vy	Sets VX to the value of VY.
8XY1	BitOp	Vx=Vx|Vy	Sets VX to VX or VY. (Bitwise OR operation)
8XY2	BitOp	Vx=Vx&Vy	Sets VX to VX and VY. (Bitwise AND operation)
8XY3	BitOp	Vx=Vx^Vy	Sets VX to VX xor VY.
8XY4	Math	Vx += Vy	Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
8XY5	Math	Vx -= Vy	VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
8XY6	BitOp	Vx=Vy=Vy>>1	Shifts VY right by one and copies the result to VX. VF is set to the value of the least significant bit of VY before the shift.[2]
8XY7	Math	Vx=Vy-Vx	Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
8XYE	BitOp	Vx=Vy=Vy<<1	Shifts VY left by one and copies the result to VX. VF is set to the value of the most significant bit of VY before the shift.[2]
9XY0	Cond	if(Vx!=Vy)	Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
ANNN	MEM	I = NNN	Sets I to the address NNN.
BNNN	Flow	PC=V0+NNN	Jumps to the address NNN plus V0.
CXNN	Rand	Vx=rand()&NN	Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
DXYN	Disp	draw(Vx,Vy,N)	Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
EX9E	KeyOp	if(key()==Vx)	Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
EXA1	KeyOp	if(key()!=Vx)	Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
FX07	Timer	Vx = get_delay()	Sets VX to the value of the delay timer.
FX0A	KeyOp	Vx = get_key()	A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
FX15	Timer	delay_timer(Vx)	Sets the delay timer to VX.
FX18	Sound	sound_timer(Vx)	Sets the sound timer to VX.
FX1E	MEM	I +=Vx	Adds VX to I.[3]
FX29	MEM	I=sprite_addr[Vx]	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
FX33	BCD	set_BCD(Vx);
*(I+0)=BCD(3);

*(I+1)=BCD(2);

*(I+2)=BCD(1);

Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
FX55	MEM	reg_dump(Vx,&I)	Stores V0 to VX (including VX) in memory starting at address I. I is increased by 1 for each value written.
FX65	MEM	reg_load(Vx,&I)	Fills V0 to VX (including VX) with values from memory starting at address I. I is increased by 1 for each value written.
