#include <stdio.h>
#include "Employee.h"

int main(int argc, char *argv[]) {
    Employee employee = new_Employee("John Smith", 1234);
    printEmployee(employee);
    printf("\n");
}
