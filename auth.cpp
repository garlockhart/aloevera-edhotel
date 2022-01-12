/*
File Name		: auth.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 30/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "auth.h"
#include "user.h"
#include "compare.h"
#include "administrator.h"
#include "concierge.h"
#include "session.h"
#include "welcome.h"
#include "hidden.h"
/* ======= End of Header File ====== */

int Login()
{
	User UserData, TempUserData;
	FILE *f_user, *f_tempuser;
	int CompareUsername, ComparePassword;
	
	printf("|==================================|\n");
	printf("|              Login               |\n");
	printf("|==================================|\n");
	
	printf("\n\n");

	printf("Username : "); 
	fflush(stdin);
	scanf("%[^\n]", &TempUserData.Username); 

	printf("Password : "); 
	fflush(stdin);
	HiddenPassword(TempUserData.Password); 

	printf("\n");
	fflush(stdin);
	
	/* Open File */
	f_user = fopen("User.DAT", "rb");
	f_tempuser = fopen("TempUser.DAT", "wb");
	
	/* Error Handle About Open File */
	if (!f_user)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		Welcome(); 
	}
	
	/* Error Handle About Open File */
	if (!f_tempuser)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		Welcome(); 
	}
	
	while (fread(&UserData, sizeof(UserData), 1, f_user))
	{
		CompareUsername = StringCompare(UserData.Username, TempUserData.Username);  
		ComparePassword = StringCompare(UserData.Password, TempUserData.Password); 
		if((CompareUsername == 0) && (ComparePassword == 0)){
			TempUserData.Code = UserData.Code;
			strcpy(TempUserData.FullName, UserData.FullName);
			strcpy(TempUserData.Email, UserData.Email);
			TempUserData.Role = UserData.Role;
			TempUserData.Status = 1;
			
			fwrite(&TempUserData, sizeof(TempUserData), 1, f_tempuser);  
		}  
		else {
			fwrite(&UserData, sizeof(UserData), 1, f_tempuser);  
		}
	}
	
	/* Close File */
	fclose(f_user);
	fclose(f_tempuser);
	
	/* Remove File */
	remove("User.DAT");
	
	/* Rename File */
	rename("TempUser.DAT", "User.DAT");
	
	if (TempUserData.Role == 1){
		system("cls");
		
		/* Call Modul Menu Administrator */
		AdministratorMenu();
	} else if(TempUserData.Role == 2){
		system("cls");
		
		/* Call Modul Menu Concierge */
		ConciergeMenu();
	} else{
		system("cls");
		printf ("ERROR : Username or Password is incorrect!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		
		/* Call Modul Welcome */
		Welcome();
	}
}

int Logout()
{
	/* Call Modul Session Destroy */
	SessionDestroy();
	
	printf ("Account successfully logout!!!\n"); 
    getch();
		
	system("cls");
	
	/* Call Modul Welcome */
	Welcome();
}
