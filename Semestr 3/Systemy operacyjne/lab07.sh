#!/bin/bash

folder="/sys/module"

if [ $# -eq 0 ]
then
	>&2 echo "Brak parametrow"
	exit 1
fi

# Funkcja do wypisywania w kolumnach
wypisz() {
    printf "%-20s %-2s %-s\n" "$1" "$2" "$3"
}

while getopts "lb" par; do
    case $par in
        l)
            for modul in "$folder"/*/
            do
                nazwaModulu=$(basename "$modul")

                if [ -e "$modul/refcnt" ]
                then
                    holdersFolder="$modul/holders"

		    if [ -d "$holdersFolder" ]
		    then
                        liczba=$(find "$holdersFolder" -mindepth 1 | wc -l)
                        nazwy=$(find "$holdersFolder" -mindepth 1 -exec basename {} \; | sort | paste -sd, -)
		    fi

                    if (( liczba > 0 ))
                    then
                        wypisz "$nazwaModulu" "$liczba" "$nazwy"
                    else
                        wypisz "$nazwaModulu" "0" ""
                    fi
            	fi
            done
            ;;
        b)
	    for modul in "$folder"/*/
            do
                nazwaModulu=$(basename "$modul")

                if [ ! -e "$modul/refcnt" ]
		then
                    parametersFolder="$modul/parameters"

		    if [ -d "$parametersFolder" ]
		    then
                        liczba=$(find "$parametersFolder" -mindepth 1 | wc -l)
                        nazwy=$(find "$parametersFolder" -mindepth 1 -exec basename {} \; | sort | paste -sd, -)
		    fi

                    if (( liczba > 0 ))
                    then
                        wypisz "$nazwaModulu" "$liczba" "$nazwy"
                    else
                        wypisz "$nazwaModulu" "0" ""
                    fi
                fi

            done
	    ;;
        \?)
            # Zly parametr
            >&2 echo "Zly parametr: -$OPTARG"
            exit 1
            ;;
    esac
done
