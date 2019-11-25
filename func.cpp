#include "header.h"

int last_vid_num=1; //초기 비디오 num은 1
int last_person_num=0; //초기 고객 num은 0

void disp_screen(int option) //화면 출력용 함수
{
	/* disp_screen option
	0 - 메인메뉴
	1 - 검색
	2 - 대여 또는 반납
	3 - 출력
	4 - 추가
	5 - 삭제
	-----------------------
	6 - 저장
	7 - 불러오기
	8 - 저장 및 종료
	9 - 저장하지 않고 종료
	*/

	switch(option)
	{
	case 0: //메인메뉴
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "	비디오 대여 프로그램	"<<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 또는 고객 정보 검색" <<std::endl;
	std::cout<< "(2) 비디오 대여 및 반납" <<std::endl;
	std::cout<< "(3) 전체 비디오, 고객 정보 출력" <<std::endl;
	std::cout<< "(4) 비디오 또는 고객 정보 추가" <<std::endl;
	std::cout<< "(5) 비디오 또는 고객 정보 삭제" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(6) 저장" <<std::endl;
	std::cout<< "(7) 불러오기" <<std::endl;
	std::cout<< "(8) 저장 및 종료" <<std::endl;
	std::cout<< "(9) 저장하지 않고 종료" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 1: //검색
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 정보 검색" <<std::endl;
	std::cout<< "(2) 고객 정보 검색" <<std::endl;
	std::cout<< "(3) 뒤로가기" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 2: //대여 또는 반납
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 대여" <<std::endl;
	std::cout<< "(2) 비디오 반납" <<std::endl;
	std::cout<< "(3) 뒤로가기" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 3: //출력
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 전체 출력" <<std::endl;
	std::cout<< "(2) 고객 전체 출력" <<std::endl;
	std::cout<< "(3) 뒤로가기" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 4: //추가
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 추가" <<std::endl;
	std::cout<< "(2) 고객 정보 추가" <<std::endl;
	std::cout<< "(3) 뒤로가기" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 5: //삭제
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) 비디오 삭제" <<std::endl;
	std::cout<< "(2) 고객 정보 삭제" <<std::endl;
	std::cout<< "(3) 뒤로가기" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;
	}
}

const std::string get_time() { //현재 시간 구하는 함수
	time_t now = time(0); //현재시간을 time_t타입으로 설정
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf,sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 string

	return buf;
}

void free_list(Video_Info **head_vid, Person_Info **head_person) //메모리 공간 반환함수
{
	//head_vid,head_person의 주소값을 받아서 순차적으로 메모리공간 반환
	Video_Info *tmp_vid_indexer = NULL; //원본 head_vid를 순차적으로 인덱싱하는 포인터
	Video_Info *del_vid = NULL; //tmp 인덱서로부터 주소를 받아와 메모리를 해제하기위한 포인터
	Person_Info *tmp_person_indexer = NULL; //원본 head_person을 순차적으로 인덱싱하는 포인터
	Person_Info *del_person = NULL; //tmp 인덱서로부터 주소를 받아와 메모리를 해제하기위한 포인터
	
	tmp_vid_indexer = *head_vid;
	tmp_person_indexer = *head_person;

	while (tmp_vid_indexer != NULL)
	{	
		del_vid = tmp_vid_indexer;
		tmp_vid_indexer = tmp_vid_indexer->next; //인덱서를 이동시킨 후 삭제
		delete(del_vid);
	}

	while (tmp_person_indexer != NULL)
	{
		del_person = tmp_person_indexer;
		tmp_person_indexer = tmp_person_indexer->next; //인덱서를 이동시킨 후 삭제
		delete(del_person);
	}
}

int load_db(Video_Info **head_vid, Person_Info **head_person) //데이터베이스 로드 함수
{
	/**
	정보 삭제 작업 수행시에 vid_num 및 person_num에 대해 순차적으로 정렬이 되지 않았으므로
	고객의 비디오 대여 목록에 기록된 vid_num에 대해 접근하려면
	vid_num,person_num에 대해 데이터베이스에 저장해야 삭제 작업이 일어나도 다시 로드했을때 접근가능
	**/

	FILE *vid_load, *person_load, *last_count;

	int last_max_rental_count=0; //마지막으로 사용된 최대 대여 가능 수 임시저장
	int fix_last_file = 0; //last.dat파일 손상여부
	int fix_last_vid_num = 1, fix_last_person_num = 0; //비디오,고객 데이터로부터 가장 큰 수를 기록

	if ((last_count = fopen("last.dat", "rt")) != NULL)
	{
			fscanf(last_count, "%d %d %d",&last_vid_num, &last_person_num, &last_max_rental_count); //마지막으로 사용했던 vid_num,person_num,최대 대여 가능 수 로드
			last_vid_num++; last_person_num++; //비디오 또는 고객을 새로 입력할 경우 vid_num,person_num에 대해 이니셜라이징시 값을 바로 할당해야하므로 증가시킴
			if (last_max_rental_count != MAX_RENTAL_COUNT) //최대 대여 가능 수가 마지막으로 저장한 값하고 다를 경우
			{
				while (1)
				{
					int select = 0;
					std::cout << "경고 : 현재 최대 대여 가능 수가 마지막으로 사용된 최대 대여 가능 수와 다릅니다." << std::endl; 
					std::cout << "마지막으로 사용된 최대 대여 가능 수 : " << last_max_rental_count << std::endl;
					std::cout << "현재 최대 대여 가능 수 : " << MAX_RENTAL_COUNT << std::endl;
					std::cout << "데이터가 손실될 수 있습니다. 계속하시겠습니까?" << std::endl;
					std::cout << "계속 : 1 , 취소 : -1" << std::endl;
					std::cin >> select;

					if (select == -1) break;
					else if (select != 1)
						//입력범위 초과 또는 잘못된 문자입력
					{
						std::cout << "메뉴중에서 선택하세요!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}
					else break;
					//현재 최대 대여 가능 수가 마지막으로 사용된 대여 가능 수보다 크면 기록된 대여목록 이후의 값들은 자동적으로 0으로 처리
					//현재 최대 대여 가능 수가 마지막으로 사용된 대여 가능 수보다 작은 경우에는 현재 최대 대여 가능 수 까지만 데이터베이스상에 로드
				}
			}
	}
	else //파일이 제대로 열리지 않았을 경우
	{
		fprintf(stderr, "last.dat파일을 불러올 수 없습니다. 기존 최대 대여 가능 수가 현재 값과 같다고 간주합니다.");
		std::cout << std::endl;
		last_max_rental_count = MAX_RENTAL_COUNT; //기존 최대 대여 가능 횟수가 현재 최대 대여 횟수랑 같다고 간주
		fix_last_file = 1;
	}

	if ((vid_load = fopen("vid_info.dat", "rt")) != NULL && (person_load = fopen("person_info.dat", "rt")) != NULL) //읽기 + 텍스트 파일 모드
	{
		//**** 비디오 데이터베이스 로드
		Video_Info *new_vid = NULL;
		int tmp_vid_num = 1;

		while (!feof(vid_load)) //파일의 끝까지
		{
			new_vid = new Video_Info; //공간할당
			fscanf(vid_load, "%d %s %s %d",&tmp_vid_num, &new_vid->vid_name, &new_vid->vid_added_date, &new_vid->vid_rental); //파일로부터 vid_num,이름,추가날짜,대여상태을 불러와 new_vid에 기록

			new_vid->set_vid_num(tmp_vid_num); //기존 vid_num으로 설정
				
			if (fix_last_file == 1 && fix_last_vid_num <= tmp_vid_num) //last.dat파일이 손상된 경우
				fix_last_vid_num = tmp_vid_num;

			if (*head_vid == NULL) //헤드포인터가 NULL이면 새로운 헤드포인터 설정
			{ 
				*head_vid = new_vid;
			}
			else 
			{
				Video_Info *vid_indexer = *head_vid; //head_vid의 next링크를 따라서 인덱싱할 vid_indexer 생성
				while (vid_indexer->next != NULL) { //노드의 next링크를 따라 끝까지 이동
					vid_indexer = vid_indexer->next;
				}
				vid_indexer ->next = new_vid; //끝 노드의 next링크가 새로운 노드를 가리키게함
				new_vid->pre = vid_indexer; //끝 노드와 새로운 노드의 pre링크로 연결
			}
		}

		//**** 고객 데이터베이스 로드
		Person_Info *new_person = NULL;
		int tmp_person_num = 0;
		char tmp_newline[MAX_CHAR_LENGTH]; //줄바꿈 문자가 나올때까지 읽기위해 사용하는 임시변수

		while (!feof(person_load)) //파일의 끝까지
		{
			new_person = new Person_Info; //공간할당
			
			fscanf(person_load, "%d %s %s",&tmp_person_num, &new_person->name, &new_person->phone_num); //파일로부터 person_num,이름,전화번호를 불러와 new_person에 기록
			new_person->set_person_num(tmp_person_num); //기존 person_num으로 설정

			if (fix_last_file == 1 && fix_last_person_num <= tmp_person_num) //last.dat파일이 손상된 경우
				fix_last_person_num = tmp_person_num;

			int i = 0;

			if (last_max_rental_count >= MAX_RENTAL_COUNT) //현재 최대 대여 가능 수가 마지막으로 사용된 대여 가능 수보다 작은 경우 또는 같은 경우 현재 최대 대여 가능 수 까지만 데이터베이스상에 로드
			{
				while (i < MAX_RENTAL_COUNT) //파일로부터 대여목록을 불러와 기록
				{
					fscanf(person_load, "%d", &new_person->rental_list[i]);
					i++;
				}
				fscanf(person_load, "%[^\n]s", &tmp_newline); //줄바꿈문자가 나올때까지 읽는다
				fflush(stdin); //버퍼를 비움

				if (*head_person == NULL) //헤드포인터가 NULL이면 새로운 헤드포인터 설정
				{
					*head_person = new_person;
				}
				else 
				{
					Person_Info *person_indexer = *head_person; //head_person의 next링크를 따라서 인덱싱할 person_indexer 생성
					while (person_indexer->next != NULL) //노드의 next링크를 따라 끝까지 이동
					{
						person_indexer = person_indexer->next;
					}
						person_indexer->next = new_person; //끝 노드의 next링크가 새로운 노드를 가리키게함
						new_person->pre = person_indexer; //끝 노드와 새로운 노드의 pre링크로 연결

				}
			}

			else //현재 최대 대여 가능 수가 마지막으로 사용된 대여 가능 수보다 크면 기록된 대여목록 이후의 값들은 자동적으로 0으로 처리
			{
				while (i < last_max_rental_count) //파일로부터 대여목록을 불러와 기록
				{
					fscanf(person_load, "%d", &new_person->rental_list[i]);
					i++;
				}

				fscanf(person_load, "%[^\n]s", &tmp_newline); //줄바꿈문자가 나올때까지 읽는다
				fflush(stdin); //버퍼를 비움

				if (*head_person == NULL) //헤드포인터가 NULL이면 새로운 헤드포인터 설정
				{
					*head_person = new_person;
				}
				else 
				{
					Person_Info *person_indexer = *head_person; //head_person의 next링크를 따라서 인덱싱할 person_indexer 생성
					while (person_indexer->next != NULL) { //노드의 next링크를 따라 끝까지 이동
						person_indexer = person_indexer->next;
					}
						person_indexer->next = new_person; //끝 노드의 next링크가 새로운 노드를 가리키게함
						new_person->pre = person_indexer; //끝 노드와 새로운 노드의 pre링크로 연결

				}
			}
		}

		//last.dat파일이 손상된 경우 비디오,고객 정보로부터 복구
		if (fix_last_file == 1)
		{
			last_vid_num = fix_last_vid_num;
			last_person_num = fix_last_person_num;
			last_vid_num++; last_person_num++; //비디오 또는 고객을 새로 입력할 경우 vid_num,person_num에 대해 이니셜라이징시 값을 바로 할당해야하므로 증가시킴
		}
	}
	else
	{
		fprintf(stderr, "저장된 데이터베이스가 없거나 데이터베이스를 읽기모드로 여는 중 오류가 발생했습니다.");
		return 0;
	}
	fclose(vid_load);
	fclose(person_load);
	if(last_count != NULL)
		fclose(last_count);
	return 1;
}

int save_db(Video_Info **head_vid, Person_Info **head_person) //데이터베이스 저장 함수
{

	FILE *vid_save, *person_save, *last_count;

	if ((vid_save = fopen("vid_info.dat", "wt")) != NULL && (person_save = fopen("person_info.dat", "wt")) != NULL && (last_count = fopen("last.dat", "wt")) != NULL) //쓰기 + 텍스트 파일 모드
	{
		//**** 비디오 데이터베이스 저장
		if (*head_vid != NULL)
		{
			Video_Info *vid_indexer = *head_vid; //head_vid의 next링크를 따라서 인덱싱할 vid_indexer

			while (vid_indexer->next != NULL) //노드의 끝 바로 전 노드까지
			{
				fprintf(vid_save, "%d %s %s %d\n", vid_indexer->get_vid_num(), vid_indexer->vid_name, vid_indexer->vid_added_date, vid_indexer->vid_rental); //줄바꿈을 마지막에 추가하여 기록
				vid_indexer = vid_indexer->next;
			}
			//마지막 노드 저장(줄 바꾸지 않음)
			fprintf(vid_save, "%d %s %s %d", vid_indexer->get_vid_num(), vid_indexer->vid_name, vid_indexer->vid_added_date, vid_indexer->vid_rental);
		}

		//**** 고객 데이터베이스 저장
		if (*head_person != NULL)
		{
			Person_Info *person_indexer = *head_person; //head_person의 next링크를 따라서 인덱싱할 person_indexer
			while (person_indexer->next != NULL) //노드의 끝 바로 전 노드까지
			{
				fprintf(person_save, "%d %s %s", person_indexer->get_person_num(), person_indexer->name, person_indexer->phone_num);
				fprintf(person_save, " "); //데이터를 구분하기 위해 띄어쓰기 삽입

				int i = 0;
				while (i < MAX_RENTAL_COUNT - 1) //고객의 대여 목록 기록
				{
					fprintf(person_save, "%d ", person_indexer->rental_list[i]);
					i++;
				}
				fprintf(person_save, "%d\n", person_indexer->rental_list[i]); //마지막 데이터 기록 후 줄바꿈

				person_indexer = person_indexer->next;
			}

			//마지막 노드 저장
			fprintf(person_save, "%d %s %s", person_indexer->get_person_num(), person_indexer->name, person_indexer->phone_num);
			fprintf(person_save, " "); //데이터를 구분하기 위해 띄어쓰기 삽입

			int i = 0;
			while (i < MAX_RENTAL_COUNT - 1)
			{
				fprintf(person_save, "%d ", person_indexer->rental_list[i]);
				i++;
			}
			fprintf(person_save, "%d", person_indexer->rental_list[i]); //마지막 데이터 기록
		}

		//**** last.dat 파일 기록
		fprintf(last_count, "%d %d %d", last_vid_num,last_person_num, MAX_RENTAL_COUNT); //마지막으로 사용한 vid_num,person_num,최대 대여 가능 수 저장
	}
	else
	{
		fprintf(stderr, "데이터베이스를 쓰기모드로 여는 중 오류가 발생했습니다.");
		return 0;
	}
	fclose(vid_save);
	fclose(person_save);
	fclose(last_count);
	return 1;
}

int search_db(Video_Info **head_vid,Person_Info **head_person,Video_Info **Dst_vid,Person_Info **Dst_person,const char name[],int option) //데이터베이스 검색 전용 함수(검색, 추가, 삭제, 대여, 반납에서 사용)
{
	/* search_db option
	0 - 비디오 정보 이름으로 검색 (공간 할당하여 Dst_vid 로 전달)
	1 - 고객 정보 이름으로 검색 (공간 할당하여 Dst_person으로 전달)
	2 - 최대 대여 횟수를 넘기지 않는 고객을 이름으로 검색 (공간 할당하여 Dst_person으로 전달)
	삭제 해야 함 3 - 현재 대여중인 비디오를 이름으로 검색 (공간 할당하여 Dst_vid 로 전달)
	3 - 현재 대여중이지 않는 비디오를 이름으로 검색 (공간 할당하여 Dst_vid 로 전달)
	4 - vid_num에 해당하는 비디오의 원본 DB상에서 저장된 주소를 전달 (Dst_vid 로 전달)
	5 - person_num에 해당하는 고객의 원본 DB상에서 저장된 주소를 전달 (Dst_person 로 전달)
	*/

	//*head_vid 또는 *head_person의 주소값을 받아서
	//검색 수행후 *Dst_vid 또는 *Dst_person 으로 주소값을 전달
	//검색결과로 할당된 공간은 호출한 곳에서 free_list로 메모리를 해제한다
	//string을 char형으로 바꾸는 c_Str()함수는 const char*를 리턴하므로 search_db 인수를 const char형으로 받아야함

	Video_Info *search_vid_result = NULL; //검색 결과를 공간할당 받아 저장하기 위한 포인터
	Video_Info *head_search_vid_result = NULL; //저장된 검색결과의 맨 처음을 가리키는 헤드포인터
	Video_Info *vid_indexer = NULL; //원본 DB 인덱서

	Person_Info *search_person_result = NULL; //검색 결과를 공간할당 받아 저장하기 위한 포인터
	Person_Info *head_search_person_result = NULL; //저장된 검색결과의 맨 처음을 가리키는 헤드포인터
	Person_Info *person_indexer = NULL; //원본 DB 인덱서

	int choice_num; //vid_num 또는 person_num을 char[]형으로 변환 받아서 인수로 받은 후 int로 변환하기 위한 변수

	//검색된 결과를 Dst_vid 또는 Dst_person로 전달
	switch (option)
	{
	case 0: //비디오 정보 검색
		if (*head_vid != NULL) //저장된 정보가 있을때만
		{ 
			vid_indexer = *head_vid; //원본 DB 인덱서
			//head_vid의 next링크를 따라서 검색 후 이름이 일치하면
			//search_vid_result에 추가

			if (vid_indexer->next == NULL) //원본 DB에 저장된 정보가 1개뿐일 경우
			{
				if (strcmp(name, vid_indexer->vid_name) == 0)
				{
					search_vid_result = new Video_Info; //검색 결과를 저장하기 위해 공간할당
					memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사
					*Dst_vid = search_vid_result; //검색된 결과가 저장된 공간의 주소값을 전달
				}
				return 1;
			}

			while (vid_indexer != NULL) //노드의 끝까지
			{
				if (strcmp(name, vid_indexer->vid_name) == 0)
				{
					if (head_search_vid_result == NULL) //맨 처음 검색결과에 대해서 공간할당하고 검색결과의 헤드포인터 설정
					{
						search_vid_result = new Video_Info; //검색 결과를 저장하기 위해 공간할당
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사

						//검색결과의 next,pre링크 변경
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;

						head_search_vid_result = search_vid_result; //헤드포인터 설정
					}
					else //맨 처음 검색결과가 아닐 경우 검색결과의 next링크가 가리키는 곳에 공간할당 후 이동 및 내용 복사
					{
						search_vid_result->next = new Video_Info; //검색 결과를 저장하기위해 next가 가리키는 곳에 공간할당
						search_vid_result = search_vid_result->next; //search_vid_result를 next따라 이동
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사
						//검색결과의 next,pre링크 변경
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;
					}
				}

				vid_indexer = vid_indexer->next;
			}
			*Dst_vid = head_search_vid_result; //검색된 결과가 저장된 공간의 헤드포인터를 전달
			return 1;
		}
		return 0;

	case 1: //고객 정보 검색
		if (*head_person != NULL) //저장된 정보가 있을때만
		{ 
			person_indexer = *head_person; //원본 DB 인덱서
			//head_person의 next링크를 따라서 검색 후 이름이 일치하면
			//search_person_result에 추가
			if (person_indexer->next == NULL) //원본 DB에 저장된 정보가 1개뿐일 경우
			{
				if (strcmp(name, person_indexer->name) == 0)
				{
					search_person_result = new Person_Info; //검색 결과를 저장하기 위해 공간할당
					memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
					*Dst_person = search_person_result; //검색된 결과가 저장된 공간의 주소값을 전달
				}
				return 1;
			}

			while (person_indexer != NULL) //노드의 끝까지
			{
				if (strcmp(name, person_indexer->name) == 0)
				{
					if (head_search_person_result == NULL) //맨 처음 검색 결과에 대해서 공간할당 및 검색결과의 헤드포인터 설정
					{
						search_person_result = new Person_Info; //검색 결과를 저장하기 위해 공간할당
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
						//검색결과의 next,pre링크 변경
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
						
						head_search_person_result = search_person_result; //헤드포인터 설정
					}
					else //맨 처음 검색결과가 아닐 경우 검색결과의 next링크가 가리키는 곳에 공간할당 후 이동 및 내용 복사
					{
						search_person_result->next = new Person_Info; //검색 결과를 저장하기위해 next가 가리키는 곳에 공간할당
						search_person_result = search_person_result->next; //search_person_result를 next따라 이동
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
						//검색결과의 next,pre링크 변경
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
					}
				}

				person_indexer = person_indexer->next;
			}

			*Dst_person = head_search_person_result; //검색된 결과가 저장된 공간의 헤드포인터를 전달
			return 1;
		}
		return 0;

	case 2: //최대 대여 횟수를 넘기지 않는 고객을 이름으로 검색
		if(*head_person != NULL) //저장된 정보가 있을때만
		{
			person_indexer = *head_person; //원본 DB 인덱서
			//head_person의 next링크를 따라서 검색 후 이름이 일치및 rental_list[MAX_RENTAL_COUNT - 1]이 0인지 여부 확인
			//search_person_result에 추가
			if (person_indexer->next == NULL) //원본 DB에 저장된 정보가 1개뿐일 경우
			{
				if (strcmp(name, person_indexer->name) == 0 && person_indexer->rental_list[MAX_RENTAL_COUNT - 1] == 0)
				{
					search_person_result = new Person_Info; //검색 결과를 저장하기 위해 공간할당
					memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
					*Dst_person = search_person_result; //검색된 결과가 저장된 공간의 주소값을 전달
				}
				return 1;
			}

			while (person_indexer != NULL) //노드의 끝까지
			{
				if (strcmp(name, person_indexer->name) == 0 && person_indexer->rental_list[MAX_RENTAL_COUNT - 1] == 0)
				{
					if (head_search_person_result == NULL) //맨 처음 검색 결과에 대해서 공간할당 및 검색결과의 헤드포인터 설정
					{
						search_person_result = new Person_Info; //검색 결과를 저장하기 위해 공간할당
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
						//검색결과의 next,pre링크 변경
						search_person_result->next = NULL;
						search_person_result->pre = NULL;

						head_search_person_result = search_person_result; //헤드포인터 설정
					}
					else //맨 처음 검색결과가 아닐 경우 검색결과의 next링크가 가리키는 곳에 공간할당 후 이동 및 내용 복사
					{
						search_person_result->next = new Person_Info; //검색 결과를 저장하기위해 next가 가리키는 곳에 공간할당
						search_person_result = search_person_result->next; //search_person_result를 next따라 이동
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //내용 복사
						 //검색결과의 next,pre링크 변경
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
					}
				}
				person_indexer = person_indexer->next;
			}

			*Dst_person = head_search_person_result; //검색된 결과가 저장된 공간의 헤드포인터를 전달
			return 1;
		}
		return 0;
	
	case 3: //현재 대여중이지 않는 비디오를 이름으로 검색
		if(*head_vid != NULL) //저장된 정보가 있을때만
		{
			vid_indexer = *head_vid; //원본 DB 인덱서
			//head_vid의 next링크를 따라서 검색 후 이름이 일치,대여중이지 않은 비디오만
			//search_vid_result에 추가

			if (vid_indexer->next == NULL) //원본 DB에 저장된 정보가 1개뿐일 경우
			{
				if (strcmp(name, vid_indexer->vid_name) == 0 && vid_indexer->vid_rental == 0)
				{
					search_vid_result = new Video_Info; //검색 결과를 저장하기 위해 공간할당
					memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사
					*Dst_vid = search_vid_result; //검색된 결과가 저장된 공간의 주소값을 전달
				}
				return 1;
			}

			while (vid_indexer != NULL) //노드의 끝까지
			{
				if (strcmp(name, vid_indexer->vid_name) == 0 && vid_indexer->vid_rental == 0)
				{
					if (head_search_vid_result == NULL) //맨 처음 검색결과에 대해서 공간할당하고 검색결과의 헤드포인터 설정
					{
						search_vid_result = new Video_Info; //검색 결과를 저장하기 위해 공간할당
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사

						//검색결과의 next,pre링크 변경
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;

						head_search_vid_result = search_vid_result; //헤드포인터 설정
					}
					else //맨 처음 검색결과가 아닐 경우 검색결과의 next링크가 가리키는 곳에 공간할당 후 이동 및 내용 복사
					{
						search_vid_result->next = new Video_Info; //검색 결과를 저장하기위해 next가 가리키는 곳에 공간할당
						search_vid_result = search_vid_result->next; //search_vid_result를 next따라 이동
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //내용 복사
						//검색결과의 next,pre링크 변경
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;
					}
				}

				vid_indexer = vid_indexer->next;
			}

			*Dst_vid = head_search_vid_result; //검색된 결과가 저장된 공간의 헤드포인터를 전달
			return 1;
		}
		return 0;
		
	case 4: // vid_num에 해당하는 비디오의 원본 DB상에서 저장된 주소를 전달
 		if (*head_vid != NULL) //저장된 정보가 있을때만
		{
			choice_num = atoi(name); //사용자로부터 받은 char형 vid_num을 정수로 변환

			vid_indexer = *head_vid; //원본 DB 인덱서
			//head_vid의 next링크를 따라서 검색 후 vid_num이 일치하면 전달
			while (vid_indexer != NULL)
			{
				if (vid_indexer->get_vid_num() == choice_num)
				{
					*Dst_vid = vid_indexer; //vid_num이 일치할 경우 원본 DB에서 해당위치를 전달
					return 1;
				}
				vid_indexer = vid_indexer->next;
			}
			return 0;
										
		}
		return 0;
	
	case 5: // person_num에 해당하는 고객의 원본 DB상에서 저장된 주소를 전달
		if (*head_person != NULL) //저장된 정보가 있을때만
		{
			choice_num = atoi(name); //사용자로부터 받은 char형 person_num을 정수로 변환

			person_indexer = *head_person; //원본 DB 인덱서
			//head_person의 next링크를 따라서 검색 후 vid_num이 일치하면 전달
			while (person_indexer != NULL)
			{
				if (person_indexer->get_person_num() == choice_num)
				{
					*Dst_person = person_indexer; //person_num이 일치할 경우 원본 DB에서 해당위치를 전달
					return 1;
				}
				person_indexer = person_indexer->next;
			}
		}
		return 0;

	}
	return 0;
}

int search_info(Video_Info **head_vid, Person_Info **head_person, int option) //검색 및 출력 함수
{
	/*
	search_info option
	0 - 비디오 정보 검색
	1 - 고객 정보 검색
	*/
	
	//*head_vid,*head_person의 주소값을 받아와서 검색
	Video_Info *search_vid_result = NULL;
	Person_Info *search_person_result = NULL;

	std::string tmp_name;

	switch (option)
	{
	case 0: //비디오 정보 검색
		while (1)
		{
			std::cout << "검색하고자 하는 비디오의 이름을 입력하세요. 취소 : -1 입력" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
			}
			else break;
		}
		if (tmp_name.compare("-1") == 0) return -1;
		if (search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 0) == 0) return 0; //검색 수행
		if (print_info(&search_vid_result, &search_person_result, 0) == 0) return 0; //출력
		break;

	case 1: //고객 정보 검색
		while (1)
		{
			std::cout << "검색하고자 하는 고객의 이름을 입력하세요. 취소 : -1 입력" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
			}
			else break;
		}
		if (tmp_name.compare("-1") == 0) return -1;
		if (search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 1) == 0) return 0; //검색 수행
		if (print_info(&search_vid_result, &search_person_result, 1) == 0) return 0; //출력
		break;
	}

	free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리 공간 해제
	return 1;
}

int print_info(Video_Info **head_vid,Person_Info **head_person,int option) //출력 함수
{
	/* print_info option
	0 - 비디오 정보 출력
	1 - 고객 정보 출력
	2 - 단일 고객이 대여중인 비디오 목록 출력
	*/

	//헤드포인터를 손상시키지 않고 탐색하기 위한 인덱서
	Video_Info *vid_indexer = NULL;
	Person_Info *person_indexer = NULL;

	switch(option)
	{
	case 0: //비디오 정보 출력
		if (*head_vid != NULL) { //저장된 정보가 있을때만
			vid_indexer = *head_vid; //원본 DB 인덱서
			while (vid_indexer != NULL)
			{
				std::cout << "=================================" << std::endl;
				std::cout << "비디오 이름 : " << vid_indexer->vid_name << std::endl;
				std::cout << "비디오 추가 날짜 : " << vid_indexer->vid_added_date << std::endl;
				std::cout << "비디오 대여 상태 : ";
				if (vid_indexer->vid_rental == 0) std::cout << "대여되지 않음" << std::endl;
				else std::cout << "대여됨" << std::endl;
				std::cout << "VID_NUM : " << vid_indexer->get_vid_num() << std::endl;
				std::cout << "=================================" << std::endl;
				vid_indexer = vid_indexer-> next;
			}
			return 1;
		}
		else return 0;

	case 1: //사용자 정보 출력
		if (*head_person != NULL) { //저장된 정보가 있을때만
			person_indexer = *head_person; //원본 DB 인덱서
			vid_indexer = *head_vid; //원본 DB 인덱서
			while (1)
			{
				std::cout << "=================================" << std::endl;
				std::cout << "고객 이름 : " << person_indexer->name << std::endl;
				std::cout << "전화번호 : " << person_indexer->phone_num << std::endl;
				std::cout << "대여한 비디오 목록 : ";
				if (person_indexer->rental_list[0] == 0) std::cout << "대여한 비디오가 없습니다.";
				else 
				{
					for (int i = 0; i < MAX_RENTAL_COUNT; i++)
					{
						vid_indexer = *head_vid; //원본 DB 인덱서

						while (1) //비디오 DB상에서 해당하는 비디오의 이름을 찾아서 출력
						{	
							if(vid_indexer->get_vid_num() == person_indexer->rental_list[i]) //원본 vid_num과 대여한 비디오 목록의 vid_num이 일치하면 출력
								std::cout << vid_indexer->vid_name<<" ";
							vid_indexer = vid_indexer->next; //이동
							if (vid_indexer == NULL) break;
						}
					}
				}
				std::cout << std::endl;
				std::cout << "PERSON_NUM : " << person_indexer->get_person_num() << std::endl;
				std::cout << "=================================" << std::endl;
				person_indexer = person_indexer->next; //이동
				if (person_indexer == NULL) break; //이동했는데 NULL일경우 종료
			}
			return 1;
		}
		else return 0;

	case 2: //단일 고객이 대여중인 비디오 목록 출력
		if (*head_person != NULL && *head_vid != NULL) //저장된 정보가 있을때만
		{
			vid_indexer = *head_vid; //원본 DB 인덱서
			person_indexer = *head_person; //사용자로부터 받은 단일 고객 정보

			while (1)
			{
				for (int i = 0; i < MAX_RENTAL_COUNT; i++) //고객이 대여중인 비디오 목록에 대해 반복
				{
					if (person_indexer->rental_list[i] == vid_indexer->get_vid_num()) //고객이 대여한 비디오가 맞을경우 출력
					{
						std::cout << "=================================" << std::endl;
						std::cout << "비디오 이름 : " << vid_indexer->vid_name << std::endl;
						std::cout << "비디오 추가 날짜 : " << vid_indexer->vid_added_date << std::endl;
						std::cout << "비디오 대여 상태 : ";
						if (vid_indexer->vid_rental == 0) std::cout << "대여되지 않음" << std::endl;
						else std::cout << "대여됨" << std::endl;
						std::cout << "VID_NUM : " << vid_indexer->get_vid_num() << std::endl;
						std::cout << "=================================" << std::endl;
					}
				}
				vid_indexer = vid_indexer->next;
				if (vid_indexer == NULL) break;
			}
			return 1;
		}
		else return 0;
		
	}
	return 1;
}
int add_del_info(Video_Info **head_vid,Person_Info **head_person,int option) //추가,삭제 함수
{
	/* add_del_info option
	0 - 비디오 정보 추가
	1 - 고객 정보 추가
	2 - 비디오 정보 삭제
	3 - 고객 정보 삭제
	*/

	//정보 추가시에 현재 DB상에서 이름이 빠른순으로 정렬하여 추가
	//정보 삭제시에 앞 뒤노드의 next,pre변경 후 free
	//이미 대여중인 비디오 및 비디오를 대여중인 고객은 삭제불가

	
	Video_Info *new_vid = NULL; //새로 생성한 노드의 정보를 가리킴
	Video_Info *tmp_head_vid = NULL; //노드삽입을 위한 원본 DB의 헤드 임시저장
	Video_Info *search_vid_result = NULL; //검색 결과를 가리킴
	Video_Info *search_vid_result_indexer = NULL; //검색 결과를 메모리 해제를 위해 헤드포인터를 건드리지 않고 인덱싱하기 위한 포인터

	Person_Info *new_person = NULL; //새로 생성한 노드의 정보를 가리킴
	Person_Info *tmp_head_person = NULL; //노드삽입을 위한 원본 DB의 헤드 임시저장
	Person_Info *search_person_result = NULL; //검색 결과를 가리킴
	Person_Info *search_person_result_indexer = NULL; //검색 결과를 메모리 해제를 위해 헤드포인터를 건드리지 않고 인덱싱하기 위한 포인터

	//string의 length사용 길이검사
	std::string tmp_name;
	std::string tmp_phone_num;

	int choice; //사용자로부터 선택값
	char choice_buffer[MAX_NUM_LENGTH] = { 0 }; //사용자로부터 선택값을 문자로 변환하여 검색에 인수로 주기위한 변수

	Video_Info *choiced_vid = NULL; //사용자가 선택한 비디오 정보 주소 임시저장
	Person_Info *choiced_person = NULL; //사용자가 선택한 고객 정보 주소 임시저장

	switch(option)
	{
	case 0: //비디오 정보 추가
		new_vid = new Video_Info; //새로 추가할 노드의 공간 할당

		while (1)
		{
			std::cout << "추가하고자 하는 비디오의 이름을 입력하세요. 취소 : -1 입력" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.compare("-1") == 0)
			{
				delete new_vid; //정보 추가를 위해 할당한 공간 제거
				return -1;
			}

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자 또는 " << "숫자: " << MAX_NUM_LENGTH << "자를 초과했습니다!" << std::endl;
			}

			else
				break;
		}
		new_vid->init_num_count(); //vid_num에 대해 이니셜라이징
		strcpy(new_vid->vid_name, tmp_name.c_str()); //string 문자열을 const char형으로 바꾸어 입력
		strcpy(new_vid->vid_added_date, get_time().c_str());  //시스템으로부터 현재 시간을 알아내어 비디오 추가 날짜 입력
		
		//노드가 존재하는 경우 이름이 빠른순으로 앞에 오게 삽입
		if (*head_vid != NULL) //노드가 존재할경우
		{
			tmp_head_vid = *head_vid; //기존 헤드 임시저장
			
			while(1) //노드의 끝까지 수행
			{ 
				//strcmp(A,B) < 0 (음수) A < B
				//strcmp(B,A) > 0 (양수) 
				if (strcmp(new_vid->vid_name, (*head_vid)->vid_name) < 0) //앞에 문자열이 사전순에서 먼저오면
				{
					//new_vid를 head_vid의 앞에 삽입
					new_vid->next = *head_vid;
					if ((*head_vid)->pre != NULL) //현재 노드의 이전노드가 존재하면
					{
						new_vid->pre = (*head_vid)->pre;
						(*head_vid)->pre->next = new_vid;
					}
					(*head_vid)->pre = new_vid;
					
					if (new_vid->pre == NULL) //new_vid가 삽입된 위치가 맨 처음인 경우
						*head_vid = new_vid; //헤드포인터를 새로운 노드로 변경
					else //new_vid가 중간에 삽입된 경우
						*head_vid = tmp_head_vid; //헤드포인터를 기존 헤드로 다시 변경
					break;
				}
				if ((*head_vid)->next != NULL)
					*head_vid = (*head_vid)->next;
				else break;
			}
			//노드 끝까지 비교하여 삽입이 되지 않은 경우 맨 뒤에 삽입
			if (new_vid->next == NULL && new_vid->pre == NULL)
			{
				new_vid->pre = *head_vid;
				(*head_vid)->next = new_vid;
				*head_vid = tmp_head_vid; //헤드포인터를 기존 헤드로 다시 변경
			}
		}
		//노드가 존재하지 않는경우
		else *head_vid = new_vid; //헤드포인터가 new_vid를 가리키게 함

		break;

	case 1: //고객 정보 추가
		new_person = new Person_Info; //새로 추가할 노드의 공간 할당

		while (1)
		{
			std::cout << "추가하고자 하는 고객의 정보(이름, 전화번호)를 입력하세요. 취소 : -1 입력" << std::endl;
			std::cin >> tmp_name>>tmp_phone_num;

			if (tmp_name.compare("-1") == 0 || tmp_phone_num.compare("-1") == 0)
			{
				delete new_person; //정보 추가를 위해 할당한 공간 제거
				return -1;
			}
			if (tmp_name.length() > MAX_CHAR_LENGTH || tmp_phone_num.length() > MAX_NUM_LENGTH)
			{
				std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자 또는 " << "숫자: " << MAX_NUM_LENGTH << "자를 초과했습니다!" << std::endl;
			}
			else
			{
				strcpy(new_person->name, tmp_name.c_str()); //string 문자열을 char*형으로 바꾸어 입력
				strcpy(new_person->phone_num, tmp_phone_num.c_str());
			}
				break;
		}

		new_person->init_num_count(); //person_num에 대해 이니셜라이징
		if (*head_person != NULL) //노드가 존재할경우
		{
			tmp_head_person = *head_person; //기존 헤드 임시저장

			while (1) //노드의 끝까지 수행
			{
				//strcmp(A,B) < 0 (음수) A < B
				//strcmp(B,A) > 0 (양수) 
				if (strcmp(new_person->name, (*head_person)->name) < 0) //앞에 문자열이 사전순에서 먼저오면
				{
					//new_person를 head_person의 앞에 삽입
					new_person->next = *head_person;
					if ((*head_person)->pre != NULL) //현재 노드의 이전노드가 존재하면
					{
						new_person->pre = (*head_person)->pre;
						(*head_person)->pre->next = new_person;
					}
					(*head_person)->pre = new_person;

					if (new_person->pre == NULL) //new_person가 삽입된 위치가 맨 처음인 경우
						*head_person = new_person; //헤드포인터를 새로운 노드로 변경
					else //new_person가 중간에 삽입된 경우
						*head_person = tmp_head_person; //헤드포인터를 기존 헤드로 다시 변경
					break;
				}
				if ((*head_person)->next != NULL)
					*head_person = (*head_person)->next;
				else break;
			}
			//노드 끝까지 비교하여 삽입이 되지 않은 경우 맨 뒤에 삽입
			if (new_person->next == NULL && new_person->pre == NULL)
			{
				new_person->pre = *head_person;
				(*head_person)->next = new_person;
				*head_person = tmp_head_person; //헤드포인터를 기존 헤드로 다시 변경
			}
		}
		//노드가 존재하지 않는경우
		else *head_person = new_person; //헤드포인터가 new_person를 가리키게 함
		break;

	case 2: //비디오 정보 삭제
		
		if (*head_vid != NULL) { //노드가 존재할 경우에만
			while (1)
			{
				std::cout << "삭제하고자 하는 비디오의 이름을 입력하세요. 취소 : -1 입력" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_name;

				if (tmp_name.compare("-1") == 0)
					return -1;
				if (tmp_name.length() > MAX_CHAR_LENGTH)
					std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
				break;
			}

			//검색하여 동일이름 목록 출력
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 0); //비디오 검색
			if (search_vid_result != NULL) //검색 결과가 존재하면 목록 출력
			{
				search_vid_result_indexer = search_vid_result; //인덱서가 검색결과의 헤드를 가리키게함
				print_info(&search_vid_result, &search_person_result, 0);

				while (1) {
					std::cout << "삭제할 비디오의 VID_NUM을 입력하세요. 대여중인 비디오는 삭제 할 수 없습니다." << std::endl;
					std::cout << "취소 : -1 입력" << std::endl;
					std::cout << ">>";
					std::cin >> choice;
					if (choice == -1) return -1;

					if(choice < 1 || choice >last_vid_num) //잘못됟 문자 또는 입력범위를 초과할 경우
					{
						std::cout << "숫자만 입력 가능합니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}

					while (search_vid_result_indexer != NULL)  //올바르게 선택하였는지 검사
					{
						if (choice == search_vid_result_indexer->get_vid_num() && search_vid_result_indexer->vid_rental == 0) //검색결과에 속하는 vid_num에 맞게 입력하였는지, 해당 비디오가 대여상태인지 검사
						{
							itoa(choice, choice_buffer, 10); //사용자가 입력한 vid_num값을 문자형으로 변환
							//사용자가 선택한 vid_num으로 원본 DB에서 해당 비디오를 찾아 choiced_vid가 가리키게함
							search_db(head_vid, head_person, &choiced_vid, &search_person_result,choice_buffer, 4);
							break;
						}
						search_vid_result_indexer = search_vid_result_indexer->next;
					}

					if (choiced_vid == NULL)
					{
						//선택한 번호가 목록중에서 선택되지않았을 경우
						std::cout << "대여중인 비디오를 선택하였거나 목록에서 선택하지 않았습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					}
					else break;
				}
			}
			else
			{
				std::cout << "해당하는 비디오가 존재하지 않습니다." << std::endl;
				free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
				return 0;
			}

			//삭제하려는 노드가 헤드포인터인 경우 헤드포인터를 변경한다
			if (*head_vid == choiced_vid)
				*head_vid = (*head_vid)->next;

			if(choiced_vid->pre != NULL) //삭제하려는 노드의 이전노드가 있을 경우에만
				choiced_vid->pre->next = choiced_vid->next; //삭제하려는 노드의 이전노드의 next링크가 삭제하려는 노드의 다음노드를 가리키게함
			if(choiced_vid->next != NULL) //삭제하려는 노드의 다음노드가 있을 경우에만
				choiced_vid->next->pre = choiced_vid->pre; //삭제하려는 노드의 다음노드의 pre링크가 삭제하려는 노드의 이전노드를 가리키게함
			delete(choiced_vid);
			free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
			break;
		}
		else return 0;
		break;

	case 3: //고객 정보 삭제
		if (*head_person != NULL) { //노드가 존재할 경우에만
			while (1)
			{
				std::cout << "삭제하고자 하는 고객의 이름을 입력하세요. 취소 : -1 입력" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_name;

				if (tmp_name.compare("-1") == 0)
					return -1;
				if (tmp_name.length() > MAX_CHAR_LENGTH)
					std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
				break;
			}

			//검색하여 동일이름 목록 출력
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 1); //검색 수행
			if (search_person_result != NULL) //검색 결과가 존재하면 목록 출력
			{
				search_person_result_indexer = search_person_result; //인덱서가 검색결과의 헤드를 가리키게함
				print_info(head_vid, &search_person_result, 1);

				while (1) {
					std::cout << "삭제할 고객의 PERSON_NUM을 입력하세요. 대여중인 고객은 삭제 할 수 없습니다." << std::endl;
					std::cout << "취소 : -1 입력" << std::endl;
					std::cout << ">>";
					std::cin >> choice;
					if (choice == -1) return -1;

					if(choice < 0 || choice > last_person_num) //잘못됟 문자 또는 입력범위를 초과할 경우
					{
						std::cout << "숫자만 입력 가능합니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}

					while (search_person_result_indexer != NULL)  //올바르게 선택하였는지 검사
					{

						if (choice == search_person_result_indexer->get_person_num() && search_person_result_indexer->rental_list[0] == 0) //검색결과에 속하는 person_num에 맞게 입력하였는지, 검색결과의 고객이 대여중인 비디오가 있는지 검사
						{
							itoa(choice, choice_buffer, 10); //사용자가 입력한 person_num값을 문자형으로 변환
							//사용자가 선택한 person_num으로 원본 DB에서 해당 고객를 찾아 choiced_person가 가리키게함
							search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5);
							break;
						}
						search_person_result_indexer = search_person_result_indexer->next;
					}

					if (choiced_person == NULL)
					{
						//선택한 번호가 목록중에서 선택되지않았을 경우
						std::cout << "대여중인 고객를 선택하였거나 목록에서 선택하지 않았습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					}

					else break;
				}
			}
			else
			{
				std::cout << "해당하는 고객이 존재하지 않습니다." << std::endl;
				free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
				return 0;
			}

			//삭제하려는 노드가 헤드포인터인 경우 헤드포인터를 변경한다
			if (*head_person == choiced_person)
				*head_person = (*head_person)->next;

			if (choiced_person->pre != NULL) //삭제하려는 노드의 이전노드가 있을 경우에만
				choiced_person->pre->next = choiced_person->next; //삭제하려는 노드의 이전노드의 next링크가 삭제하려는 노드의 다음노드를 가리키게함
			if (choiced_person->next != NULL) //삭제하려는 노드의 다음노드가 있을 경우에만
				choiced_person->next->pre = choiced_person->pre; //삭제하려는 노드의 다음노드의 pre링크가 삭제하려는 노드의 이전노드를 가리키게함
			delete(choiced_person);
			free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
			break;
		}
		else return 0;
		break;
	}

	return 1;
}


int rental_return(Video_Info **head_vid,Person_Info **head_person,int option) //대여,반납 함수
{
	/* rental_return option
	0 - 비디오 대여
	1 - 비디오 반납
	*/

	//대여시에 비디오의 vid_rental 값 변경, 고객의 rental_list[]에 순서대로 추가
	//대여 한도를 넘긴 고객은 대여불가능
	//반납시에 비디오의 vid_rental 값 변경, 고객의 rental_list[]에서 삭제 후 정렬
	//중복된 정보가 있을경우 선택받음

	Video_Info *search_vid_result = NULL; //검색 결과를 가리키는 포인터
	Person_Info *search_person_result = NULL; //검색 결과를 가리키는 포인터
	Video_Info *search_vid_result_indexer = NULL; //검색 결과를 메모리 해제를 위해 헤드포인터를 건드리지 않고 인덱싱하기 위한 포인터
	Person_Info *search_person_result_indexer = NULL; //검색 결과를 메모리 해제를 위해 헤드포인터를 건드리지 않고 인덱싱하기 위한 포인터

	//string의 length사용 길이검사
	std::string tmp_person_name;
	std::string tmp_vid_name;

	int vid_choice,person_choice; //사용자로부터 선택값
	char choice_buffer[MAX_NUM_LENGTH] = { 0 }; //사용자로부터 선택값을 문자로 변환하여 검색에 인수로 주기위한 변수
	Video_Info *choiced_vid = NULL; //사용자가 선택한 비디오 정보 주소 임시저장
	Person_Info *choiced_person = NULL; //사용자가 선택한 고객 정보 주소 임시저장
	
	switch(option)
	{
	case 0: //비디오 대여
		if (*head_vid!= NULL && *head_person != NULL) //비디오와 고객의 정보가 비어있지 않을때만
		{ 
			while (1) {
				std::cout << "대여를 원하는 고객의 이름과 비디오의 이름을 입력하세요. (고객 이름, 비디오 이름)" << std::endl;
				std::cout << "취소 : -1 입력" << std::endl;
				 std::cout << ">>";
				std::cin >> tmp_person_name>>tmp_vid_name;

				if (tmp_person_name.compare("-1") == 0 || tmp_vid_name.compare("-1") == 0)
					return -1;
				else if (tmp_person_name.length() > MAX_CHAR_LENGTH || tmp_vid_name.length() > MAX_CHAR_LENGTH)
					std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
				else break;
			}
			
			//고객이름과 비디오이름 검색 후 선택받음
			
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_person_name.c_str(), 2); //대여 한도를 넘기지 않은 고객 검색
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_vid_name.c_str(), 3); //대여중이지 않은 비디오 검색

			if (search_person_result != NULL && search_vid_result != NULL) //검색 결과가 존재하면 목록 출력
			{
				search_vid_result_indexer = search_vid_result; //인덱서가 검색결과의 헤드를 가리키게함
				search_person_result_indexer = search_person_result; //인덱서가 검색결과의 헤드를 가리키게함

				std::cout << "< 고객 목록 >" << std::endl;
				print_info(head_vid, &search_person_result, 1); //검색된 고객 정보 출력
				std::cout<<std::endl;
				std::cout << "< 비디오 목록 >" << std::endl;
				print_info(&search_vid_result, &search_person_result, 0); //검색된 비디오 정보 출력

				while (1) {
					std::cout << "대여할 사용자의 PERSON_NUM 및 대여할 비디오의 VID_NUM을 입력하세요." << std::endl;
					std::cout << "대여한도 " << MAX_RENTAL_COUNT << "개를 넘긴 고객은 대여할 수 없습니다." << std::endl;
					std::cout << "취소 : -1 입력" << std::endl;
					std::cout << ">>";
					std::cin >> person_choice >> vid_choice;

					if (person_choice == -1 || vid_choice == -1) return -1;

					if (person_choice < 0 || person_choice > last_person_num || vid_choice < 1 || vid_choice >last_vid_num)  //잘못됟 문자 또는 입력범위를 초과할 경우
					{
						std::cout << "잘못된 문자를 입력하였거나 선택한도를 벗어났습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}

						while (search_person_result_indexer != NULL) //고객에 대해 person_num 값을 비교하여 검사
						{
							if (person_choice == search_person_result_indexer->get_person_num())
							{
								itoa(person_choice, choice_buffer, 10); //사용자가 입력한 vid_num값을 문자형으로 변환
								//사용자가 선택한 고객 정보를 person_num으로 원본 DB상에서 찾아 choiced_person에 주소를 받아온다
								search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5);
								break;
							}
							search_person_result_indexer = search_person_result_indexer->next;
						}

						while(search_vid_result_indexer != NULL)
						{
							if (vid_choice == search_vid_result_indexer->get_vid_num()) //비디오에 대해 vid_num값을 비교하여 검사
							{
								itoa(vid_choice,choice_buffer,10); //사용자가 입력한 vid_num값을 문자형으로 변환
								//사용자가 선택한 비디오 정보를 vid_num으로 원본 DB상에서 찾아 choiced_vid에 주소를 받아온다
								search_db(head_vid, head_person, &choiced_vid, &search_person_result, choice_buffer, 4);
								break;
							}
							search_vid_result_indexer = search_vid_result_indexer->next;
						}

					if (choiced_person == NULL || choiced_vid == NULL) //목록중에서 입력하지않았을 경우 search_db가 호출되지 않아 NULL값을 가리키게됨
					{
						//선택한 번호가 목록중에서 선택되지않았을 경우
						std::cout << "목록에서 선택하지 않았습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					}
					else break;
				}
				//대여시에 비디오의 vid_rental 값 변경, 고객의 rental_list[]에 순서대로 추가
				//대여 한도를 넘긴 고객은 대여불가능
				choiced_vid->vid_rental = 1;
				for (int i = 0; i < MAX_RENTAL_COUNT; i++)
				{
					if (choiced_person->rental_list[i] == 0) //빈 공간에 삽입
					{
						choiced_person->rental_list[i] = choiced_vid->get_vid_num();
						free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
						return 1;
					}
				}

			}
			else
			{
				std::cout << "존재하지 않는 고객,비디오를 입력하였거나 최대 대여 한도: " << MAX_RENTAL_COUNT << "을 넘긴 고객 또는 이미 대여중인 비디오입니다." << std::endl;
				free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
				return 0;
			}
		}
		else
		{
			std::cout << "데이터베이스상에 저장된 비디오나 고객의 정보가 없습니다." << std::endl;
			return 0;
		}

		break;

	case 1: //비디오 반납
		//반납을 원하는 고객의 이름과 비디오의 이름을 입력받는다
		//이름에 해당하는 고객의 목록을 출력하고 선택
		//해당 고객이 대여중인 비디오 목록을 출력하고 선택
		if (*head_vid != NULL && *head_person != NULL) //비디오와 고객의 정보가 비어있지 않을때만
		{ 
			while (1) {
				std::cout << "반납를 원하는 고객의 이름을 입력하세요." << std::endl;
				std::cout << "취소 : -1 입력" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_person_name;

				if (tmp_person_name.compare("-1") == 0 || tmp_vid_name.compare("-1") == 0)
					return -1;
				else if (tmp_person_name.length() > MAX_CHAR_LENGTH || tmp_vid_name.length() > MAX_CHAR_LENGTH)
					std::cout << "최대길이 제한 " << "문자: " << MAX_CHAR_LENGTH << "자를 초과했습니다!" << std::endl;
				else break;
			}
			
			//고객이름 검색 후 선택받음
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_person_name.c_str(), 1); //이름으로 고객 검색

			if (search_person_result != NULL) //검색 결과가 존재하면 목록 출력
			{
				search_person_result_indexer = search_person_result; //인덱서가 헤드를 가리키게함
				print_info(head_vid, &search_person_result, 1); //고객 목록 출력(고객이 대여한 목록도 출력하기위해 인수로 비디오 헤드포인터 전달)

				while (1) {
					std::cout << "반납할 사용자의 PERSON_NUM을 입력하세요." << std::endl;
					std::cout << "취소 : -1 입력" << std::endl;
					std::cout << ">>";
					std::cin >> person_choice;

					if (person_choice == -1) return -1;

					if(person_choice < 0 || person_choice > last_person_num) //잘못됟 문자 또는 입력범위를 초과할 경우
					{
						std::cout << "잘못된 문자를 입력하였거나 선택한도를 벗어났습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}

						while(search_person_result_indexer != NULL) //고객에 대해 올바르게 선택하였는지 검사
						{ 
							if (person_choice == search_person_result_indexer->get_person_num())
							{
								itoa(person_choice,choice_buffer,10); //사용자가 입력한 person_num값을 문자형으로 변환
								//사용자가 선택한 고객 정보를 person_num으로 원본 DB상에서 찾아 choiced_person에 주소를 받아온다
								search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5); 
								break;
							}
							search_person_result_indexer = search_person_result_indexer->next;
						}

					if (choiced_person == NULL)
					{
						//선택한 번호가 목록중에서 선택되지않았을 경우
						std::cout << "목록에서 선택하지 않았습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					}
					else break;
				}
				//해당 고객이 대여중인 목록 출력 및 선택
				std::cout << choiced_person->name << "님이 대여중인 비디오목록입니다." << std::endl;
				print_info(head_vid,&choiced_person, 2); //해당 고객이 대여중인 목록 출력
				
				while(1)
				{
					std::cout<< "반납할 비디오의 VID_NUM을 입력하세요." <<std::endl;
					std::cout << "취소 : -1 입력" << std::endl;
					std::cout << ">>";
					std::cin >> vid_choice;

					if (vid_choice == -1) return -1;

					if(vid_choice < 1 || vid_choice > last_vid_num) //잘못됟 문자 또는 입력범위를 초과할 경우
					{
						std::cout << "잘못된 문자를 입력하였거나 선택한도를 벗어났습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
						continue;
					}
	
	
						for (int i = 0; i < MAX_RENTAL_COUNT; i++) //입력값이 고객이 대여한 목록의 vid_num과 일치하는지 검사
						{
							if (vid_choice == choiced_person->rental_list[i])
							{
								itoa(vid_choice, choice_buffer, 10); //사용자가 입력한 person_num값을 문자형으로 변환
								//사용자가 선택한 vid_num으로 원본 DB에서 해당 비디오를 찾아 choiced_vid가 가리키게함
								search_db(head_vid, head_person, &choiced_vid, &search_person_result, choice_buffer, 4);
								break;
							}
						}
				

					if (choiced_vid == NULL)
					{
						//선택한 번호가 목록중에서 선택되지않았을 경우
						std::cout << "목록에서 선택하지 않았습니다!!" << std::endl;
						std::cin.clear(); //오류스트림 초기화
						std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					}
					else break;
				}

				//반납시에 비디오의 vid_rental 값 변경, 고객의 rental_list[]에서 삭제 후 정렬
				choiced_vid->vid_rental = 0;
				//대여목록에 대해 정렬
				for(int i = 0; i < MAX_RENTAL_COUNT;i++)
				{
					if(choiced_person->rental_list[i] == vid_choice) //해당 위치부터 정렬
					{
						//뒤의 값을 앞에 덮어씌우고
						for(int j = i ; j < MAX_RENTAL_COUNT ; j++)
						{
							choiced_person->rental_list[j]=choiced_person->rental_list[j+1];
						}
					}
				}
				//대여목록의 마지막 값은 배열의 최대 수를 넘는 곳에서 읽어온 잘못된 값이 들어가게되므로 0으로 바꿈
				if (choiced_person->rental_list[MAX_RENTAL_COUNT - 1] != 0)
					choiced_person->rental_list[MAX_RENTAL_COUNT - 1] = 0;
			
				free_list(&search_vid_result, &search_person_result); //검색에 사용한 메모리공간 반환
				return 1;
			}
			else
			{
				std::cout << "고객이 존재하지 않습니다." << std::endl;
				return 0;
			}

		}
		else
		{
			std::cout << "데이터베이스상에 저장된 비디오나 고객의 정보가 없습니다." << std::endl;
			return 0;
		}

	break;

	}
	return 1;
}