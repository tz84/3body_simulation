CC := clang++
CCFLAG := -std=c++17 -I/opt/homebrew/include

all: app 

app: main.o 
	$(CC) $(CCFLAG) -o app main.o

%.o: %.cpp
	$(CC) $(CCFLAG) -c $< -o $@ 

.PHONY: clean
clean: 
	rm -f app main.o 

