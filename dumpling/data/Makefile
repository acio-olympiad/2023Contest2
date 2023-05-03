.PHONY: all clean

all: input output
	zip data.zip *.in *.out

input:
	python3 generator.py

output:
	bash ./make-duds.sh

clean:
	-rm *.in *.out data.zip
