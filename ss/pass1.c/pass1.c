#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[10], operand[10], label[10], code[10], mnemonic[10];
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtbl.txt", "w");
    fp4 = fopen("out1.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) {
        perror("Error opening files");
        exit(1);
    }

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s", label);

            if (strcmp(opcode, "EQU") != 0) {
                fprintf(fp3, "\t%X\n", locctr);
            } else {
                fprintf(fp3, "\t%s\n", operand);
            }
        }

        fprintf(fp4, "%X\t", locctr);

        rewind(fp2);
        int found = 0;

        while (fscanf(fp2, "%s\t%s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * atoi(operand));
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                ++locctr;
            }
        }

        fprintf(fp4, "%s\t%s\t%s\n", label, opcode, operand);
        fflush(fp4);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }

    length = locctr - start;

    printf("The length of the code: %X\n", length);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
