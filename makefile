CXX = g++
CXXFLAGS = -Wall -g

mytest: rqueue.o  mytest.cpp
	$(CXX) $(CXXFLAGS) rqueue.o mytest.cpp -o mytest

rqueue.o: rqueue.h rqueue.cpp
	$(CXX) $(CXXFLAGS) -c rqueue.cpp

driver.o: rqueue.o driver.cpp driver.txt
	$(CXX) $(CXXFLAGS) -c driver.cpp


clean:
	rm *.o*
	rm *~


run:
	./mytest


val:
	valgrind ./mytest
