COMPILER ?= g++
SRC ?= main.cpp
OUT ?= run

run: seq
	./$(OUT)

seq:
	$(COMPILER) $(SRC) -o $(OUT)

clean:
	rm $(OUT)
