CFLAGS = -lm -g -pg -Wall -W -Wextra -O3
prog.exe: main.o qr_razlog.o proverka.o
	g++ $(CFLAGS) main.o qr_razlog.o proverka.o -o prog.exe
main.o: main.cpp qr_razlog.h proverka.h
	g++ $(CFLAGS) -c main.cpp
qr_razlog.o: qr_razlog.cpp qr_razlog.h
	g++ $(CFLAGS) -c qr_razlog.cpp
proverka.o:proverka.cpp proverka.h
	g++ $(CFLAGS) -c proverka.cpp
clean:
	rm -f prog.exe