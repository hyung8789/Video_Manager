#pragma warning(disable :4996) //sdl disable

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <stdlib.h> //atoi,itoa
//#include <locale.h> //�ѱ۱��������� �߰�
#define MAX_RENTAL_COUNT 3 //�ִ� ���� �뿩 ���� ��
#define MAX_NUM_LENGTH 13 //�ִ� ��ȭ��ȣ ����
#define MAX_CHAR_LENGTH 20 //�ִ� ���ڿ� ����

//�ܺκ����� ���� vid_num�� person_num�� ����
//�����ͺ��̽� ���� �� last.dat���Ͽ� ���
extern int last_vid_num; //�ʱ� ���� num�� 1
extern int last_person_num; //�ʱ� �� num�� 0

class Video_Info //���� ����
{
public:
	char vid_name[MAX_CHAR_LENGTH]; //���� �̸�
	char vid_added_date[MAX_CHAR_LENGTH]; //���� �߰� ��¥
	int vid_rental; //���� �뿩 ����
	
	class Video_Info* next; //���� ���� ������ ����Ŵ
	class Video_Info* pre; //���� ���� ������ ����Ŵ

	Video_Info(){ //������
		vid_rental = 0; //�ʱ� �뿩 ���´� 0
		next = NULL;
		pre = NULL;
	}

	void init_num_count(){ //���� �߰��ÿ� ȣ��
		vid_num = last_vid_num;
		last_vid_num++; //���� �߰��ø��� ����
	}

	void set_vid_num(int num) { //�����ͺ��̽� �ε� �� ȣ���Ͽ� ���� ������ ����
		vid_num = num;
	}

	int get_vid_num() {
		return vid_num;
	}

private:
	int vid_num; //���� �̸��� ������ ������ ������ �� �����Ƿ� ������ �����ϱ� ���� ����, ���� �߰��ø��� ����
};

class Person_Info //�� ����
{
public:
	char name[MAX_CHAR_LENGTH]; //�̸�
	char phone_num[MAX_NUM_LENGTH]; //��ȭ��ȣ
	int rental_list[MAX_RENTAL_COUNT]; //������ ���� ���(vid_num ����Ʈ)
	class Person_Info* next; //���� �� ������ ����Ŵ
	class Person_Info* pre; //���� �� ������ ����Ŵ

	Person_Info(){ //������
		for (int i = 0; i< MAX_RENTAL_COUNT; i++) //�뿩��� �ʱ�ȭ
		{
			rental_list[i] = 0;
		}

		next = NULL;
		pre = NULL;
	}

	void init_num_count() { //�� �߰��ÿ� ȣ��
		person_num = last_person_num;
		last_person_num++; //�� �߰��ø��� ����		
	}

	void set_person_num(int num) { //�����ͺ��̽� �ε� �� ȣ���Ͽ� ���� ������ ����
		person_num = num;
	}

	int get_person_num() {
		return person_num;
	}

private:
	int person_num; //���� �̸��� ���� �����ϱ� ���� ����
};

//���α׷� ���ο��� ��ü������ �����ϴ� �Լ���
const std::string get_time(); //���� �ð����ϴ� �Լ�
void free_list(Video_Info **head_vid, Person_Info **head_person); //�޸� ���� ��ȯ�Լ�
int search_db(Video_Info **head_vid,Person_Info **head_person,Video_Info **Dst_vid,Person_Info **Dst_person,const char name[],int option); //�����ͺ��̽� �˻� ���� �Լ�(�˻�, �߰�, ����, �뿩, �ݳ����� ���)

//main���� ���������� ����ϴ� �Լ���
int load_db(Video_Info **head_vid, Person_Info **head_person); //�����ͺ��̽� �ε� �Լ�
int save_db(Video_Info **head_vid, Person_Info **head_person); //�����ͺ��̽� ���� �Լ�
int search_info(Video_Info **head_vid, Person_Info **head_Person, int option); //�˻� �Լ�
int print_info(Video_Info **head_vid,Person_Info **head_person, int option);//��� �Լ�
int add_del_info(Video_Info **head_vid,Person_Info **head_person, int option);//�߰�,���� �Լ�
int rental_return(Video_Info **head_vid,Person_Info **head_person, int option); //�뿩,�ݳ� �Լ�
void disp_screen(int option); // ȭ�� ��¿� �Լ�