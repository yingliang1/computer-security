#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*定义一个学生类型*/
typedef struct student
{
    char stuid[16];//学号
    char name[16];//学生姓名
    int num;//学生学号
    struct student* next;//下一个学生的指针
}Stu;

Stu* students;//学生链表

int input = 0;//选择
char tempInput[64];
char tempName[64];
char tempStuid[64];
int tempNum = 0;


void initFromTxt(void);//初始化
void deleteInfo(char* stuid);//删除信息
void reWrite(void);//重写
void insert2txt(Stu* stu);//插入文本
int addinfo(char* stuid, char* name, int num);//增加信息
void modify(char* stuid, char* name, int num);//修改信息
int checkAdd(char* stuid);//判断学号输入
void showInfo(void);//展示信息
Stu* findInfo(char* stuid);//查找信息
void view(void);//界面
int checkInput(char* input, int begin, int end);//判断输入是否再给定的范围内

void initFromTxt(void)
{
    students = (Stu*)malloc(sizeof(Stu));//给链表的头节点分配内存
    students->next = NULL;//指向设为空
    FILE* file;
    file = fopen("..\\directory.txt", "r");//打开信息文件
    if (file == NULL)
    {
        printf("[initFromTxt]打开文件失败!");
        return;
    }
    Stu* s = students;//当前结点
    while (1)
    {
        Stu* stu = (Stu*)malloc(sizeof(Stu));
        //从文本读入学生信息，存进stu中
        if (fscanf(file, "%s %s %d", &(stu->stuid), &(stu->name), &(stu->num)) == EOF)
        {
            //如果读入为EOF，也就说为读入为空，那么刚刚新建的stu就不要了，释放分配的内存
            free(stu);
            break;
        }
        stu->next = NULL;

        s->next = stu;//将当前节点和新建的节点链接起来
        s = stu;//调整当前节点为新节点
    }
    fclose(file);
}

void deleteInfo(char* stuid)
{
    Stu* stu = students->next;//当前节点
    Stu* pre = students;//当前节点的父节点
    int isFound = 0;//是否找到学生
    while (stu != NULL)
    {
        if (strcmp(stu->stuid, stuid) == 0)//判断id是否相同
        {
            pre->next = stu->next;
            free(stu);
            reWrite();//重写进文件
            isFound = 1;
            break;
        }
        pre = pre->next;
        stu = stu->next;
    }
    if (isFound)
    {
        printf("删除成功!\n");
    }
    else
    {
        printf("没有找到该记录!\n");
    }
}

void reWrite(void)
{
    Stu* stu = students->next;
    FILE* file = fopen("..\\directory.txt", "w");//清空文件
    fclose(file);
    if (stu == NULL)//这个代表当前没有学生，直接返回
    {
        return;
    }

    while (stu != NULL)
    {
        insert2txt(stu);
        stu = stu->next;
    }

}
//插入一条学生信息进入文本文件
void insert2txt(Stu* stu)
{
    FILE* file;
    file = fopen("..\\directory.txt", "a");
    if (file == NULL)
    {
        printf("[insert2txt]文件写入不成功!");
        return;
    }
    fprintf(file, "%s %s %d\n", stu->stuid, stu->name, stu->num);
    fclose(file);
}

int addinfo(char* stuid, char* name, int num)
{
    if (!checkAdd(stuid))
    {
        printf("学号重复，不能添加!\n");
        return 0;
    }
    Stu* newinfo = (Stu*)malloc(sizeof(Stu));//新建一个新节点
    newinfo->next = NULL;
    //给新节点赋值
    strcpy(newinfo->stuid, stuid);
    strcpy(newinfo->name, name);
    newinfo->num = num;
    //调整p到最后一个节点
    Stu* p = students;
    while (p->next != NULL)
    {
        p = p->next;
    }
    //p链接新节点
    p->next = newinfo;
    //插入新信息
    insert2txt(newinfo);
    return 1;
}
/*修改学生信息*/
void modify(char* stuid, char* name, int num)
{
    //修改信息是先删除再添加
    deleteInfo(stuid);
    if (addinfo(stuid, name, num))
        printf("修改成功!");
    else
        printf("修改失败!");
}
/*判断学号是否重复*/
int checkAdd(char* stuid)
{
    Stu* stu = students->next;
    while (stu != NULL)
    {
        if (strcmp(stu->stuid, stuid) == 0)
            return 0;
        stu = stu->next;
    }
    return 1;
}

/*打印所有信息*/
void showInfo(void)
{
    Stu* stu = students->next;
    while (stu != NULL)
    {
        printf("%s %s, %d\n", stu->stuid, stu->name, stu->num);
        stu = stu->next;
    }
    getchar();
    getchar();
}

/*根据学生信息查找学生*/
Stu* findInfo(char* stuid)
{
    Stu* stu = students->next;
    while (stu != NULL)
    {
        if (strcmp(stu->stuid, stuid) == 0)
            return stu;
        stu = stu->next;
    }
    return NULL;
}

void main(void)
{
    initFromTxt();
    view();
}

/*判断输入是否再范围内，用来判断*/
int checkInput(char* input, int begin, int end)
{
    //如果不是一个字符，直接返回
    if (strlen(input) != 1)
    {
        return -1;
    }
    //判断输入是不在范围内
    if (input[0] < '0' + begin || input[0]>'0' + end)
    {
        return -1;
    }
    return input[0] - '0';
}

void view(void)
{

    while (1)
    {
        system("cls");
        printf("****************************\n");
        printf("1.增加学生信息\n");
        printf("2.删除学生信息\n");
        printf("3.改变学生信息\n");
        printf("6.退出\n");
        printf("****************************\n");
        scanf("%s", tempInput);
        input = checkInput(tempInput, 1, 6);
        switch (input)
        {
        case 1:
            printf("请输入学号,姓名,数字(例如:20151111 张三 0)数据以空格隔开:");
            scanf("%s%s%d", tempStuid, tempName, &tempNum);
            addinfo(tempStuid, tempName, tempNum);
            break;
        case 2:
            printf("请输入学号:");
            scanf("%s", tempStuid);
            deleteInfo(tempStuid);
            break;
        case 3:
            printf("请输入学号:");
            break;
        case 6:
            return;
            break;
        default:
            printf("输入错误!按任意键返回\n");
            getchar(); getchar();
            break;
        }
    }

}
