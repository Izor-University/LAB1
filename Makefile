CC     = clang
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = vector3d

$(TARGET): main.o Vector3D.o TypeInfo.o Complex.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o Vector3D.o TypeInfo.o Complex.o -lm

main.o: main.c Vector3D.h TypeInfo.h Complex.h
	$(CC) $(CFLAGS) -c main.c

Vector3D.o: Vector3D.c Vector3D.h TypeInfo.h
	$(CC) $(CFLAGS) -c Vector3D.c

TypeInfo.o: TypeInfo.c TypeInfo.h Complex.h
	$(CC) $(CFLAGS) -c TypeInfo.c

Complex.o: Complex.c Complex.h
	$(CC) $(CFLAGS) -c Complex.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
