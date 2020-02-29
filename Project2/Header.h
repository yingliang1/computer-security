#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
//#include <unistd.h>
#define MAXLEN 10240
#define TIME 1000 
//define an Employee type
typedef struct employee
{
    int EmployeeID=0;
    char First_Name[16];
    char Last_Name[16];
    char Posistion[16];
    char telephone[16];
    struct employee* next;//point to next employee
}Emp;

Emp* employees;//employee chain table

int tempInput = 0;
int tempID=0;
char tempFN[64];
char tempLN[64];
char temppos[64];
char temptel[64];
char newchoice;
char passwords[100];
char username[100];
char usernametemp[100];
char passwordtemp[100];
char newpassword[100];
char renewpassword[100];

void initFromTxt(void);//initialize file information
void deleteInfo(int EmployeeID);//delete information
void reWrite(void);//rewrite
void insert2txt(Emp* emp);//insert information into txt file
int addinfo(int EmployeeID, char* First_Name, char* Last_Name, char* Position, char* telephone);//add information
void modify();//modify information
void showInfo(void);//show information
void view(void);//menu
void newview(void);//main menu

void initFromTxt(void)
{
    employees = (Emp*)malloc(sizeof(Emp));
    employees->next = NULL;
    FILE* file;
    file = fopen("..\\directory1.txt", "r");
    if (file == NULL)
    {
        printf("txt filecontent is null");
        Sleep(TIME);
        return;
    }
    Emp* e = employees;
    while (1)
    {
        Emp* emp = (Emp*)malloc(sizeof(Emp));
        if (fscanf(file, "%d %s %s %s %s", &(emp->EmployeeID), &(emp->First_Name), &(emp->Last_Name), &(emp->Posistion), &(emp->telephone)) == EOF)
        {
            free(emp);
            break;
        }
        emp->next = NULL;

        e->next = emp;
        e = emp;
    }
    fclose(file);
}

void deleteInfo(int EmployeeID)
{
    Emp* emp = employees->next;
    Emp* pre = employees;
    int isFound = 0;
    while (emp != NULL)
    {
        if (emp->EmployeeID==EmployeeID)
        {
            pre->next = emp->next;
            free(emp);
            reWrite();
            isFound = 1;
            break;
        }
        pre = pre->next;
        emp = emp->next;
    }
    if (isFound)
    {
        printf("sucess!\n");
        Sleep(TIME);
    }
    else
    {
        printf("no record!\n");
        Sleep(TIME);
    }
}

void reWrite(void)
{
    Emp* emp = employees->next;
    FILE* file = fopen("..\\directory1.txt", "w");
    fclose(file);
    if (emp == NULL)
    {
        return;
    }

    while (emp != NULL)
    {
        insert2txt(emp);
        emp = emp->next;
    }

}

void insert2txt(Emp* emp)
{
    FILE* file;
    file = fopen("..\\directory1.txt", "a");
    if (file == NULL)
    {
        printf("[insert2txt]not success!");
        return;
    }
    fprintf(file, "\n%d %s %s %s %s", emp->EmployeeID, emp->First_Name, emp->Last_Name, emp->Posistion, emp->telephone);
    fclose(file);
}

int addinfo(int EmployeeID, char* First_Name, char* Last_Name, char* Position, char* telephone)
{
    int len = 0;
    int NewEmployeeID = EmployeeID;
    while (NewEmployeeID != 0) {
        NewEmployeeID /= 10;    
        ++len;
    }
    Emp* emp = employees->next;
    while (emp != NULL)
    {
       
        if (emp->EmployeeID == EmployeeID)
        {
            printf("password is repeated!\n");
            Sleep(TIME);
            return 0;
        }      
        emp = emp->next;
    }
    if (len != 6) {
        printf("password is not exact 6 digit!\n");
        Sleep(TIME);
        return 0;
    }
    Emp* newinfo = (Emp*)malloc(sizeof(Emp));
    newinfo->next = NULL;
    newinfo->EmployeeID = EmployeeID;
    strcpy(newinfo->First_Name, First_Name);
    strcpy(newinfo->Last_Name, Last_Name);
    strcpy(newinfo->Posistion, Position);
    strcpy(newinfo->telephone, telephone);
    Emp* p = employees;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newinfo;
        insert2txt(newinfo);
        showInfo();
       return 1;
}

void modify()
{
    FILE* file;
    FILE* filetemp;
    int f = 0;
    int EmployeeID = 0;
    char First_Name[16];
    char Last_Name[16];
    char Posistion[16];
    char telephone[16];
    file = fopen("..\\directory1.txt", "r");
    filetemp = fopen("..\\directorytemp.txt", "a");
    if (file == NULL)
    {
        printf("employee file no record");
    }
    printf("please enter your employeeid:");
    scanf("%d", &tempID);
    printf("please enter the employee's first name you want change to:");
    scanf("%s", tempFN);
    printf("please enter the employee's last name you want change to:");
    scanf("%s", tempLN);
    printf("please enter the employee's position you want change to:");
    scanf("%s", temppos);
    printf("please enter the employee's telephone you want change to:");
    scanf("%s", temptel);
    while (fscanf(file, "%d %s %s %s %s", &EmployeeID, First_Name, Last_Name, Posistion, telephone) != EOF) {
        if (EmployeeID == tempID) {
            f = 1;
            fprintf(filetemp, "\n%d %s %s %s %s", tempID, tempFN, tempLN, temppos, temptel);
        }
        else {
            fprintf(filetemp, "\n%d %s %s %s %s", EmployeeID, First_Name, Last_Name, Posistion, telephone);
        }
    }
    if (f == 0) {
        printf("no records");
    }
    fclose(file);
    fclose(filetemp);

    file = fopen("..\\directory1.txt", "w");
    fclose(file);

    file = fopen("..\\directory1.txt", "a");
    filetemp = fopen("..\\directorytemp.txt", "r");
    while (fscanf(filetemp, "%d %s %s %s %s", &EmployeeID, First_Name, Last_Name, Posistion, telephone) != EOF) {
        fprintf(file, "\n%d %s %s %s %s", EmployeeID, First_Name, Last_Name, Posistion, telephone);
    }
    fclose(file);
    fclose(filetemp);
    file = fopen("..\\directorytemp.txt", "w");
    fclose(file);
    _getch();
}



void showInfo(void)
{
    Emp* emp = employees->next;
    while (emp != NULL)
    {
        printf("EmployeeID:%d First Name:%s  Last Name:%s Position:%s telephone:%s\n", emp->EmployeeID, emp->First_Name, emp->Last_Name, emp->Posistion, emp->telephone);
        emp = emp->next;
    }
    getchar();
    getchar();
}


void changePassword() {
   
    FILE* file;
    FILE* filetemp;
    file = fopen("..\\password.txt", "r");
    filetemp = fopen("..\\passwordtemp.txt", "a");
    if (file == NULL)
    {
        printf("password file no record");
    }
    printf("please enter your username:");
    scanf("%s", &usernametemp);
    printf("please enter your password:");
    scanf("%s", &passwordtemp);
    int f = 0;
    while (fscanf(file, "%s %s", username, passwords)!=EOF) {
        if (strcmp(usernametemp, username) == 0) {
            f = 1;
            if (strcmp(passwordtemp, passwords) == 0) {
                printf("Enter your new password:");
                scanf("%s",newpassword);
                printf("Enter your new password again:");
                scanf("%s", renewpassword);
                if (strcmp(newpassword, renewpassword) == 0)
                {
                    fprintf(filetemp, "%s %s", username, newpassword);
                   
                } 
                else {
                    fprintf(filetemp, "%s %s", username, passwords);
                }
            }
            else {
                printf("wrong original password!");
            }
        }
        else {
            fprintf(filetemp, "\n%s %s", username, passwords);
        }
    }
    if (f == 0) {
        printf("no records");
    }
    fclose(file);
    fclose(filetemp);

    file = fopen("..\\password.txt", "w");
    fclose(file);

    file = fopen("..\\password.txt", "a");
    filetemp = fopen("..\\passwordtemp.txt", "r");
    while (fscanf(filetemp, "%s %s", username, passwords) != EOF) {
        fprintf(file, "\n%s %s", username, passwords);
    }
    fclose(file);
    fclose(filetemp);
    file = fopen("..\\passwordtemp.txt", "w");
    fclose(file);
    _getch();
}


void usermodify() {
  
    FILE* file;
    int f = 0;
    file = fopen("..\\password.txt", "r");
    if (file == NULL)
    {
        printf("password file no record");
    }
    printf("please enter your username:");
    scanf("%s", &usernametemp);
    printf("please enter your password:");
    scanf("%s", &passwordtemp);
    char usernametemp2[100] = "root";
    while (fscanf(file, "%s %s", username, passwords)!=EOF) {
        if (strcmp(username, usernametemp) == 0) {
            f = 1;
            if (strcmp(username, usernametemp2) == 0) {
                if (strcmp(passwordtemp, passwords) == 0) {
                    initFromTxt();
                    view();
                }
                else {
                    printf("wrong password!\n");
                }
            }
            else {
                printf("wrong username\n");
            }
          
        }
       
    }  
    if (f == 0) {
        printf("No record!\n");
    }
}

void userview() {
    FILE* file;
    int f = 0;
    file = fopen("..\\password.txt", "r");
    if (file == NULL)
    {
        printf("password file no record");
    }

    printf("please enter your username:");
    scanf("%s", &usernametemp);
    printf("please enter your password:");
    scanf("%s", &passwordtemp);
    while (fscanf(file, "%s %s", username, passwords)!=EOF) {
        if (strcmp(usernametemp, username) == 0) {
            f = 1;
            if (strcmp(passwordtemp, passwords) == 0) {
                printf("****************************\n");
                printf("Employee Directory information is shown on the list:\n");
                initFromTxt();
                showInfo();
            }
            else {
                printf("wrong password!");
            }
        }
    }
    if (f == 0) {
        printf("No record!");
    }
}

void newview(void)
{
   
    int newchoice = 0;
    while (1)
    {
        //system("cls");
        printf("****************************\n");
        printf("1.Modify Employee Information\n");
        printf("2.View Employee Information\n");
        printf("3.change password\n");
        printf("****************************\n");
        scanf("%d", &newchoice);
        switch (newchoice) {
        case 1:
            usermodify();
            break;
        case 2:
            userview();
            break;
        case 3:
            changePassword();
            break;
        }
    }

}

void view(void)
{

    while (1)
    {
        //system("cls");
        printf("****************************\n");
        printf("1.Add Information\n");
        printf("2.Delete Information\n");
        printf("3.Modify Information\n");
        printf("4.show the results\n");
        printf("5.return to main menu\n");
        printf("6.exit\n");
        printf("****************************\n");
        scanf("%d", &tempInput);
        switch (tempInput)
        {
        case 1:
            printf("insert EmployeeID(has to be 6 digit or cannot success):");
            scanf("%d", &tempID);
            printf("Please Enter Employee First Name:");
            scanf("%s", tempFN);
            printf("Please Enter Employee Last Name:");
            scanf("%s", tempLN);
            printf("Please Enter Employee Position:");
            scanf("%s", temppos);
            printf("Please Enter Employee telephone:");
            scanf("%s", temptel);
            addinfo(tempID, tempFN, tempLN, temppos, temptel);

            break;
        case 2:
            printf("insert EmployeeID:");
            scanf("%d", &tempID);
            deleteInfo(tempID);
            break;
        case 3:
            modify();
            break;
        case 4:
            showInfo();
            break;
        case 5:
            newview();
            break;
        case 6:
            return;
            break;
        default:
            printf("wrong\n");
            getchar(); getchar();
            break;
        }
    }

}