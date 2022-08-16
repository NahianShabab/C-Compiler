yacc -d -y 1805031.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex 1805031.l
echo 'Generated the scanner C file'
g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'

g++ -w -c -o SymbolInfo.o SymbolInfo.cpp
g++ -w -c -o Scopetable.o ScopeTable.cpp
g++ -w -c -o SymbolTable.o SymbolTable.cpp

echo 'Generated the other object files'

g++ *.o -lfl -o 1805031

echo 'All ready, running'
./1805031 $1