/*
File Name		: user.cpp
Description		: 
Author			: Garly Nugraha & Nazwa Fitriyani Zahra
Date			: 08/12/2001
*/

/* ========== Header File ========== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "administrator.h"
#include "user.h"
/* ======= End of Header File ====== */
	
int MenuUser()
{
	int Menu;
	
	printf("|==================================|\n");
	printf("|             User Menu            |\n");
	printf("|==================================|\n");
	printf("|1. Create                         |\n");
	printf("|2. Read                           |\n");
	printf("|3. Update                         |\n");
	printf("|4. Delete                         |\n");
	printf("|5. Back                           |\n");
	printf("|==================================|\n");
    
    printf("\n\n");
    printf("Select Menu : ");
	scanf("%d", &Menu);
	system("cls");
	
    switch (Menu) { 
        case 1:
        	/* Call Modul Create Data User */
			CreateUser();
			break;
		case 2:
			/* Call Modul Read Data User */
			ReadUser();
			break;
		case 3:
			/* Call Modul Update Data User */
			UpdateUser();
			break; 
		case 4:
			/* Call Modul Delete Data User */
			DeleteUser();
			break;
	 	case 5:
	 		/* Call Modul Menu Administrator */
			AdministratorMenu();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
	 		
	 		/* Call Modul Menu User */
			MenuUser();
			break;
    }
}

void CreateUser()
{
	char More;
	int Check;
	User UserData;
    FILE *f_user;
	
	/* Open File */
	f_user = fopen("User.DAT", "ab+");
	
	/* Erro Handle About Open File */
    if (!f_user) 
    { 
        printf ("ERROR : Sorry the file is unavailable!!!\n");
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		MenuUser(); 
    }
    
    do {
    	system("cls");
    	printf("|=====================================|\n");
		printf("|              Create User            |\n");
		printf("|=====================================|\n");
	
		printf("User Code : ");
		fflush(stdin);
		scanf("%d", &UserData.Code);
		
		Check = CheckUserCode(UserData, UserData.Code);
		
		if(Check != 0)
		{
			system("cls");
			printf("ERROR : User code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			CreateUser();
		}
		
		printf("Full Name : ");
		fflush(stdin);
		scanf("%[^\n]",&UserData.FullName); 
		
		printf("Username : ");
		fflush(stdin);
		gets(UserData.Username);
		
		printf("Email : ");
		fflush(stdin);
		gets(UserData.Email);
		
		printf("Password : ");
		fflush(stdin);
		gets(UserData.Password);
		
		printf("Role (1/2) : ");
		fflush(stdin);
		scanf("%d", &UserData.Role); 
		
		fflush(stdin);
		UserData.Status = 0;
		
		fwrite(&UserData, sizeof(UserData), 1, f_user);
		
		printf("\n");
		printf("Do you want to create more data? (Y/N) ");
		fflush(stdin);
		
		More = getche();
	} while (More == 'Y' || More == 'y');
	
	/* Close File */
	fclose(f_user);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	
	/* Call Modul Menu User */
	MenuUser();
}

void ShowUser()
{
	FILE *f_user;
	User UserData;
	char Role[15], Status[7];
	
	/* Open File */
	f_user = fopen("User.DAT", "rt");
	
	/* Error Handle About Open File */
    if (!f_user) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		/* Call Modul Menu User */
		MenuUser();
    } 

    printf("|==========================================================================================================================================|\n");
    printf("|                                                 User Data                                                                                |\n");
    printf("|==========================================================================================================================================|\n");
    printf("| User ID         Full Name            Username                   mail                        Password         Role            Status      |\n");
    printf("|==========================================================================================================================================|\n");
	
	while ((fread(&UserData, sizeof(UserData), JUM_BLOK, f_user)) == JUM_BLOK)
	{
		if(UserData.Role == 1){
			strcpy(Role, "Administrator");
		} else if(UserData.Role == 2){
			strcpy(Role, "Concierge");
		} else{
			strcpy(Role, "-");
		}

		if(UserData.Status == 1){
			strcpy(Status, "Login");
		} else{
			strcpy(Status, "Logout");
		}
		
		printf("     %-5d %-26s %-15s %-38s %-15s %-17s %-10s\n", UserData.Code, UserData.FullName, UserData.Username, UserData.Email, UserData.Password, Role, Status);
	}
	
	printf("\n\n\n");
	
	/* Close User */
	fclose(f_user);
}

void ReadUser() 
{
	/* Call Modul Show Data User */
	ShowUser();
	
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    
    /* Call Modul Menu User */
    MenuUser();
} 

void UpdateUser()
{
	int Code;
	User UserData, TempUserData;
	FILE *f_user, *f_tempuser;
	
	fflush(stdin);
	printf("Enter the User Code to be updated : ");
	scanf("%d", &Code);
	
	printf("Full Name : ");
	fflush(stdin);
	scanf("%[^\n]", &TempUserData.FullName);
	
	printf("Username : ");
	fflush(stdin);
	gets(TempUserData.Username);
		
	printf("Email : ");
	fflush(stdin);
	gets(TempUserData.Email);
		
	printf("Password : ");
	fflush(stdin);
	gets(TempUserData.Password);
		
	printf("Role (1/2) : ");
	fflush(stdin);
	scanf("%d", &TempUserData.Role);

	fflush(stdin);
	TempUserData.Status = 0;
	
	/* Open File */
	f_user = fopen("User.DAT", "rb");
	f_tempuser = fopen("TempUser.DAT", "wb");
	
	/* Error Handle About Open File */
	if (!f_user) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		MenuUser();
    } 
    
    /* Error Handle About Open File */
    if (!f_tempuser) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
		
		system("cls");
		MenuUser();
    }
	
	while (fread(&UserData, sizeof(UserData),1, f_user))
	{
		if(Code == UserData.Code){
			TempUserData.Code = UserData.Code;
			fwrite(&TempUserData, sizeof(TempUserData), 1, f_tempuser);
		}  else {
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
	
	system("cls");
	printf("Data successfully updated!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
	
	system("cls");
	
	/* Call Modul Menu User */
	MenuUser();
}

int CheckUserCode(User UserData, int ID)
{
	FILE *f_user;
	
	/* Open File */
	f_user = fopen("User.DAT","rb");
	while(fread(&UserData, sizeof(UserData), 1, f_user))
	{
		if(ID == UserData.Code)
		{
			/* Close File */
			fclose(f_user);
			return 1;
		}
	}
}

void DeleteUser()
{
	int MenuDelete;
	
	/* Call Modul Show Data User */
	ShowUser();
	
	printf("|==================================|\n");
	printf("|            User Delete           |\n");
	printf("|==================================|\n");
	printf("|1. One Record                     |\n");
	printf("|2. All                            |\n");
	printf("|3. Back                           |\n");
	printf("|==================================|\n");
	
    printf("\n");
    printf("Select Menu : ");
	scanf("%d", &MenuDelete);
	system("cls");
	
    switch (MenuDelete) { 
        case 1:
        	/* Call Modul Alert Delete One Record Data User */
			AlertDeleteOneRecordUser();
			break;
		case 2:
			/* Call Modul Alert Delete All Data User */
			AlertDeleteAllUser();
			break;
		case 3:
			/* Call Modul Menu User */
			MenuUser();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!\n");
	 		printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			
			/* Call Modul Delete Data User */
			DeleteUser();
			break;
    }
}

void AlertDeleteOneRecordUser()
{
	User UserData;
	char Answer;
	int Code;
	
	printf("\n");
	printf("Enter the User Code to be deleted : ");
	scanf("%d", &Code);
	fflush(stdin);
	
	printf("\n");
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		DeleteOneRecordUser(UserData, Code);
		
		printf("Data successfully deleted!!!\n");
		printf("Press Any Key to continue . . .");
		getch();
		
		system("cls");
		DeleteUser();
	}
	
	system("cls");
	
	/* Call Modul Delete Data User */
	DeleteUser();
}

void DeleteOneRecordUser(User UserData, int ID)
{
	FILE *f_user, *f_tempuser;
	int Code, Check;
	
	Check = CheckUserCode(UserData, ID);
		
	if(Check != 0)
	{
		/* Open File */
		f_user = fopen("User.DAT", "rb");
		f_tempuser = fopen("TempUser.DAT", "wb");
		
		while (fread(&UserData, sizeof(UserData), 1, f_user))
		{
			Code = UserData.Code;
			if (Code != ID){
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
	} else{
		system("cls");
		printf("ERROR : User data with code %d not found!!!\n", ID);
		printf("Press Any Key to continue . . .");
		getch();
			
		system("cls");
		
		/* Call Modul Alert Delete One Record Data User */
		AlertDeleteOneRecordUser();
	}
}

void AlertDeleteAllUser()
{
	char Answer;
	
	printf("Are you sure? (Y/N)");
	Answer = getche();
	
	if (Answer == 'Y' || Answer == 'y')
	{
		system("cls");
		
		/* Call Modul Delete All Data User */
		DeleteAllUser();
	}
	system("cls");
	
	/* Call Modul Delete Data User */
	DeleteUser();
}

void DeleteAllUser()
{
	FILE *f_user;
	
	/* Open File */
	f_user = fopen("User.DAT","wb");
	
	/* Close File */
	fclose(f_user);
	
	printf("All data was deleted!!!\n");
	printf("Press Any Key to continue . . .");
	getch();
			
	system("cls");
	
	/* Call Modul Delete Data User */
	DeleteUser();
}
