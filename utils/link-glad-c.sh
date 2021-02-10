#! /bin/bash

printf "Reading \"glad-c-location.txt\"...\n"
declare -a lines

while IFS= read -r line; do
    lines+=("${line}") 
done < ./glad-c-location.txt

glad_c=${lines[0]}

printf "Linking \"%s\" to \"./glad.c\"...\n" "${glad_c}"
ln -s ${glad_c} ./glad.c

printf "Done.\n"
