# Simply execute "make" in working directory to create executable "hw7"
# Running "make clean" will remove the executable

# Deleting the # sign at the end of line 10 and renaming the additional files
# to whatever you have named them will let you compile more files

# PLEASE TEST YOUR MAKEFILE TO ENSURE IT WORKS BEFORE SUBMITTING

all:
	g++ -std=c++17 Huffman.cpp main.cpp -o problem5
clean:
	rm problem5
