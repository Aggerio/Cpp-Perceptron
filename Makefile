
run:
	clang++ main.cpp Useful_Functions.cpp Neuron.cpp Read_Data.cpp -g -o main && ./main
clean:
	rm -rf main
