#include "MyClass.h"
#include <stdio.h>

int MyClass::doSomething(int number) {
    emit didSomething(number);
    return number + 1;
}

void MyClass::onDidSomething(int number) {
    printf("Number %i was called", number);
}