typedef struct Employee* Employee;

extern Employee new_Employee(char *name, int id);

extern void printEmployee(Employee this);
extern char* getEmployeeName(Employee this);
extern void setEmployeeName(Employee this, char *name);
extern int getEmployeeId(Employee this);
extern void setEmployeeId(Employee this, int id);

extern void freeEmployee(Employee this);