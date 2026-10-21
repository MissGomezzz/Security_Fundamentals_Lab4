#!/usr/bin/env bash
# Compila las reconstrucciones en C y compara salida y codigo de retorno con los binarios originales.
# Uso: tests/verify_reconstruccion.sh [directorio_binarios]   (requiere gcc)
set -u
BIN="${1:-bin}"; HERE="$(cd "$(dirname "$0")/.." && pwd)"; T="$(mktemp -d)"; fail=0
gcc -Wall -Wextra -o "$T/l1" "$HERE/src/crackme_level1_reconstruido.c" || exit 1
gcc -Wall -Wextra -o "$T/l2" "$HERE/src/crackme_level2_reconstruido.c" || exit 1
cmp_run(){ # nombre original reconstruido arg...
  local n="$1" o="$2" r="$3"; shift 3
  a=$(cd "$T"; "$o" "$@" 2>&1; echo "rc=$?" | sed "s#$o#X#") ; b=$("$r" "$@" 2>&1; echo "rc=$?")
  a=$(echo "$a" | sed -E 's#^Uso: .* <#Uso: X <#'); b=$(echo "$b" | sed -E 's#^Uso: .* <#Uso: X <#')
  [ "$a" = "$b" ] && echo "PASS  $n [$*]" || { echo "FAIL  $n [$*]"; fail=1; }
}
O1="$(cd "$BIN" && pwd)/crackme_level1"; O2="$(cd "$BIN" && pwd)/crackme_level2"
for a in "" x REDTEAM-101; do cmp_run L1 "$O1" "$T/l1" $a; done
for a in "" AAAA FDSI-REVERSE-2026 FDSI-REVERSE-2025; do cmp_run L2 "$O2" "$T/l2" $a; done
rm -rf "$T"; exit $fail