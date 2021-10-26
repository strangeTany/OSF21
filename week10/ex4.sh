mkdir tmp
cd tmp
nano file1
nano file2
ln file1 link1
cd ..
gcc ex4.c  -o ex4.o
./ex4.o >> ex4.txt
