/*
 * RECONSTRUCCION de crackme_level1 a partir de ingenieria inversa
 * (strings + objdump). NO es el codigo fuente original del docente.
 *
 * Hallazgos:
 *  - main compara argv[1] con "REDTEAM-101" usando strcmp.
 *  - print_flag decodifica 26 bytes con XOR de clave 0x5a y los imprime con putchar.
 */
#include <stdio.h>
#include <string.h>

static void print_flag(void) {
    /* bytes recuperados de los movabs de print_flag (little-endian) */
    unsigned char enc[26] = { 0x1c, 0x16, 0x1b, 0x1d, 0x21, 0x29, 0x2e, 0x28, 0x33, 0x34, 0x3d, 0x29, 0x05, 0x3b, 0x28, 0x3f, 0x05, 0x3f, 0x2c, 0x33, 0x3e, 0x3f, 0x34, 0x39, 0x3f, 0x27 };
    unsigned char key = 0x5a;
    for (size_t i = 0; i < sizeof(enc); i++)
        putchar(enc[i] ^ key);
    putchar('\n');
}

int main(int argc, char **argv) {
    const char *password = "REDTEAM-101";
    puts("=== FDSI CrackMe Level 1 ===");
    if (argc != 2) {
        printf("Uso: %s <password>\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], password) == 0) {
        puts("Access granted.");
        print_flag();
        return 0;
    }
    puts("Access denied.");
    return 2;
}