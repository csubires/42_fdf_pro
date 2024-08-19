#!/bin/zsh

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csubires <csubires@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 10:37:58 by csubires          #+#    #+#              #
#    Updated: 2024/04/25 10:37:58 by csubires         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRECTORY="maps"
fdf_files=()

# Buscar archivos
while IFS= read -r -d '' file; do
	fdf_files+=("$file")
done < <(find "$DIRECTORY" -type f -name "*.fdf" -print0)


function mostrar_menu {
    echo "Available maps (fdf):"
	x=1;
    for i in "${fdf_files[@]}"; do
        echo "$((x++)). $(basename $i)"
    done
    echo "0. Salir"
}

while true; do
    mostrar_menu
    print -n "Seleccione un archivo por su número (o 0 para salir): "
	read choice

    if [[ $choice -ge 1 && $choice -le ${#fdf_files[@]} ]]; then
        selected_file=${fdf_files[$((choice-1))]}
        ./fdf "$selected_file"
    elif [[ $choice -eq 0 ]]; then
        echo "Saliendo..."
        break
    else
        echo "Opción no válida, por favor intente de nuevo."
    fi
done
