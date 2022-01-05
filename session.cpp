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
	user userdata, tempuserdata;
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
	
	while (fread(&userdata, sizeof(userdata),1, f_user))
	{
		if(userdata.status == 1){
			tempuserdata.code = userdata.code;
			strcpy(tempuserdata.fullname,userdata.fullname);
			strcpy(tempuserdata.email,userdata.email);
			strcpy(tempuserdata.username,userdata.username);
			strcpy(tempuserdata.password,userdata.password);
			tempuserdata.role = userdata.role;
			tempuserdata.status = 0;

			fwrite(&tempuserdata, sizeof(tempuserdata), 1, f_tempuser);  
		}
		else {
			fwrite(&userdata, sizeof(userdata), 1, f_tempuser);  
		}
	}
	
	fclose(f_user);
	fclose(f_tempuser);

	remove("User.DAT");
	rename("TempUser.DAT", "User.DAT");
}
