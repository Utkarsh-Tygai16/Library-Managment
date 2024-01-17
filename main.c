#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "admin.h"
#include "user.h"
int reg(){
    char username[50], name[50], ch[50], fname;
    FILE*p=fopen("users.txt","r");
    printf("\t\t\tEnter username to create acccount.");
    scanf("\t\t\t%s",username);
    while(fgets(ch,sizeof(ch),p)!=NULL){
        ch[strcspn(ch,"\n")]='\0';
        if(strcmp(ch,username)==0){
            fclose(p);
            printf("\t\t\tUsername already exists.\n");
            reg();
        }
    }
    fclose(p);
    p=fopen("users.txt", "a");
    fprintf(p,"%s\n", username);
    fclose(p);
    adduserData(username,"Null","Null",0);
    printf("\t\t\tSuccessfully Registered\n");
    main();
    return 0;
}
int login(){
    char username[50], ch[50];
    int found=0;
    FILE*p=fopen("users.txt","r");
    printf("\t\t\tEnter username: ");
    scanf("\t\t\t%s",username);
    while (fgets(ch,sizeof(ch),p)!=NULL){
		ch[strcspn(ch,"\n")]='\0';
        if (strcmp(ch,username)==0){
        	found=1;
            break;
        }
    }
    fclose(p);
    if(found==1){
    	if(strcmp(username,"Admin")==0){
    		adminmenu();
    		main();
		}
		else{
			printf("\n\n\n\t\t\tWelcome %s",username);
    		usermenu();
    		main();
		}
    }
    else{
        printf("\n\t\t\tInvalid ID.\n");
        login();
    }
}    
void project_details(){
    printf("\t\t\tProject:Library Management System \n\t\t\tBy:Utkarsh Tyagi\n\t\t\tClass:3-C");
}
int main(){
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM\t\t\t\t\t\t\t\t\n");
    printf("\n\n\n\n\n\n");
    int n=0;
    do{
        printf("\t\t\tPress 1 to Register\n\t\t\tPress 2 to Login\n\t\t\tPress 3 to view 'Project Details'\n");
        scanf("\t\t\t%d",&n);
        if(n==1){
        	reg();
		}
        else if(n==2){
            login();
            return 0;
        }
        else if(n==3){
            project_details();
            main();
        }
        else{
            printf("\t\t\tInvalid choice entered.");
        }
    }while(n<=3);
    return 0;
}