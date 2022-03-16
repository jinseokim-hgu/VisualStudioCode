#include "members.h"

// 애플리케이션용 함수 원형
void create_record();
void read_record();
void update_record();
void delete_record();
void list_record();

int main(){
    int menu;
    while(1){
        printf("\nMenu : 1.Create 2.Read 3.Update 4.Delete 5.List 0.Quit > ");
        scanf("%d", &menu);
        printf("\n");
        switch(menu){
            case 1: 
                create_record();
                break;
            case 2: 
                read_record();
                break;
            case 3: 
                update_record();
                break;
            case 4: 
                delete_record();
                break;
            case 5: 
                list_record();
                break;
            case 0: 
            default: 
                return 0;
        }
    }
    return 0;
}

void create_record(){
    char name[20], phone[20], city[20];
    int year;

    if(m_is_available()==0){
        printf("There is no space!\n");
        return;
    }

    printf("Enter a new member's info.\n");
    printf("Name > ");
    scanf("%s", name);
    if(m_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("Phone > ");
    scanf("%s", phone);
    printf("Birth year > ");
    scanf("%d", &year);
    printf("City > ");
    scanf("%s", city);
    m_create(name, phone, year, city);
}

void list_record(){
    // 전체 리스트 출력
    printf("All records.\n");
    int size = m_count();
    T_Record* records[MAX_MEMBERS];
    m_get_all(records);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, m_to_string(p));
    }
}

void read_record(){
    char name[20];
    T_Record* record;

    printf("Enter a name > ");
    scanf("%s", name);

    record=m_search_by_name(name);

    if(record==NULL){
        printf("No such member!\n");
        return;
    }
    else{
        printf("Member info.\n");
        printf("Name : %s\n", m_getname(record));
        printf("Phone : %s\n", m_getphone(record));
        printf("Birth year : %d\n", m_getbirthyear(record));
        printf("City : %s\n", m_getcity(record));
    }
}

void update_record(){
    char name[20], phone[20], city[20];
    int year;
    T_Record* record;

    printf("Enter a name > ");
    scanf("%s", name);

    record=m_search_by_name(name);

    if(record==NULL){
        printf("No such member!\n");
        return;
    }
    else{
        printf("Enter a updated info.\n");
        printf("Phone > ");
        scanf("%s", phone);
        printf("Birth year > ");
        scanf("%d", &year);
        printf("City > ");
        scanf("%s", city);
        m_update(record, phone, year, city);
    }
}

void delete_record(){
    char name[20];
    T_Record* record;

    printf("Enter a name > ");
    scanf("%s", name);

    record=m_search_by_name(name);

    if(record==NULL){
        printf("No such member!\n");
        return;
    }
    else{
        m_delete(record);
        printf("The record is deleted!\n");
    }
}