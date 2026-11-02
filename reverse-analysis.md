# Reverse Engineering — Análisis

Ver `docs/evidence/reverse/` (baseline, level1, level2, gdb, stripped).

## Preguntas de análisis (borrador)
1. Sin ejecutar: cadenas, símbolos, arquitectura, mensajes y, en el nivel 1, la contraseña.
2. Una contraseña como string compilado la expone a cualquiera con `strings`.
3. En el stripped desaparecen la tabla de símbolos (nombres de funciones y variables); la lógica es idéntica.
4. Ghidra da decompilación, renombrado, referencias cruzadas y navegación; objdump solo ensamblador lineal.
5. GDB confirmó los valores reales de RDI/RAX y el flujo en ejecución.
6. Burp analiza tráfico HTTP, no binarios.
7. Controles: no embeber secretos, secret scanning, revisión de código, validación en servidor, hashes salados/KDF, gestores de secretos.
