all: file_sha512.cpp
	g++ file_sha512.cpp -o file_sha512.out -Ofast -march=native -funroll-loops

clean:
	$(RM) file_sha512.out