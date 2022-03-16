#include <stdio.h>
#include <string.h>

typedef struct{
    char name [10];
    char date [20];
    int age;
} Person;

void ReadPerson(Person *man){
    for(int i=0;i<10;i++){
        printf("name? "); scanf("%s",man[i].name);
        printf("date of birth? "); scanf("%s",man[i].date);
        printf("age? " ); scanf("%d",&man[i].age);
    }
}

void PrintPersons(Person *man){
    for(int i=0;i<10;i++){
        printf("name:\t\t%s\n",man[i].name);
        printf("date of birth:\t%s\n",man[i].date); 
        printf("age:\t\t%d\n",man[i].age);
    }
}

void PrintOldestPerson(Person *man){
    int maxage = 0;
    int maxn=0;

    for(int i=0;i<10;i++){
        if(man[i].age>maxage){
            maxage=man[i].age;
            maxn=i;
        }
    }
    printf("\n\n");
    printf("Oldest person\n");
    printf("name: %s\ndate of birth: %s\nage: %d\n",man[maxn].name,man[maxn].date,man[maxn].age);
}

int main(void)
{
    Person man[10];

    ReadPerson(man);
    PrintPersons(man);
    PrintOldestPerson(man);
    return 0;
}
