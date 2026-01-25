// class Employee {
//    String name;
//    int id;
//    public Employee(String name, int id) { constructor in Java
//        this.name = name;
//        this.id = id;
//    }
//    public void toString() {
//        System.out.println("Employee [" + this.name + "]");
//    }
//}; Java "Employee" class, this type of data could also be put in a hashmap

// Employee employee = new Employee("John Smith", 1234); instantiating in Java

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char* name;
    int id;
}; // C version

struct Employee* new_Employee(char* name, int id) {
    struct Employee* employee = (struct Employee*)malloc(sizeof(struct Employee));
    if (employee == NULL) {
        return NULL;
    }
    employee->name = strdup(name);
    employee->id = id;
    return employee;
}

void printEmployee(struct Employee* employee) {
    printf("Employee[%s, %i]\n", employee->name, employee->id);
}

char* getName(struct Employee* employee) {
    return employee->name;
}

int getId(struct Employee* employee) {
    return employee->id;
}

void setName(struct Employee* employee, char* name) {
    employee->name = name;
}

void setID(struct Employee* employee, int id) {
    employee->id = id;
}

void freeEmployee(struct Employee* employee) {
    free(employee->name);
    free(employee);
}

char* strdup(const char* src) {
    char *dst = (char*)malloc(strlen(src) + 1);
    strcpy(dst, src);
    return dst;
}

int main(int argc, char* argv[]) {
    struct Employee* employee = new_Employee("John Smith", 1234);
    struct Employee* employee2 = new_Employee("George Ferguson", 1731);
    struct Employee* employee3 = new_Employee("Tom Brady", 1819);
    printEmployee(employee);
    printEmployee(employee2);
    printEmployee(employee3);
    freeEmployee(employee);
}
