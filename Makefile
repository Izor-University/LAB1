CC      = clang
CFLAGS  = -std=c11 -Wall -Wextra -g
LDFLAGS = -lm


LIB_OBJ = Complex.o TypeInfo.o Vector3D.o

.PHONY: all clean run run_tests

all: LAB1 LAB1_tests



LAB1: main.o $(LIB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

LAB1_tests: tests.o unity.o $(LIB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)



main.o:     main.c
	$(CC) $(CFLAGS) -c $< -o $@

tests.o:    tests.c
	$(CC) $(CFLAGS) -c $< -o $@

unity.o:    unity.c
	$(CC) $(CFLAGS) -c $< -o $@

Complex.o:  Complex.c Complex.h
	$(CC) $(CFLAGS) -c $< -o $@

TypeInfo.o: TypeInfo.c TypeInfo.h Complex.h
	$(CC) $(CFLAGS) -c $< -o $@

Vector3D.o: Vector3D.c Vector3D.h TypeInfo.h
	$(CC) $(CFLAGS) -c $< -o $@


run: LAB1
	./LAB1

run_tests: LAB1_tests
	./LAB1_tests


clean:
	rm -f *.o LAB1 LAB1_tests
