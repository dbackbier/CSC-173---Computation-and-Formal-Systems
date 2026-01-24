#include "Employee.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// This function is in the C standard library but so what
char* strdup(const char* s) {
    char *t = (char*)malloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}

struct Employee {
    char* name;
    int id;
};

Employee new_Employee(char *name, int id) {
    Employee this = (Employee)malloc(sizeof(struct Employee));
    if (this == NULL) {
        return NULL;
    }
    this->name = strdup(name);
    this->id = id;
    return this;
}

void printEmployee(Employee this) {
    printf("Employee[%s,%d]", this->name, this->id);
}

char* getEmployeeName(Employee this) {
    return strdup(this->name);
}

void setEmployeeName(Employee this, char *name) {
    this->name = name; // See text
}

int getEmployeeId(Employee this) {
    return this->id;
}

void setEmployeeId(Employee this, int id) {
    this->id = id;
}

void freeEmployee(struct Employee *this) {
    free(this->name);
    free(this);
}