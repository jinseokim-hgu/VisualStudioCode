#include "books.h"

T_Record* books[MAX_BOOKS]; // 회원정보데이터 (전역)
int _count = 0;

int b_is_available(){
    int i;
    for(i=0; i<MAX_BOOKS; i++){
        if(books[i]==NULL) return 1;
    }
    return 0;
}

int b_first_available(){
    int i;
    for(i=0; i<MAX_BOOKS; i++){
        if(books[i]==NULL) return i;
    }
    return -1;
}

int b_count(){
#ifdef DEBUG
        printf("[DEBUG] B_Count success!\n");
#endif
    return _count;
}

void b_create(char* n, char* w, char* pu, int s, char* l){
    int index = b_first_available();
    books[index] = (T_Record*)malloc(sizeof(T_Record));
    T_Record* p = books[index];
    strcpy(p->name, n);
    strcpy(p->writer, w);
    strcpy(p->publisher, pu);
    p->status=s;
    strcpy(p->location, l);
#ifdef DEBUG
        printf("[DEBUG] %s_Create success!\n", n);
#endif
    _count++;
}

T_Record* b_search_by_name(char* n){
    int i;
    for(i=0; i<MAX_BOOKS; i++){
        if(books[i]!=NULL && strcmp(books[i]->name, n)==0){
#ifdef DEBUG
        printf("[DEBUG] B_Search_By_name success!\n");
#endif
         return books[i];
        }
    }
    return NULL;
}

void b_update(T_Record* p, char* w, char* pu, int s, char* l){
    strcpy(p->writer, w);
    strcpy(p->publisher, pu);
    p->status=s;
    strcpy(p->location, l);
#ifdef DEBUG
        printf("[DEBUG] B_Update success!\n");
#endif
}

void b_delete(T_Record* p){
    int i, index;
    for(i=0; i<_count; i++)
        if(books[i]==p) {
            index=i;
            break;
        }
    free(p);
    books[index] = NULL;
#ifdef DEBUG
        printf("[DEBUG] B_Delete success!\n");
#endif
    _count--;
}

char* b_to_string(T_Record* p){
    static char str[150];
    sprintf(str, "[%d] %s / %s / %s / %s", p->status, p->name, p->writer, p->publisher, p->location);
#ifdef DEBUG
        printf("[DEBUG] B_To_String success!\n");
#endif
    return str;
}

void b_get_all(T_Record* a[]){
    int i, c=0;
    for(i=0; i<MAX_BOOKS; i++){
        if(books[i]!=NULL){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_ALL success!\n");
#endif
}

void b_get_all_debug(T_Record* a[]){
    int i, c=0;
    for(i=0; i<MAX_BOOKS; i++){
        a[i]=books[i];
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All2 success!\n");
#endif
}

char* b_getname(T_Record* p){
#ifdef DEBUG
        printf("[DEBUG] B_Getname success!\n");
#endif
    return p->name;
}

char* b_getwriter(T_Record* p){
#ifdef DEBUG
        printf("[DEBUG] B_Getwriter success!\n");
#endif
    return p->writer;
}

char* b_getpublisher(T_Record* p){
#ifdef DEBUG
        printf("[DEBUG] B_Getpublisher success!\n");
#endif
        return p->publisher;
}

int b_getstatus(T_Record* p){
#ifdef DEBUG
        printf("[DEBUG] B_Getstatus success!\n");
#endif
    return p->status;
}

char* b_getlocation(T_Record* p){
#ifdef DEBUG
        printf("[DEBUG] B_Getlocation success!\n");
#endif
    return p->location;
}

int b_get_all_by_name(T_Record* a[], char* n){
    // 회원이름에 문자열이 포함된 모든 레코드 포인터의 배열 만들기
    int i, c=0;
    for(i=0; i<_count; i++){
        if(books[i]!=NULL && strstr(books[i]->name, n)){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All_By_%s success!\n", n);
#endif
    return c;
}

int b_get_all_by_writer(T_Record* a[], char* w){
    // 회원거주도시가 문자열과 일치하는 모든 레코드 포인터의 배열 만들기
    int i, c=0;
    for(i=0; i<_count; i++){
        if(books[i]!=NULL && (strcmp(books[i]->writer, w)==0)){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All_By_%s success!\n", w);
#endif
    return c;
}

int b_get_all_by_publisher(T_Record* a[], char* pu){
    // 회원거주도시가 문자열과 일치하는 모든 레코드 포인터의 배열 만들기
    int i, c=0;
    for(i=0; i<_count; i++){
        if(books[i]!=NULL && (strcmp(books[i]->publisher, pu)==0)){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All_By_%s success!\n", pu);
#endif
    return c;
}

int b_get_all_by_status(T_Record* a[], int s){
    // 회원거주도시가 문자열과 일치하는 모든 레코드 포인터의 배열 만들기
    int i, c=0;
    for(i=0; i<_count; i++){
        if(books[i]!=NULL && books[i]->status==s){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All_By_%d success!\n", s);
#endif
    return c;
}

int b_get_all_by_location(T_Record* a[], char* l){
    // 회원이름에 문자열이 포함된 모든 레코드 포인터의 배열 만들기
    int i, c=0;
    for(i=0; i<_count; i++){
        if(books[i]!=NULL && strstr(books[i]->location, l)){
            a[c]=books[i];
            c++;
        }
    }
#ifdef DEBUG
        printf("[DEBUG] B_Get_All_By_%s success!\n", l);
#endif
    return c;
}

void b_defragmentation(){
    for(int i=0;i<MAX_BOOKS;i++){
        for(int j=i+1;j<MAX_BOOKS;j++){
            if(books[i]==NULL && books[j]!=NULL){
                b_create(books[j]->name, books[j]->writer, books[j]->publisher, books[j]->status, books[j]->location);
                b_delete(books[j]);
                break;
            }
        }
    }
}

void b_sort_by_name(){
        T_Record temp;
        for(int i=0;i<MAX_BOOKS;i++){
                if(books[i]!=NULL){
                        for(int j=i+1;j<MAX_BOOKS;j++){
                                if(books[j]!=NULL && strcmp(books[i]->name,books[j]->name)>0){
                                        temp=*books[i];
                                        *books[i]=*books[j];
                                        *books[j]=temp;
                                }
                        }
                }
        }
}

void b_sort_by_writer(){
        T_Record temp;
        for(int i=0;i<MAX_BOOKS;i++){
                if(books[i]!=NULL){
                        for(int j=i+1;j<MAX_BOOKS;j++){
                                if(books[j]!=NULL && strcmp(books[i]->writer,books[j]->writer)>0){
                                        temp=*books[i];
                                        *books[i]=*books[j];
                                        *books[j]=temp;
                                }
                        }
                }
        }
}

void b_sort_by_publisher(){
        T_Record temp;
        for(int i=0;i<MAX_BOOKS;i++){
                if(books[i]!=NULL){
                        for(int j=i+1;j<MAX_BOOKS;j++){
                                if(books[j]!=NULL && strcmp(books[i]->publisher,books[j]->publisher)>0){
                                        temp=*books[i];
                                        *books[i]=*books[j];
                                        *books[j]=temp;
                                }
                        }
                }
        }
}

void b_sort_by_status(){
        T_Record temp;
        for(int i=0;i<MAX_BOOKS;i++){
                if(books[i]!=NULL){
                        for(int j=i+1;j<MAX_BOOKS;j++){
                                if(books[j]!=NULL && books[i]->status<books[j]->status){
                                        temp=*books[i];
                                        *books[i]=*books[j];
                                        *books[j]=temp;
                                }
                        }
                }
        }
}

void b_sort_by_location(){
        T_Record temp;
        for(int i=0;i<MAX_BOOKS;i++){
                if(books[i]!=NULL){
                        for(int j=i+1;j<MAX_BOOKS;j++){
                                if(books[j]!=NULL && strcmp(books[i]->location,books[j]->location)>0){
                                        temp=*books[i];
                                        *books[i]=*books[j];
                                        *books[j]=temp;
                                }
                        }
                }
        }
}

void b_init(){
    // 모든 레코드 제거
    int i;
    for(i=0; i<MAX_BOOKS; i++){
        if(books[i]!=NULL) {
            free(books[i]);
        }
        books[i] = NULL;
    }
    _count = 0;
#ifdef DEBUG
        printf("[DEBUG] B_Init success!\n");
#endif
}

char* b_to_string_save(T_Record* p){
    static char str[150];
    sprintf(str, "%s\n%s\n%s %d %s", p->name, p->writer, p->publisher, p->status, p->location);
#ifdef DEBUG
        printf("[DEBUG] B_To_String_Save success!\n");
#endif
    return str;
}