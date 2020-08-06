#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<ctype.h>
#define MAX 100
COORD coord = { 0, 0 };
void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
typedef struct node{
                    char email[20];
                    char pwd[20];
                    char fName[20];
                    char lName[20];
                    char id[20];
                    char country[20];
                    char state[20];
                    char no[15];
                    char dob[15];
                    struct node* next;
                    }user;
typedef struct Node{
                    char email[20];
                    char pwd[20];
                    char fName[20];
                    char lName[20];
                    char id[20];
                    char country[20];
                    char state[20];
                    char no[15];
                    char dob[15];
                    struct Node *left, *right;
                    }tree;
typedef struct times{ char day[3], mon[3]; int date, hh, mm, ss, year;}times;
typedef struct stack{ times val[MAX]; unsigned int top;} stack;

user *l = NULL;
tree *tId = NULL;
tree *tEmail = NULL;
int **friends;
void delay(int number_of_seconds)
{

    int milli_seconds = 1000 * number_of_seconds;

    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds)
        ;
}
user* makeNode(char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    user *temp = (user *)malloc(sizeof(user));
    strcpy(temp->email, email);
    strcpy(temp->pwd, pwd);
    strcpy(temp->fName, fName);
    strcpy(temp->lName, lName);
    strcpy(temp->id, id);
    strcpy(temp->country, country);
    strcpy(temp->state, state);
    strcpy(temp->no, no);
    strcpy(temp->dob, dob);
    temp->next = NULL;
    return temp;
}
tree* createNode(char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    tree *temp = (tree *)malloc(sizeof(tree));
    strcpy(temp->email, email);
    strcpy(temp->pwd, pwd);
    strcpy(temp->fName, fName);
    strcpy(temp->lName, lName);
    strcpy(temp->id, id);
    strcpy(temp->country, country);
    strcpy(temp->state, state);
    strcpy(temp->no, no);
    strcpy(temp->dob, dob);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
tree* insertId(tree *t, char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    if(!t)
        return createNode(email, pwd, fName, lName, id, country, state, no, dob);
    if(strcmp(id, t->id) < 0)
        t->left=insertId(t->left, email, pwd, fName, lName, id, country, state, no, dob);
    else if(strcmp(id, t->id) > 0)
        t->right=insertId(t->right, email, pwd, fName, lName, id, country, state, no, dob);
    return t;
}
tree* insertEmail(tree *t, char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    if(!t)
        return createNode(email, pwd, fName, lName, id, country, state, no, dob);
    if(strcmp(email, t->email) < 0)
        t->left=insertEmail(t->left, email, pwd, fName, lName, id, country, state, no, dob);
    else if(strcmp(email, t->email) > 0)
        t->right=insertEmail(t->right, email, pwd, fName, lName, id, country, state, no, dob);
    return t;
}
user* iE(user *l, char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    user *head = l;
    if(!l)
        return makeNode(email, pwd, fName, lName, id, country, state, no, dob);
    while(l->next)
        l = l->next;
    l->next = makeNode(email, pwd, fName, lName, id, country, state, no, dob);
    return head;
}

user* getUser(user *l)
{
    char email[20], pwd[20], fName[20], lName[20], id[20], country[20], state[20], no[15], dob[15];
    FILE *fp = fopen("userId.txt", "r");
    while(fscanf(fp, "%s%s%s%s%s%s%s%s%s",email, pwd, fName, lName, id, country, state, no, dob) != -1)
        l = iE(l, email, pwd, fName, lName, id, country, state, no, dob);
    return l;
}
tree* getUserT(user *l, tree *t, int a)
{
    char email[20], pwd[20], fName[20], lName[20], id[20], country[20], dob[15], no[15], state[20];
    t = NULL;
    if(a)
        while(l)
        {
            t = insertEmail(t, l->email, l->pwd, l->fName, l->lName, l->id, l->country, l->state, l->no, l->dob);
            l = l->next;
        }
    else
        while(l)
        {
            t = insertId(t, l->email, l->pwd, l->fName, l->lName, l->id, l->country, l->state, l->no, l->dob);
            l = l->next;
        }
    return t;
}
tree* getUserDataId(tree *t, char id[20])
{
    if(!t)
        return NULL;
    else if(strcmp(id, t->id) < 0)
        return getUserDataId(t->left, id);
    else if(strcmp(id, t->id) > 0)
        return getUserDataId(t->right, id);
    else
        return t;
}
tree* getUserDataEmail(tree *t, char email[20])
{
    if(!t)
        return NULL;
    else if(strcmp(email, t->email) < 0)
        return getUserDataEmail(t->left, email);
    else if(strcmp(email, t->email) > 0)
        return getUserDataEmail(t->right, email);
    else
        return t;
}
void inits(stack *s)
{
    s->top=0;
}

int push(stack *s,char y[],char z[],int date,int hh,int mm,int ss, int year)
{
    if(s->top==MAX-1) return 0;
    s->top=s->top+1;
    strcpy(s->val[s->top].day,y);
    strcpy(s->val[s->top].mon,z);
    s->val[s->top].date=date;
    s->val[s->top].hh=hh;
    s->val[s->top].mm=mm;
    s->val[s->top].ss=ss;
    s->val[s->top].year=year;
    return 1;
}

int pop(stack *s,char y[],char z[],int *date,int *hh,int *mm,int *ss, int *year)
{
    if(s->top==0) return 0;
    strcpy(y,s->val[s->top].day);
    strcpy(z,s->val[s->top].mon);
    *date=s->val[s->top].date;
    *hh=s->val[s->top].hh;
    *mm=s->val[s->top].mm;
    *ss=s->val[s->top].ss;
    *year=s->val[s->top].year;
    s->top=s->top-1;
    return 1;
}

int noOfUsers(user *l)
{
    int i = 0;
    while(l)
        i++, l = l->next;
    return i;
}
user* update(user *l, char email[20], char pwd[20], char fName[20], char lName[20], char id[20], char country[20], char state[20], char no[15], char dob[15])
{
    user* temp = l;
    while(temp)
    {
        if(strcmp(temp->email, email) == 0)
        {
                strcpy(temp->pwd, pwd);
                strcpy(temp->fName, fName);
                strcpy(temp->lName, lName);
                strcpy(temp->id, id);
                strcpy(temp->country, country);
                strcpy(temp->state, state);
                strcpy(temp->no, no);
                strcpy(temp->dob, dob);
        }
        temp = temp->next;
    }
    return l;
}
void viewProfile(tree *fbUser, int i)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 5);
    printf("\t%s %s :-", fbUser->fName, fbUser->lName);
    gotoxy(25, 7);
    int c =7;
    printf("\t\tFacebook Id    : %s", fbUser->id); gotoxy(25, c+2);
    printf("\t\tFirst Name     : %s", fbUser->fName); gotoxy(25, c+4);
    printf("\t\tLast Name      : %s", fbUser->lName); gotoxy(25, c+6);
    if(i)printf("\t\tEmail Id       : %s", fbUser->email); gotoxy(25, c+8);
    printf("\t\tDate Of  Birth : %s", fbUser->dob); gotoxy(25, c+10);
    if(i)printf("\t\tMobile Number  : %s", fbUser->no); gotoxy(25, c+12);
    printf("\t\tCountry        : %s", fbUser->country); gotoxy(25, c+14);
    printf("\t\tState          : %s", fbUser->state);
    getch();
}
tree* editProfile(tree *fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 4);
    printf("%s %s :- ", fbUser->fName, fbUser->lName);
    char a[5], fName[20], lName[20], id[20], country[20], state[20], no[15], dob[15];
    gotoxy(25, 6); printf("Facebook Id                   : %s", fbUser->id);
    gotoxy(25, 7); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        while(1)
        {
            gotoxy(25, 8); printf("Facebook Id                   : ");
            scanf("%s",id);
            tree *user = NULL;
            user = getUserDataId(tId, id);
            if(!user)
                break;
            else
                gotoxy(25, 9); printf("Id Already Taken!!! Enter a new Id!!!");
        }
    }
    else
        strcpy(id, fbUser->id);
    gotoxy(25, 10); printf("First Name                     : %s", fbUser->fName);
    gotoxy(25, 11); printf("Do you want to change(yes/no)  : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 12); printf("Enter                         : ");
        scanf("%s", fName);
    }
    else
        strcpy(fName, fbUser->fName);
    gotoxy(25, 13) ;printf("Last Name                     : %s", fbUser->lName);
    gotoxy(25, 14); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 15); printf("Enter                         : ");
        scanf("%s", lName);
    }
    else
        strcpy(lName, fbUser->lName);
    gotoxy(25, 16); printf("Date Of  Birth                : %s", fbUser->dob);
    gotoxy(25, 17); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 18); printf("Enter                         : ");
        scanf("%s", dob);
    }
    else
        strcpy(dob, fbUser->dob);
    gotoxy(25, 19); printf("Mobile Number                 : %s", fbUser->no);
    gotoxy(25, 20); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 21); printf("Enter                         : ");
        scanf("%s", no);
    }
    else
        strcpy(no, fbUser->no);
    gotoxy(25, 22); printf("Country        : %s", fbUser->country);
    gotoxy(25, 23); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 24); printf("Enter                        : ");
        scanf("%s", country);
    }
    else
        strcpy(country, fbUser->country);
    gotoxy(25, 25); printf("State                         : %s", fbUser->state);
    gotoxy(25, 26); printf("Do you want to change(yes/no) : ");
    scanf("%s", a);
    if(strcmp(a, "yes") == 0)
    {
        gotoxy(25, 27); printf("Enter                         : ");
        scanf("%s", state);
    }
    else
        strcpy(state, fbUser->state);
    l = update(l, fbUser->email, fbUser->pwd, fName, lName, id, country, state, no, dob);
    tId = getUserT(l, tId, 0);
    tEmail = getUserT(l, tEmail, 1);
    fbUser = getUserDataEmail(tEmail, fbUser->email);
    gotoxy(25, 29); printf("Profile updated !!");
    getch();
    viewProfile(fbUser, 1);
    return fbUser;
}
tree* changePwd(tree* fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    char pwd[20], pwd2[20];
    int c = 6;
    while(1)
    {
        gotoxy(25, c++); printf("Enter Current Password : ");
        int p=0;
        do
        {
            pwd[p]=getch();
            if(pwd[p] != '\r')
            printf("*");
            p++;
        }while(pwd[p-1]!='\r');
        pwd[p-1]='\0';
        if(strcmp(pwd, fbUser->pwd) == 0)
            break;
        else
            gotoxy(25, c++);printf("INCORRECT PASSWORD\n");
    }
    gotoxy(25, c++);printf("Enter New Password : ");
    int p=0;
    do
    {
        pwd[p]=getch();
        if(pwd[p] != '\r')
        printf("*");
        p++;
    }while(pwd[p-1]!='\r');
    pwd[p-1]='\0';
    while(1)
    {
        gotoxy(25, c++); printf("Confirm Password   : ");
        int p=0;
        do
        {
            pwd2[p]=getch();
            if(pwd2[p] != '\r')
            printf("*");
            p++;
        }while(pwd2[p-1]!='\r');
        pwd2[p-1]='\0';

        if(strcmp(pwd, pwd2) == 0)
            break;
        else
            gotoxy(25, c++); printf("Passwords did not match!!! Please enter correctly !");
    }
    l = update(l, fbUser->email, pwd2, fbUser->fName, fbUser->lName, fbUser->id, fbUser->country, fbUser->state, fbUser->no, fbUser->dob);
    tId = getUserT(l, tId, 0);
    tEmail = getUserT(l, tEmail, 1);
    fbUser = getUserDataEmail(tEmail, fbUser->email);
    gotoxy(25, c+1); printf("Password changed succesfully!!!");
    getch();
    return fbUser;
}
int getPos(tree *fbUser, user *l)
{
    int i = 0;
    while(l)
     {
        if(strcmp(fbUser->id, l->id) == 0)
            break;
        i++;
        l = l->next;
     }
    return i;
}
char* getId(int i, user *l)
{
    int j = 0;
    user *t = l;
    while(t && j != i)
    {
        j++;
        t = t->next;
    }
    return t->id;
}
int getPosId(char id[20], user *l)
{
    int i = 0;
    while(l)
    {
        if(strcmp(l->id, id) == 0)
            break;
        i++;
        l = l->next;
    }
    if(!l) return 0;
    return i;
}
int display(user *l, tree *fbUser)
{
    int i = 1;
    gotoxy(25, 4);
    int c = 6;
    while(l)
        if(strcmp(l->id, fbUser->id))
            gotoxy(25, c++), printf("\t%d.%s", i, l->id), l = l->next, i++;
        else
            l = l->next;
    return c;
}
void viewFriends(tree *fbUser, int **f, user *l, int n)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 7);printf("FRIENDS :-");
    int c = 9;
    int pos = getPos(fbUser, l);
    int i = 1, j = 0;
    user *t = l;
    while(l)
    {
        if(f[pos][j])
        {
            char id[20];
            strcpy(id, getId(j, t));
            gotoxy(25, c++), printf("\t%d.%s", i, id);
            i++;
        }
        j++;
        l = l->next;
    }
    if(i == 1)
        gotoxy(25, c++), printf("NO FRIENDS !!!");
    getch();
}
void dispGraph(int **f, int n)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            printf("-%d- ", f[i][j]);
        printf("\n");
    }
}
int viewNonF(tree *fbUser, user *l, int **f)
{
    int cPos = getPos(fbUser, l);
    int i = 1, j = 0;
    user *t = l;
    gotoxy(25, 8);int c = 8;
    while(l)
    {
        if(!f[cPos][j] && cPos != j)
        {
            char id[20];
            strcpy(id, getId(j, t));
            gotoxy(25, c++),printf("\t\t%d.%s", i, id);
            i++;
        }
        j++;
        l = l->next;
    }
    return c;
}
int viewF(tree *fbUser, user *l, int **f)
{
    int cPos = getPos(fbUser, l);
    int i = 1, j = 0;
    gotoxy(25, 6); int c = 8;
    user *t = l;
    while(l)
    {
        if(f[cPos][j])
        {
            char id[20];
            strcpy(id, getId(j, t));
            gotoxy(25, c++),printf("\t\t%d.%s", i, id);
            i++;
        }
        j++;
        l = l->next;
    }
    if(i == 1)
    {
        gotoxy(25, c++),printf("NO FIRENDS");
        return 0;
    }
    return c;
}
int viewSuggF(user *l, int cPos, int fPos, int **f)
{
    int i = 1, j = 0;
    user *t = l;
    gotoxy(25, 6); int c = 8;
    while(l)
    {
        if(f[fPos][j] && f[cPos][j] != 1 && cPos != j)
        {
            char id[20];
            strcpy(id, getId(j, t));
            gotoxy(25, c++), printf("\t\t%d.%s", i, id);
            i++;
        }
        j++;
        l = l->next;
    }
    if(i == 1)
    gotoxy(25, c++), printf("\t\tNO SUGGESTED FRIENDS");
    return c;
}
void addFriends(tree *fbUser, int **f, user *l, int n)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 6);
    char id[20];
    printf("ADD FRIENDS :- ");
    int c = viewNonF(fbUser, l, f);
    gotoxy(25, c+1);printf("Enter Id(user-Id) : ");
    scanf("%s", id);
    int cPos = getPos(fbUser, l);
    int fPos = getPosId(id, l);
    if(fPos == 0)
    {
        gotoxy(25, c+2); printf("NO SUCH USER!!"); getch(); return;
    }
    f[cPos][fPos] = 1;
    f[fPos][cPos] = 1;
    gotoxy(25, c+2); printf("FRIEND ADDED SUCCESSFULLY!!");
    getch();
    //getch();
}
void removeFriends(tree *fbUser, int **f, user *l, int n)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 6);
    char id[20];
    printf("DELETE FRIENDS :- ");
    int c = viewF(fbUser, l, f);
    if(c == 0){ getch(); return;}
    gotoxy(25, c+1);printf("Enter Id (user-Id) : ");
    scanf("%s", id);
    int cPos = getPos(fbUser, l);
    int fPos = getPosId(id, l);
    if(fPos == 0)
    {
        gotoxy(25, c+2); printf("NO SUCH FRIEND!!"); getch(); return;
    }
    f[cPos][fPos] = 0;
    f[fPos][cPos] = 0;
    gotoxy(25, c+2); printf("FRIEND REMOVED SUCCESSFULLY!!");
    getch();
    //getch();
}
void mutual(tree *expUser, tree *fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 5);
    printf("MUTUAL FRIENDS :- ");
    int cPos = getPos(fbUser, l);
    int fPos = getPosId(expUser->id, l);
    int i = 1, j = 0, c = 7;
    user *t = l;
    int n = noOfUsers(l);
    while(j < n)
    {
        if(friends[fPos][j] && friends[cPos][j])
        {
            char id[20];
            strcpy(id, getId(j, t));
            gotoxy(25, c++), printf(" \t%d.%s", i, id);
            i++;
        }
        j++;
    }
    if(i == 1)
        gotoxy(25, c++), printf("NO MUTUAL FRIENDS !!!");
    getch();
}
void exploreUser(tree *expUser, tree *fbUser)
{
    int cPos, fPos, n, k;
    n = noOfUsers(l);
    cPos = getPos(fbUser, l);
    fPos = getPosId(expUser->id, l);
    /*if(friends[cPos][fPos] == 0)
        printf("\n\t3.Add Friend");
    else
        printf("\n\t3.Remove Friend");*/
    //printf("\n\t4.Return");
    while(1)
    {
        system("cls");
        gotoxy(38, 3);
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
        gotoxy(25, 4);
        printf("===========================================================");
        gotoxy(25, 5);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 6); printf("|\tEXPLORE\t%s", expUser->id); gotoxy(84, 6); printf("|");
        gotoxy(25, 7); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 8); printf("|\t\t1.View profile"); gotoxy(84, 8); printf("|");
        gotoxy(25, 9); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 10); printf("|\t\t2.View Mutual Friends"); gotoxy(84, 10); printf("|");
        gotoxy(25, 11); printf("|\t\t\t\t\t\t\t    |");
        if(friends[cPos][fPos] == 0)
            gotoxy(25, 12), printf("|\t\t3.Add Friend"), gotoxy(84, 12), printf("|");
        else
            gotoxy(25, 12), printf("|\t\t3.Remove Friend"), gotoxy(84, 12), printf("|");
        gotoxy(25, 13); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 14); printf("|\t\t4.Return"); gotoxy(84, 14); printf("|");
        gotoxy(25, 15);
        printf("===========================================================");
        gotoxy(25, 16);
        printf("Enter your option : ");
        scanf("%d",&k);
        if(k == 4)
            break;
        switch(k)
        {
            case 1: viewProfile(expUser, 0);
                    break;
            case 2: mutual(expUser, fbUser);
                    break;
            case 3: {
                    if(friends[cPos][fPos] == 0)
                    {
                        friends[cPos][fPos] = 1;
                        friends[fPos][cPos] = 1;
                        gotoxy(25, 16);printf("FRIEND ADDED SUCCESSFULLY!!"), getch();
                    }
                    else
                    {
                        friends[cPos][fPos] = 0;
                        friends[fPos][cPos] = 0;
                        gotoxy(25, 16);printf("FRIEND REMOVED SUCCESSFULLY!!"), getch();
                    }
                    break;
                    }
            default:gotoxy(25, 16);
                    printf("Enter correctly");
                    delay(2);
        }
    }
}
void suggestions(tree *fbUser, int **f, user *l, int n)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 6);
    char id[20];
    int cPos = getPos(fbUser, l);
    int i, j;
    while(1)
    {
        j = rand() % n;
        if(friends[cPos][j])
            break;
    }
    strcpy(id, getId(j, l));
    printf("SUGGESTED FRIENDS OF\t%s", id);
    int c = viewSuggF(l, cPos, j, f);
    char id2[20];
    gotoxy(25, c+1); printf("Explore User : ");
    scanf("%s", id2);
    tree *expUser = NULL;
    expUser = getUserDataId(tId, id2);
    if(!expUser)
       gotoxy(25, c+2), printf("No Such User Found!!\n"), getch();
    else
        exploreUser(expUser, fbUser);
}
void viewUsers(tree *fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 4);
    printf("USERS :-");
    int c = display(l, fbUser);
    char id[20];
    gotoxy(25, c+1); printf("Explore User : ");
    scanf("%s", id);
    tree *expUser = NULL;
    expUser = getUserDataId(tId, id);
    if(!expUser)
        gotoxy(25, c+2), printf("No Such User Found!!\n"), getch();
    else
        exploreUser(expUser, fbUser);
}
void searchUsers(tree *fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 6);
    char profile[20];
    tree *pro = NULL;
    int n;
    printf("SEARCH USERS :-");
    gotoxy(25, 7);
    printf("User Id : ");
    scanf("%s",profile);
    pro = getUserDataId(tId, profile);
    if(!pro)
        gotoxy(25, 7), printf("\nNo Such User Found!!\n");
    else
    {
        exploreUser(pro, fbUser);
    }
    getch();
}

void Friends(tree *fbUser)
{
    int n = noOfUsers(l);
    int k;
    while(1)
    {   system("cls");
        gotoxy(38, 3);
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
        gotoxy(25, 4);
        printf("===========================================================");
        gotoxy(25, 5);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 6); printf("|\tFRIENDS\t"); gotoxy(84, 6); printf("|");
        gotoxy(25, 7); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 8); printf("|\t\t1.View friends"); gotoxy(84, 8); printf("|");
        gotoxy(25, 9); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 10); printf("|\t\t2.Add Friends"); gotoxy(84, 10); printf("|");
        gotoxy(25, 11); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 12); printf("|\t\t3.Remove Friends"); gotoxy(84, 12); printf("|");
        gotoxy(25, 13); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 14); printf("|\t\t4.View Suggestions"); gotoxy(84, 14); printf("|");
        gotoxy(25, 15); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 16); printf("|\t\t5.Return"); gotoxy(84, 16); printf("|");
        gotoxy(25, 17); printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 18);printf("===========================================================");
        gotoxy(25, 19);printf("Enter your option : ");
        scanf("%d",&k);
        if(k == 5)
            break;
        switch(k)
        {
            case 1: viewFriends(fbUser, friends, l, n);
                    break;
            case 2: addFriends(fbUser, friends, l , n);
                    break;
            case 3: removeFriends(fbUser, friends, l, n);
                    break;
            case 4: suggestions(fbUser, friends, l, n);
                    break;
            default:gotoxy(25, 21);printf("Enter correctly");
                    delay(2);
        }
    }



}
void storelogin(tree *fbUser)
{
    FILE *logs=fopen("logs.txt","a");
    char *buffer;
    buffer=(char *)malloc(sizeof(char)*50);
    time_t t;
    time(&t);
    buffer=ctime(&t);
    buffer[24]='\0';
    fprintf(logs,"%s %s\n",buffer,fbUser->id);
    fclose(logs);
}

void lastlogs(tree *fbUser)
{
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 6);printf("LOGIN HISTORY :-");
    stack s;
    inits(&s);
    int i = 0, j = 1;
    char y[3],z[3],n[20];
    int date,hh,mm,ss,year,cou=8;
    FILE *logs=fopen("logs.txt","r");
    while(!feof(logs))
    {
        fscanf(logs,"%s %s %d %d:%d:%d %d %s",y,z,&date,&hh,&mm,&ss,&year,n);
        if(!strcmp(fbUser->id,n))
            push(&s,y,z,date,hh,mm,ss,year);
    }
    while(pop(&s,y,z,&date,&hh,&mm,&ss,&year))
    {
        gotoxy(25,cou);
        if(i)
            printf("Log-%d=> %s %s %d %d:%d:%d %d",j++,y,z,date,hh,mm,ss,year);
        i = 1;
        cou++;
    }
    getch();
}
void profile(tree *fbUser, int k)
{
    storelogin(fbUser);
    int n = noOfUsers(l);
    int nf = n;
    friends = (int**)malloc(sizeof(int*) * n);
    int i = 0, j = 0;
    for(i = 0; i < n; i++)
        friends[i] = (int*)malloc(sizeof(int) * n);
    FILE *f = fopen("friends.txt", "r");
    i = 0, j = 0;
    char c;
    while(!feof(f))
    {
        c = fgetc(f);
        if(c != '\n' && c != ' ' && c != EOF)
        {
             friends[i][j] = c - '0';
             j++;
        }
        else if(c == '\n')
        {
            i++;
            j = 0;
        }
    }
    if(k == 0)
    {
        for(i = 0; i < n; i++)
        {
            friends[n-1][i] = 0;
            friends[i][n-1] = 0;
        }
    }
    while(1)
    {
        system("cls");
        gotoxy(38, 3);
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
        gotoxy(25, 4);
        printf("===========================================================");
        gotoxy(25, 5);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 6);
        printf("|\tWELCOME %s %s\n", fbUser->fName, fbUser->lName); gotoxy(84, 6); printf("|");
        gotoxy(25, 7);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 8);
        printf("|\t\t\xB2\xB2\xB2 1.View Profile"); gotoxy(84, 8); printf("|");
        gotoxy(25, 9);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 10);
        printf("|\t\t\xB2\xB2\xB2 2.Edit Profile"); gotoxy(84, 10); printf("|");
        gotoxy(25, 11);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 12);
        printf("|\t\t\xB2\xB2\xB2 3.Change Password"); gotoxy(84, 12); printf("|");
        gotoxy(25, 13);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 14);
        printf("|\t\t\xB2\xB2\xB2 4.View Users"); gotoxy(84, 14); printf("|");
        gotoxy(25, 15);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 16);
        printf("|\t\t\xB2\xB2\xB2 5.Search Users"); gotoxy(84, 16); printf("|");
        gotoxy(25, 17);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 18);
        printf("|\t\t\xB2\xB2\xB2 6.Friends"); gotoxy(84, 18); printf("|");
        gotoxy(25, 19);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 20);
        printf("|\t\t\xB2\xB2\xB2 7.Login History"); gotoxy(84, 20); printf("|");
        gotoxy(25, 21);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 22);
        printf("|\t\t\xB2\xB2\xB2 8.Log Out"); gotoxy(84, 22); printf("|");
        gotoxy(25, 23);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 24);
        printf("|\t\t\t\t\t\t\t    |");
        gotoxy(25, 25);
        printf("===========================================================");
        gotoxy(25, 27);
        printf("Enter your option : ");
        scanf("%d",&n);
        if(n == 8)
        {
            user *t = l;
            FILE *fp = fopen("userId.txt", "w");
            while(t)
            {
                fprintf(fp, "%s %s %s %s %s %s %s %s %s\n",t->email, t->pwd, t->fName, t->lName, t->id, t->country, t->state, t->no, t->dob);
                t = t->next;
            }
            FILE *f2 = fopen("friends.txt", "w");
            int i, j;
            for(i = 0; i < nf; i++)
            {
                for(j = 0; j < nf; j++)
                    if(j != nf-1)
                        fprintf(f2, "%d ", friends[i][j]);
                    else
                        fprintf(f2, "%d\n", friends[i][j]);
            }
            gotoxy(25, 29); printf("\t\tLOGGED OUT SUCCESSFULLY!!!"), gotoxy(25, 30), printf("\t\tThanks For Using Facebook!!!"), getch();
            break;
        }
        switch(n)
        {
            case 1: viewProfile(fbUser, 1);
                    break;
            case 2: fbUser = editProfile(fbUser);
                    break;
            case 3: fbUser = changePwd(fbUser);
                    break;
            case 4: viewUsers(fbUser);
                    break;
            case 5: searchUsers(fbUser);
                    break;
            case 6: Friends(fbUser);
                    break;
            case 7: lastlogs(fbUser);
                    break;
            default:gotoxy(25, 29);printf("Enter correctly");
                    delay(2);
        }
    }

}
void login(int i)
{
    char email[20], pwd[20];
    tree *user1 = NULL;
    while(1)
    {
        system("cls");
        gotoxy(38, 3);
        printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
        gotoxy(25, 5);
        printf("\xB2\xB2\xB2LOGIN:-");
        gotoxy(25, 7);
        printf("Email Id   : ");
        scanf("%s", email);
        gotoxy(25, 8);
        printf("Password   : ");
        int p=0;
        do
        {
            pwd[p]=getch();
            if(pwd[p] != '\r')
            printf("*");
            p++;
        }while(pwd[p-1]!='\r');
        pwd[p-1]='\0';
        user1 = getUserDataEmail(tEmail, email);
        if(user1 != NULL)
        {
            if(strcmp(user1->pwd, pwd) == 0)
            {
                gotoxy(25, 10);
                printf("LOGIN SUCCESSFULL");
                delay(1);
                break;
            }
            else
            {
                gotoxy(25, 10);
                printf("INCORRECT email id OR password!!! RE-ENTER CORRECTLY!!!");
                delay(2);
                continue;
            }
        }
        else
        {
            gotoxy(25, 10);
            printf("INCORRECT email id OR password!!! RE-ENTER CORRECTLY!!!\n");
            delay(2);
            continue;
        }
    }
    profile(user1, i);
}
void signUp()
{

    char email[20], pwd[20], pwd2[20], fName[20], lName[20], id[20], country[20], dob[15], no[15], state[20];
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 5);
    printf("\xB2\xB2\xB2SIGN UP :- ");
    gotoxy(25, 7);
    //gotoxy(25, 13); printf("SIGN UP :- ");
    //printf("\t\t\tSIGN UP\n");
    //gotoxy(25, 13);
    int c = 7;
    while(1)
    {   gotoxy(25, c++);
        printf("Email Id   : ");
        scanf("%s",email);
        tree *user = NULL;
        user = getUserDataEmail(tEmail, email);
        if(!user)
            break;
        else
            printf("Email id already used!!! Use another Email id!!!\n\n");
    }
    gotoxy(25, c);
    printf("Password   : ");
    int p=0;
    do
    {
        pwd[p]=getch();
        if(pwd[p] != '\r')
        printf("*");
        p++;
    }while(pwd[p-1]!='\r');
    pwd[p-1]='\0';
    //int c = 16;
    c = c+1;
    while(1)
    {
        gotoxy(25, c++); printf("Confirm Password   : ");
        int p=0;
        do
        {
            pwd2[p]=getch();
            if(pwd2[p] != '\r')
            printf("*");
            p++;
        }while(pwd2[p-1]!='\r');
        pwd2[p-1]='\0';
        if(strcmp(pwd, pwd2) == 0)
            break;
        else
            gotoxy(25, c++), printf("Passwords did not match!!! Please enter correctly !\n\n");
    }
    gotoxy(25, c);
    printf("Enter Your Details :-");
    gotoxy(25, c+2); printf("First Name : ");
    scanf("%s", fName);
    gotoxy(25, c+4); printf("Last Name : ");
    scanf("%s", lName);
    gotoxy(25, c+6); printf("Mobile Number : ");
    scanf("%s", no);
    c = c+8;
    while(1)
    {
        gotoxy(25, c++); printf("Facebook Id   : ");
        scanf("%s",id);
        tree *user = NULL;
        user = getUserDataId(tId, id);
        if(!user)
            break;
        else
            gotoxy(25, c++);printf("Id Already Taken!!! Enter a new Id!!!\n\n");
    }
    gotoxy(25, c+1); printf("Date Of Birth(dd-mm-yyyy) : ");
    scanf("%s", dob);
    gotoxy(25, c+2); printf("Country : ");
    scanf("%s", country);
    gotoxy(25, c+3); printf("state : ");
    scanf("%s", state);
    l = iE(l, email, pwd, fName, lName, id, country, state, no, dob);
    tId = insertId(tId, email, pwd, fName, lName, id, country, state, no, dob);
    tEmail = insertEmail(tEmail, email, pwd, fName, lName, id, country, state, no, dob);
    FILE *fp = fopen("userId.txt", "a");
    fprintf(fp,"%s %s %s %s %s %s %s %s %s\n",email, pwd, fName, lName, id, country, state, no, dob);
    fclose(fp);
    gotoxy(25, c+4); printf("\t\t\tSIGNED UP SUCCESSFULLY!!!");
    gotoxy(25, c+5); printf("LOGIN NOW!!!");
    delay(1);
    login(0);
}
void dispTree(tree *t)
{
    if(t)
    {
        dispTree(t->left);
        printf("%s\n",t->id);
        dispTree(t->right);
    }
}
int main()
{
    srand(time(NULL));
    int n;
    l = getUser(l);
    tId = getUserT(l, tId, 0);
    tEmail = getUserT(l, tEmail, 1);
    system("cls");
    gotoxy(38, 3);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB FACEBOOK \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\n");
    gotoxy(25, 4);
    printf("===========================================================");
    gotoxy(25, 5);
    printf("|\t\t\t\t\t\t\t    |");
    gotoxy(25, 6);
    printf("|\t\t\t1.Login\t\t\t\t    |");
    gotoxy(25, 7);
    printf("|\t\t\t2.Sign up\t\t\t    |");
    gotoxy(25, 8);
    printf("|\t\t\t3.Quit\t\t\t\t    |");
    gotoxy(25, 9);
    printf("|\t\t\t\t\t\t\t    |");
    gotoxy(25, 10);
    printf("===========================================================");
    gotoxy(25, 12);
    printf("Enter your option : ");
    scanf("%d",&n);
    switch(n)
    {
        case 1: login(1);
                break;
        case 2: signUp();
                break;
        case 3: printf("\n\t\t\tThanks For Using Faceook!!!");
                break;
        default:gotoxy(25, 15);printf("Invalid choice\n");delay(1);main();
    }
    printf("\n\n\n");
    return 0;
}
