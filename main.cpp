#include "header.h"


//////////////////////////////////////////////
/**
	disp_screen option - 메뉴 출력 함수
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
	
	search_db option - 데이터베이스 검색 전용 함수(검색,추가,삭제,대여,반납에서 사용)
	0 - 비디오 정보 이름으로 검색 (공간 할당하여 Dst_vid 로 전달)
	1 - 고객 정보 이름으로 검색 (공간 할당하여 Dst_person으로 전달)
	2 - 최대 대여 횟수를 넘기지 않는 고객을 이름으로 검색 (공간 할당하여 Dst_person으로 전달)
	3 - 현재 대여중이지 않는 비디오를 이름으로 검색 (공간 할당하여 Dst_vid 로 전달)
	4 - vid_num에 해당하는 비디오의 원본 DB상에서 저장된 주소를 전달 (Dst_vid 로 전달)
	5 - person_num에 해당하는 고객의 원본 DB상에서 저장된 주소를 전달 (Dst_person 로 전달)

	search_info option - 검색 함수
	0 - 비디오 정보 이름으로 검색
	1 - 고객 정보 이름으로 검색
	

	print_info option - 정보 출력 함수
	0 - 비디오 정보 출력
	1 - 고객 정보 출력
	2 - 단일 고객이 대여중인 비디오 목록 출력

	add_del_info option - 정보 추가,삭제 함수
	0 - 비디오 정보 추가
	1 - 고객 정보 추가
	2 - 비디오 정보 삭제
	3 - 고객 정보 삭제
	

	rental_return option - 대여,반납 함수
	0 - 비디오 대여
	1 - 비디오 반납
	
**/
//////////////////////////////////////////////

void main()
{
	//_wsetlocale( LC_ALL, L"korean" ); //지역화 설정을 전역적으로 적용

	/*
	함수 리턴값
	-1 : 사용자 실행 취소
	0 : 실패
	1 : 성공
	*/

	Video_Info *head_vid = NULL; //비디오 정보의 헤드 포인터
	Person_Info *head_person = NULL; //고객 정보의 헤드 포인터

	Video_Info *search_vid_result = NULL; //검색 결과 출력을 위해 저장된 공간을 가리키는 포인터
	Person_Info *search_person_result = NULL; //검색 결과 출력을 위해 저장된 공간을 가리키는 포인터

	while (1)
	{
		int main_select = 0; //사용자로부터 메뉴선택을 입력받는 변수
		int sub_select = 0; //서브에뉴에 대한 선택을 입력받는 변수
		disp_screen(0);

		std::cin >> main_select;

		if (main_select == 9) break;
		else if (main_select < 1 || main_select > 9)
			//입력범위 초과 또는 잘못된 문자입력
		{
			std::cout << "메뉴중에서 선택하세요!!" << std::endl;
			std::cin.clear(); //오류스트림 초기화
			std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
			Sleep(1000);
		}

		switch (main_select) //메인메뉴에 대한 스위치문
		{
		case 1: //비디오 또는 고객 정보 검색
			while (1) {
				disp_screen(1);
				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					Sleep(1000);
				}

				switch (sub_select) //서브메뉴에 대한 스위치문
				{
				case 1: //비디오 정보 검색 및 출력
					if (search_info(&head_vid, &head_person, 0))
						system("pause");
					else
					{
						std::cout << "해당하는 비디오 정보가 없습니다." << std::endl;
						system("pause");
					}
					break;

				case 2: //고객 정보 검색 및 출력
					if (search_info(&head_vid, &head_person, 1))
						system("pause");
					else
					{
						std::cout << "해당하는 고객 정보가 없습니다." << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 2: //비디오 대여 및 반납
			while (1) {
				disp_screen(2);
				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					Sleep(1000);
				}

				switch (sub_select) //서브메뉴에 대한 스위치문
				{
				case 1: //비디오 대여
					if (rental_return(&head_vid, &head_person, 0) == 1)
					{
						std::cout << "대여되었습니다." << std::endl;
						system("pause");
					}
					else system("pause");
					break;

				case 2: //비디오 반납
					if (rental_return(&head_vid, &head_person, 1) == 1)
					{
						std::cout << "반납되었습니다." << std::endl;
						system("pause");
					}
					else system("pause");
					break;
				}
				break;
			}
			break;

		case 3: //전체 비디오, 고객 정보 출력
			while (1) {
				disp_screen(3);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					Sleep(1000);
				}

				switch (sub_select) //서브메뉴에 대한 스위치문
				{
				case 1: //전체 비디오 출력
					if (print_info(&head_vid, &head_person, 0) == 1)
						system("pause");
					else
					{
						std::cout << "저장된 비디오 정보가 없습니다." << std::endl;
						system("pause");
					}
					break;

				case 2: //전체 고객 정보 출력
					if (print_info(&head_vid, &head_person, 1) == 1)
						system("pause");
					else
					{
						std::cout << "저장된 고객 정보가 없습니다." << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 4: //비디오 또는 고객 정보 추가			
			while (1) {
				disp_screen(4);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					Sleep(1000);
				}

				switch (sub_select) //서브메뉴에 대한 스위치문
				{
				case 1: //비디오 추가
					if (add_del_info(&head_vid, &head_person, 0) == 1)
					{
						std::cout << "추가 성공" << std::endl;
						system("pause");
					}
					break;

				case 2: //고객 추가
					if (add_del_info(&head_vid, &head_person, 1) == 1)
					{
						std::cout << "추가 성공" << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 5: //비디오 또는 고객 정보 삭제
			while (1) {
				disp_screen(5);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					Sleep(1000);
				}

				switch (sub_select) //서브메뉴에 대한 스위치문
				{
				case 1: //비디오 삭제
					if (add_del_info(&head_vid, &head_person, 2) == 1)
					{
						std::cout << "삭제 성공" << std::endl;
						system("pause");
					}
					break;

				case 2: //고객 삭제
					if (add_del_info(&head_vid, &head_person, 3) == 1)
					{
						std::cout << "삭제 성공" << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 6: //데이터베이스 저장
			if (save_db(&head_vid, &head_person) == 1)
			{
				std::cout << "저장 성공" << std::endl;
				system("pause");
			}
			else
			{
				std::cout << "저장 실패" << std::endl;
				system("pause");
			}
			break;

		case 7: //데이터베이스 불러오기
			while (1) {
				std::cout << "현재 작업중인 내용을 잃을수도 있습니다." << std::endl;
				std::cout << "계속 : 1, 취소 : -1" << std::endl;
				std::cout << ">>" << std::endl;
				std::cin >> sub_select;

				if (sub_select == -1) break;
				else if (sub_select != 1)
					//입력범위 초과 또는 잘못된 문자입력
				{
					std::cout << "메뉴중에서 선택하세요!!" << std::endl;
					std::cin.clear(); //오류스트림 초기화
					std::cin.ignore(INT_MAX, '\n'); //입력버퍼비우기
					continue;
				}
				else {
					//현재 메모리상에 로드된 데이터베이스 해제
					free_list(&head_vid, &head_person);
					//데이터베이스 로드를 위해 비디오,고객 헤드포인터를 NULL로 초기화
					head_vid = NULL;
					head_person = NULL;
					//데이터베이스 로드
					if (load_db(&head_vid, &head_person) == 1)
					{
						std::cout << "불러오기 성공" << std::endl;
						system("pause");
					}
					else
					{
						std::cout << "불러오기 실패" << std::endl;
						system("pause");
					}
					break;
				}
			}
			break;

		case 8: //저장하고 종료하기
			if (save_db(&head_vid, &head_person) == 1)
			{
				std::cout << "저장 성공" << std::endl;
			}
			else
			{
				std::cout << "저장 실패" << std::endl;
			}
			free_list(&head_vid, &head_person);
			exit(1);
		}

	}
}