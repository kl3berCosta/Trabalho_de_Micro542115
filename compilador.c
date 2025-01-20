#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* assembly_to_binary(const char* instruction) {
    if (strcmp(instruction, "MOV") == 0) {
        return "00000000";
    } else if (strcmp(instruction, "ADD") == 0) {
        return "00000001";
    } else if (strcmp(instruction, "SUB") == 0) {
        return "00000010";
    } else if (strcmp(instruction, "MUL") == 0) {
        return "00000011";
    } else if (strcmp(instruction, "DIV") == 0) {
        return "00000100";
    } else if (strcmp(instruction, "JMP") == 0) {
        return "00000101";
    } else if (strcmp(instruction, "NOP") == 0) {
        return "00000110";
    } else if (strcmp(instruction, "HALT") == 0) {
        return "00000111";
    } else if (strcmp(instruction, "IN") == 0) {
        return "00001000";
    } else if (strcmp(instruction, "OUT") == 0) {
        return "00001001";
    } else if (strcmp(instruction, "CMP") == 0) {
        return "00001010";
    } else if (strcmp(instruction, "INT") == 0) {
        return "00001011";
    } else if (strcmp(instruction, "JZ") == 0) {
        return "00001100";
    } else if (strcmp(instruction, "JNZ") == 0) {
        return "00001101";
    } else if (strcmp(instruction, "FUNC_CALL") == 0) {
        return "00001110";
    } else if (strcmp(instruction, "FUNC_RETURN") == 0) {
        return "00001111";
    } else if (strcmp(instruction, "NAND") == 0) {
        return "00010000";
    } else if (strcmp(instruction, "NOR") == 0) {
        return "00010001";
    } else if (strcmp(instruction, "XNOR") == 0) {
        return "00010010";
    } else {
        return NULL;
    }
}

void int_to_binary(int num, char* bin_str, int len) {
    for (int i = len - 1; i >= 0; i--) {
        bin_str[i] = (num & 1) ? '1' : '0';
        num >>= 1;
    }
    bin_str[len] = '\0';
}

int main() {
    FILE *inputFile, *outputFile;
    char line[256];
    char bin_str[33];

    inputFile = fopen("instructions.txt", "r");
    if (inputFile == NULL) {
        perror("CRIE UM ARQUIVO COM O NOME instructions.txt");
        return 1;
    }

    outputFile = fopen("instructions.bin", "wb");
    if (outputFile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(inputFile);
        return 1;
    }

    while (fgets(line, sizeof(line), inputFile)) {
        line[strcspn(line, "\n")] = 0;

        if (line[0] == '\0' || line[0] == ';') {
            continue;
        }

        char* endptr;
        long num = strtol(line, &endptr, 10);

        if (*endptr == '\0') {
            int_to_binary(num, bin_str, 32);
            unsigned char opcode = strtol(bin_str, NULL, 2);
            fwrite(&opcode, sizeof(unsigned char), 1, outputFile);
        } else {
            const char* binary = assembly_to_binary(line);
            if (binary != NULL) {
                unsigned char opcode = strtol(binary, NULL, 2);
                fwrite(&opcode, sizeof(unsigned char), 1, outputFile);
            } else {
                fprintf(stderr, "Erro: Instrução inválida '%s' encontrada no arquivo.\n", line);
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Conversão concluída. O arquivo 'instructions.bin' foi criado.\n");

    return 0;
}
