# Boss — binario stripped

- `nm crackme_level2_stripped` → `no symbols`: desaparecieron los nombres (`validate_key`, `reveal_flag`, `main`, `k.1`, `expected.0`). Las llamadas a libc siguen visibles por el PLT y las cadenas siguen en `.rodata`.
- Cómo se re-encontró la lógica: `_start` pasa la dirección de `main` a `__libc_start_main` (en RDI); desde `main` se sigue el `call` que precede al mensaje "License accepted."; esa función es la misma que `validate_key` (misma secuencia: `strlen`, `cmp 0x11`, bucle XOR con `and 3`).
- Misma clave y misma FLAG que `crackme_level2`.
