#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>

struct signup {
    char name[50];
    char address[25];
    long long int phone;
    char email[40];
    char username[40];
    char password[15];
}form;

struct Data {
    char name[50];
    long long int phone_no;
    char email[30];
    char dob[11];
}info;

void red () 
{
  printf("\033[1;31m");
}

void green()
{
  printf("\033[1;32m");
}

void reset () 
{
  printf("\033[0m");
}

void loginPage();
void forgotPassword();
void signUp();
void loading();
void mainMenu();
void add_contact();
void birthday_reminder();
void display_contact();
void delete_contact();
void search_contact();
void modify_contact();
void sort_contacts(struct Data [], int );
int validate_dob(char []);
void hidePass(char *pass);
void loginMenu();

int main() 
{
    loginMenu();
    return 0;
}

void loginMenu()
{
	int choice;
    while (1)
	{
		reset();
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
        switch (choice) 
		{
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
                break;
            default:
            	red();
                printf("\n You Entered Wrong Choice......");
                system("cls");
                break;
        }
    }
}

void loginPage() 
{
    int i = 0;
    FILE *fileLogin;
    char username[40], pass[15],forgetPass;
    int usernameExists = 0;
    int passwordCorrect = 0;
    system("cls");
    reset();
    reusername:
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tLogin Page\n");
    printf("\t\t\t:*********************************************************************:\n\n");
    fileLogin = fopen("LoginPage.DAT", "rb");
    rewind(fileLogin);
    if (fileLogin == NULL) 
	{
		red();
        printf("\n File Not Found");
        exit(0);
    }
    reset();
    printf("\n\n");
    printf("\n-------------------------------------------");
    fflush(stdin);
    printf("\nUsername: ");
    gets(username);
	    repass:
    fflush(stdin);
	    printf("\n -------------------------------------------");
	    printf("\nPassword: ");
	    //gets(pass);
	    hidePass(pass);
	    fflush(stdin);
	    rewind(fileLogin);
        loading();
        
        while (fread(&form, sizeof(form), 1, fileLogin) == 1)
		{
            if (strcmp(username, form.username) == 0) 
			{
                usernameExists = 1;
                if (strcmp(pass, form.password) == 0) 
				{
                    passwordCorrect = 1;
                    break;
                }
            }
        }
        if(usernameExists==0)
		 {
		 	red();
	        printf("\n ******************************************************");
	        printf("\n Incorrect Username or password");
	        printf("\n ******************************************************");
	        printf("\n Please Sign up your account and then Login");
	        fclose(fileLogin);
            printf("\n");
            reset();
        	loading();
            system("cls");
            loginMenu();
	    }
	    if (usernameExists == 1 && passwordCorrect == 1) 
			{
				green();
	            system("cls");
	            green();
	            printf("\n *********************************************");
	            printf("\n Successfully Logged in into System");
	            printf("\n *********************************************");
	            printf("\n\n");
	            reset();
	            fclose(fileLogin);
	            loading();
	            system("cls");
                mainMenu();   
	        }
	        else
			{
				
		 		red();
			    printf("\n Incorrect Password. Try Again.");
			    i++;
			    reset();
			    if(i<3)
			    {
			    	goto repass;
			    }
			    if(i==3)
			    {
					system("cls");
					red();
				    printf("\n ******************************************************");
				    printf("\n Too many incorrect password attempts.");
				    printf("\n ******************************************************");
				    fclose(fileLogin);
				    reset();
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
			}
}

void signUp() 
{
    FILE *fileLogin;
    int password_len;
    char confirmPass[15],chkUsername[15];
    fileLogin = fopen("LoginPage.DAT", "ab+");
    if (fileLogin == NULL) {
        printf("\nFile Not Found");
        exit(0);
    }
    system("cls");
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tSign Up\n");
    printf("\t\t\t:*********************************************************************:\n\n");
	fflush(stdin);
    printf("\nEnter Name: ");
    gets(form.name);
	fflush(stdin);
    printf("\nEnter address: ");
    gets(form.address);
	fflush(stdin);
	rephone:
    printf("\nEnter phone no: ");
    scanf("%lld", &form.phone);
    if(form.phone<1000000000||form.phone>9999999999) //check if the number is of exactly 10 digits
	{
		red();
        printf("Error: Phone number must be exactly 10 digits.\n");
        reset();
        goto rephone;
        
    }
	fflush(stdin);
    printf("\nEnter email: ");
    gets(form.email);
	fflush(stdin);
    reuser:
    printf("\nEnter username: ");
    gets(chkUsername);
    while (fread(&form, sizeof(form), 1, fileLogin)==1)
		{
	        if(strcmp(chkUsername, form.username) == 0)
			{
	            red();
	            printf("\n *********************************************");
	            printf("\n Username Already Exist. Try Again.'");
	            printf("\n *********************************************");
	            printf("\n\n");
	            fclose(fileLogin);
	            reset();
	            loading();
	            goto reuser;
				break;               
	        }
	    }
	strcpy(form.username,chkUsername);
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
	hidePass(form.password);
	printf("\nConfirm Password: ");
	hidePass(confirmPass);
	if (strcmp(form.password,confirmPass)!= 0) 
	{
       		loading();
       		red();
       		printf("\n *************************************************************");
            printf("\nPasswords do not match. Please try again.\n");
            printf("\n *************************************************************");
            Sleep(4000);
            reset();
            goto password_check;
    }
	password_len = strlen(form.password);
	if(password_len>15)
	{
		red();
		printf("\n *************************************************************");
		printf("\n Password is too Long.... Must have maximum 15 Characters");
		printf("\n *************************************************************");
		loading();
		reset();
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
	loading();
	if(count_numbers>0 && count_alphabets>0 && count_special_characters>0 )
	{
		green();
		printf("\n *************************************************");
		printf("\n The Entered Password is Strong");
		printf("\n *************************************************\n");
		reset();
		loading();
		
	}
	else
	{
		printf("\n\n");
		red();
		printf("\n *************************************************");
		printf("\n The Entered Password is not Strong Enough");
		printf("\n *************************************************\n");
		reset();
		loading();
		goto password_check;
		
	}
    fwrite(&form, sizeof(form), 1, fileLogin);
	fclose(fileLogin);
    system("cls");
    green();
    printf("\n *********************************************");
    printf("\n\t\tSuccessfully Signed Up");
    printf("\n *********************************************");
    printf("\n");
    reset();
    loading();
    system("cls");
}

void forgotPassword()
{
	FILE *fileLogin;
	int password_len;
    fileLogin = fopen("LoginPage.DAT", "rb+");
    if (fileLogin == NULL)
	{
        printf("\nFile Not Found");
        exit(0);
    }
	long long int forgot_password_number;
	char forgot_password_username[15],new_password[15],confPass[15],email[40];
	int count_not_found=0;
	fflush(stdin);
	rewind(fileLogin);
	system("cls");
	printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tForget Password\n");
    printf("\t\t\t:*********************************************************************:\n");
	printf("\n Enter username: ");
	fflush(stdin);
	gets(forgot_password_username);
	reenter_phone:
	printf("\n Enter Phone Number: ");
	scanf("%lld", &forgot_password_number);
	    if(forgot_password_number<1000000000||forgot_password_number>9999999999) //check if the number is of exactly 10 digits
	{
		red();
        printf("Error: Phone number must be exactly 10 digits.\n");
        reset();
        goto reenter_phone;
        
    }
	fflush(stdin);
	printf("\nEnter your email: ");
	gets(email);
	fflush(stdin);
	while(fread(&form,sizeof(form),1,fileLogin))
	{
		//printf("hello");
		if (strcmp(forgot_password_username,form.username)==0 && (forgot_password_number==form.phone) && strcmp(email,form.email)==0)
		{
				loading();
				system("cls");
				repass:
				printf("\n *************** Reset Password****************\n\n");
				printf("\nEnter New Password: ");
				fflush(stdin);
				hidePass(new_password);
				printf("\nConfirm Password: ");
				hidePass(confPass);
				if (strcmp(new_password,confPass)!= 0) 
					{
       					loading();
       					red();
            			printf("\nPasswords do not match. Please try again.\n");
            			Sleep(4000);
            			system("cls");
            			reset();
            			goto repass;	
    				}
    			password_len = strlen(new_password);
	if(password_len>15)
	{
		red();
		printf("\n *************************************************************");
		printf("\n Password is too Long.... Must have maximum 15 Characters");
		printf("\n *************************************************************");
		Sleep(5000);
		reset();
		goto repass;
		
	}
	int i=0;
	fflush(stdin);
	int count_numbers=0;
	int count_alphabets=0;
	int count_special_characters=0;
	for(i=0; i<15; i++)
	{
		if(new_password[i]>=48 && new_password[i]<=57)
		{
			count_numbers++;
		}
		if(new_password[i]>='A' && new_password[i]<='Z')
		{
			count_alphabets++;
		}
		if(new_password[i]=='@' || new_password[i]=='#' || new_password[i]=='*' || new_password[i]=='$')
		{
			count_special_characters++;
		}
	}
	loading();
	if(count_numbers>0 && count_alphabets>0 && count_special_characters>0 )
	{
		green();
		printf("\n *************************************************");
		printf("\n The Entered Password is Strong");
		printf("\n *************************************************");
		reset();
		loading();
		system("cls");
	}
	else
	{
		
		printf("\n\n");
		red();
		printf("\n *************************************************");
		printf("\n The Entered Password is not Strong Enough");
		printf("\n *************************************************");
		reset();
		loading();
		system("cls");
		goto repass;
		
	}
				strcpy(form.password,new_password);
				fseek(fileLogin,-sizeof(form),SEEK_CUR);
				fwrite(&form,sizeof(form),1,fileLogin);
				loading();
				green();
				printf("\n *****************************************");
				printf("\n password successfully reset\n");
				printf("\n *****************************************");
				reset();
				count_not_found++;
				printf("\n");
				loading();
				system("cls");
				loginMenu();
		}
	}
	fclose(fileLogin);
	if(count_not_found==0)
	{
		red();
		printf("\n *****************************************");
		printf("\n The Account is not Registered");
		printf("\n *****************************************");
		printf("\n\n");
		reset();
		system("pause");
		system("cls");
	}
}

void mainMenu()
{
	 while (1) 
	{
        int entrychoice;
        printf("\t\t\t:*********************************************************************:\n");
        printf("\t\t\t\t\t\tPhonebook Application\n");
        printf("\t\t\t:*********************************************************************:\n");
        printf("\n");
        printf("\t\t\t\t\t1.Add new Contact\n");
        printf("\t\t\t\t\t2.Display Contact\n");
        printf("\t\t\t\t\t3.Search Contact\n");
        printf("\t\t\t\t\t4.Modify Contact\n");
        printf("\t\t\t\t\t5.Delete \n");
        printf("\t\t\t\t\t6.Birthday reminder\n");
        printf("\t\t\t\t\t7.Return To Login Page");
        printf("\n");
        printf("\t\t\t:*********************************************************************:\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &entrychoice);
    		system("cls");
        switch (entrychoice) 
		{
            case 1:
                add_contact();
                break;
            case 2:
                display_contact();
                break;
            case 3:
                search_contact();
                break;
            case 4:
                modify_contact();
                break;
            case 5:
                delete_contact();
                break;
            case 6:
                birthday_reminder();
                break;
            case 7:
            	loading();
            	system("cls");
                loginMenu();
                //break;
            default:
            	red();
                printf("\nInvalid Choice\n");
                reset();
                break;
        }
    }
}

void add_contact()
{
    FILE *ptr;
    ptr=fopen("Info.DAT","ab+");
    if(ptr==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }
    fflush(stdin);
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tAdd New Contact\n");
    printf("\t\t\t:*********************************************************************:\n");
    printf("Enter Your Name: ");
    gets(info.name);
    fflush(stdin);
    
	reenter_phone:
    printf("Enter Your Phone Number: ");
    scanf("%lld",&info.phone_no);
    if(info.phone_no<1000000000||info.phone_no>9999999999) //check if the number is of exactly 10 digits
	{
		red();
        printf("Error: Phone number must be exactly 10 digits.\n");
        reset();
        goto reenter_phone;
    }
    
    fflush(stdin);
    printf("Enter Your Email: ");
    gets(info.email);
    fflush(stdin);
    reenter_dob:
     printf("Enter Your Date of Birth (YYYY-MM-DD): ");
    gets(info.dob);
    if(validate_dob(info.dob)==0) 
	{
		red();
        printf("Error: Date of Birth must be in YYYY-MM-DD format.\n");
        reset();
        goto reenter_dob;
    }
    fwrite(&info, sizeof(info), 1, ptr);
    fclose(ptr);
    green();
    printf("\nContact added successfully\n");
    reset();
    printf("\n");
    system("pause");
    system("cls");
}

void display_contact() 
{
    FILE *ptr;
    ptr=fopen("Info.DAT","rb");
    if(ptr==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }
    int count=0,i=0;
    struct Data *contacts=NULL;
    
    while(fread(&info, sizeof(info), 1, ptr))
    {
        count++;
    }
    if(count==0) 
	{
		red();
        printf("\nNo contacts found\n");
        reset();
        fclose(ptr);
        return;
	}
    contacts=(struct Data*)malloc(count*sizeof(struct Data)); //memory allocattion of struct contact to sort
    if(contacts==NULL) 
	{
        printf("Memory allocation failed\n");
        fclose(ptr);
    }
    rewind(ptr);
    for(i=0;i<count;i++) 
	{
        fread(&contacts[i],sizeof(contacts[i]),1,ptr);
    }
    sort_contacts(contacts,count);
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tList of Contacts\n");
    printf("\t\t\t:*********************************************************************:\n");
    for(i=0;i<count;i++) //displaying in sorted format
	{
		printf("\n%d.\n",i+1);
        printf("Name: %s\n",contacts[i].name);
        printf("Phone number: %lld\n",contacts[i].phone_no);
        printf("Email: %s\n",contacts[i].email);
        printf("Date of Birth:%s",contacts[i].dob);
        printf("\n");
    }
    free(contacts);
    fclose(ptr);
    printf("\n");
    system("pause");
    system("cls");
}

void search_contact() 
{
	FILE *ptr;
    int count=0,i;
    int flag=0;
    struct Data *contacts=NULL;
    ptr=fopen("Info.DAT", "rb");
    if(ptr==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }
    char full_name[50];
    fflush(stdin);
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\tSearch your Contact\n");
    printf("\t\t\t:*********************************************************************:\n");
    printf("\nEnter your full name to search contact:");
    gets(full_name);
    rewind(ptr);
    while(fread(&info,sizeof(info),1,ptr)!=0)
    {
        if(strcmp(full_name,info.name)==0) 
		{
			
            printf("\nName: %s\n", info.name);
            printf("Phone number: %lld\n", info.phone_no);
            printf("Email: %s\n", info.email);
            printf("Date of Birth:%s\n",info.dob);
            printf("\n");
            flag=1;
            break;
        }
	}	
    if (flag==0) 
	{
		red();
        printf("\t\t\t:*********************************************************************:\n");
	    printf("\t\t\t\t\t\tName Not found\n");
	    printf("\t\t\t:*********************************************************************:\n");
	    reset();
	}
	    fclose(ptr);
	    printf("\n");
	    system("pause");
	    system("cls");
}

void modify_contact() 
{
	printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tModify Contact\n");
    printf("\t\t\t:*********************************************************************:\n");
    FILE *ptr;
    int flag=0;
    ptr=fopen("Info.DAT","rb+");
    if(ptr==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }
    char prev_name[50];
    fflush(stdin);
    printf("\nEnter your previous contact name to modify:");
    gets(prev_name);
    rewind(ptr);
    while (fread(&info,sizeof(info),1,ptr)!=0) 
	{
        if (strcmp(prev_name,info.name)==0) 
		{
            fseek(ptr,-sizeof(info),SEEK_CUR);
            reenter_phone:
    		printf("\nEnter Your Phone Number: ");
    		scanf("%lld",&info.phone_no);
    		if(info.phone_no<1000000000||info.phone_no>9999999999) //check if the number is of exactly 10 digits
			{
				red();
        		printf("Error: Phone number must be exactly 10 digits.\n");
        		reset();
        		goto reenter_phone;
   			 }
            fflush(stdin);
            printf("\nEnter Your Email: ");
    		gets(info.email);
    		fflush(stdin);
    		reenter_dob:
     		printf("\nEnter Your Date of Birth (YYY-MM-DD): ");
    		gets(info.dob);
   			 if(validate_dob(info.dob)==0) 
			{
				red();
        		printf("\nError: Date of Birth must be in YYYY-MM-DD format.\n");
        		reset();
        		goto reenter_dob;
   			 }
            fwrite(&info, sizeof(info), 1, ptr);
            flag=1;
            break;
        }
        fflush(stdin);
    }
    loading();
    if (flag==0) 
	{
		red();
        printf("\nName not found\n");
        reset();
    } 
	else 
	{
		green();
        printf("\nsuccessfully modified\n");
        reset();
    }
    fclose(ptr);
    printf("\n");
    system("pause");
    system("cls");
}

void delete_contact() 
{
    FILE*ptr,*temp;
    int flag=0;
    ptr=fopen("Info.DAT","rb");
    if(ptr==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }

    temp=fopen("Temp.DAT","a+");
    if (temp==NULL) 
	{
        printf("File Not Found!");
        exit(0);
    }
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tDelete Contact\n");
    printf("\t\t\t:*********************************************************************:\n");
    char del_name[50];
    fflush(stdin);
    printf("\nEnter your previous contact name to delete:");
    gets(del_name);
    rewind(ptr);
    while(fread(&info,sizeof(info),1,ptr)!=0) 
	{
        if(strcmp(del_name,info.name)!=0) 
		{
            fwrite(&info, sizeof(info), 1, temp);
        } 
		else 
		{
            flag = 1;
        }
    }
    fclose(ptr);
    fclose(temp);
    remove("Info.DAT");
    rename("Temp.DAT", "Info.DAT");
    if(flag==1) 
	{
		green();
		printf("\t\t:*********************************************************************:\n");
        printf("\n\t\tContact deleted successfully\n");
        printf("\t\t:*********************************************************************:\n");
        reset();
    } 
	else 
	{
		red();
		printf("\t\t:*********************************************************************:\n");
        printf("\n\t\tContact not found\n");
        printf("\t\t:*********************************************************************:\n");
        reset();
    }
    printf("\n");
    system("pause");
    system("cls");
}

void sort_contacts(struct Data contacts[],int n) 
{
	int i,j;
    struct Data temp;
    for (i=0; i<n-1;i++) 
	{
        for (j=i+1;j<n;j++) 
		{
            if (strcmp(contacts[i].name,contacts[j].name)>0) 
			{
                temp=contacts[i];
                contacts[i]=contacts[j];
                contacts[j]=temp;
            }
        }
    }
}

int validate_dob(char dob[])
{
	int i;
    if(strlen(dob)!=10) 
	return 0;
    if (dob[4]!='-'||dob[7]!= '-')
	return 0;
    for(i=0;i<10; i++)
	{
        if(i==4||i==7) 
		continue;
        if(dob[i]<'0'||dob[i]>'9') 
		return 0;
    }
    return 1;
}

void birthday_reminder()
{

    FILE *ptr;
    time_t t=time(NULL);     //gets the calander time
    struct tm tm =*localtime(&t); //converts calender time into local time
    char current_date[6]; // Format: MM-DD
    int found=0;

    snprintf(current_date,sizeof(current_date),"%02d-%02d",tm.tm_mon + 1,tm.tm_mday);

    ptr=fopen("Info.DAT","rb");
    if (ptr==NULL) 
	{
        printf("File Not Found!\n");
        exit(0);
    }
    printf("\t\t\t:*********************************************************************:\n");
    printf("\t\t\t\t\t\tToday's Birthday \n");
    printf("\t\t\t:*********************************************************************:\n");
    rewind(ptr);
    while (fread(&info, sizeof(info), 1, ptr) != 0) 
	{
        if (strncmp(&info.dob[5], current_date, 5) == 0) 
		{
			printf("\n-------------------------------------------");
            printf("\nHappy Birthday to you %s.\n", info.name);
            printf("\n-------------------------------------------");
            found=1;
        }
    }
    if(found==0) 
	{
		printf("\n-------------------------------------------");
        printf("\nWe don't have any birthdays today.\n");
        printf("\n-------------------------------------------");
    }
    fclose(ptr);
    printf("\n");
    system("pause");
    system("cls");
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
