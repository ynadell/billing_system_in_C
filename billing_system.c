#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
FILE *fptr1;
FILE *fptr2;
typedef struct produc{
    int barcode;
    float price;
    int items;
}product;
typedef struct accoun{
    long long int phone;
    int id;
    char name[100];
    int transactions;
    float total_spent;
}account;
product menu[100];int top1=-1;//stack for products
account list[100];int top2=-1;//stack for accounts
void insert_products()
{
    top1++;
    printf("Enter the barcode\n");
    scanf("%d",&menu[top1].barcode);
    fprintf(fptr2,"%d\n",menu[top1]);
    printf("Enter the price\n");
    scanf("%f",&menu[top1].price);
    fprintf(fptr2,"%f\n",menu[top1].price);
}
void insert_account()
{
    top2++;
    printf("Enter the phone number\n");
    scanf("%lld",&list[top2].phone);
    fprintf(fptr1,"%d\n",list[top2].phone);
    //list[top2].id=rand();
    printf("Enter the name\n");
    scanf("%s",list[top2].name);
    fprintf(fptr1,"%s\n",list[top2].name);
    list[top2].transactions=0;
    list[top2].total_spent=0;
}
void show_product(product a)
{
    printf("\n\t\t\t\t\t%d is the barcode and %.2f is the price\n",a.barcode,a.price);
}
void show_account(account a)
{
    printf("\n\t\t\t\t\t-=-=-=-=-=-=-=-\n\t\t\t\t\tCustomer Name:%s\n\t\t\t\t\tPhone Number: %lld\n\n\t\t\t\t\tTransactions: %d\n\t\t\t\t\tTotal Spent: %f\n\t\t\t\t\t-=-=-=-=-=-=-=-\n",a.name,a.phone,a.id,a.transactions,a.total_spent);
}
int main()
{
    fptr1=fopen("C:\\Users\\DELL\\Desktop\C\\Billing system in c\\products.txt","r");
    fptr2=fopen("C:\\Users\\DELL\\Desktop\C\\Billing system in c\\customers.txt","a+");
    int bcode,flag,item;
	float pric;
    char c[25];
	while(!feof(fptr1))
	{
        fscanf(fptr1,"%d %f %d",&bcode,&pric,&item);
        top1++;
        menu[top1].barcode=bcode;
        menu[top1].price=pric;
        menu[top1].items=item;
        //printf("%d %.2f %d\n",menu[top1].barcode,menu[top1].price,menu[top1].items);
    }
    char nam[100];
    int transaction;
    long long int number;
    float total;
    while(!feof(fptr2))
	{
        fscanf(fptr2,"%lld %s %d %f",&number,nam,&transaction,&total);
        top2++;
        list[top2].phone=number;
        strcpy(list[top2].name,nam);
        list[top2].transactions=transaction;
        list[top2].total_spent=total;
        //printf("%lld %s %d %f\n",list[top2].phone,list[top2].name,list[top2].transactions,list[top2].total_spent);
    }
    system("color 70");//terminal text colors
    int emp_id,n,code=0;
    long long int phon;
    float sum;
    while(1)
    {
        system("cls");
        sum=0;
        printf("\n\n\t\t\t\t\tPlease Enter your employee id to login\n\t\t\t\t\t\t-1 to quit\n\t\t\t\t\t\t");
        scanf("%d",&emp_id);
        if((emp_id<99 && emp_id>0) || emp_id>1000)//three digit number
        {
            printf("\n\t\t\t\t\t\tPlease enter a valid employee id\n");continue;
        }
        else if(emp_id<0)
        {
            printf("\t\t\t\t\t\tHave a nice day\n");break;
        }
        system("cls");
        printf("\n\n\t\t\t\t\tHello employee %d, What do you want to do?\n\t\t\t\t\t\t1) Add Account\n\t\t\t\t\t\t2)Enter billing\n\t\t\t\t\t",emp_id);
        scanf("%d",&n);
        if(n==1)
        {
            system("cls");
            printf("\n\n\t\t\t\t\tAccount add\n");
            insert_account();
            fprintf(fptr2,"\n\t\t\t\t\t%lld\n\t\t\t%s\n\t\t\t\t\t%d\n\t\t\t\t\t%f\n",list[top2].phone,list[top2].name,list[top2].transactions,list[top2].total_spent);
            printf("\n\n\t\t\t\t\t\tEnter any character to continue\n\t\t\t\t\t\t");
            scanf("%s",c);
        }
        else if(n==2)
        {
            system("cls");
            code=0;
            printf("\n\n\n\t\t\t\t\t-=-=-=-=-=-=-=-\n");
            printf("\t\t\t\t\tPlease enter the product code\n\t\t\t\t\t-1 to checkout\n");
            while(code>=0)
            {
                printf("\t\t\t\t\tProduct Code: ");
                scanf("%d",&code);
                for(int i=0;i<=top1;i++)
                {
                    if(code==menu[i].barcode)
                    {
                        while(1)
                        {
                            printf("\t\t\t\t\t\t");
                            show_product(menu[i]);
                            printf("\n\t\t\t\t\tHow many items?: ");
                            scanf("%d",&flag);
                            if(flag<0){printf("\t\t\t\t\t\tPlease recheck the value\n");break;}
                            sum=(menu[i].price)*flag+sum;
                            if(flag<menu[i].items)
                            {
                                menu[i].items-=flag;
                                break;
                            }
                            else
                            {
                                printf("\n\t\t\t\t\t\tNot enough items\n\t\t\t\t\t\tEnter 0 to skip this item\n");continue;
                            }
                        }
                    }
                }
            }
            printf("\n\t\t\t\t\t\t-=-=-=-=-=-=-=-\n");flag=0;
            system("cls");
            printf("\n\n\t\t\t\t\tPlease enter the customer phone number\n\t\t\t\t\t\t0 for anonymous billing: ");
            scanf("%lld",&phon);
            for(int i=0;i<=top2;i++)
            {
                if(phon==list[i].phone)
                {
                    list[i].transactions++;
                    list[i].total_spent+=sum;
                    show_account(list[i]);flag=9;
                    printf("\n\t\t\t\t\t\t*^*^*^*^*^*^*^*^*^*^\n\t\t\t\t\t\tThe customer has to pay %.2f\n\t\t\t\t\t\t*^*^*^*^*^*^*^*^*^*^\n",sum);
                    break;
                }
            }
            if(flag!=9)
            printf("\n\t\t\t\t\t\t*^*^*^*^*^*^*^*^*^*^\n\n\n\t\t\t\t\t\tCustomer not in loyalty program\n\t\t\t\t\t\tThe customer has to pay %.2f\n\n\n\t\t\t\t\t\t*^*^*^*^*^*^*^*^*^*^\n",sum);
            printf("\n\n\t\t\t\t\t\tEnter any character to continue\n\t\t\t\t\t\t\t");
            scanf("%s",c);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    fptr1=fopen("products.txt","w");
    fptr2=fopen("customers.txt","w");
    for(int i=0;i<=top2;i++)
    {
        //printf("\n***Copying***\n%lld\n%s\n%d\n%f\n",list[i].phone,list[i].name,list[i].transactions,list[i].total_spent);
        fprintf(fptr2,"%lld\n%s\n%d\n%f\n",list[i].phone,list[i].name,list[i].transactions,list[i].total_spent);
    }
    for(int i=0;i<=top1;i++)
    {
        fprintf(fptr1,"%d %f %d\n",menu[i].barcode,menu[i].price,menu[i].items);
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

