.PHONY: all clean

all: input output
	zip data.zip *.in *.out

input:
	python3 generator.py
	cp handmade/* .

output:
	bash ./make-output.sh

clean:
	-rm *.in *.out data.zip
