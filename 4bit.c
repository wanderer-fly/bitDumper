#include <stdio.h>

// CPU指令集
enum Instruction {
    ADD = 0b0000,
    SUB = 0b0001,
    AND = 0b0010,
    OR  = 0b0011,
    XOR = 0b0100,
    MOV = 0b0101,
    LDA = 0b0110,
    STA = 0b0111,
    JMP = 0b1000,
    JZ  = 0b1001,
    JC  = 0b1010,
    HLT = 0b1011,
    INP = 0b1100,
    OUT = 0b1101
};

// CPU结构体
struct CPU {
    unsigned char PC; // 计数器
    unsigned char IR; // 寄存器
    unsigned char A;  // 累加器
    unsigned char B;  // 寄存器B
    unsigned char Z;  // 零标志
    unsigned char C;  // 进位标志
    unsigned char memory[16]; // 内存
};

// 初始化
void init(struct CPU* cpu) {
    cpu->PC = 0;
    cpu->IR = 0;
    cpu->A  = 0;
    cpu->B  = 0;
    cpu->Z  = 0;
    cpu->C  = 0;

    // 内存初始化
    for (int i = 0; i < 16; i++) {
        cpu->memory[i] = 0;
    }
}

void execute(struct CPU* cpu) {
    switch (cpu -> IR) {
        case ADD: cpu->A += cpu->B; break;
        case SUB: cpu->A -= cpu->B; break;
        case AND: cpu->A &= cpu->B; break;
        case  OR: cpu->A |= cpu->B; break;
        case XOR: cpu->A ^= cpu->B; break;
        case MOV: cpu->B =  cpu->A; break;
        case LDA: cpu->A = cpu->memory[cpu->B]; break;
        case STA: cpu->memory[cpu->B] = cpu->A; break;
        case JMP: cpu->PC = cpu->B; break;
        case  JZ:
                  if (cpu->Z) {
                      cpu->PC = cpu -> B;
                  } break;
        case JC:
                  if (cpu->C) {
                      cpu->PC = cpu->B;
                  } break;
        case HLT: printf("CPU Halted\n"); break;
        case INP: printf("Input: ");
                  scanf("%hhu", &cpu->A);
                  break;
        case OUT: printf("Output %d\n", cpu->A); break;
        default: printf("Bad instruction %x\n", cpu->IR);  cpu->IR = HLT; break;
    }
}

void run(struct CPU* cpu) {
    while (cpu->IR != HLT) {
        // 取指令
        cpu->IR = cpu->memory[cpu->PC];

        // 执行指令
        execute(cpu);

        cpu -> PC++; // 更新程序计数器

        // 打印状态
        printf("    PC: %d, A: %d, B: %d, Z: %d, C: %d\n", cpu->PC, cpu->A, cpu->B, cpu->Z, cpu->C);

        // 打印内存状态
        printf("    Memory: ");
        for (int i = 0; i < 16; i++) {
            printf("%d ", cpu->memory[i]);
        }
        printf("\n");
    }
}

int main() {
    struct CPU cpu;
    init(&cpu); // 初始化CPU

    // 设置程序
    cpu.memory[0] = INP;         // 输入第一个数到 A
    cpu.memory[1] = MOV;     // 存储第一个数到内存位置0
    cpu.memory[2] = INP;         // 输入第二个数到 A
    cpu.memory[3] = ADD;     // 存储第二个数到内存位置1
    cpu.memory[4] = OUT;     // 加上内存位置0的数
    cpu.memory[5] = HLT;         // Halt


    run(&cpu);

    return 0;
}
