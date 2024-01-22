# Proje ismi (yürütülebilir dosyanın adı)
PROJECT_NAME := main

# Kaynak (.cpp) ve header (.h) dosyalarını bul
SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)

# İşletim Sistemi tespiti
OS := $(shell uname -s)

# Başlık ve kütüphane dosyalarının yolu
INCLUDE_PATH := raylib
LIBRARY_PATH := raylib

# Derleyici ve derleyici bayrakları
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I$(INCLUDE_PATH)

# Linker bayrakları ve işletim sistemine özgü ayarlar
LDFLAGS := -L$(LIBRARY_PATH) -lraylib
ifeq ($(OS), Linux)
    LDFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
endif
ifeq ($(OS), Darwin) # macOS için
    LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif
ifeq ($(OS), MINGW32_NT-6.2) # Windows için, OS değeri sisteme göre değişebilir
    LDFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

# Derleme hedefi
build: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(PROJECT_NAME)

# Çalıştırma hedefi
run: build
	./$(PROJECT_NAME)

# Temizleme komutu
clean:
	rm -f $(PROJECT_NAME)