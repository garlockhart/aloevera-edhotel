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
/* ======= End of Header File ====== */

int Login()
{
	user userdata, tempuserdata;
	FILE *f_user, *f_tempuser;
	int CompareUsername, ComparePassword;
	
	printf("|==================================|\n");
	printf("|              Login               |\n");
	printf("|==================================|\n");
	
	printf("\n\n");

	printf("Username : "); 
	fflush(stdin);
	scanf("%[^\n]", &tempuserdata.username); 

	printf("Password : "); 
	fflush(stdin);
	scanf("%s", &tempuserdata.password); 

	printf("\n");
	fflush(stdin);
	
	f_user = fopen("User.DAT", "rb");
	f_tempuser = fopen("TempUser.DAT", "wb");
	
	if (!f_user)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		Welcome(); 
	}
	
	if (!f_tempuser)
	{
		printf ("ERROR : Sorry the file is unavailable!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		Welcome(); 
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
	} else if(tempuserdata.role == 2){
		system("cls");
		ConciergeMenu();
	} else{
		system("cls");
		printf ("ERROR : Username or Password is incorrect!!!\n"); 
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		Welcome();
	}
}

int Logout()
{
	SessionDestroy();
	printf ("Account successfully logout!!!\n"); 
    getch();
		
	system("cls");
	Welcome();
}
