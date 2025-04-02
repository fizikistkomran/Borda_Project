# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall

# Kaynak dosyalar
SRC = main.c sensors.c filter.c buffer.c


# Hedef (çıktı) dosya
TARGET = main

# Derleme kuralı
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

# Temizleme kuralı
clean:
	rm -f $(TARGET) *.o

