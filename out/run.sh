echo "Compiling lexer..."
flex -o lexer.yy.cpp -l lexer.l

echo "Compiling parser..."
bison -o parser.cpp -vd parser.y

echo "Building..."
g++ -o main parser.cpp lexer.yy.cpp main.cpp -lm -ll

echo "Running..."
./main < test.c
