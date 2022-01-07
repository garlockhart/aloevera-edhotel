/*
File Name		: user.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef user_H
#define user_H

#define JUM_BLOK 1

typedef struct {
	int Code;
	char FullName[40];
	char Username[20];
	char Email[60];
	char Password[50];
	int Role;
	int Status;
} User;

int MenuUser();
void CreateUser();
void ShowUser();
void ReadUser();
void UpdateUser();
int CheckUserCode(User UserData, int ID);
void DeleteUser();
void AlertDeleteOneRecordUser();
void DeleteOneRecordUser(User UserData, int ID);
void AlertDeleteAllUser();
void DeleteAllUser();

#endif
