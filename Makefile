KERNEL_NAME := $(shell uname -s)

ifeq ($(KERNEL_NAME),Darwin)
    CXX = g++-15
    LIB_NAME = libjsonparser.dylib
    RPATH = -Wl,-rpath,@executable_path/../shared
else ifeq ($(KERNEL_NAME),Linux)
    CXX = g++
    LIB_NAME = libjsonparser.so
    RPATH = -Wl,-rpath,'$$ORIGIN/../shared'
else
    $(error Unsupported OS: $(KERNEL_NAME))
endif

CXXFLAGS = -std=c++20 -Iinclude -fPIC -Wall

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

app: src/main.cpp
	mkdir -p exe
	$(CXX) $(CXXFLAGS) src/main.cpp \
		-Lshared -ljsonparser \
		$(RPATH) \
		-o exe/app.x

run: app
	./exe/app.x

clean:
	rm -rf exe