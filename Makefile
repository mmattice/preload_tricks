
all:	logforce.so

logforce.so:
	gcc main.c -o logforce.so -fPIC -shared -ldl
