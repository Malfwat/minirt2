#!/bin/bash
# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   run_tests.sh                                       :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: admoufle <admoufle@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2026/11/22 23:55:00 by admoufle          #+#    #+#             #
#   Updated: 2026/11/22 23:55:00 by admoufle         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #
#
# Compile et lance toute la batterie de tests, sans fenetre et sans serveur X.
#
#   ./tests/run_tests.sh              tous les tests
#   ASAN=1 ./tests/run_tests.sh       avec AddressSanitizer et detecteur de fuites
#
# Code de sortie : 0 si tout passe, 1 des qu'un test echoue.

set -u

ROOT=$(cd "$(dirname "$0")/.." && pwd)
cd "$ROOT" || exit 1

CC=${CC:-cc}
INC="-Iincludes -Iminilibx-linux"
CFLAGS="-O1 -g -w"
[ "${ASAN:-0}" = "1" ] && CFLAGS="$CFLAGS -fsanitize=address"

TMP=$(mktemp -d "${TMPDIR:-/tmp}/minirt_tests.XXXXXX")
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$TMP/objM" "$TMP/objB" "$TMP/bin"

echo "construction des objets..."

if ! $CC $INC $CFLAGS -c tests/mlx_stub.c -o "$TMP/mlx_stub.o"; then
	echo "echec de compilation du stub MiniLibX"
	exit 1
fi

ALL=$(find srcs -name '*.c' | sort)
SET_M=$(echo "$ALL" | grep -v '_bonus\.c$' | grep -v 'srcs/main\.c$')
SET_B=$(echo "$ALL" | grep -v 'srcs/main\.c$' | grep -v 'srcs/main_bonus\.c$' \
	| grep -vE 'srcs/parsing/loop\.c$|srcs/parsing/parse_line\.c$|srcs/rendering/render\.c$|srcs/rendering/rt_mlx_loop\.c$')

build_set()
{
	local dir=$1
	local list=$2
	local file
	local obj

	for file in $list; do
		obj="$dir/$(echo "$file" | tr '/' '_' | sed 's/\.c$/.o/')"
		if ! $CC $INC $CFLAGS -c "$file" -o "$obj"; then
			echo "echec de compilation : $file"
			return 1
		fi
	done
	return 0
}

build_set "$TMP/objM" "$SET_M" || exit 1
build_set "$TMP/objB" "$SET_B" || exit 1

pass=0
fail=0
link_ko=0

for test_file in tests/test_*.c; do
	name=$(basename "$test_file" .c)
	bin="$TMP/bin/$name"
	linked=""

	for set in M B; do
		if $CC $INC $CFLAGS "$test_file" "$TMP"/obj$set/*.o "$TMP/mlx_stub.o" \
			-o "$bin" -lm -lpthread 2>/dev/null; then
			linked=$set
			break
		fi
	done

	if [ -z "$linked" ]; then
		printf '%-26s LIEN IMPOSSIBLE\n' "$name"
		link_ko=$((link_ko + 1))
		continue
	fi

	output=$(timeout 120 "$bin" 2>&1)
	code=$?
	summary=$(echo "$output" | tail -1)

	if [ "$code" -eq 0 ]; then
		printf '%-26s ok      %s\n' "$name" "$summary"
		pass=$((pass + 1))
	else
		printf '%-26s ECHEC   code=%d  %s\n' "$name" "$code" "$summary"
		echo "$output" | sed 's/^/    /'
		fail=$((fail + 1))
	fi
done

echo "-------------------------------------------------------"
echo "tests: $((pass + fail + link_ko))   ok: $pass   echecs: $fail   liens impossibles: $link_ko"

if [ "$fail" -ne 0 ] || [ "$link_ko" -ne 0 ]; then
	exit 1
fi
exit 0
