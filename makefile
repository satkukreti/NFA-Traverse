test: kukreti_p1

kukreti_p1: kukreti_p1.o
	g++ -Wall -Wextra kukreti_p1.o -o kukreti_p1

kukreti_p1.o: kukreti_p1.cpp
	g++ -Wall -Wextra -c kukreti_p1.cpp

clean:
	rm -f *.o kukreti_p1
