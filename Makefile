CXX = g++-15
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
	rm -f *.dylib *.o