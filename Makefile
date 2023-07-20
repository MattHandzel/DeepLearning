exec: ./bin/main
	./bin/main 100
	gprof ./bin/main gmon.out > analysis.txt

./bin/main: ./src/main.cc ./src/Neuron.cc ./src/ActivationFunction.cc ./src/NeuralLayer.cc ./src/utils.cc
	$(CXX) ./src/main.cc ./src/Neuron.cc ./src/ActivationFunction.cc ./src/NeuralLayer.cc ./src/utils.cc $(FLAGS) -o ./bin/main 

./src/%.cc: ./includes/%.cc
	%@


.PHONY: exec
.DEFAULT: exec

CXX = g++
FLAGS = -Iincludes -fpermissive -O0 -Wall -pg -g