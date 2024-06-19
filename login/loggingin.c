#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
struct loggingIn {
    char username[50];
    char pass[50];
} login;

struct signup {
    char name[50];
    char address[25];
    long long int phone;
    char email[40];
    char username[40];
    char password[15];
}form;

void loginPage();
void forgotPassword();
void signUp();
void hidePass(char *pass);
void loading();
int main() {
    int choice;
    while (1)
	{
		
        printf("\t\t\t:*********************************************************************:\n");
        printf("\t\t\t\t\t\tWelcome To Phonebook Application\n");
        printf("\t\t\t:*********************************************************************:\n");
        printf("\n\t\t\t\t\t 1.  Login");
        printf("\n\t\t\t\t\t 2.  Sign up ");
        printf("\n\t\t\t\t\t 3.  Forgot Password");
        printf("\n\t\t\t\t\t 4.  Exit");
        printf("\n\t\t\t:*********************************************************************:\n");
        fflush(stdin);
        printf("\n\n\n\n Enter Your Choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                loginPage();
                break;
            case 2:
                signUp();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                exit(0);
            default:
                printf("\n You Entered Wrong Choice......");
                break;
        }
    }
    return 0;
}

void loginPage() 
{
    int i = 0, count = 0;
    FILE *fileLogin;
    char username[50], pass[50],forgetPass;
    system("cls");
    //printf("\n\t\t\t---------Login Page--------");

    fileLogin = fopen("LoginPage.DAT", "rb");
    rewind(fileLogin);
    if (fileLogin == NULL) 
	{
        printf("\n File Not Found");
        exit(0);
    }
    reusername:
    printf("\n\t\t\t *****************Login Page*****************\n");
    printf("\n\n");
    printf("\n-------------------------------------------");
    fflush(stdin);
    printf("\nUsername: ");
    gets(username);
    int usernameExists=0;
    
    	while (fread(&form, sizeof(form), 1, fileLogin)==1)
		{
	        if(strcmp(username, form.username) == 0)
			{
	            usernameExists++;
				break;               
	        }
	    }
    fflush(stdin);
    while(i<3)
    {
	    printf("\n -------------------------------------------");
	    printf("\nPassword: ");
	    //gets(pass);
	    hidePass(pass);
	    fflush(stdin);
	    rewind(fileLogin);
	    count=0;
	
	    while (fread(&form, sizeof(form), 1, fileLogin)==1)
		{
			count ++;
	        if ((strcmp(username, form.username) == 0) && (strcmp(pass, form.password) == 0)) 
			{
	            system("cls");
	            printf("\n *********************************************");
	            printf("\n Successfully Logged in into System");
	            printf("\n *********************************************");
	            printf("\n\n");
	            fclose(fileLogin);
	            loading();
	            system("cls");
               // mainMenu();
                //system("pause"); 
				break;               
	        }
	    }
		if(usernameExists!=0)
		 {
	        system("cls");
	        printf("\n ***********************ERROR*************************");
	        printf("\n ******************************************************");
	        printf("\n No record Found");
	        printf("\n Please Sign up your account and then Login");
	        fclose(fileLogin);
            printf("\n");
        	system("pause");
            system("cls");
            return; 
	    }
	    printf("\n Incorrect Password. Try Again.");
	    i++;
	}
	system("cls");
	//printf("\n ***********************ERROR*************************");
    printf("\n ******************************************************");
    printf("\n Too many incorrect password attempts.");
    fclose(fileLogin);
    printf("\nDid you Forget Your Password?");
    printf("\nYes(y) or No(n): ");
    scanf("%c",&forgetPass);
    if(forgetPass=='y'||forgetPass=='Y')
    {
    	forgotPassword();
	}
	if(forgetPass=='n'||forgetPass=='N')
	{
		system("cls");
		return;
	}
    printf("\n");
    system("pause");
    system("cls");
}
void signUp() 
{
    FILE *fileLogin;
    int password_len;
    char confirmPass[15],chkUsername[50];
    fileLogin = fopen("LoginPage.DAT", "ab+");
    if (fileLogin == NULL) {
        printf("\nFile Not Found");
        exit(0);
    }
	fflush(stdin);
    printf("\nEnter Name: ");
    gets(form.name);
	fflush(stdin);
    printf("\nEnter address: ");
    gets(form.address);
	fflush(stdin);
    printf("\nEnter phone no: ");
    scanf("%lld", &form.phone);
    
	fflush(stdin);
    printf("\nEnter email: ");
    gets(form.email);
	fflush(stdin);
	reuser:
    printf("\nEnter username: ");
    gets(chkUsername);
    while (fread(&form, sizeof(form), 1, fileLogin)==1)
		{
			//count ++;
	        if(strcmp(chkUsername, form.username) == 0)
			{
	            //system("cls");
	            printf("\n *********************************************");
	            printf("\n Username Already Exist. Try Again.'");
	            printf("\n *********************************************");
	            printf("\n\n");
	            fclose(fileLogin);
	            loading();
	            system("cls");
	            goto reuser;
               // mainMenu();
                //system("pause"); 
				break;               
	        }
	    }
	fflush(stdin);
	strcpy(chkUsername,form.username);
	// Code for Strong Password
	fflush(stdin);
	password_check:
	system("cls");
	printf("\n *******************************************************************");
	printf("\n Enter the Strong Password");
	printf("\n *******************************************************************");
	printf("\n The Password Must Contain");
	printf("\n 1. Maximum 15 Characters");
	printf("\n 2. Must contain atleast One Digit/Number");
	printf("\n 3. Must contain atleast One Symbol '@', '#', '*', '$'");
	printf("\n 4. Must contain atleast One Capital Letter");
	
	printf("\n *******************************************************************");
	printf("\n\n");
	fflush(stdin);
	printf("\n:--------------------------------------------:");
	fflush(stdin);
	printf("\nPassword: ");
	//gets(form.password);
	hidePass(form.password);
	printf("\nConfirm Password: ");
	//gets(confirmPass);
	hidePass(confirmPass);
	if (strcmp(form.password,confirmPass)!= 0) 
	{
       		loading();
            printf("\nPasswords do not match. Please try again.\n");
            Sleep(4000);
            goto password_check;
    }
	password_len = strlen(form.password);
	if(password_len>15)
	{
		printf("\n *************************************************************");
		printf("\n Password is too Long.... Must have maximum 15 Characters");
		printf("\n *************************************************************");
		Sleep(5000);
		goto password_check;
		
	}
	int i=0;
	fflush(stdin);
	int count_numbers=0;
	int count_alphabets=0;
	int count_special_characters=0;
	for(i=0; i<15; i++)
	{
		if(form.password[i]>=48 && form.password[i]<=57)
		{
			count_numbers++;
		}
		if(form.password[i]>='A' && form.password[i]<='Z')
		{
			count_alphabets++;
		}
		if(form.password[i]=='@' || form.password[i]=='#' || form.password[i]=='*' || form.password[i]=='$')
		{
			count_special_characters++;
		}
	}
	if(count_numbers>0 && count_alphabets>0 && count_special_characters>0 )
	{
		printf("\n The Entered Password is Strong");
		loading();
		
	}
	else
	{
		printf("\n\n");
		printf("\n *************************************************");
		printf("\n The Entered Password is not Strong Enough");
		printf("\n *************************************************");
		Sleep(5000);
		goto password_check;
		
	}
    fwrite(&form, sizeof(form), 1, fileLogin);
    
	fclose(fileLogin);
    system("cls");
    printf("\n *********************************************");
    printf("\n\t\t\t Successfully Signed Up");
    printf("\n *********************************************");
    printf("\n");
    system("pause");
    system("cls");
}

void forgotPassword()
{
	FILE *fileLogin;
    fileLogin = fopen("LoginPage.DAT", "rb+");
    if (fileLogin == NULL)
	{
        printf("\nFile Not Found");
        exit(0);
    }
	long long int forgot_password_number;
	char forgot_password_username[15],new_password[15];
	
	int count_not_found=0;
	fflush(stdin);
	rewind(fileLogin);
	system("cls");
	printf("\n *****************FORGOT PASSWORD*****************");
	printf("\n Enter username: ");
	fflush(stdin);
	gets(forgot_password_username);
	printf("\n Enter Phone Number: ");
	scanf("%lld", &forgot_password_number);
	while(fread(&form,sizeof(form),1,fileLogin))
	{
		if (strcmp(forgot_password_username,form.username)==0 && (forgot_password_number==form.phone))
		{
				system("cls");
				printf("\n *************** Reset Password****************\n\n");
				/*printf("\n Username                       |                 Password                    ");
				printf("\n Username = %s      |      Password = %s", form.username, form.password);
				*/
				printf("\nEnter New Password: ");
				fflush(stdin);
				//gets(new_password);
				hidePass(new_password);
				strcpy(form.password,new_password);
				fseek(fileLogin,-sizeof(form),SEEK_CUR);
				fwrite(&form,sizeof(form),1,fileLogin);
				printf("\n password successfully reset\n");
				count_not_found++;
				//system("pause");
				loading();
				system("cls");
				break;
		}
	}
	if(count_not_found==0)
	{
		//system("cls");
		printf("\n *****************************************");
		printf("\n The Account is not Registered");
		printf("\n *****************************************");
		printf("\n\n");
		system("pause");
		system("cls");
	}
}

void loading()
{
	printf("\nLoading");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);
    printf(".");
    Sleep(500);	
}

void hidePass(char *pass) 
{
    char ch;
    int i = 0;
    while ((ch = getch()) != '\r') 
	{ 
        if (ch == '\b') 
		{ // Backspace handling
            if (i > 0) 
			{
                printf("\b \b");
                i--;
            }
        } 
		else 
		{
            pass[i] = ch;
            printf("*");
            i++;
        }
    }
    pass[i] = '\0';
}

