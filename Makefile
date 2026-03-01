# vars:
CXX = g++
CXXFLAGS = -std=c++17 -O3
TARGET = protozip
INSTALL_PATH = /usr/local/bin

all:
	$(CXX) $(CXXFLAGS) huffman.cpp compressor.cpp compmain.cpp -o $(TARGET)

install: all
	install -m 755 $(TARGET) $(INSTALL_PATH)

uninstall:
	rm -f $(INSTALL_PATH)/$(TARGET)

clean:
	rm -f $(TARGET)


