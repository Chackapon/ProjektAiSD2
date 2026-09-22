KERNEL_NAME := $(shell uname -s)

ifeq ($(KERNEL_NAME),Darwin)
    CXX = g++-15
    LIB_NAME = libjsonparser.dylib
    RPATH = -Wl,-rpath,@executable_path
else ifeq ($(KERNEL_NAME),Linux)
    CXX = g++
    LIB_NAME = libjsonparser.so
    RPATH = -Wl,-rpath,'$$ORIGIN'
else
    $(error Unsupported OS: $(KERNEL_NAME))
endif

CXXFLAGS = -std=c++23 -Iinclude -fPIC -Wall


# Iinclude - allows to get rid of relative paths in includes

LIB_NAME = libjsonparser.dylib

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

app: src/main.cpp
	mkdir -p exe
	$(CXX) $(CXXFLAGS) -Lshared -ljsonparser -Wl,-rpath,@executable_path -o exe/app.x src/main.cpp

run: app
	./exe/app.x

clean:
	rm -f *.o