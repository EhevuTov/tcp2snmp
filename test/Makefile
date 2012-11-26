test: all
	./snmptrap_simple
all:
	clang -o snmptrap_simple -arch x86_64 \
	-lnetsnmp -lnetsnmpagent -lnetsnmphelpers -lnetsnmpmibs \
	snmptrap_simple.c
clean:
	rm *.o *.log *.core snmptrap
