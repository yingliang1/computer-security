// encrept.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <conio.h>
#include "Header.h"
#define MAXLEN 10240

char filepath[250];
char password[256];
FILE* fpt;
FILE* fptr;
int i;
int pwdlen;
char* line[MAXLEN];
char line1[MAXLEN];
int choice = 0;
int temp;
void readFile()
{
    //insert into filepath and check if this file is exist
    printf("Enter file path:\n");
    scanf("%s", filepath);
    fptr = fopen(filepath, "r");
    if (fptr == NULL)
    {
        printf("filepath Error!");
        exit(1);
    }

    //enter into encrept password to check if it empty
    printf("Enter encrept password:\n");
    scanf("%s", password);
    if (password == 0) {
        printf("password cannot empty!!!\n");
        exit(1);
    }
    //store the file into char array
    i = 0;
   
    while (fgets(line1, sizeof line1, fptr) != NULL)
    {
        line[i] = (char*)malloc(MAXLEN);
        strcpy(line[i], line1);
        i++;
       // char tmp = fgetc(fptr);
    }
    temp = i;
}


void encrypt(char* messagenew[MAXLEN], char* key)
{
    char* message;
    for (int z = 0; z < temp; z++) {
        message = messagenew[z];
        int b = strlen(key);
        int a = strlen(message);
        for (int k = 0; message[k] != NULL; ++k) {
                if (message[k] >= 'A' && message[k] <= 'Z')
                {
                     message[k] = ((message[k] - 'A') + (int(key[k%b])-97)) % 26 + 'A';
                }
                else if (message[k] >= 'a' && message[k] <= 'z')
                {
                     message[k] = ((message[k] - 'a') + (int(key[k%b]) - 97)) % 26 + 'a';
                }
                else {
                    message[k] = message[k];
                }
        }
    }

}

void decrypt(char* messagenew[MAXLEN], char* key)
{
    char* message;
    for (int z = 0; z < temp; z++) {
        int b = strlen(key);
        message = messagenew[z];
        int cont=0;
        int a = strlen(message);
        if (message[0] == '\r') {
            cont = 1;
        }
        for (int k = cont; message[k]!=NULL; ++k) {
           
                if (message[k] >= 'A' && message[k] <= 'Z')
                {
                    message[k-cont] = (( message[k]-'A') + (26-int(key[(k-cont)%b]) + 97)) % 26 + 'A';
                }
                else if (message[k] >= 'a' && message[k] <= 'z')
                {
           
                    message[k-cont] = ((message[k]-'a' ) + (26-int(key[(k-cont)%b]) + 97)) % 26 + 'a';
                }
                else {
                    message[k-cont] = message[k];
                }
        }
        message[a-cont] = '\0';
    }   
    
}


void getencryptfile(char* messagenew[MAXLEN]) {
    fpt = fopen("C:\\temp\\decryptfile.txt", "w");
    if (fpt == NULL)
    {
        printf("Error!");
        exit(1);
    }
    int p;
    for (p = 0; p < temp; p++)
    {
        fprintf(fpt, "%s", messagenew[p]);
        fprintf(fpt, "\r");
    }
    fclose(fpt);
    printf("%s", "The encrpte file located in C:\\temp\\encryptfile.txt.");
}


void getdecryptfile(char* messagenew[MAXLEN]) {
    fpt = fopen("C:\\temp\\decryptfile.txt", "w");
    if (fpt == NULL)
    {
        printf("Error!");
        exit(1);
    }
    int p;
    for (p = 0; p < temp; p++)
    {
        fprintf(fpt, "%s", messagenew[p]);
        fprintf(fpt, "\r");
    }
    fclose(fpt);
    printf("%s", "The encrpte file located in C:\\temp\\decryptfile.txt.");
}






void menu() {
    printf("Menu\n\n");
    printf("\n 1.Encrypt\n");
    printf("\n 2.Decrypt\n");
    printf("\n 3.Employee Directory\n");
    printf("\n 4.Main Menu\n");
}


void main(void)
{
    while (1) {
        menu();
        scanf("%d", &choice);
        if (choice == '3') {
            break;
        }
        switch (choice)
        {
        case 1:
            readFile();
            encrypt(line, password);
            getencryptfile(line);
            exit(0);
        case 2:
            readFile();
            decrypt(line,password);
            getdecryptfile(line);
            exit(0);
        case 3:
            newview();
           
            exit(0);
        case 4:
            break;
        default:
            printf("wrong choice.Enter Again");
            break;
        }
    }
}





