#!/bin/bash

output_file="output.txt"

# Clear the file if it already exists
> $output_file

first_N=1500
second_N=2000

echo -e "          N = $first_N                                 N = $second_N\n" >> $output_file
echo -e "          Bez transponowania | Z transponowaniem | Bez transponowania | Z transponowaniem\n" >> $output_file

for i in {1..6}; do
	echo -n "Watki: $i: " >> $output_file
	
    result=$(./lab01-bez-transponowania $i $first_N)
    printf "%18s   " "$result" >> $output_file
    echo -e "$first_N | $i | bez transponowania | $result"
    
    result=$(./lab01-z-transponowaniem $i $first_N)
    printf "%17s   " "$result" >> $output_file
    echo -e "$first_N | $i | z transponowaniem  | $result"
    
    result=$(./lab01-bez-transponowania $i $second_N)
    printf "%18s   " "$result" >> $output_file
    echo -e "$second_N | $i | bez transponowania | $result"
    
    result=$(./lab01-z-transponowaniem $i $second_N)
    printf "%17s\n" "$result" >> $output_file
    echo -e "$second_N | $i | z transponowaniem  | $result"
done

echo "Wyniki zapisane do: $output_file"
