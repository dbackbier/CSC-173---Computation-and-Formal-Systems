#include <stdlib.h>
#include <stdio.h>
#include "Employee.h"
#include "LinkedList.h"

int main() {
    LinkedList list = new_LinkedList();
    prepend(list, new_Employee("John Smith", 1234));
    printf("Name: %s", getEmployeeName(getFirst(list)));
    printf("\nID: %d", getEmployeeId(getFirst(list)));
}