#pragma warning(disable :4996) //sdl disable

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <stdlib.h> //atoi,itoa
//#include <locale.h> //한글깨짐때문에 추가
#define MAX_RENTAL_COUNT 3 //최대 비디오 대여 가능 수
#define MAX_NUM_LENGTH 13 //최대 전화번호 길이
#define MAX_CHAR_LENGTH 20 //최대 문자열 길이

//외부변수로 현재 vid_num과 person_num을 관리
//데이터베이스 저장 시 last.dat파일에 기록
extern int last_vid_num; //초기 비디오 num은 1
extern int last_person_num; //초기 고객 num은 0

class Video_Info //비디오 정보
{
public:
	char vid_name[MAX_CHAR_LENGTH]; //비디오 이름
	char vid_added_date[MAX_CHAR_LENGTH]; //비디오 추가 날짜
	int vid_rental; //비디오 대여 여부
	
	class Video_Info* next; //다음 비디오 정보를 가리킴
	class Video_Info* pre; //이전 비디오 정보를 가리킴

	Video_Info(){ //생성자
		vid_rental = 0; //초기 대여 상태는 0
		next = NULL;
		pre = NULL;
	}

	void init_num_count(){ //비디오 추가시에 호출
		vid_num = last_vid_num;
		last_vid_num++; //비디오 추가시마다 증가
	}

	void set_vid_num(int num) { //데이터베이스 로드 시 호출하여 이전 값으로 설정
		vid_num = num;
	}

	int get_vid_num() {
		return vid_num;
	}

private:
	int vid_num; //동일 이름의 비디오가 여러개 존재할 수 있으므로 비디오를 관리하기 위한 변수, 비디오 추가시마다 증가
};

class Person_Info //고객 정보
{
public:
	char name[MAX_CHAR_LENGTH]; //이름
	char phone_num[MAX_NUM_LENGTH]; //전화번호
	int rental_list[MAX_RENTAL_COUNT]; //빌려간 비디오 목록(vid_num 리스트)
	class Person_Info* next; //다음 고객 정보를 가리킴
	class Person_Info* pre; //이전 고객 정보를 가리킴

	Person_Info(){ //생성자
		for (int i = 0; i< MAX_RENTAL_COUNT; i++) //대여목록 초기화
		{
			rental_list[i] = 0;
		}

		next = NULL;
		pre = NULL;
	}

	void init_num_count() { //고객 추가시에 호출
		person_num = last_person_num;
		last_person_num++; //고객 추가시마다 증가		
	}

	void set_person_num(int num) { //데이터베이스 로드 시 호출하여 이전 값으로 설정
		person_num = num;
	}

	int get_person_num() {
		return person_num;
	}

private:
	int person_num; //동일 이름의 고객을 관리하기 위한 변수
};

//프로그램 내부에서 자체적으로 실행하는 함수들
const std::string get_time(); //현재 시간구하는 함수
void free_list(Video_Info **head_vid, Person_Info **head_person); //메모리 공간 반환함수
int search_db(Video_Info **head_vid,Person_Info **head_person,Video_Info **Dst_vid,Person_Info **Dst_person,const char name[],int option); //데이터베이스 검색 전용 함수(검색, 추가, 삭제, 대여, 반납에서 사용)

//main에서 직접적으로 사용하는 함수들
int load_db(Video_Info **head_vid, Person_Info **head_person); //데이터베이스 로드 함수
int save_db(Video_Info **head_vid, Person_Info **head_person); //데이터베이스 저장 함수
int search_info(Video_Info **head_vid, Person_Info **head_Person, int option); //검색 함수
int print_info(Video_Info **head_vid,Person_Info **head_person, int option);//출력 함수
int add_del_info(Video_Info **head_vid,Person_Info **head_person, int option);//추가,삭제 함수
int rental_return(Video_Info **head_vid,Person_Info **head_person, int option); //대여,반납 함수
void disp_screen(int option); // 화면 출력용 함수