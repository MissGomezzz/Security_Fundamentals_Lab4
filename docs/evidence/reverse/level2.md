# Nivel 2 — Reconstrucción de la validación

## Hallazgos (Ghidra / objdump)
- `main` llama a `validate_key(argv[1])`; si devuelve 1 llama a `reveal_flag`.
- Longitud esperada: `0x11` = **17** bytes (comparada contra `strlen`).
- Arreglo `k` (4 bytes, `.rodata` 0x40208b): `23 51 17 6a`
- Arreglo `expected` (17 bytes, `.rodata` 0x402090): `65 15 44 23 0e 03 52 3c 66 03 44 2f 0e 63 27 58 15`
- Transformación: XOR byte a byte con `k[i & 3]` (clave cíclica de 4 bytes).

## Pseudocódigo propio
```
validate_key(key):
    if strlen(key) != 17: return 0
    diff = 0
    for i in 0..16:
        t = key[i] XOR k[i % 4]
        diff |= t XOR expected[i]
    return (diff == 0)
```

## Inversión
XOR es reversible: `key[i] = expected[i] XOR k[i % 4]`.

## Resultado
Clave: `FDSI-REVERSE-2026` → `License accepted.` → **FLAG{ghidra_plus_gdb}**

## Nota de diseño
Comparar con `|=` evita salir temprano en el primer byte distinto (comparación de tiempo casi constante), pero la clave sigue siendo recuperable porque `k` y `expected` están en el binario.

(Pendiente: agregar capturas de Ghidra con renombres en `screenshots/`.)
