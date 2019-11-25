#include "header.h"


//////////////////////////////////////////////
/**
	disp_screen option - �޴� ��� �Լ�
	0 - ���θ޴�
	1 - �˻�
	2 - �뿩 �Ǵ� �ݳ�
	3 - ���
	4 - �߰�
	5 - ����
	-----------------------
	6 - ����
	7 - �ҷ�����
	8 - ���� �� ����
	9 - �������� �ʰ� ����
	
	search_db option - �����ͺ��̽� �˻� ���� �Լ�(�˻�,�߰�,����,�뿩,�ݳ����� ���)
	0 - ���� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_vid �� ����)
	1 - �� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_person���� ����)
	2 - �ִ� �뿩 Ƚ���� �ѱ��� �ʴ� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_person���� ����)
	3 - ���� �뿩������ �ʴ� ������ �̸����� �˻� (���� �Ҵ��Ͽ� Dst_vid �� ����)
	4 - vid_num�� �ش��ϴ� ������ ���� DB�󿡼� ����� �ּҸ� ���� (Dst_vid �� ����)
	5 - person_num�� �ش��ϴ� ���� ���� DB�󿡼� ����� �ּҸ� ���� (Dst_person �� ����)

	search_info option - �˻� �Լ�
	0 - ���� ���� �̸����� �˻�
	1 - �� ���� �̸����� �˻�
	

	print_info option - ���� ��� �Լ�
	0 - ���� ���� ���
	1 - �� ���� ���
	2 - ���� ���� �뿩���� ���� ��� ���

	add_del_info option - ���� �߰�,���� �Լ�
	0 - ���� ���� �߰�
	1 - �� ���� �߰�
	2 - ���� ���� ����
	3 - �� ���� ����
	

	rental_return option - �뿩,�ݳ� �Լ�
	0 - ���� �뿩
	1 - ���� �ݳ�
	
**/
//////////////////////////////////////////////

void main()
{
	//_wsetlocale( LC_ALL, L"korean" ); //����ȭ ������ ���������� ����

	/*
	�Լ� ���ϰ�
	-1 : ����� ���� ���
	0 : ����
	1 : ����
	*/

	Video_Info *head_vid = NULL; //���� ������ ��� ������
	Person_Info *head_person = NULL; //�� ������ ��� ������

	Video_Info *search_vid_result = NULL; //�˻� ��� ����� ���� ����� ������ ����Ű�� ������
	Person_Info *search_person_result = NULL; //�˻� ��� ����� ���� ����� ������ ����Ű�� ������

	while (1)
	{
		int main_select = 0; //����ڷκ��� �޴������� �Է¹޴� ����
		int sub_select = 0; //���꿡���� ���� ������ �Է¹޴� ����
		disp_screen(0);

		std::cin >> main_select;

		if (main_select == 9) break;
		else if (main_select < 1 || main_select > 9)
			//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
		{
			std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
			std::cin.clear(); //������Ʈ�� �ʱ�ȭ
			std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
			Sleep(1000);
		}

		switch (main_select) //���θ޴��� ���� ����ġ��
		{
		case 1: //���� �Ǵ� �� ���� �˻�
			while (1) {
				disp_screen(1);
				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					Sleep(1000);
				}

				switch (sub_select) //����޴��� ���� ����ġ��
				{
				case 1: //���� ���� �˻� �� ���
					if (search_info(&head_vid, &head_person, 0))
						system("pause");
					else
					{
						std::cout << "�ش��ϴ� ���� ������ �����ϴ�." << std::endl;
						system("pause");
					}
					break;

				case 2: //�� ���� �˻� �� ���
					if (search_info(&head_vid, &head_person, 1))
						system("pause");
					else
					{
						std::cout << "�ش��ϴ� �� ������ �����ϴ�." << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 2: //���� �뿩 �� �ݳ�
			while (1) {
				disp_screen(2);
				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					Sleep(1000);
				}

				switch (sub_select) //����޴��� ���� ����ġ��
				{
				case 1: //���� �뿩
					if (rental_return(&head_vid, &head_person, 0) == 1)
					{
						std::cout << "�뿩�Ǿ����ϴ�." << std::endl;
						system("pause");
					}
					else system("pause");
					break;

				case 2: //���� �ݳ�
					if (rental_return(&head_vid, &head_person, 1) == 1)
					{
						std::cout << "�ݳ��Ǿ����ϴ�." << std::endl;
						system("pause");
					}
					else system("pause");
					break;
				}
				break;
			}
			break;

		case 3: //��ü ����, �� ���� ���
			while (1) {
				disp_screen(3);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					Sleep(1000);
				}

				switch (sub_select) //����޴��� ���� ����ġ��
				{
				case 1: //��ü ���� ���
					if (print_info(&head_vid, &head_person, 0) == 1)
						system("pause");
					else
					{
						std::cout << "����� ���� ������ �����ϴ�." << std::endl;
						system("pause");
					}
					break;

				case 2: //��ü �� ���� ���
					if (print_info(&head_vid, &head_person, 1) == 1)
						system("pause");
					else
					{
						std::cout << "����� �� ������ �����ϴ�." << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 4: //���� �Ǵ� �� ���� �߰�			
			while (1) {
				disp_screen(4);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					Sleep(1000);
				}

				switch (sub_select) //����޴��� ���� ����ġ��
				{
				case 1: //���� �߰�
					if (add_del_info(&head_vid, &head_person, 0) == 1)
					{
						std::cout << "�߰� ����" << std::endl;
						system("pause");
					}
					break;

				case 2: //�� �߰�
					if (add_del_info(&head_vid, &head_person, 1) == 1)
					{
						std::cout << "�߰� ����" << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 5: //���� �Ǵ� �� ���� ����
			while (1) {
				disp_screen(5);

				std::cin >> sub_select;

				if (sub_select == 3) break;
				else if (sub_select < 1 || sub_select > 3)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					Sleep(1000);
				}

				switch (sub_select) //����޴��� ���� ����ġ��
				{
				case 1: //���� ����
					if (add_del_info(&head_vid, &head_person, 2) == 1)
					{
						std::cout << "���� ����" << std::endl;
						system("pause");
					}
					break;

				case 2: //�� ����
					if (add_del_info(&head_vid, &head_person, 3) == 1)
					{
						std::cout << "���� ����" << std::endl;
						system("pause");
					}
					break;
				}
				break;
			}
			break;

		case 6: //�����ͺ��̽� ����
			if (save_db(&head_vid, &head_person) == 1)
			{
				std::cout << "���� ����" << std::endl;
				system("pause");
			}
			else
			{
				std::cout << "���� ����" << std::endl;
				system("pause");
			}
			break;

		case 7: //�����ͺ��̽� �ҷ�����
			while (1) {
				std::cout << "���� �۾����� ������ �������� �ֽ��ϴ�." << std::endl;
				std::cout << "��� : 1, ��� : -1" << std::endl;
				std::cout << ">>" << std::endl;
				std::cin >> sub_select;

				if (sub_select == -1) break;
				else if (sub_select != 1)
					//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
				{
					std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
					std::cin.clear(); //������Ʈ�� �ʱ�ȭ
					std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					continue;
				}
				else {
					//���� �޸𸮻� �ε�� �����ͺ��̽� ����
					free_list(&head_vid, &head_person);
					//�����ͺ��̽� �ε带 ���� ����,�� ��������͸� NULL�� �ʱ�ȭ
					head_vid = NULL;
					head_person = NULL;
					//�����ͺ��̽� �ε�
					if (load_db(&head_vid, &head_person) == 1)
					{
						std::cout << "�ҷ����� ����" << std::endl;
						system("pause");
					}
					else
					{
						std::cout << "�ҷ����� ����" << std::endl;
						system("pause");
					}
					break;
				}
			}
			break;

		case 8: //�����ϰ� �����ϱ�
			if (save_db(&head_vid, &head_person) == 1)
			{
				std::cout << "���� ����" << std::endl;
			}
			else
			{
				std::cout << "���� ����" << std::endl;
			}
			free_list(&head_vid, &head_person);
			exit(1);
		}

	}
}