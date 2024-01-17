struct node2{
	char bookname[150];
    int qty;
    int issued;
    struct node2*loc;
};
struct node2*Start=NULL;
struct usernode2{
	char username[50];
    char book1[100];
    char book2[100];
    int userIssued;
    struct usernode2*loc;
};
struct usernode2*Userstart=NULL;
int usermenu(){
    printf("\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\tUSERS MENU\t\t\t\t\t\t\n");
    printf("\n\n\n");
	int n=0;
    do{
        printf("\n\n\t\t\tPress 1 to view list of Books\n\t\t\tPress 2 to view list of Books issued\n");
        printf("\t\t\tPress 3 to check available Books\n\t\t\tPress 0 to return to main menu\n");
        scanf("\t\t\t%d",&n);
        if(n==0){
        	return 0;
		}
        else if(n==1){
        	showBooks();
		}
        else if(n==2){
            viewIssued();
        }
        else if(n==3){
            viewStatus();
        }
        else{
            printf("\t\t\tInvalid choice.");
        }
    }while(n<=3);
	return 0;
}
int showBooks(){
	char booknqty[200];
	char name[100];
	char status[100];
    int qty,issued;
	FILE*p=fopen("books.txt","r");
	if(p==NULL){
		printf("Error");
		return 0;
	}
	printf("\n\t\t\tBOOK \t\t\tINFO\n\n");
    while(fgets(booknqty,sizeof(booknqty),p)!=NULL){
        if(sscanf(booknqty,"%s %d %d",name,&qty,&issued)==3) {
        	if(qty>issued){
        		strcpy(status,"Available");
        		printf("\t\t\t%s\t\t\t%s\n",name,status);
			}
			else{
				strcpy(status,"Not Available");
        		printf("\t\t\t%s\t\t\t%s\n",name,status);
			}
        }
    }
    fclose(p);
	return 0;
}
int viewIssued() {
    char username[50];
    struct usernode2* userStart = NULL;
    struct usernode2* userEnd = NULL;
    FILE* p = fopen("usersdata.txt", "r");
    if (p == NULL) {
        printf("\n\t\t\tError\n\n");
        return 0;
    }
    char userData[300];
    while (fgets(userData, sizeof(userData), p) != NULL) {
        char exusername[50], exbook1[100], exbook2[100];
        int exuserIssued;
        if (sscanf(userData, "%s %s %s %d", exusername, exbook1, exbook2, &exuserIssued) == 4) {
            struct usernode2* temp = (struct usernode2*)malloc(sizeof(struct usernode2));
            strcpy(temp->username, exusername);
            strcpy(temp->book1, exbook1);
            strcpy(temp->book2, exbook2);
            temp->userIssued = (exuserIssued > 0) ? 1 : 0;
            temp->loc = NULL;
            if (userEnd == NULL) {
                userStart = temp;
            }
            else {
                userEnd->loc = temp;
            }
            userEnd = temp;
        }
    }
    fclose(p);
    printf("\t\t\tEnter your username: ");
    scanf("%s", username);
    struct usernode2* ucurrent = userStart;
    while (ucurrent != NULL) {
        if (strcmp(ucurrent->username, username) == 0) {
            if (ucurrent->userIssued == 0) {
                printf("\n\t\t\tNo books have been issued\n");
                return 0;
            }
            else if (ucurrent->userIssued == 1) {
                printf("\n\t\t\t1 book is issued.\n");
                printf("\t\t\tName of the book: %s\n", ucurrent->book1);
                return 0;
            }
            else if (ucurrent->userIssued == 2) {
                printf("\n\t\t\t2 books are issued. Only one book can be issued at a time.\n");
                printf("\t\t\tName of the book: %s\n", ucurrent->book1);
                return 0;
            }
            break;
        }
        ucurrent = ucurrent->loc;
    }
    return 0;
}
int viewStatus(){
	char name[100];
    printf("\t\t\tEnter Book: ");
    scanf("%s",name);
    struct node2*bookStart=NULL;
    struct node2*bookEnd=NULL;
    FILE*p=fopen("books.txt","r");
    if(p==NULL){
    	addBooks();
    	return 0;
	}
	char bookData[200];
    while(fgets(bookData,sizeof(bookData),p)!=NULL){
    	char exname[100];
    	int exqty,exissued;
        if(sscanf(bookData,"%s %d %d",exname,&exqty,&exissued)==3){
        	struct node2*temp=(struct node2*)malloc(sizeof(struct node2));
        	strcpy(temp->bookname,exname);
        	temp->qty=exqty;
        	temp->issued=exissued;
        	temp->loc=NULL;
        	
        	if(bookEnd==NULL){
        		bookStart=temp;
			}
			else{
				bookEnd->loc=temp;
			}
			bookEnd=temp;
		}
	}
	fclose(p);
	struct node2*current=bookStart;
    while(current!=NULL) {
        if(strcmp(current->bookname,name)==0) {
            if(current->issued<current->qty){
            	printf("\n\t\t\tBook is available.\n\n");
			}
			else{
				printf("\n\t\t\tBook is not available.\n\n");
			}
            return 0;
        }
        current=current->loc;
    }
	printf("\n\t\t\tBook is not available.\n\n");
	return 0;
}