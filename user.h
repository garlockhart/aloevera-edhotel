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
	int code;
	char fullname[40];
	char username[20];
	char email[60];
	char password[50];
	char role[20];
	int status;
} user;

int UserMenu();
void UserCreate();
void UserData();
void UserRead();
void UserUpdate();
int CheckUserCode(user userdata, int id);
void UserDelete();

#endif
