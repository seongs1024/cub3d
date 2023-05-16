#!/bin/sh
CASE_BG="\033[46;30m"
SUCCESS_BG="\033[42;1;37m"
FAIL_BG="\033[41;5;11m"
CLEAR_COLOR="\033[m"

EXEC=./cub3D
MAPS=(./maps/e1-invalid-char-in-map.cub
	./maps/e2-no-wall.cub
	./maps/e3-no-wall2.cub
	./maps/e4-empty.cub
	./maps/e5-more-player.cub
	./maps/e6-invalid-path.cub
	./maps/e7-invalid-path2.cub
	./maps/e8-color-float.cub
	./maps/e9-color-out-of-range.cub
	./maps/e10-color-2num.cub
	./maps/e11-lack-comp.cub
	./maps/e12-lack-comp2.cub
	./maps/e13-lack-comp3.cub
	./maps/e14-more-map.cub
	./maps/e15-empty-image.cub
)

for MAP in ${MAPS[@]}
do
	${EXEC} ${MAP}
	if [ $? ]
		then
			echo "${CASE_BG}MAP: "${MAP}"${SUCCESS_BG}-->PASS${CLEAR_COLOR}"
		else
			echo "${CASE_BG}MAP: "${MAP}"${FAIL_BG}-->FAIL${CLEAR_COLOR}"
	fi
done