/*
 * RECONSTRUCCION de crackme_level2 a partir de ingenieria inversa
 * (objdump + GDB). NO es el codigo fuente original del docente.
 *
 * Hallazgos:
 *  - validate_key: longitud 17; para cada i, (key[i] ^ k[i & 3]) debe ser igual a expected[i].
 *  - reveal_flag decodifica 21 bytes con XOR de clave 0x37.
 *  - Codigos de retorno: 1 = argumentos incorrectos, 3 = licencia invalida.
 */
#include <stdio.h>
#include <string.h>

static const unsigned char k[4] = { 0x23, 0x51, 0x17, 0x6a };
static const unsigned char expected[17] = {
    0x65, 0x15, 0x44, 0x23, 0x0e, 0x03, 0x52, 0x3c, 0x66,
    0x03, 0x44, 0x2f, 0x0e, 0x63, 0x27, 0x58, 0x15
};

static int validate_key(const char *candidate) {
    size_t len = 0x11;
    if (strlen(candidate) != len)
        return 0;
    int diff = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char t = k[i & 3] ^ (unsigned char)candidate[i];
        diff |= t ^ expected[i];
    }
    return diff == 0;
}

static void reveal_flag(void) {
    unsigned char enc[21] = { 0x71, 0x7b, 0x76, 0x70, 0x4c, 0x50, 0x5f, 0x5e, 0x53, 0x45, 0x56, 0x68, 0x47, 0x5b, 0x42, 0x44, 0x68, 0x50, 0x53, 0x55, 0x4a };
    unsigned char key = 0x37;
    for (size_t i = 0; i < sizeof(enc); i++)
        putchar(enc[i] ^ key);
    putchar('\n');
}

int main(int argc, char **argv) {
    puts("=== FDSI CrackMe Level 2 ===");
    puts("Hint: static + dynamic analysis.");
    if (argc != 2) {
        printf("Uso: %s <license-key>\n", argv[0]);
        return 1;
    }
    if (validate_key(argv[1])) {
        puts("License accepted.");
        reveal_flag();
        return 0;
    }
    puts("Invalid license.");
    return 3;
}