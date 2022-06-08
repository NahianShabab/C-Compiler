flex -o $1.c $1.l
g++ $1.c -lfl -o $1.out
rm $1.c
./$1.out input.txt
rm $1.out