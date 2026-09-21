KERNEL_NAME := $(shell uname -s)

ifeq ($(KERNEL_NAME),Darwin)
    CXX = g++-15
    LIB_NAME = libjsonparser.dylib
    RPATH = @executable_path/../shared
else
    CXX = g++
    LIB_NAME = libjsonparser.so
    RPATH = \$$ORIGIN/../shared
endif

CXXFLAGS = -std=c++23 -Iinclude -fPIC -Wall

app: src/main.cpp
	mkdir -p exe
	$(CXX) $(CXXFLAGS) -o exe/app.x src/main.cpp \
		-Lshared -ljsonparser \
		-Wl,-rpath,$(RPATH)

run: app
	./exe/app.x

clean:
	rm -f *.o exe/app.x
