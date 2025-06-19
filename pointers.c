#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int squarefoot;
    int roomCount;
    int bathCount;
} House; 

int add(int a, int b) {
    return a+b;
}

int main() {

    // Make sure to null your pointers on creation
    // Make sure to free your pointers when done
    // Make sure to ffree memory not used.
    // Malloc returns a void * so it needs to be cast.
    House *myHouse2 = (House *)malloc(1*sizeof(House));
    free(myHouse2);
    myHouse2 = NULL;

    // Pointers decorate the variable not the type
    int *x, y; 
    y = 5; 
    x = &y; // y is not a pointer

    House myHouse = { 1000, 2, 1 };
    House *myHousePtr = &myHouse;

    printf("Size: %d, Bedrooms %d, Bath: %d\n", myHouse.squarefoot, myHouse.roomCount, myHouse.bathCount);
    printf("PTR: Size: %d, Bedrooms %d, Bath: %d\n", myHousePtr->squarefoot, myHousePtr->roomCount, myHousePtr->bathCount);

    // Hello Array has size information 
    char hello[] = "Hello World";
    // Decays to a pointer to the first element with no size information
    char *hello_ptr = &hello[0];
    // Arrays already are addresses but size information is lost
    char *hello_ptr1 = hello;

    // Steps the size of the type (in this case char = 1 byte)
    hello_ptr++; 

    int numbers[] = { 1, 2, 3, 4, 5 };
    int *numbers_ptr = numbers;

    // This will step 4 bytes for the size of an int
    numbers_ptr++;

    // Pointers to pointers
    char **hello_ptr_ptr = &hello_ptr;

    // This kind of pointers to the first element
    printf("%s\n", hello);
    // THis points to the first element
    printf("%s\n", hello_ptr);
    // This points to a pointer to the first element.
    printf("%s\n", *hello_ptr_ptr);

    // Function pointer:
    int (*pAdd)(int,int) = add;
    int sum = (*pAdd)(1,2);
    printf("%d\n", sum);

    return 0;

}