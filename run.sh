
./clean.sh

echo "Compiling lexer..."
flex -o out/lexer.yy.cpp -l src/lexer.l

echo "Compiling parser..."
bison -o out/parser.cpp -vd src/parser.y

echo "Building..."
#g++ -stdlib=libc++ -std=c++11 `llvm-config --system-libs core jit native --cxxflags` out/parser.cpp out/lexer.yy.cpp src/main.cpp

g++ -o ./out/main -stdlib=libc++ -std=c++11 -Wno-deprecated \
    `llvm-config --cppflags --system-libs --ldflags --libs`  -I/usr/local/opt/llvm/include \
    -L/usr/local/opt/llvm/lib -lllvm out/parser.cpp out/lexer.yy.cpp src/main.cpp


if [ $# -eq 0 ]
  then
    echo "Running...";
    ./out/main < src/test.c
fi
