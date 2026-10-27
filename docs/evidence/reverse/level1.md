# Nivel 1 — Strings are evidence

## 1. Observación inicial
- `./crackme_level1` sin argumentos imprime el banner y `Uso: ./crackme_level1 <password>`. Código de retorno 1.
- `./crackme_level1 prueba` imprime `Access denied.`. Código de retorno 2.
- El programa espera exactamente un argumento y lo valida contra algo interno.

## 2. Hipótesis
El programa compara el argumento con una contraseña fija guardada en el binario. Si está en texto plano,
`strings` debería mostrarla cerca de los mensajes de éxito y fallo y de la función de comparación.

## 3. Evidencia
- `strings -n 5 crackme_level1` muestra `REDTEAM-101` junto a `strcmp`, `Access granted.` y `Access denied.`.
  Es la única cadena con aspecto de contraseña.
- `strings ... | grep -i FLAG` solo devuelve `print_flag`, el nombre de una función (visible porque el binario no está stripped). El texto `FLAG{...}` no aparece: la FLAG no está en texto plano, solo la contraseña.
- `objdump -d -M intel crackme_level1` (función `main`):
  - carga la dirección de la cadena `REDTEAM-101` en una variable local,
  - llama a `strcmp@plt` con `argv[1]` y esa cadena,
  - hace `test eax,eax` y `jne`: si la comparación da 0 llama a `print_flag`; si no, imprime `Access denied.`.
- Capturas: `screenshots/03-level1-strings.png` y `screenshots/04-level1-objdump-strcmp.png`.

## 4. Resultado
Comando: `./crackme_level1 REDTEAM-101`

Salida: `Access granted.` y la FLAG **FLAG{strings_are_evidence}** (código de retorno 0).
Captura: `screenshots/05-level1-flag.png`.

## 5. ¿Por qué strings puede revelar secretos?
Las cadenas constantes de un programa en C se guardan tal cual en la sección `.rodata` del ELF.
`strings` recorre el archivo y extrae toda secuencia de caracteres imprimibles, sin ejecutar nada.
Cualquier secreto compilado como literal (contraseñas, claves, tokens) queda legible para quien tenga el binario.
Esto es un diseño inseguro: ocultar un secreto en el ejecutable no es protegerlo.
