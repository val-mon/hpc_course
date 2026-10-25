COMPILER ?= g++
SRC ?= main.cpp
OUT ?= run

.DEFAULT_GOAL := run
.PHONY: run seq clean

run: seq
	./$(OUT)

seq:
	$(COMPILER) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
