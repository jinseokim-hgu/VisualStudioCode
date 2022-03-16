#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 55      // 저장할 수 있는 도서 레코드 최대 갯수

// 도서 정보 레코드의 데이터 타입을 정의함
typedef struct st_book{
    char name[50];  // 도서명
    char writer[50]; // 저자명
    char publisher[20];  // 출판사명
    int status;  // 대출가능여부 (가능:1, 불가:0)
    char location[20];  // 위치
} T_Record;

// 라이브러리 함수 원형을 선언함
int b_is_available();       // 현재 추가할 수 있는 데이터 공간이 있는가?
int b_first_available();    // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
int b_count();              // 현재 저장된 도서 레코드의 갯수 가져오기
void b_create(char* n, char* w, char* pu, int s, char* l);   // 도서정보로 신규 도서 레코드 추가
T_Record* b_search_by_name(char* n);                // 도서명이 일치하는 레코드 포인터 찾기
void b_update(T_Record* p, char* w, char* pu, int s, char* l);  // 특정 도서 레코드의 정보 업>데이트
void b_delete(T_Record* p);     // 특정 도서 레코드의 회원정보 제거
void b_get_all(T_Record* a[]);  // 도서정보가 들어있는 모든 레코드 포인터의 배열을 만들기
void b_get_all_debug(T_Record* a[]);  // 모든 레코드 포인터의 배열을 만들기 (for debug)
char* b_to_string(T_Record* p); // 특정 도서 레코드의 내용을 문자열로 가져오기
char* b_getname(T_Record* p);   // 특정 도서 레코드의 도서명 가져오기
char* b_getwriter(T_Record* p);  // 특정 도서 레코드의 저자명 가져오기
char* b_getpublisher(T_Record* p);// 특정 도서 레코드의 출판사명 가져오기
int b_getstatus(T_Record* p);   // 특정 도서 레코드의 대출가능여부 가져오기
char* b_getlocation(T_Record* p);   // 특정 도서 레코드의 위치 가져오기
int b_get_all_by_name(T_Record* a[], char* n);  // 도서명에 문자열이 포함된 모든 레코드 포인터의 배열 만들기
int b_get_all_by_writer(T_Record* a[], char* w);  // 저자명이 문자열과 일치하는 모든 레코드 포인터의 배열 만들기
int b_get_all_by_publisher(T_Record* a[], char* pu);  // 출판사명이 문자열과 일치하는 모든 레코드 포인터의 배열 만들기
int b_get_all_by_status(T_Record* a[], int s);  // 대출가능여부에 일치하는 모든 레코드 포인터의 배열 만들기
int b_get_all_by_location(T_Record* a[], char* l); // 위치에 문자열이 포함된 모든 레코드 포인터의 배열 만들기
void b_defragmentation(); // 데이터 조각 모음
void b_sort_by_name();
void b_sort_by_writer();
void b_sort_by_publisher();
void b_sort_by_status();
void b_sort_by_location();
void b_init(); // 모든 레코드 제거
char* b_to_string_save(T_Record* p); // 특정 도서 레코드의 내용을 파일저장용 문자열로 가져오기