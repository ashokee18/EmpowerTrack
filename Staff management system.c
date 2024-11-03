 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILE_NAME "employees.txt"

//structure storing information of employees
struct Employee 
{
    int id;
    char name[50];
    int age;
    float ctc;
    struct Employee *next_salary;
};
typedef struct Employee Employee;

Employee employees[MAX_EMPLOYEES];
int numEmployees = 0;

//adding a new employee to your database
void addEmployee() 
{
    Employee emp;

    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name(Enter underscore between firstname and lastname): ");
    scanf(" %s", emp.name);
    printf("Enter employee age: ");
    scanf("%d", &emp.age);
    printf("Enter employee salary: ");
    scanf("%f", &emp.ctc);

    employees[numEmployees] = emp;
    numEmployees++;

    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d,%s ,%d,%.2f\n", emp.id, emp.name, emp.age, emp.ctc);

    fclose(file);

    printf("Employee added successfully!\n");
}

//displaying an employee
void displayEmployees() 
{
    if (numEmployees == 0)
    {
        printf("No employees found.\n");
        return;
    }

    printf("Employee List:\n");
    printf("--------------------------------------------------------------\n");
    printf("ID\tName\t\t\t      Age\tCTC\n");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < numEmployees; i++)
    {
        printf("%d\t", employees[i].id);
        int j = 0;
        for (; employees[i].name[j] != 0; j++)
        	printf("%c", employees[i].name[j]);
        for (; j < 30; j++)
        	printf(" ");
        printf("%d  \t%.2f\n", employees[i].age, employees[i].ctc);
    }

    printf("--------------------------------------------------------------\n");
}

//to load the employees form txt file
void loadEmployeesFromFile() 
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Employee emp;
    while (fscanf(file, "%d,%s ,%d,%f\n", &emp.id, emp.name, &emp.age, &emp.ctc) != EOF)
    {
        employees[numEmployees] = emp;
        numEmployees++;
    }

    fclose(file);
}

//bubble sort to sort data according to user id
void sort(Employee employees[])
{
    int n=numEmployees;

    Employee temp;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(employees[j+1].id<employees[j].id)
            {
                temp=employees[j];
                employees[j]=employees[j+1];
                employees[j+1]=temp;
            }
        }
    }
    
}

// uses binary search to search for the employee
void searchEmployee()
{

    int searchId;
    int found = 0;
    int res;
    printf("Enter employee ID to search: ");
    scanf("%d", &searchId);
    
    int low=0;
    int high=numEmployees-1;
    
    while(low<=high)
    {
      
      int mid=low+(high-low)/2;

      if(employees[mid].id==searchId)
      {
      res=mid;
      found=1;
      } 
      if(employees[mid].id<searchId)
      low=mid+1;
      else
      high=mid-1;
    }

    if (!found) 
    {
        printf("Employee not found.\n");
    }
    else
    {
        printf("Employee with ID %d found\n",searchId);
        printf("Name: %s \t ID: %d \t Age: %d \t Salary: %0.2f \t\n",employees[res].name,employees[res].id,employees[res].age,employees[res].ctc);
    }

}

//deletes the employee record
void deleteEmployee() 
{

    int deleteId;
    int found = 0;

    printf("Enter employee ID to delete: ");
    scanf("%d", &deleteId);

    for (int i = 0; i < numEmployees; i++) 
    {
        if (employees[i].id == deleteId) 
        {
            found = 1;

            for (int j = i; j < numEmployees - 1; j++) 
            {
                employees[j] = employees[j + 1];
            }

            numEmployees--;
            printf("Employee deleted successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Employee not found.\n");
    }
}

//calculates the distribution of ctc of each employee
 void ctc_distribution()
 {
    
     int searchId;
    printf("Enter employee ID to search: ");
    scanf("%d", &searchId);int c=0;
    for(int i=0;i<numEmployees;i++)
    {
        if(employees[i].id == searchId)
        {
            printf("CTC DISTRIBUTION\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("SALARY(60%%)\t\t\tSTOCK(15%%)\t\t\tBONUS(10%%)\t\t\tTAX(8%%)\t\t\tMEDICAL ALLOWANCES(7%%)\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
           printf("%0.2f\t\t\t%0.2f\t\t\t%0.2f\t\t\t%0.2f\t\t\t%0.2f",(employees[i].ctc)*0.6,(employees[i].ctc)*0.15,(employees[i].ctc)*0.1,(employees[i].ctc)*0.08,(employees[i].ctc)*0.07);
           c++;
           break;
        }
    }
    if(c==0)
    {
        printf("INVALID EMPLOYEE ID");
    }

 }

//checks for valid username
 int login()
 {
    char str1[200],str2[200];
    printf("Enter username: ");
    scanf("%s",str1);
    printf("Enter Password: ");
    scanf("%s",str2);
if(strcmp(str1,"2201ME17")==0)
{
    if(strcmp(str2,"ashish")==0)
    return 1;
    else
    return 0;
}
else if(strcmp(str1,"2201EE18")==0)
{
    if(strcmp(str2,"ashok")==0)
    return 1;
    else
    return 0;
}
else if(strcmp(str1,"2201PH06")==0)
{
    if(strcmp(str2,"arun")==0)
    return 1;
    else
    return 0;
}
else 
return 0;
 }



int main() 

{
    int choice;          
    int n=1;
    while(n<=3)
    {

        if(login()==0)
        {
            printf("Wrong username\n");
            n++;
            if(n==3)
            printf("Access Denied");
            continue;
        }

        else
        {
            n=4;
            loadEmployeesFromFile();

    do 
    {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Delete Employee\n");
        printf("5.CTC Distribution\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
         {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                sort(employees);
                searchEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                ctc_distribution();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } 
    while (choice != 0);

    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < numEmployees; i++) 
    {
        fprintf(file, "%d,%s ,%d,%.2f\n", employees[i].id, employees[i].name, employees[i].age, employees[i].ctc);
    }

    fclose(file);
        }
    }
    return 0;
}
