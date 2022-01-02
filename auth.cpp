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
#include "welcome.h"
/* ======= End of Header File ====== */

int Login()
{
	user userdata, tempuserdata;
	FILE *f_user, *f_tempuser;
	int CompareUsername, ComparePassword;
	
	printf("|==================================|\n");
	printf("|              Login               |\n");
	printf("|==================================|\n");
	

	fflush(stdin);
	printf("  Username : "); 
	scanf("%[^\n]",&tempuserdata.username); 

	fflush(stdin);
	printf("  Password : "); 
	scanf("%s",&tempuserdata.password); 

	printf("\n");
	fflush(stdin);
	
	if ((f_user=fopen("User.DAT", "rb"))==NULL)
	{
		printf ("File tidak dapat dibuka\n"); 
		exit(1);
	}
	
	if ((f_tempuser=fopen("TempUser.DAT", "ab+"))==NULL)
	{
		printf ("File tidak dapat dibuka\n"); 
		exit(1);
	}
	
	while (fread(&userdata, sizeof(userdata),1, f_user))
	{
		CompareUsername = StringCompare(userdata.username,tempuserdata.username);  
		ComparePassword = StringCompare(userdata.password,tempuserdata.password); 
		if((CompareUsername == 0) && (ComparePassword == 0)){
			tempuserdata.code = userdata.code;
			strcpy(tempuserdata.fullname,userdata.fullname);
			strcpy(tempuserdata.email,userdata.email);
			tempuserdata.role = userdata.role;
			tempuserdata.status = 1;
			
			fwrite(&tempuserdata, sizeof(tempuserdata),1,f_tempuser);  
		}  
		else {
			fwrite(&userdata, sizeof(userdata),1,f_tempuser);  
		}
	}
	
	fclose(f_user);
	fclose(f_tempuser);

	remove("User.DAT");
	rename("TempUser.DAT", "User.DAT");
	
	if (tempuserdata.role == 1){
		system("cls");
		AdministratorMenu();
	} else if(tempuserdata.role = 2){
		system("cls");
		ConciergeMenu();
	} else{
		system("cls");
		Welcome();
	}
}

int Logout()
{
	printf ("Account successfully logout!!!\n"); 
    getch();
		
	system("cls");
	Welcome();
}
