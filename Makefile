all:
	g++ -o lambda_example main.cpp
.PHONY: clean
clean:
	rm lambda_example
