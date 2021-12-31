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
#include "welcome.h"
#include "user.h"
/* ======= End of Header File ====== */
	
int UserMenu()
{
	int menu;
	
	printf("|==================================|\n");
	printf("|             Room Menu            |\n");
	printf("|==================================|\n");
	printf("|1. Create                         |\n");
	printf("|2. Read                           |\n");
	printf("|3. Update                         |\n");
	printf("|4. Delete                         |\n");
	printf("|5. Back                           |\n");
	printf("|==================================|\n");
    
    printf("\n\n");
    printf("Select Menu : ");
	scanf("%d", &menu);
	system("cls");
	
    switch (menu) { 
        case 1:
			UserCreate();
			break;
		case 2:
			UserRead();
			break;
		case 3:
			UserUpdate();
			break; 
		case 4:
			UserDelete();
			break;
	 	case 5:
			Welcome();
			break;
	 	default:
	 		printf("ERROR : Sorry I don't know the answer to this one!!!");
	 		getch();
	 		
	 		system("cls");
			UserMenu();
			break;
    }
}

void UserCreate()
{
	char more;
	int check;
	user userdata;
    FILE *f_user;
	
	f_user = fopen("User.DAT", "ab+");

    if (!f_user) 
    { 
        printf ("ERROR : Sorry the file is unavailable!!!\n");
		printf("Press Any Key to continue . . ."); 
		
		getch();
			
		system("cls");
		UserMenu(); 
    }
    
    do {
    	system("cls");
    	printf("|=====================================|\n");
		printf("|              Create Room            |\n");
		printf("|=====================================|\n");
	
		printf("Code User : ");
		fflush(stdin);
		scanf("%d", &userdata.code);
		
		check = CheckUserCode(userdata, userdata.code);
		
		if(check != 0)
		{
			system("cls");
			printf("ERROR : Room code has been used, please enter another code!!!\n");
			printf("Press Any Key to continue . . .");
			getch();
			
			system("cls");
			UserCreate();
		}
		
		printf("Full Name : ");
		fflush(stdin);
		scanf("%[^\n]",&userdata.fullname); 
		
		printf("Username : ");
		fflush(stdin);
		gets(userdata.username);
		
		printf("Email : ");
		fflush(stdin);
		gets(userdata.email);
		
		printf("Password : ");
		fflush(stdin);
		gets(userdata.password);
		
		printf("Role (Administrator/Operator) : ");
		fflush(stdin);
		gets(userdata.role);
		
		fflush(stdin);
		userdata.status = 0;
		
		fwrite(&userdata, sizeof(userdata), 1, f_user);
		
		printf("\n");
		printf("Do you want to create more data? (Y/N) ");
		fflush(stdin);
		
		more = getche();
	} while (more == 'Y' || more == 'y');
	
	fclose(f_user);
	
	system("cls");
	printf("The data is already stored in the file!!!\n");
	printf("Press Any Key to continue . . .");
	getche();
	
	system("cls");
	UserMenu();
}

void UserData()
{
	FILE *f_user;
	user userdata;
	
	f_user = fopen("User.DAT", "rt");
	
    if (!f_user) 
    { 
        printf ("ERROR : Sorry file cannot be open!!!\n"); 
        getch();
			
		UserMenu();
    } 

    printf("|==================================================|\n");
    printf("|                     User Data                    |\n");
    printf("|==================================================|\n");
    printf("| User ID      Full Name      Username     Email       Password     Role     Status|\n");
    printf("|==================================================|\n");
	
	while ((fread(&userdata, sizeof(userdata), JUM_BLOK, f_user)) == JUM_BLOK)
	{
		printf("  %d %s %s %s %s %s %d\n", userdata.code, userdata.fullname, userdata.username, userdata.email, userdata.password, userdata.role, userdata.status);
	}
	
	printf("\n\n\n");
	
	fclose(f_user);
}

void UserRead() 
{
	UserData();
	
    printf("Press Any Key to continue . . .");
    getche();
    
    system("cls");
    UserMenu();
} 

void UserUpdate()
{
	
}

int CheckUserCode(user userdata, int id)
{
	int i = 1;
	FILE *f_user;
	
	if(i == 1){
		f_user = fopen("User.DAT","rb");
		while(fread(&userdata, sizeof(userdata), 1, f_user))
		{
			if( id == userdata.code)
			{
				fclose(f_user);
				return 1;
			}
		}
	} else{
		i = 0;
		fclose(f_user);
		return 0;
	}
}

void UserDelete()
{
	
}
