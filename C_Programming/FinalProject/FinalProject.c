#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct member{
    int id;
    char givenname[20];
    char familyname[20];
    int age;
    char gender[2];
};

void start();

int loadmembers(struct member *members[]);

int selectmode();

void Print_members(struct member *m[], int *count);

void Add_member(struct member *members[], int *count);

void Delete_member(struct member *members[], int *count);

void Search_member(struct member *members[], int count);

void memberfree(struct member *members[], int count);

int main()
{
    struct member *Members[MAX];
    int mode,membercount=0;

    start();
    
    while(1){
        mode=selectmode();
        membercount=loadmembers(Members);
        
        if(mode==0){
            break;
        }
        else if(mode==1){
            Print_members(Members,&membercount);
        }
        else if(mode==2){
            Add_member(Members,&membercount);
        }
        else if(mode==3){
            Delete_member(Members,&membercount);
        }
        else if(mode==4){
            Search_member(Members,membercount);
        }
    }
    memberfree(Members, membercount);
    printf("\nGoodBuy~\n");
    return 0;
}

void start(){
    printf("=========================\n");
    printf("Member Management Program\n");
    printf("=========================\n");
}

int loadmembers(struct member *members[]){
    int i;
    FILE *f;

    f=fopen("members.txt", "rt");

    if(f!=NULL){
        for(i=0;i<MAX;i++){
            if(feof(f)){
                break;
            }
            members[i]=(struct member *)malloc(sizeof(struct member));
            fscanf(f, "%d", &members[i]->id);
            fscanf(f, "%s", members[i]->givenname);
            fscanf(f, "%s", members[i]->familyname);
            fscanf(f, "%d", &members[i]->age);
            fscanf(f, "%s", members[i]->gender);
        }
    }
    fclose(f);
    return i;
}

int selectmode(){
    int mode;

    printf("1) show members\n");
    printf("2) add member\n");
    printf("3) delete member\n");
    printf("4) search member\n");
    printf("0) exit program\n");
    printf("-------------------------\n");
    printf("command> ");
    scanf("%d", &mode);
    
    return mode;
}

void Print_members(struct member *m[], int *count){
    printf("\n=========================\n");
    printf("Member Management Program: show members\n");
    printf("===========================\n");
    printf("id\tGivenName\tFamilyName\tAge\tGender\n");
    for(int i=0;i<*count;i++){
        if(m[i]->id!=0){
            printf("%d\t%s\t\t%s\t\t%d\t%s\n", m[i]->id, m[i]->givenname, m[i]->familyname, m[i]->age, m[i]->gender);
        }
    }
    printf("\n");
}

void Add_member(struct member *members[], int *count){
    char givenname[20];
    char familyname[20];
    int age;
    char gender[2];

    printf("\n=========================\n");
    printf("Member Management Program: add member\n");
    printf("=========================\n");
    printf("GivenName: ");
    scanf("%s", givenname);
    printf("FamilyName: ");
    scanf("%s", familyname);
    printf("Age: ");
    scanf("%d", &age);
    printf("Gender: ");
    scanf("%s", gender);
    

    for(int i=0;i<=*count;i++){
        if(members[i]->id!=i+1 || i==*count){
            if(i==*count){
                members[i]=(struct member *)malloc(sizeof(struct member));
            }
            (*count)++;
            members[i]->id=i+1;
            strcpy(members[i]->givenname,givenname);
            strcpy(members[i]->familyname,familyname);
            members[i]->age=age;
            strcpy(members[i]->gender,gender);
            break;
        }
    }

    printf("\nid\tGivenName\tFamilyName\tAge\tGender\n");
    for(int i=0;i<*count;i++){
        printf("%d\t%s\t\t%s\t\t%d\t%s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
    }
    printf("\n");

    FILE *f;

    f=fopen("members.txt", "wt");
    for(int i=0;i<*count-1;i++){
        fprintf(f, "%d %s %s %d %s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
    }
    fprintf(f, "%d %s %s %d %s", members[*count-1]->id, members[*count-1]->givenname, members[*count-1]->familyname, members[*count-1]->age, members[*count-1]->gender);
    fclose(f);
} 

void Delete_member(struct member *members[], int *count){
    int id;

    printf("\n=========================\n");
    printf("Member Management Program: delete member\n");
    printf("=========================\n");
    printf("id> ");
    scanf("%d", &id);

    printf("%s %s is deleted.\n\n", members[id-1]->givenname, members[id-1]->familyname);

    if(id==members[id-1]->id){
        members[id-1]->id=0;
        (*count)--;
    }

    FILE *f;

    f=fopen("members.txt", "wt");

    for(int i=0;i<*count-1;i++){
        if(members[i]->id!=0){
            fprintf(f, "%d %s %s %d %s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
        }
    }
    if(members[*count-1]->id!=0){
        fprintf(f, "%d %s %s %d %s", members[*count-1]->id, members[*count-1]->givenname, members[*count-1]->familyname, members[*count-1]->age, members[*count-1]->gender);
    }
    fclose(f);
}

void Search_member(struct member *members[], int count){
    int mode;

    printf("\n=========================\n");
    printf("Member Management Program: search member\n");
    printf("=========================\n");
    printf("1) by GivenName\n");
    printf("2) by FamilyName\n");
    printf("3) by Age\n");
    printf("4) by Gender\n");
    printf("-------------------------\n");
    printf("command> ");
    scanf("%d", &mode);

    if(mode==1){
        char givenname[20];

        printf("=========================\n");
        printf("Member Management Program: search member by GivenName\n");
        printf("=========================\n");
        printf("GivenName> ");
        scanf("%s", givenname);

        printf("\n");
        printf("id\tGivenName\tFamilyName\tAge\tGender\n");
        for(int i=0;i<count;i++){
            if(strcmp(givenname,members[i]->givenname)==0){
                printf("%d\t%s\t\t%s\t\t%d\t%s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
            }
        }
        printf("\n");
    }
    else if(mode==2){
        char familyname[20];

        printf("=========================\n");
        printf("Member Management Program: search member by FamilyName\n");
        printf("=========================\n");
        printf("FamilyName> ");
        scanf("%s", familyname);

        printf("\n");
        printf("id\tGivenName\tFamilyName\tAge\tGender\n");
        for(int i=0;i<count;i++){
            if(strcmp(familyname,members[i]->familyname)==0){
                printf("%d\t%s\t\t%s\t\t%d\t%s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
            }
        }
        printf("\n");
    }
    else if(mode==3){
        int age;

        printf("=========================\n");
        printf("Member Management Program: search member by Age\n");
        printf("=========================\n");
        printf("Age> ");
        scanf("%d", &age);

        printf("\n");
        printf("id\tGivenName\tFamilyName\tAge\tGender\n");
        for(int i=0;i<count;i++){
            if(age==members[i]->age){
                printf("%d\t%s\t\t%s\t\t%d\t%s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
            }
        }
        printf("\n");
    }
    else if(mode==4){
        char gender[2];

        printf("=========================\n");
        printf("Member Management Program: search member by Gender\n");
        printf("=========================\n");
        printf("Gender> ");
        scanf("%s", gender);

        printf("\n");
        printf("id\tGivenName\tFamilyName\tAge\tGender\n");
        for(int i=0;i<count;i++){
            if(strcmp(gender,members[i]->gender)==0){
                printf("%d\t%s\t\t%s\t\t%d\t%s\n", members[i]->id, members[i]->givenname, members[i]->familyname, members[i]->age, members[i]->gender);
            }
        }
        printf("\n");
    }
}

void memberfree(struct member *members[], int count){
    for(int i=0;i<=count;i++){
        free(members[i]);
    }
}