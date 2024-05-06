CXX = g++
CXXFLAGS = -Wall

DayOfYear.o: DayOfYear.h DayOfYear.cpp
    $(CXX) $(CXXFLAGS) -c DAYOfYear.cpp

driver: DayOfYear.o driver.cpp
    $(CXX) $(CXXFLAGS) -c DayOfYear.o driver.cpp -o driver
clean:
    rm *~
    rm *.o
run:
    ./driver
    
submit:
    cp proj1.cpp ~/cs202proj/proj1

