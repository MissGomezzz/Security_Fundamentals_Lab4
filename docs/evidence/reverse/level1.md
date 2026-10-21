# Nivel 1 — Strings are evidence

## Observación
- `./crackme_level1` sin argumentos: imprime el uso (`Uso: ./crackme_level1 <password>`), rc=1.
- `./crackme_level1 prueba`: `Access denied.`, rc=2.

## Hipótesis
El programa compara el argumento con una contraseña embebida. Si está en texto plano, `strings` la mostrará.

## Evidencia
- `strings -n 5 crackme_level1` muestra `REDTEAM-101` junto a `strcmp`, `Access granted.` y `Access denied.`.
- `objdump -d -M intel crackme_level1` (función `main`):
  - `lea rax,[rip+...]` carga la cadena secreta en `[rbp-0x8]`
  - `call strcmp@plt` compara `argv[1]` con ella
  - `test eax,eax` / `jne` → si es 0 llama a `print_flag`, si no imprime "Access denied."

## Resultado
`./crackme_level1 REDTEAM-101` → `Access granted.` → **FLAG{strings_are_evidence}**

## Por qué strings revela secretos
Una cadena constante compilada vive en `.rodata` del ELF en texto plano; `strings` extrae toda secuencia imprimible, no hace falta ejecutar nada.
