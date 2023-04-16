#include <stdio.h>
#include <string.h>
struct banker{
	char buser[20];
	char bpass[20];
	int bcode;
};
struct customer{
	int accno;
	char acctype[20];
	char accname[20];
	char cuser[20];
	char cpass[20];
	int ccode;
	float balance;
};
void deleteacc(customer list[],int id);
void addacc(customer temp);
void searchacc(customer list[], int id);
void updateacc(customer list[], int id);
void withdraw(customer list[], float amount, int id);
void transfer(customer list[], float amount, int id, int acc);
int main()
{
	FILE *st, *ct, *temp;
	int id, option=0, code, login = 0, i=0, bchoice = 0, cchoice = 0, account;
	float amount;
	char user[10], pass[10];
	banker staff[5];
	customer cust[20], tempo;
	printf("\t\t\t _____________________________________________________________________\n");
	printf("\t\t\t>\t\t\t\t\t\t\t\t     <\n");
	printf("\t\t\t>\t\t\tBank Mangement System\t\t\t     <\n");
	printf("\t\t\t>____________________________________________________________________<\n\n");
	printf("\t\t\t\t\t\tSelect Login Type: \n\t\t\t\t\t\t1. Staff\n\t\t\t\t\t\t2. Customer\n\n\t\t\t\t\t\tYour Choice: ");
	scanf("%d",&option);
	if(option == 1)
	{
		printf("\t\t\t\t\t\tEnter Username: ");
		scanf("%s",&user);
		printf("\t\t\t\t\t\tEnter Password: ");
		scanf("%s",&pass);
		printf("\t\t\t\t\t\tEnter Code: ");
		scanf("%d",&code);
		st = fopen("baccounts.txt","r+");
		while(fread(&staff[i], sizeof(banker), 1, st))
		{
			if(strcmp(user, staff[i].buser) == 0 && strcmp(pass, staff[i].bpass) == 0 && code == staff[i].bcode)
			{
				login = 1;
			}
			i++;
		}
		fclose(st);
		if(login == 1)
		{
			printf("\n\t\t\t\t\t\t***Login Successful***\n");
			while(bchoice != 6)
			{
				printf("\nChoose an Option:\n1. Add a Customer\n2. Remove a Customer\n3. List Customers\n4. Find a Customer\n5. Update a Customer\n6. Exit\n\nYour Choice: ");
				scanf("%d",&bchoice);
				if(bchoice == 1)
				{
					addacc(tempo);
				}
				else if(bchoice == 2)
				{
					printf("\nEnter Account Number of Customer: ");
					scanf("%d",&id);
					deleteacc(cust, id);
				}
				else if(bchoice == 3)
				{
					i = 0;
					ct = fopen("caccounts.txt","r+");
					while(fread(&cust[i], sizeof(customer), 1, ct))
					{
						printf("\nCustomer %d Details:\nAccount No: %d\nAccount Type: %s\nAccount Name: %s\nAccount Balance: %0.2f\n",i+1,cust[i].accno,cust[i].acctype,cust[i].accname,cust[i].balance);
						i++;
					}	
				}
				else if(bchoice == 4)
				{
					printf("Enter Account Number of Customer: ");
					scanf("%d",&id);
					searchacc(cust, id);
				}
				else if(bchoice == 5)
				{
					printf("Enter Account Number of Customer: ");
					scanf("%d",&id);
					updateacc(cust, id);
				}
				else if(bchoice == 6)
				{
					printf("\nProgram Terminated !");
					break;
				}
				else
				{
					printf("Invalid Option !\n");
				}
			}
		}
		else
		{
			printf("\n\t\t\t\t\t\tInvalid Credentials Entered !!!");
		}
	}
	else if(option == 2)
	{
		printf("\t\t\t\t\t\tEnter Username: ");
		scanf("%s",&user);
		printf("\t\t\t\t\t\tEnter Password: ");
		scanf("%s",&pass);
		printf("\t\t\t\t\t\tEnter Code: ");
		scanf("%d",&code);
		ct = fopen("caccounts.txt","r+");
		while(fread(&cust[i], sizeof(customer), 1, ct))
		{
			if(strcmp(user, cust[i].cuser) == 0 && strcmp(pass, cust[i].cpass) == 0 && code == cust[i].ccode)
			{
				login = 1;
				tempo.accno = cust[i].accno;
				tempo.balance = cust[i].balance;
				strcpy(tempo.acctype, cust[i].acctype);
				strcpy(tempo.accname, cust[i].accname);
			}
			i++;
		}
		fclose(ct);
		if(login == 1)
		{
			printf("\n\t\t\t\t\t\t***Login Successful***\n");
			while(cchoice != 4)
			{
				ct = fopen("caccounts.txt","r+");
				printf("\nChoose an Option:\n1. Your Account Information\n2. Withdraw Funds\n3. Transfer Funds\n4. Exit\n\nYour Choice: ");
				scanf("%d", &cchoice);
				if(cchoice == 1)
				{
					printf("\nAccount Number: %d\nAccount Type: %s\nAccount Name: %s\nAccount Balance: %0.2f\n",tempo.accno,tempo.acctype,tempo.accname,tempo.balance);
				}
				else if(cchoice == 2)
				{
					printf("\nEnter Amount to Withdraw: ");
					scanf("%f",&amount);
					id = tempo.accno;
					if(amount < tempo.balance)
					{
						withdraw(cust, amount, id);
					}
					else
					{
						printf("Invalid Amount Entered !\n");
					}
				}
				else if(cchoice == 3)
				{
					printf("\nEnter Amount to Transfer: ");
					scanf("%f",&amount);
					printf("Enter Destination Account: ");
					scanf("%d",&account);
					id = tempo.accno;
					if(amount < tempo.balance)
					{
						transfer(cust, amount, id, account);
					}
					else
					{
						printf("Invalid Amount Entered !\n");
					}
				}
				else if(cchoice == 4)
				{
					printf("\nProgram Terminated !");
					break;
				}
				else
				{
					printf("\nInvalid Option Entered !\n");
				}
			}
			fclose(ct);
		}
		else
		{
			printf("\n\t\t\t\t\t\t***Invalid Credentials Entered !");
		}
	}
}
void addacc(customer temp)
{
	FILE *t;
	t = fopen("caccounts.txt","a");				
	printf("\nEnter AccNo: ");
	scanf("%d",&temp.accno);
	printf("Enter AccType: ");
	scanf("%s",&temp.acctype);
	printf("Enter AccName: ");
	scanf("%s",&temp.accname);
	printf("Enter CUser: ");
	scanf("%s",&temp.cuser);
	printf("Enter CPass: ");
	scanf("%s",&temp.cpass);
	printf("Enter CCode: ");
	scanf("%d",&temp.ccode);
	printf("Enter Balance: ");
	scanf("%f",&temp.balance);
	fwrite(&temp, sizeof(customer), 1, t);
	fclose(t);
}
void deleteacc(customer list[],int id)
{
	FILE *c, *temp;
	int check=0;
	c = fopen("caccounts.txt","r+");
	temp = fopen("temp.txt","w+");
	int i=0;
	while(fread(&list[i], sizeof(struct customer), 1, c))
	{
		if(id == list[i].accno)
		{
			check = 1;
		}
		else
		{
			fwrite(&list[i], sizeof(struct customer), 1, temp);
		}
		i++;
	}
	fclose(c);
	fclose(temp);
					
	if(check == 1)
	{
		printf("Customer Acount Deleted !\n");
		i = 0;
		c = fopen("caccounts.txt","w+");
		temp = fopen("temp.txt","r+");
		while(fread(&list[i], sizeof(struct customer), 1, temp))
		{	
			fwrite(&list[i], sizeof(struct customer), 1, c);
			i++;
		}
	}
	else
	{
		printf("Customer Account Not Found !!\n");
	}
	check = 0;
	fclose(c);
	fclose(temp);
}
void searchacc(customer list[], int id)
{
	FILE *c;
	int check=0;
	c = fopen("caccounts.txt","r+");
	int i=0;
	while(fread(&list[i], sizeof(struct customer), 1, c))
	{
		if(id == list[i].accno)
		{
			printf("\nCustomer Details:\nAccount No: %d\nAccount Type: %s\nAccount Name: %s\nAccount Balance: %0.2f\n",list[i].accno,list[i].acctype,list[i].accname,list[i].balance);
		}
		i++;
	}
	fclose(c);
}
void updateacc(customer list[], int id)
{
	FILE *c, *temp;
	int check=0, opt, opt1;
	char type1[8] = "Current", type2[7] = "Saving", accn[10];
	float new1;
	c = fopen("caccounts.txt","r+");
	temp = fopen("temp.txt","w+");
	int i=0;
	while(fread(&list[i], sizeof(struct customer), 1, c))
	{
		if(id == list[i].accno)
		{
			printf("Select the Attribute:\n1. Account Type\n2. Account Name\n3. Balance\nYour Choice: ");
			scanf("%d", &opt);
			if(opt == 1)
			{
				printf("Choose New Account Type:\n1. Current\n2. Saving");
				scanf("%d", &opt1);
				{
					if(opt1 == 1)
					{
						strcpy(list[i].acctype, type1);
					}
					else if(opt1 == 2)
					{
						strcpy(list[i].acctype, type2);
					}
					else
					{
						printf("Invalid Option Entered !\n");
					}
				}
			}
			else if(opt == 2)
			{
				printf("Enter New Account Name: ");
				scanf("%s",accn);
				strcpy(list[i].accname, accn);
			}
			else if(opt == 3)
			{
				printf("Enter New Amount: ");
				scanf("%f",&new1);
				list[i].balance = new1;
			}
			else
			{
				printf("Invalid Option Entered !");
			}
		}
		fwrite(&list[i], sizeof(struct customer), 1, temp);
		i++;
	}
	printf("\nAccount Info Updated Successfully !\n");
	fclose(c);
	fclose(temp);
	i=0;
	temp = fopen("temp.txt","r+");
	c = fopen("caccounts.txt","w+");
	while(fread(&list[i], sizeof(struct customer), 1, temp))
	{	
		fwrite(&list[i], sizeof(struct customer), 1, c);
		i++;
	}
	fclose(c);
	fclose(temp);
}
void withdraw(customer list[], float amount, int id)
{
	FILE *c, *temp;
	int check=0;
	c = fopen("caccounts.txt","r+");
	temp = fopen("temp.txt","w+");
	int i=0;
	while(fread(&list[i], sizeof(struct customer), 1, c))
	{
		if(id == list[i].accno)
		{
			list[i].balance = list[i].balance - amount;
			check = 1;
		}
		fwrite(&list[i], sizeof(struct customer), 1, temp);
		i++;
	}
	fclose(c);
	fclose(temp);
	i=0;
	temp = fopen("temp.txt","r+");
	c = fopen("caccounts.txt","w+");
	while(fread(&list[i], sizeof(struct customer), 1, temp))
	{	
		fwrite(&list[i], sizeof(struct customer), 1, c);
		i++;
	}
	if(check = 1)
	{
		printf("\nAmount Withdrawal Successful !\n");
	}
	fclose(c);
	fclose(temp);
}
void transfer(customer list[], float amount, int id, int acc)
{
	FILE *c, *temp;
	int check=0;
	c = fopen("caccounts.txt","r+");
	temp = fopen("temp.txt","w+");
	int i=0;
	while(fread(&list[i], sizeof(struct customer), 1, c))
	{
		if(id == list[i].accno)
		{
			list[i].balance = list[i].balance - amount;
			check = 1;
		}
		fwrite(&list[i], sizeof(struct customer), 1, temp);
		i++;
	}
	fclose(c);
	fclose(temp);
	i=0;
	temp = fopen("temp.txt","r+");
	c = fopen("caccounts.txt","w+");
	while(fread(&list[i], sizeof(struct customer), 1, temp))
	{	
		fwrite(&list[i], sizeof(struct customer), 1, c);
		i++;
	}
	if(check = 1)
	{
		printf("\nAmount Successfully Transfered to %d.\n", acc);
	}
	fclose(c);
	fclose(temp);
}