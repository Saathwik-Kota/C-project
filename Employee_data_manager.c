#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------DEFINING STRUCTS--------------

typedef struct Employee{
    int employee_id;
    char *name;         // Memory will be allocated using malloc
    float salary;
    int dept_id;        
    struct Employee *next; 
}Employee;

typedef struct Department{
    int dept_id;        
    char *dept_name;    // Memory will be allocated using malloc
    struct Department *next; 
}Department;

typedef struct JoinedRecord{
    int employee_id;
    char *employee_name;
    float salary;
    char *department_name;
    struct JoinedRecord *next; 
}JoinedRecord;


// ---------MEMORY MANAGEMENT FUNCTIONS--------

// Frees the memory for a single Employee node
void free_employee_node(Employee *emp){
    if(emp!=NULL){
        free(emp->name);
        free(emp);
    }
}

// Frees the memory for a single Department node
void free_department_node(Department *dept){
    if(dept!=NULL){
        free(dept->dept_name);
        free(dept);
    }
}

// Frees the memory for a single JoinedRecord node
void free_joined_record_node(JoinedRecord *rec){
    if(rec!=NULL){
        free(rec->employee_name);
        free(rec->department_name);
        free(rec);
    }
}

// Cleans up the entire employee list
void free_employee_list(Employee **head){
    Employee *current = *head;
    Employee *next_node;
    while(current!=NULL){
        free(current->name);
        free(current);
        current = current->next;
    }
    *head = NULL;
}

// cleans up the entire department list
void free_department_list(Department **head){
    Department *current = *head;
    Department *next_node;
    while(current!=NULL){
        free(current->dept_name);
        free(current);
        current = current->next;
    }
    *head = NULL;
}

//cleans up the entire joined record list
void free_joined_record_list(JoinedRecord **head){
    JoinedRecord *current = *head;
    JoinedRecord *next_node;
    while(current!=NULL){
        free(current->employee_name);
        free(current->department_name);
        free(current);
        current = current->next;
    }
    *head = NULL;
}

// -------------EMPLOYEE AND DEPARTMENT RELATED FUNCTIONS-----------------

// Creates a new Employee node
Employee* create_employee(int id, const char *name, float salary, int dept_id){
    Employee *new_emp = (Employee *)malloc(sizeof(Employee));
    if (new_emp==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_emp->employee_id = id;
    new_emp->name = strdup(name);   
    new_emp->salary = salary;
    new_emp->dept_id = dept_id;
    new_emp->next = NULL;
    if (new_emp->name==NULL){
         free(new_emp); 
         return NULL; 
        }
    return new_emp;
}

// Insert new Employee at the beginning of Linked List
void add_employee(Employee **head, Employee *new_node){
    if (new_node!=NULL){
        new_node->next = *head;
        *head = new_node;
    }
}

// Creates a new Department node
Department* create_department(int id, const char *name){
    Department *new_dept = (Department *)malloc(sizeof(Department));
    if (new_dept==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    new_dept->dept_id = id;
    new_dept->dept_name = strdup(name); 
    new_dept->next = NULL;
    if (new_dept->dept_name==NULL){
         free(new_dept); 
         return NULL;
        }
    return new_dept;
}

// Insert a new department at the beginning of Linked List
void add_department(Department **head, Department *new_node){
    if (new_node!=NULL){
        new_node->next = *head;
        *head = new_node;
    }
}

//Displays all the employees' records
void display_employee_list(Employee *head){
    Employee *current = head;
    printf("\n-----------------Employee Records-----------------\n");
    printf("ID   | Name                 | Salary       | Dept ID\n");
    printf("-----|----------------------|--------------|--------\n");
    while(current!= NULL){
        printf("%-4d | %-20s | Rs.%-10.2f | %d\n", current->employee_id, current->name, current->salary, current->dept_id); 
        current = current->next;
    }
    printf("----------------------------------------------------\n");
}

//Displays all the departments
void display_department_list(Department *head){
    Department *current = head;
    printf("\n--- Department Records ---\n");
    printf("ID   | Name                 \n");
    printf("-----|----------------------\n");
    while(current!=NULL){
        printf("%-4d | %s\n", current->dept_id,current->dept_name);
        current = current->next;
    }
    printf("----------------------------\n");
}

// Finds an employee by ID and updates their salary
void update_employee_salary(Employee *head, int id, float new_salary){
    Employee *current = head;
    while(current!=NULL){
        if (current->employee_id == id) {
            current->salary = new_salary;
            printf("Employee ID %d salary updated to Rs.%.2f\n", id, new_salary);
            return;
        }
        current = current->next;
    }
    printf("Employee with ID %d not found\n", id);
}

// Finds an employee by ID and deletes the employee
void delete_employee(Employee **head, int id){
    Employee *current = *head;
    Employee *prev = NULL;
    if (current!=NULL && current->employee_id==id){
        *head = current->next; 
        free_employee_node(current); 
        printf("Employee ID %d deleted\n", id);
        return;
    }
    while(current!=NULL && current->employee_id!=id){
        prev = current;
        current = current->next;
    }
    if (current==NULL){
        printf("Employee with ID %d not found\n", id);
        return;
    }
    prev->next = current->next;
    free_employee_node(current);
    printf("Employee ID %d deleted\n", id);
}

void delete_employees_by_dept(Employee **head, int dept_id){
    Employee *current = *head;
    Employee *prev = NULL;
    int count = 0;
    while(current!=NULL){
        if (current->dept_id==dept_id){
            Employee *to_delete = current;
            if (prev==NULL){
                *head = current->next;
            } 
            else{
                prev->next = current->next;
            }
            current = current->next;
            free_employee_node(to_delete); 
            count = count + 1;
            continue;
        }
        prev = current;
        current = current->next;
    }
    printf("Deleted %d employees from department ID %d\n", count, dept_id);
}

Department* find_department(Department *head, int id){
    Department *current = head;
    while(current!=NULL){
        if (current->dept_id==id){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Uses delete_employees_by_dept to delete a department by its id and also all of the employees in that department 
void delete_department(Department **dept_head, Employee **emp_head, int id){
    Department *current = *dept_head;
    Department *prev = NULL;
    if (current!=NULL && current->dept_id==id){
        *dept_head = current->next;
        delete_employees_by_dept(emp_head, id); 
        free_department_node(current); 
        printf("Department ID %d and its employees deleted\n", id);
        return;
    }
    while(current!=NULL && current->dept_id!=id){
        prev = current;
        current = current->next;
    }
    if (current==NULL){
        printf("Department with ID %d not found\n", id);
        return;
    }
    prev->next = current->next;
    delete_employees_by_dept(emp_head, id); 
    free_department_node(current); 
    printf("Department ID %d and its employees deleted\n", id);
}

// ------------FILE I/O FUNCTIONS-----------------

// Saves the Employee List to disk
void save_employees(Employee *head){
    FILE *file = fopen("employees.csv", "w");
    if (file==NULL){
        printf("Failed to open file\n");
        return;
    }
    Employee *current = head;
    while(current!=NULL){
        fprintf(file, "%d,\"%s\",%.2f,%d\n", current->employee_id, current->name, current->salary, current->dept_id);
        current = current->next;
    }
    fclose(file);
    printf("Data saved successfully to employees.csv\n");
}

// Loads the Employee List from disk 
void load_employees(Employee **head){
    FILE *file = fopen("employees.csv", "r");
    if (file==NULL){ 
        printf("Employee file not found ,starting with empty list.\n"); 
        return; 
    }
    char line[1024];
    free_employee_list(head);
    while(fgets(line, sizeof(line), file)!=NULL){
        int id, dept_id;
        float salary;
        char name_buffer[50]; 
        char *start = strchr(line, '"');
        char *end = strrchr(line, '"');
        if (start && end && start < end) {
            size_t len = end - start - 1;
            if (len >= 50) len = 50 - 1;
            strncpy(name_buffer, start + 1, len);
            name_buffer[len] = '\0';
            if (sscanf(end + 2, "%f,%d", &salary, &dept_id) == 2) {
                if (sscanf(line, "%d,", &id) == 1) { 
                    Employee *new_emp = create_employee(id, name_buffer, salary, dept_id);
                    add_employee(head, new_emp);
                }
            }
        }
    }
    fclose(file);
    printf("Employees loaded from employees.csv\n");
}

// Saves the Department List to disk
void save_departments(Department *head){
    FILE *file = fopen("departments.csv", "w");
    if (file==NULL){
        printf("Failed to open file\n");
        return;
    }
    Department *current = head;
    while(current!=NULL){ 
        fprintf(file, "%d,\"%s\"\n", current->dept_id, current->dept_name);
        current = current->next;
    }
    fclose(file);
    printf("Data saved successfully to departments.csv\n");
}

// Loads the Department List from disk
void load_departments(Department **head){
    FILE *file = fopen("departments.csv", "r");
    if (file==NULL){ 
        printf("Department file not found. starting with empty list\n"); 
        return; 
    }
    char line[1024];
    free_department_list(head);
    while(fgets(line, sizeof(line), file)!=NULL){
        int id;
        char name_buffer[50]; 
        char *start = strchr(line, '"');
        char *end = strrchr(line, '"');
        if (start && end && start < end) {
            size_t len = end - start - 1;
            if (len >= 50) len = 50 - 1;
            strncpy(name_buffer, start + 1, len);
            name_buffer[len] = '\0';
            if (sscanf(line, "%d,", &id) == 1) { 
                Department *new_dept = create_department(id, name_buffer);
                add_department(head, new_dept);
            }
        }
    }
    fclose(file);
    printf("Departments loaded from departments.csv\n");
}

// ----------JOIN OPERATION AND DISPLAY FUNCTIONS----------

// Creates a new JoinedRecord node
JoinedRecord* create_joined_record(Employee *emp, Department *dept){
    JoinedRecord *new_record = (JoinedRecord *)malloc(sizeof(JoinedRecord));
    if (new_record==NULL){
        return NULL;
    }
    new_record->employee_id = emp->employee_id;
    new_record->salary = emp->salary;
    new_record->employee_name = strdup(emp->name);
    new_record->department_name = strdup(dept->dept_name);
    new_record->next = NULL;
    if (new_record->employee_name==NULL || new_record->department_name==NULL){ 
        free(new_record->employee_name);
        free(new_record->department_name);
        free(new_record); 
        return NULL; 
    }
    return new_record;
}

// Logic of JOIN function
JoinedRecord* perform_join(Employee *emp_head, Department *dept_head){
    JoinedRecord *join_head = NULL;
    JoinedRecord *join_tail = NULL;
    Employee *current_emp = emp_head;
    while(current_emp!=NULL){
        Department *current_dept = dept_head; 
        while(current_dept!=NULL){
            if (current_emp->dept_id==current_dept->dept_id){
                JoinedRecord *new_node = create_joined_record(current_emp, current_dept);
                if (new_node==NULL){
                    return join_head;
                }
                if (join_head==NULL){
                    join_head = new_node;
                    join_tail = new_node;
                } 
                else{
                    join_tail->next = new_node;
                    join_tail = new_node;
                }
                break; 
            }
            current_dept = current_dept->next;
        }
        current_emp = current_emp->next;
    }
    return join_head;
}

// For displaying the joined list
void display_joined_results(JoinedRecord *head){
    JoinedRecord *current = head;
    printf("\n-----------Query Result: Employee & Department Join-----------\n");
    printf("E_ID  | Name                 | Salary       | Department        \n");
    printf("-----|----------------------|--------------|--------------------\n");
    if (current==NULL){
        printf("No matching records found\n");
    }
    while(current!=NULL){
        printf("%-5d| %-20s | Rs.%-10.2f | %s\n", current->employee_id, current->employee_name, current->salary, current->department_name);
        current = current->next;
    }
    printf("----------------------------------------------------------------\n");
}

void add_department_cli(Department** head){
    int id;
    char name[50];
    printf("Enter Department ID: "); 
    if (scanf("%d", &id)!=1){ 
        while(getchar()!='\n'){
            return;
        }
    }
    if (find_department(*head, id)!=NULL){
        printf("Department ID %d already exists\n", id);
        return;
    }
    printf("Enter Department Name (without spaces): "); 
    if (scanf("%s", name)!=1){
        while(getchar()!='\n'){
            return;
        }
    }
    Department *new_dept = create_department(id, name);
    if (new_dept!=NULL){
        add_department(head, new_dept);
        printf("Department added\n");
    }
}

void display_menu(){
    printf("\n-----------------------------------------------\n");
    printf("1. Load ALL Data (Employees & Depts)\n");
    printf("2. Save ALL Data (Employees & Depts)\n");
    printf("3. Add New Employee\n");
    printf("4. Display Employee List\n");
    printf("5. PERFORM JOIN Query (E. Name + Dept. Name)\n");
    printf("6. Display Department List\n");
    printf("7. Update Employee Salary\n");
    printf("8. Delete Employee\n");
    printf("9. Add New Department\n");  
    printf("10. Delete Department\n"); 
    printf("11. Exit (Saves ALL data)\n"); 
    printf("-------------------------------------------------\n");
    printf("ENTER CHOICE: ");
}

int main(){
    Employee *employee_head = NULL;
    Department *department_head = NULL;
    int choice;
    // Load data at the starting
    load_departments(&department_head);
    load_employees(&employee_head);
    do{
        display_menu();
        if (scanf("%d", &choice)!=1){
            while (getchar()!='\n'); 
            choice = 0;
            printf("Invalid input. please enter a number\n");
            continue;
        }
        switch (choice){
            case 1: // Load ALL Data
                load_departments(&department_head);
                load_employees(&employee_head);
                break;
            case 2: // Save ALL Data
                save_employees(employee_head);
                save_departments(department_head);
                break;
            case 3: // Add New Employee
                int id, dept_id;
                float salary;
                char name[50];
                printf("Enter Employee ID: "); 
                if (scanf("%d", &id)!=1){
                    break;
                }
                printf("Enter Name (without spaces): "); 
                if (scanf("%s", name)!=1){
                    break;
                }
                printf("Enter Salary: "); 
                if (scanf("%f", &salary)!=1){
                    break;
                }
                printf("Enter Department ID: "); 
                if (scanf("%d", &dept_id)!=1){
                    break;
                }
                // Check if dept_id exists before adding employee
                if (find_department(department_head, dept_id)==NULL){
                    printf(" Department ID %d does not exist. Employee added, but join query may not show department name\n", dept_id);
                }
                Employee *new_emp = create_employee(id, name, salary, dept_id);
                if (new_emp!=NULL){
                    add_employee(&employee_head, new_emp);
                    printf("Employee added\n");
                }
                break;
            case 4: // Display Employee List
                display_employee_list(employee_head);
                break;
            case 5: // PERFORM JOIN Query
                JoinedRecord *joined_results = perform_join(employee_head, department_head);
                display_joined_results(joined_results);
                free_joined_record_list(&joined_results);
                break;
            case 6: // Display Department List
                display_department_list(department_head);
                break;
            case 7: // Update Employee Salary
                int id;
                float salary;
                printf("Enter Employee ID to update salary: "); 
                if (scanf("%d", &id)!=1){
                    break;
                }
                printf("Enter new Salary: "); 
                if (scanf("%f", &salary)!=1){
                    break;
                }
                update_employee_salary(employee_head, id, salary);
                break;
            case 8: // Delete Employee 
                int id;
                printf("Enter Employee ID to delete: ");
                if (scanf("%d", &id)!=1){
                    break;
                }
                delete_employee(&employee_head, id);
                break;
            case 9: // Add New Department
                add_department_cli(&department_head);
                break;
            case 10: //Delete Department
                int id;
                printf("Enter Department ID to delete (All employes in this department will also be deleted): "); 
                if (scanf("%d", &id)!=1){
                    break;
                }
                delete_department(&department_head, &employee_head, id);
                break;
            case 11: // Exit
                save_employees(employee_head);
                save_departments(department_head);
                printf("Saved and Exited\n");
                break;
            default:
                printf("Invalid choice. please try again\n");
        }
    }while(choice!=11);
    free_employee_list(&employee_head);
    free_department_list(&department_head);
    printf("THANK YOU!\n");
    return 0;
}

