//
//  modeStudent.c
//  Cstudent
//
//  Created by 刘阳 on 15/11/27.
//  Copyright © 2015年 刘阳. All rights reserved.
//

#include "modeStudent.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//struct Student {
//    int index;
//    char studentId[20];
//    char password[20];
//    char studentName[20];
//    char class[20];
//    int age;
//    int score_1;
//    int score_2;
//    int score_3;
//    int rank;
//    
//    struct Student* previous;
//    struct Student* next;
//};


//创建一个空链表，空链表仅包含头节点而且头节点指针为NULL
StudentList createEmptyStudentList(){
    return createNewStudentNode("defaut","defaut","defaut","defaut",-1,-1,-1,-1);
}

//添加节点，头插法
StudentList insertStudentAt(StudentList L,char* studentId,char* password,char* studentName,char* class,int age,int score_1,int score_2,int score_3){
    //    printf("loop!!\n");
    assert(L!=NULL);//断言
    StudentNode *newNode=createNewStudentNode(studentId,password,studentName,class,age,score_1,score_2,score_3);
    if (newNode!=NULL) {
        //先把插入节点指向前序节点的指向
        newNode->next=L->next;
        //再把前序节点指向新节点，实现插入功能
        L->next=newNode;
    }
    
    return newNode;
}

//按值查找//这里不解决重复值的问题//用于登陆
StudentList getByStudentId(StudentList L,char* studentId){
    assert(L!=NULL);
    StudentList temPtr=L->next;//这样做没问题，虽然这个指针是临时变量，但是从一个确定的地址获取到的，返回这个指针是不会出错的
    while ((temPtr!=NULL)&&(strcmp(temPtr->studentId,studentId))!=0) {//  temPtr->userName!=userName)) {
        temPtr=temPtr->next;
    }
    return temPtr;
}

//删除学生节点，这里是按学号查找
StudentList deleteByStudentId(StudentList L,char* studentId){
    assert(L!=NULL);
    //保存前一节点
    StudentList temPtr=L;
    while (temPtr->next!=NULL){
        StudentList delPtr=temPtr->next;//保存要删除的节点
        if (strcmp(delPtr->studentId,studentId)==0) {//找到了待删除节点
            temPtr->next=delPtr->next;
            free(delPtr);
            delPtr=NULL;
            break;
        }
        temPtr=temPtr->next;
    }
    return temPtr;
}

//修改节点资料
StudentList editStudent(StudentList L,char* studentId,char* password,char* studentName,char* class,int age,int score_1,int score_2,int score_3){
    assert(L!=NULL);
    strcpy(L->studentId, studentId);
    strcpy(L->password, password);
    strcpy(L->studentName, studentName);
    strcpy(L->class, class);
    L->age=age;
    L->score_1=score_1;
    L->score_2=score_2;
    L->score_3=score_3;
    return L;
}

//遍历链表,返回长度
int getStudentListSize(StudentList L){
    int index=0;
    struct Student* temp=L->next;//通过一个临时指针遍历，不能操作原指针//这里的遍历没算头指针
    while (temp!=NULL) {
        temp=temp->next;
        index++;//如果需要获取链表长度，在此进行处理
    }
    return index;
}

//遍历链表，返回最后一个节点，引入这个方法只用于输出测试结果，不做其他
StudentList getLastStudentNode(StudentList L){
    StudentList temPtr=L->next;
    while (temPtr!=NULL) {
        printf("%s,%s,%s,%d,%d,%d,%d,%d\n",temPtr->studentId,temPtr->studentName,temPtr->class,temPtr->age,temPtr->score_1,temPtr->score_2,temPtr->score_3,temPtr->rank);
        temPtr=temPtr->next;
    }
    return temPtr;
}

//链表转数组
StudentList getStudentArray(StudentList L,StudentList nodeArray){
    //生命数组
    int length=getStudentListSize(L);
    StudentNode mArray[length];
    //遍历链表
    StudentList temPtr=L->next;
    int i=0;
    while (temPtr!=NULL) {
        mArray[i]=*temPtr;
        temPtr=temPtr->next;
        i++;
    }
    return nodeArray=mArray;
}

//创建节点函数,不显式引用
StudentList createNewStudentNode(char* studentId,char* password,char* studentName,char* class,int age,int score_1,int score_2,int score_3){
    StudentNode *newNode=NULL;//创建链表的第一步是创建节点
    newNode=(StudentNode*)calloc(1, sizeof(StudentNode));//这里的参数1怎么回事
    if (newNode==NULL) {
        return NULL;
    }
    newNode->previous=NULL;
    newNode->next=NULL;
    newNode->index=-1;//暂未用到
    newNode->rank=-1;//暂未用到
    
    strcpy(newNode->studentId, studentId);
    strcpy(newNode->password, password);
    strcpy(newNode->studentName, studentName);
    strcpy(newNode->class, class);
    newNode->age=age;
    newNode->score_1=score_1;
    newNode->score_2=score_2;
    newNode->score_3=score_3;
    return newNode;
}

//获取结构体占用的内存大小,不知道为什么在main函数不能使用这边头文件的typedef，所以定义这个
int getStructStudentSize(){
    return sizeof(struct Student);
}
