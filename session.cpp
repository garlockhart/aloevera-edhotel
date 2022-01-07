/*
File Name		: session.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 05/01/2022
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "session.h"
#include "user.h"
/* ======= End of Header File ====== */

int SessionDestroy()
{
	User UserData, TempUserData;
	FILE *f_user, *f_tempuser;
	
	f_user = fopen("User.DAT", "rb");
	f_tempuser = fopen("TempUser.DAT", "wb");
	
	if (!f_user)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		exit(1); 
	}
	
	if (!f_tempuser)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		exit(1); 
	}
	
	while (fread(&UserData, sizeof(UserData),1, f_user))
	{
		if(UserData.Status == 1){
			TempUserData.Code = UserData.Code;
			strcpy(TempUserData.FullName, UserData.FullName);
			strcpy(TempUserData.Email, UserData.Email);
			strcpy(TempUserData.Username, UserData.Username);
			strcpy(TempUserData.Password, UserData.Password);
			TempUserData.Role = UserData.Role;
			TempUserData.Status = 0;

			fwrite(&TempUserData, sizeof(TempUserData), 1, f_tempuser);  
		}
		else {
			fwrite(&UserData, sizeof(UserData), 1, f_tempuser);  
		}
	}
	
	fclose(f_user);
	fclose(f_tempuser);

	remove("User.DAT");
	rename("TempUser.DAT", "User.DAT");
}
