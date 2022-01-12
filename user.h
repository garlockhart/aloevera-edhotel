/*
File Name		: user.h
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

#ifndef user_H
#define user_H

#define JUM_BLOK 1

/* Struct User */
typedef struct {
	int Code;
	char FullName[40];
	char Username[20];
	char Email[60];
	char Password[50];
	int Role;
	int Status;
} User;

/* Menu User */
int MenuUser();

/* Create Data User */
void CreateUser();

/* Show Data User */
void ShowUser();

/* Read Data User */
void ReadUser();

/* Update Data User */
void UpdateUser();

/* Check Data User by Code */
int CheckUserCode(User UserData, int ID);

/* Delete Data User */
void DeleteUser();
void AlertDeleteOneRecordUser();
void DeleteOneRecordUser(User UserData, int ID);
void AlertDeleteAllUser();
void DeleteAllUser();

#endif
