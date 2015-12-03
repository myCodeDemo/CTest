//
//  menu.c
//  Cstudent
//
//  Created by 刘阳 on 15/11/27.
//  Copyright © 2015年 刘阳. All rights reserved.
//

#include "menu.h"

AdminList cacheAdminList;
StudentList cacheStudentList;


//选择登陆方式
int loginTypeSelect(){
    //确认用户输入
    int a=1,b=2;
    printf("选择登陆类型:\n%d,管理员\n%d,学生\n",a,b);
    int key;
    scanf("%d",&key);
    if (a!=key&&b!=key) {
        wrongInput(loginTypeSelect);
    }
    //返回输入结果
    return key;
}


//管理员登陆，登录函数应该是menu方法中唯一（还有学生登陆）返回指针的，返回的指针作为修改密码的参数
AdminList loginTypeAdmin(){
    //确认用户输入
    printf("请输入用户名:\n");
    char inputName[20];//不能用[]={}声明
    fscanf(stdin, "%s",inputName);
    fflush(stdin);
    
    printf("请输入密码:\n");
    char inputPass[20];
    fscanf(stdin, "%s",inputPass);
    fflush(stdin);
    //printf("%s,%s\n",inputName,inputPass);
    
    //缓存管理员数据
    struct Admin* L = createEmptyAdminList();
    readAdminFile(L);
    cacheAdminList=L;
    
    AdminList currentPtr=getByUserName(L, inputName);//判断登录名是否存在
    if (currentPtr) {
        if (strcmp(inputPass, currentPtr->password)==0) {//判断密码是否正确
            printf("管理员登录成功\n");
            return currentPtr;
        }else{
            printf("密码错误\n");
        }
    }else{
        printf("用户不存在\n");
    }
    //返回输入结果
    return NULL;
}


//admin主选项
int menuAdminMain(){
    //确认用户输入
    int a=1,b=2;
    printf("选择功能:\n%d,密码修改\n%d,学生管理\n",a,b);
    int key;
    scanf("%d",&key);
    if (a!=key&&b!=key) {
        wrongInput(menuAdminMain);
    }
    //返回输入结果
    return key;
}


//admin修改密码
int menuAdminPassword(AdminList currentPtr){
    //确认用户输入
    printf("请输入旧密码:\n");
    char inputOld[20];
    fscanf(stdin, "%s",inputOld);
    fflush(stdin);
    
    printf("请输入新密码:\n");
    char inputNew[20];
    fscanf(stdin, "%s",inputNew);
    fflush(stdin);
    printf("%s,%s\n",inputOld,currentPtr->password);
    if (strcmp(inputOld, currentPtr->password)==0) {
        strcpy(currentPtr->password, inputNew);
        //currentPtr->password=inputNew;
        printf("new=%s\n",currentPtr->password);
        writeAdminFile(cacheAdminList);
        printf("修改成功\n");
        return 1;
    }else{
        printf("密码错误\n");
        return 0;
    }
}


//admin学生管理
int menuAdminManagement(){
    //确认用户输入
    int a=1,b=2,c=3,d=4;
    printf("选择操作:\n%d,学生浏览\n%d,添加学生\n%d,删除学生\n%d,修改学生\n",a,b,c,d);
    int key;
    scanf("%d",&key);
    if (a!=key&&b!=key&&c!=key&&d!=key) {
        wrongInput(menuAdminManagement);
    }
    
    //缓存学生数据
    cacheStudentList = createEmptyStudentList();
    readStudentFile(cacheStudentList);
    
    //返回输入结果
    return key;
}


//显示学生列表
void menuLoadAndShowStudentList(){
    printf("-----学生信息-----\n");
    printf("学号 姓名 班级 年龄 成绩1 成绩2 成绩3 名次\n");
    getLastStudentNode(cacheStudentList);
    printf("-----------------\n");
}


//添加学生
void menuAddStudent(){
    char studentId[20],password[20],studentName[20],class[20];
    int age,score_1,score_2,score_3;
    printf("输入学生资料:\n");
    printf("依次输入学号 密码 姓名 班级 年龄 成绩1 成绩2 成绩3\n");
    fscanf(stdin,"%s %s %s %s %d %d %d %d",studentId,password,studentName,class,&age,&score_1,&score_2,&score_3);
    fflush(stdin);
    insertStudentAt(cacheStudentList,studentId,password,studentName,class,age,score_1,score_2,score_3);
    writeStudentFile(cacheStudentList);
    printf("Done!\n");
    //getLastStudentNode(cacheStudentList);
}

//删除学生
void menuDeleteStudent(){
    char studentId[20];
    printf("输入待删除的学生学号:\n");
    fscanf(stdin, "%s",studentId);
    fflush(stdin);
    printf("删除ing...:%s\n",studentId);
    deleteByStudentId(cacheStudentList,studentId);
    writeStudentFile(cacheStudentList);
    //getLastStudentNode(cacheStudentList);
}

//修改学生
void menuEditStudent(){
    char studentIdOld[20];
    printf("输入待修改的学生学号:\n");
    fscanf(stdin, "%s",studentIdOld);
    fflush(stdin);
    StudentList temPtr=getByStudentId(cacheStudentList,studentIdOld);
    char studentIdNew[20],password[20],studentName[20],class[20];
    int age,score_1,score_2,score_3;
    printf("输入学生资料:\n");
    printf("依次输入学号 密码 姓名 班级 年龄 成绩1 成绩2 成绩3\n");
    fscanf(stdin,"%s %s %s %s %d %d %d %d",studentIdNew,password,studentName,class,&age,&score_1,&score_2,&score_3);
    fflush(stdin);
    editStudent(temPtr,studentIdNew,password,studentName,class,age,score_1,score_2,score_3);
    writeStudentFile(cacheStudentList);
    //getLastStudentNode(cacheStudentList);
}

//学生登陆
int loginTypeStudent(){
    return 0;
}


















void wrongInput(int (*funcPtr)()){
    printf("输入错误请重新输入:\n");
    (*funcPtr)();
}

void systemExit(){
    exit(0);
}

