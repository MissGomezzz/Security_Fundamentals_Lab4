# Confirmación dinámica con GDB

Script: `set disassembly-flavor intel`, `break validate_key`, `run <clave>`, `info registers rdi`, `x/s $rdi`, `finish`, `info registers rax`.

| Clave | RDI en la entrada (1er arg) | Valor devuelto (RAX) |
|---|---|---|
| `AAAA` | `"AAAA"` | `0` → "Invalid license." |
| `FDSI-REVERSE-2026` | `"FDSI-REVERSE-2026"` | `1` → "License accepted." |

Conclusión: en x86-64 System V el primer argumento va en RDI y el retorno en RAX. GDB confirma que `validate_key` recibe nuestra cadena y que su retorno decide el camino, algo que el análisis estático solo permitía inferir.
