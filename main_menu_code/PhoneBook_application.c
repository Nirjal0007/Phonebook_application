#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

struct Data {
    char name[50];
    long long int phone_no;
    char email[30];
    char dob[11];
}info;
void add_contact();
void birthday_remainder();
void display_contact();
void delete_contact();
void search_contact();
void modify_contact();
void sort_contacts(struct Data [], int );
int validate_dob(char []);


int main()
{
    while (1) 
	{
        int entrychoice;
        printf("\t\t\t:*********************************************************************:\n");
        printf("\t\t\t\t\t\tPhonebook Application\n");
        printf("\t\t\t:*********************************************************************:\n");
        printf("\n");
        printf("\t\t\t\t\t1.Add new contact\n");
        printf("\t\t\t\t\t2.Display contact\n");
        printf("\t\t\t\t\t3.Search contact\n");
        printf("\t\t\t\t\t4.modify contact\n");
        printf("\t\t\t\t\t5.Delete \n");
        printf("\t\t\t\t\t6.Birthday Remainder\n");
        printf("\t\t\t\t\t7.Exit");
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
                birthday_remainder();
                break;
            case 7:
                exit(0);
                break;
            default:
                printf("\nInvalid Choice\n");
                break;
        }
    }
    return 0;
}

void add_contact()
{
    FILE *ptr;
    ptr=fopen("Info.DAT","a+");
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
        printf("Error: Phone number must be exactly 10 digits.\n");
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
        printf("Error: Date of Birth must be in YYYY-MM-DD format.\n");
        goto reenter_dob;
    }
    fwrite(&info, sizeof(info), 1, ptr);
    fclose(ptr);
    printf("\nContact added successfully\n");
    printf("\n");
    system("pause");
    system("cls");
}

void display_contact() 
{
    FILE *ptr;
    ptr=fopen("Info.DAT","r");
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
        printf("\nNo contacts found\n");
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
    ptr=fopen("Info.DAT", "r");
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
            printf("Name: %s\n", info.name);
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
        printf("\nName not found\n");
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
    ptr=fopen("Info.DAT","r+");
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
    		printf("Enter Your Phone Number: ");
    		scanf("%lld",&info.phone_no);
    		if(info.phone_no<1000000000||info.phone_no>9999999999) //check if the number is of exactly 10 digits
			{
        		printf("Error: Phone number must be exactly 10 digits.\n");
        		goto reenter_phone;
   			 }
            fflush(stdin);
            printf("Enter Your Email: ");
    		gets(info.email);
    		fflush(stdin);
    		reenter_dob:
     		printf("Enter Your Date of Birth (YYY-MM-DD): ");
    		gets(info.dob);
   			 if(validate_dob(info.dob)==0) 
			{
        		printf("Error: Date of Birth must be in YYYY-MM-DD format.\n");
        		goto reenter_dob;
   			 }
            fwrite(&info, sizeof(info), 1, ptr);
            flag=1;
            break;
        }
        fflush(stdin);
    }
    if (flag==0) 
	{
        printf("\nName not found\n");
    } 
	else 
	{
        printf("\nsuccessfully modified\n");
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
    ptr=fopen("Info.DAT","r");
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
        printf("\nContact deleted successfully\n");
    } 
	else 
	{
        printf("\nContact not found\n");
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
void birthday_remainder()
{

    FILE *ptr;
    time_t t=time(NULL);     //gets the calander time
    struct tm tm =*localtime(&t); //converts calender time into local time
    char current_date[6]; // Format: MM-DD
    int found=0;

    snprintf(current_date,sizeof(current_date),"%02d-%02d",tm.tm_mon + 1,tm.tm_mday);

    ptr=fopen("Info.DAT","r");
    if (ptr==NULL) 
	{
        printf("File Not Found!\n");
        exit(0);
    }
    rewind(ptr);
    while (fread(&info, sizeof(info), 1, ptr) != 0) 
	{
        if (strncmp(&info.dob[5], current_date, 5) == 0) 
		{
            printf("Happy Birthday to you %s \n", info.name);
            found=1;
        }
    }
    if(found==0) 
	{
        printf("No upcoming birthdays found.\n");
    }
    fclose(ptr);
    printf("\n");
    system("pause");
    system("cls");
}
	


