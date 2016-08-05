
GEN = getip libexitpreload.so

all: getip libexitpreload.so

getip: getip.c

libexitpreload.so: exitpreload.c
	gcc -Wall -shared -fPIC -o $@ $< -ldl

clean:
	rm -rf $(GEN)

