#include "header.h"

int last_vid_num=1; //�ʱ� ���� num�� 1
int last_person_num=0; //�ʱ� �� num�� 0

void disp_screen(int option) //ȭ�� ��¿� �Լ�
{
	/* disp_screen option
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
	*/

	switch(option)
	{
	case 0: //���θ޴�
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "	���� �뿩 ���α׷�	"<<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� �Ǵ� �� ���� �˻�" <<std::endl;
	std::cout<< "(2) ���� �뿩 �� �ݳ�" <<std::endl;
	std::cout<< "(3) ��ü ����, �� ���� ���" <<std::endl;
	std::cout<< "(4) ���� �Ǵ� �� ���� �߰�" <<std::endl;
	std::cout<< "(5) ���� �Ǵ� �� ���� ����" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(6) ����" <<std::endl;
	std::cout<< "(7) �ҷ�����" <<std::endl;
	std::cout<< "(8) ���� �� ����" <<std::endl;
	std::cout<< "(9) �������� �ʰ� ����" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 1: //�˻�
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� ���� �˻�" <<std::endl;
	std::cout<< "(2) �� ���� �˻�" <<std::endl;
	std::cout<< "(3) �ڷΰ���" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 2: //�뿩 �Ǵ� �ݳ�
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� �뿩" <<std::endl;
	std::cout<< "(2) ���� �ݳ�" <<std::endl;
	std::cout<< "(3) �ڷΰ���" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 3: //���
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� ��ü ���" <<std::endl;
	std::cout<< "(2) �� ��ü ���" <<std::endl;
	std::cout<< "(3) �ڷΰ���" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 4: //�߰�
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� �߰�" <<std::endl;
	std::cout<< "(2) �� ���� �߰�" <<std::endl;
	std::cout<< "(3) �ڷΰ���" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;

	case 5: //����
	system("cls");
	std::cout<< "=================================" <<std::endl;
	std::cout<< "(1) ���� ����" <<std::endl;
	std::cout<< "(2) �� ���� ����" <<std::endl;
	std::cout<< "(3) �ڷΰ���" <<std::endl;
	std::cout<< "=================================" <<std::endl;
	std::cout<< ">>";
	break;
	}
}

const std::string get_time() { //���� �ð� ���ϴ� �Լ�
	time_t now = time(0); //����ð��� time_tŸ������ ����
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf,sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss ������ string

	return buf;
}

void free_list(Video_Info **head_vid, Person_Info **head_person) //�޸� ���� ��ȯ�Լ�
{
	//head_vid,head_person�� �ּҰ��� �޾Ƽ� ���������� �޸𸮰��� ��ȯ
	Video_Info *tmp_vid_indexer = NULL; //���� head_vid�� ���������� �ε����ϴ� ������
	Video_Info *del_vid = NULL; //tmp �ε����κ��� �ּҸ� �޾ƿ� �޸𸮸� �����ϱ����� ������
	Person_Info *tmp_person_indexer = NULL; //���� head_person�� ���������� �ε����ϴ� ������
	Person_Info *del_person = NULL; //tmp �ε����κ��� �ּҸ� �޾ƿ� �޸𸮸� �����ϱ����� ������
	
	tmp_vid_indexer = *head_vid;
	tmp_person_indexer = *head_person;

	while (tmp_vid_indexer != NULL)
	{	
		del_vid = tmp_vid_indexer;
		tmp_vid_indexer = tmp_vid_indexer->next; //�ε����� �̵���Ų �� ����
		delete(del_vid);
	}

	while (tmp_person_indexer != NULL)
	{
		del_person = tmp_person_indexer;
		tmp_person_indexer = tmp_person_indexer->next; //�ε����� �̵���Ų �� ����
		delete(del_person);
	}
}

int load_db(Video_Info **head_vid, Person_Info **head_person) //�����ͺ��̽� �ε� �Լ�
{
	/**
	���� ���� �۾� ����ÿ� vid_num �� person_num�� ���� ���������� ������ ���� �ʾ����Ƿ�
	���� ���� �뿩 ��Ͽ� ��ϵ� vid_num�� ���� �����Ϸ���
	vid_num,person_num�� ���� �����ͺ��̽��� �����ؾ� ���� �۾��� �Ͼ�� �ٽ� �ε������� ���ٰ���
	**/

	FILE *vid_load, *person_load, *last_count;

	int last_max_rental_count=0; //���������� ���� �ִ� �뿩 ���� �� �ӽ�����
	int fix_last_file = 0; //last.dat���� �ջ󿩺�
	int fix_last_vid_num = 1, fix_last_person_num = 0; //����,�� �����ͷκ��� ���� ū ���� ���

	if ((last_count = fopen("last.dat", "rt")) != NULL)
	{
			fscanf(last_count, "%d %d %d",&last_vid_num, &last_person_num, &last_max_rental_count); //���������� ����ߴ� vid_num,person_num,�ִ� �뿩 ���� �� �ε�
			last_vid_num++; last_person_num++; //���� �Ǵ� ���� ���� �Է��� ��� vid_num,person_num�� ���� �̴ϼȶ���¡�� ���� �ٷ� �Ҵ��ؾ��ϹǷ� ������Ŵ
			if (last_max_rental_count != MAX_RENTAL_COUNT) //�ִ� �뿩 ���� ���� ���������� ������ ���ϰ� �ٸ� ���
			{
				while (1)
				{
					int select = 0;
					std::cout << "��� : ���� �ִ� �뿩 ���� ���� ���������� ���� �ִ� �뿩 ���� ���� �ٸ��ϴ�." << std::endl; 
					std::cout << "���������� ���� �ִ� �뿩 ���� �� : " << last_max_rental_count << std::endl;
					std::cout << "���� �ִ� �뿩 ���� �� : " << MAX_RENTAL_COUNT << std::endl;
					std::cout << "�����Ͱ� �սǵ� �� �ֽ��ϴ�. ����Ͻðڽ��ϱ�?" << std::endl;
					std::cout << "��� : 1 , ��� : -1" << std::endl;
					std::cin >> select;

					if (select == -1) break;
					else if (select != 1)
						//�Է¹��� �ʰ� �Ǵ� �߸��� �����Է�
					{
						std::cout << "�޴��߿��� �����ϼ���!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}
					else break;
					//���� �ִ� �뿩 ���� ���� ���������� ���� �뿩 ���� ������ ũ�� ��ϵ� �뿩��� ������ ������ �ڵ������� 0���� ó��
					//���� �ִ� �뿩 ���� ���� ���������� ���� �뿩 ���� ������ ���� ��쿡�� ���� �ִ� �뿩 ���� �� ������ �����ͺ��̽��� �ε�
				}
			}
	}
	else //������ ����� ������ �ʾ��� ���
	{
		fprintf(stderr, "last.dat������ �ҷ��� �� �����ϴ�. ���� �ִ� �뿩 ���� ���� ���� ���� ���ٰ� �����մϴ�.");
		std::cout << std::endl;
		last_max_rental_count = MAX_RENTAL_COUNT; //���� �ִ� �뿩 ���� Ƚ���� ���� �ִ� �뿩 Ƚ���� ���ٰ� ����
		fix_last_file = 1;
	}

	if ((vid_load = fopen("vid_info.dat", "rt")) != NULL && (person_load = fopen("person_info.dat", "rt")) != NULL) //�б� + �ؽ�Ʈ ���� ���
	{
		//**** ���� �����ͺ��̽� �ε�
		Video_Info *new_vid = NULL;
		int tmp_vid_num = 1;

		while (!feof(vid_load)) //������ ������
		{
			new_vid = new Video_Info; //�����Ҵ�
			fscanf(vid_load, "%d %s %s %d",&tmp_vid_num, &new_vid->vid_name, &new_vid->vid_added_date, &new_vid->vid_rental); //���Ϸκ��� vid_num,�̸�,�߰���¥,�뿩������ �ҷ��� new_vid�� ���

			new_vid->set_vid_num(tmp_vid_num); //���� vid_num���� ����
				
			if (fix_last_file == 1 && fix_last_vid_num <= tmp_vid_num) //last.dat������ �ջ�� ���
				fix_last_vid_num = tmp_vid_num;

			if (*head_vid == NULL) //��������Ͱ� NULL�̸� ���ο� ��������� ����
			{ 
				*head_vid = new_vid;
			}
			else 
			{
				Video_Info *vid_indexer = *head_vid; //head_vid�� next��ũ�� ���� �ε����� vid_indexer ����
				while (vid_indexer->next != NULL) { //����� next��ũ�� ���� ������ �̵�
					vid_indexer = vid_indexer->next;
				}
				vid_indexer ->next = new_vid; //�� ����� next��ũ�� ���ο� ��带 ����Ű����
				new_vid->pre = vid_indexer; //�� ���� ���ο� ����� pre��ũ�� ����
			}
		}

		//**** �� �����ͺ��̽� �ε�
		Person_Info *new_person = NULL;
		int tmp_person_num = 0;
		char tmp_newline[MAX_CHAR_LENGTH]; //�ٹٲ� ���ڰ� ���ö����� �б����� ����ϴ� �ӽú���

		while (!feof(person_load)) //������ ������
		{
			new_person = new Person_Info; //�����Ҵ�
			
			fscanf(person_load, "%d %s %s",&tmp_person_num, &new_person->name, &new_person->phone_num); //���Ϸκ��� person_num,�̸�,��ȭ��ȣ�� �ҷ��� new_person�� ���
			new_person->set_person_num(tmp_person_num); //���� person_num���� ����

			if (fix_last_file == 1 && fix_last_person_num <= tmp_person_num) //last.dat������ �ջ�� ���
				fix_last_person_num = tmp_person_num;

			int i = 0;

			if (last_max_rental_count >= MAX_RENTAL_COUNT) //���� �ִ� �뿩 ���� ���� ���������� ���� �뿩 ���� ������ ���� ��� �Ǵ� ���� ��� ���� �ִ� �뿩 ���� �� ������ �����ͺ��̽��� �ε�
			{
				while (i < MAX_RENTAL_COUNT) //���Ϸκ��� �뿩����� �ҷ��� ���
				{
					fscanf(person_load, "%d", &new_person->rental_list[i]);
					i++;
				}
				fscanf(person_load, "%[^\n]s", &tmp_newline); //�ٹٲ޹��ڰ� ���ö����� �д´�
				fflush(stdin); //���۸� ���

				if (*head_person == NULL) //��������Ͱ� NULL�̸� ���ο� ��������� ����
				{
					*head_person = new_person;
				}
				else 
				{
					Person_Info *person_indexer = *head_person; //head_person�� next��ũ�� ���� �ε����� person_indexer ����
					while (person_indexer->next != NULL) //����� next��ũ�� ���� ������ �̵�
					{
						person_indexer = person_indexer->next;
					}
						person_indexer->next = new_person; //�� ����� next��ũ�� ���ο� ��带 ����Ű����
						new_person->pre = person_indexer; //�� ���� ���ο� ����� pre��ũ�� ����

				}
			}

			else //���� �ִ� �뿩 ���� ���� ���������� ���� �뿩 ���� ������ ũ�� ��ϵ� �뿩��� ������ ������ �ڵ������� 0���� ó��
			{
				while (i < last_max_rental_count) //���Ϸκ��� �뿩����� �ҷ��� ���
				{
					fscanf(person_load, "%d", &new_person->rental_list[i]);
					i++;
				}

				fscanf(person_load, "%[^\n]s", &tmp_newline); //�ٹٲ޹��ڰ� ���ö����� �д´�
				fflush(stdin); //���۸� ���

				if (*head_person == NULL) //��������Ͱ� NULL�̸� ���ο� ��������� ����
				{
					*head_person = new_person;
				}
				else 
				{
					Person_Info *person_indexer = *head_person; //head_person�� next��ũ�� ���� �ε����� person_indexer ����
					while (person_indexer->next != NULL) { //����� next��ũ�� ���� ������ �̵�
						person_indexer = person_indexer->next;
					}
						person_indexer->next = new_person; //�� ����� next��ũ�� ���ο� ��带 ����Ű����
						new_person->pre = person_indexer; //�� ���� ���ο� ����� pre��ũ�� ����

				}
			}
		}

		//last.dat������ �ջ�� ��� ����,�� �����κ��� ����
		if (fix_last_file == 1)
		{
			last_vid_num = fix_last_vid_num;
			last_person_num = fix_last_person_num;
			last_vid_num++; last_person_num++; //���� �Ǵ� ���� ���� �Է��� ��� vid_num,person_num�� ���� �̴ϼȶ���¡�� ���� �ٷ� �Ҵ��ؾ��ϹǷ� ������Ŵ
		}
	}
	else
	{
		fprintf(stderr, "����� �����ͺ��̽��� ���ų� �����ͺ��̽��� �б���� ���� �� ������ �߻��߽��ϴ�.");
		return 0;
	}
	fclose(vid_load);
	fclose(person_load);
	if(last_count != NULL)
		fclose(last_count);
	return 1;
}

int save_db(Video_Info **head_vid, Person_Info **head_person) //�����ͺ��̽� ���� �Լ�
{

	FILE *vid_save, *person_save, *last_count;

	if ((vid_save = fopen("vid_info.dat", "wt")) != NULL && (person_save = fopen("person_info.dat", "wt")) != NULL && (last_count = fopen("last.dat", "wt")) != NULL) //���� + �ؽ�Ʈ ���� ���
	{
		//**** ���� �����ͺ��̽� ����
		if (*head_vid != NULL)
		{
			Video_Info *vid_indexer = *head_vid; //head_vid�� next��ũ�� ���� �ε����� vid_indexer

			while (vid_indexer->next != NULL) //����� �� �ٷ� �� ������
			{
				fprintf(vid_save, "%d %s %s %d\n", vid_indexer->get_vid_num(), vid_indexer->vid_name, vid_indexer->vid_added_date, vid_indexer->vid_rental); //�ٹٲ��� �������� �߰��Ͽ� ���
				vid_indexer = vid_indexer->next;
			}
			//������ ��� ����(�� �ٲ��� ����)
			fprintf(vid_save, "%d %s %s %d", vid_indexer->get_vid_num(), vid_indexer->vid_name, vid_indexer->vid_added_date, vid_indexer->vid_rental);
		}

		//**** �� �����ͺ��̽� ����
		if (*head_person != NULL)
		{
			Person_Info *person_indexer = *head_person; //head_person�� next��ũ�� ���� �ε����� person_indexer
			while (person_indexer->next != NULL) //����� �� �ٷ� �� ������
			{
				fprintf(person_save, "%d %s %s", person_indexer->get_person_num(), person_indexer->name, person_indexer->phone_num);
				fprintf(person_save, " "); //�����͸� �����ϱ� ���� ���� ����

				int i = 0;
				while (i < MAX_RENTAL_COUNT - 1) //���� �뿩 ��� ���
				{
					fprintf(person_save, "%d ", person_indexer->rental_list[i]);
					i++;
				}
				fprintf(person_save, "%d\n", person_indexer->rental_list[i]); //������ ������ ��� �� �ٹٲ�

				person_indexer = person_indexer->next;
			}

			//������ ��� ����
			fprintf(person_save, "%d %s %s", person_indexer->get_person_num(), person_indexer->name, person_indexer->phone_num);
			fprintf(person_save, " "); //�����͸� �����ϱ� ���� ���� ����

			int i = 0;
			while (i < MAX_RENTAL_COUNT - 1)
			{
				fprintf(person_save, "%d ", person_indexer->rental_list[i]);
				i++;
			}
			fprintf(person_save, "%d", person_indexer->rental_list[i]); //������ ������ ���
		}

		//**** last.dat ���� ���
		fprintf(last_count, "%d %d %d", last_vid_num,last_person_num, MAX_RENTAL_COUNT); //���������� ����� vid_num,person_num,�ִ� �뿩 ���� �� ����
	}
	else
	{
		fprintf(stderr, "�����ͺ��̽��� ������� ���� �� ������ �߻��߽��ϴ�.");
		return 0;
	}
	fclose(vid_save);
	fclose(person_save);
	fclose(last_count);
	return 1;
}

int search_db(Video_Info **head_vid,Person_Info **head_person,Video_Info **Dst_vid,Person_Info **Dst_person,const char name[],int option) //�����ͺ��̽� �˻� ���� �Լ�(�˻�, �߰�, ����, �뿩, �ݳ����� ���)
{
	/* search_db option
	0 - ���� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_vid �� ����)
	1 - �� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_person���� ����)
	2 - �ִ� �뿩 Ƚ���� �ѱ��� �ʴ� ���� �̸����� �˻� (���� �Ҵ��Ͽ� Dst_person���� ����)
	���� �ؾ� �� 3 - ���� �뿩���� ������ �̸����� �˻� (���� �Ҵ��Ͽ� Dst_vid �� ����)
	3 - ���� �뿩������ �ʴ� ������ �̸����� �˻� (���� �Ҵ��Ͽ� Dst_vid �� ����)
	4 - vid_num�� �ش��ϴ� ������ ���� DB�󿡼� ����� �ּҸ� ���� (Dst_vid �� ����)
	5 - person_num�� �ش��ϴ� ���� ���� DB�󿡼� ����� �ּҸ� ���� (Dst_person �� ����)
	*/

	//*head_vid �Ǵ� *head_person�� �ּҰ��� �޾Ƽ�
	//�˻� ������ *Dst_vid �Ǵ� *Dst_person ���� �ּҰ��� ����
	//�˻������ �Ҵ�� ������ ȣ���� ������ free_list�� �޸𸮸� �����Ѵ�
	//string�� char������ �ٲٴ� c_Str()�Լ��� const char*�� �����ϹǷ� search_db �μ��� const char������ �޾ƾ���

	Video_Info *search_vid_result = NULL; //�˻� ����� �����Ҵ� �޾� �����ϱ� ���� ������
	Video_Info *head_search_vid_result = NULL; //����� �˻������ �� ó���� ����Ű�� ���������
	Video_Info *vid_indexer = NULL; //���� DB �ε���

	Person_Info *search_person_result = NULL; //�˻� ����� �����Ҵ� �޾� �����ϱ� ���� ������
	Person_Info *head_search_person_result = NULL; //����� �˻������ �� ó���� ����Ű�� ���������
	Person_Info *person_indexer = NULL; //���� DB �ε���

	int choice_num; //vid_num �Ǵ� person_num�� char[]������ ��ȯ �޾Ƽ� �μ��� ���� �� int�� ��ȯ�ϱ� ���� ����

	//�˻��� ����� Dst_vid �Ǵ� Dst_person�� ����
	switch (option)
	{
	case 0: //���� ���� �˻�
		if (*head_vid != NULL) //����� ������ ��������
		{ 
			vid_indexer = *head_vid; //���� DB �ε���
			//head_vid�� next��ũ�� ���� �˻� �� �̸��� ��ġ�ϸ�
			//search_vid_result�� �߰�

			if (vid_indexer->next == NULL) //���� DB�� ����� ������ 1������ ���
			{
				if (strcmp(name, vid_indexer->vid_name) == 0)
				{
					search_vid_result = new Video_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
					memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����
					*Dst_vid = search_vid_result; //�˻��� ����� ����� ������ �ּҰ��� ����
				}
				return 1;
			}

			while (vid_indexer != NULL) //����� ������
			{
				if (strcmp(name, vid_indexer->vid_name) == 0)
				{
					if (head_search_vid_result == NULL) //�� ó�� �˻������ ���ؼ� �����Ҵ��ϰ� �˻������ ��������� ����
					{
						search_vid_result = new Video_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����

						//�˻������ next,pre��ũ ����
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;

						head_search_vid_result = search_vid_result; //��������� ����
					}
					else //�� ó�� �˻������ �ƴ� ��� �˻������ next��ũ�� ����Ű�� ���� �����Ҵ� �� �̵� �� ���� ����
					{
						search_vid_result->next = new Video_Info; //�˻� ����� �����ϱ����� next�� ����Ű�� ���� �����Ҵ�
						search_vid_result = search_vid_result->next; //search_vid_result�� next���� �̵�
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����
						//�˻������ next,pre��ũ ����
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;
					}
				}

				vid_indexer = vid_indexer->next;
			}
			*Dst_vid = head_search_vid_result; //�˻��� ����� ����� ������ ��������͸� ����
			return 1;
		}
		return 0;

	case 1: //�� ���� �˻�
		if (*head_person != NULL) //����� ������ ��������
		{ 
			person_indexer = *head_person; //���� DB �ε���
			//head_person�� next��ũ�� ���� �˻� �� �̸��� ��ġ�ϸ�
			//search_person_result�� �߰�
			if (person_indexer->next == NULL) //���� DB�� ����� ������ 1������ ���
			{
				if (strcmp(name, person_indexer->name) == 0)
				{
					search_person_result = new Person_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
					memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
					*Dst_person = search_person_result; //�˻��� ����� ����� ������ �ּҰ��� ����
				}
				return 1;
			}

			while (person_indexer != NULL) //����� ������
			{
				if (strcmp(name, person_indexer->name) == 0)
				{
					if (head_search_person_result == NULL) //�� ó�� �˻� ����� ���ؼ� �����Ҵ� �� �˻������ ��������� ����
					{
						search_person_result = new Person_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
						//�˻������ next,pre��ũ ����
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
						
						head_search_person_result = search_person_result; //��������� ����
					}
					else //�� ó�� �˻������ �ƴ� ��� �˻������ next��ũ�� ����Ű�� ���� �����Ҵ� �� �̵� �� ���� ����
					{
						search_person_result->next = new Person_Info; //�˻� ����� �����ϱ����� next�� ����Ű�� ���� �����Ҵ�
						search_person_result = search_person_result->next; //search_person_result�� next���� �̵�
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
						//�˻������ next,pre��ũ ����
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
					}
				}

				person_indexer = person_indexer->next;
			}

			*Dst_person = head_search_person_result; //�˻��� ����� ����� ������ ��������͸� ����
			return 1;
		}
		return 0;

	case 2: //�ִ� �뿩 Ƚ���� �ѱ��� �ʴ� ���� �̸����� �˻�
		if(*head_person != NULL) //����� ������ ��������
		{
			person_indexer = *head_person; //���� DB �ε���
			//head_person�� next��ũ�� ���� �˻� �� �̸��� ��ġ�� rental_list[MAX_RENTAL_COUNT - 1]�� 0���� ���� Ȯ��
			//search_person_result�� �߰�
			if (person_indexer->next == NULL) //���� DB�� ����� ������ 1������ ���
			{
				if (strcmp(name, person_indexer->name) == 0 && person_indexer->rental_list[MAX_RENTAL_COUNT - 1] == 0)
				{
					search_person_result = new Person_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
					memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
					*Dst_person = search_person_result; //�˻��� ����� ����� ������ �ּҰ��� ����
				}
				return 1;
			}

			while (person_indexer != NULL) //����� ������
			{
				if (strcmp(name, person_indexer->name) == 0 && person_indexer->rental_list[MAX_RENTAL_COUNT - 1] == 0)
				{
					if (head_search_person_result == NULL) //�� ó�� �˻� ����� ���ؼ� �����Ҵ� �� �˻������ ��������� ����
					{
						search_person_result = new Person_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
						//�˻������ next,pre��ũ ����
						search_person_result->next = NULL;
						search_person_result->pre = NULL;

						head_search_person_result = search_person_result; //��������� ����
					}
					else //�� ó�� �˻������ �ƴ� ��� �˻������ next��ũ�� ����Ű�� ���� �����Ҵ� �� �̵� �� ���� ����
					{
						search_person_result->next = new Person_Info; //�˻� ����� �����ϱ����� next�� ����Ű�� ���� �����Ҵ�
						search_person_result = search_person_result->next; //search_person_result�� next���� �̵�
						memcpy(search_person_result, person_indexer, sizeof(Person_Info)); //���� ����
						 //�˻������ next,pre��ũ ����
						search_person_result->next = NULL;
						search_person_result->pre = NULL;
					}
				}
				person_indexer = person_indexer->next;
			}

			*Dst_person = head_search_person_result; //�˻��� ����� ����� ������ ��������͸� ����
			return 1;
		}
		return 0;
	
	case 3: //���� �뿩������ �ʴ� ������ �̸����� �˻�
		if(*head_vid != NULL) //����� ������ ��������
		{
			vid_indexer = *head_vid; //���� DB �ε���
			//head_vid�� next��ũ�� ���� �˻� �� �̸��� ��ġ,�뿩������ ���� ������
			//search_vid_result�� �߰�

			if (vid_indexer->next == NULL) //���� DB�� ����� ������ 1������ ���
			{
				if (strcmp(name, vid_indexer->vid_name) == 0 && vid_indexer->vid_rental == 0)
				{
					search_vid_result = new Video_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
					memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����
					*Dst_vid = search_vid_result; //�˻��� ����� ����� ������ �ּҰ��� ����
				}
				return 1;
			}

			while (vid_indexer != NULL) //����� ������
			{
				if (strcmp(name, vid_indexer->vid_name) == 0 && vid_indexer->vid_rental == 0)
				{
					if (head_search_vid_result == NULL) //�� ó�� �˻������ ���ؼ� �����Ҵ��ϰ� �˻������ ��������� ����
					{
						search_vid_result = new Video_Info; //�˻� ����� �����ϱ� ���� �����Ҵ�
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����

						//�˻������ next,pre��ũ ����
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;

						head_search_vid_result = search_vid_result; //��������� ����
					}
					else //�� ó�� �˻������ �ƴ� ��� �˻������ next��ũ�� ����Ű�� ���� �����Ҵ� �� �̵� �� ���� ����
					{
						search_vid_result->next = new Video_Info; //�˻� ����� �����ϱ����� next�� ����Ű�� ���� �����Ҵ�
						search_vid_result = search_vid_result->next; //search_vid_result�� next���� �̵�
						memcpy(search_vid_result, vid_indexer, sizeof(Video_Info)); //���� ����
						//�˻������ next,pre��ũ ����
						search_vid_result->next = NULL;
						search_vid_result->pre = NULL;
					}
				}

				vid_indexer = vid_indexer->next;
			}

			*Dst_vid = head_search_vid_result; //�˻��� ����� ����� ������ ��������͸� ����
			return 1;
		}
		return 0;
		
	case 4: // vid_num�� �ش��ϴ� ������ ���� DB�󿡼� ����� �ּҸ� ����
 		if (*head_vid != NULL) //����� ������ ��������
		{
			choice_num = atoi(name); //����ڷκ��� ���� char�� vid_num�� ������ ��ȯ

			vid_indexer = *head_vid; //���� DB �ε���
			//head_vid�� next��ũ�� ���� �˻� �� vid_num�� ��ġ�ϸ� ����
			while (vid_indexer != NULL)
			{
				if (vid_indexer->get_vid_num() == choice_num)
				{
					*Dst_vid = vid_indexer; //vid_num�� ��ġ�� ��� ���� DB���� �ش���ġ�� ����
					return 1;
				}
				vid_indexer = vid_indexer->next;
			}
			return 0;
										
		}
		return 0;
	
	case 5: // person_num�� �ش��ϴ� ���� ���� DB�󿡼� ����� �ּҸ� ����
		if (*head_person != NULL) //����� ������ ��������
		{
			choice_num = atoi(name); //����ڷκ��� ���� char�� person_num�� ������ ��ȯ

			person_indexer = *head_person; //���� DB �ε���
			//head_person�� next��ũ�� ���� �˻� �� vid_num�� ��ġ�ϸ� ����
			while (person_indexer != NULL)
			{
				if (person_indexer->get_person_num() == choice_num)
				{
					*Dst_person = person_indexer; //person_num�� ��ġ�� ��� ���� DB���� �ش���ġ�� ����
					return 1;
				}
				person_indexer = person_indexer->next;
			}
		}
		return 0;

	}
	return 0;
}

int search_info(Video_Info **head_vid, Person_Info **head_person, int option) //�˻� �� ��� �Լ�
{
	/*
	search_info option
	0 - ���� ���� �˻�
	1 - �� ���� �˻�
	*/
	
	//*head_vid,*head_person�� �ּҰ��� �޾ƿͼ� �˻�
	Video_Info *search_vid_result = NULL;
	Person_Info *search_person_result = NULL;

	std::string tmp_name;

	switch (option)
	{
	case 0: //���� ���� �˻�
		while (1)
		{
			std::cout << "�˻��ϰ��� �ϴ� ������ �̸��� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
			}
			else break;
		}
		if (tmp_name.compare("-1") == 0) return -1;
		if (search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 0) == 0) return 0; //�˻� ����
		if (print_info(&search_vid_result, &search_person_result, 0) == 0) return 0; //���
		break;

	case 1: //�� ���� �˻�
		while (1)
		{
			std::cout << "�˻��ϰ��� �ϴ� ���� �̸��� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
			}
			else break;
		}
		if (tmp_name.compare("-1") == 0) return -1;
		if (search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 1) == 0) return 0; //�˻� ����
		if (print_info(&search_vid_result, &search_person_result, 1) == 0) return 0; //���
		break;
	}

	free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸� ���� ����
	return 1;
}

int print_info(Video_Info **head_vid,Person_Info **head_person,int option) //��� �Լ�
{
	/* print_info option
	0 - ���� ���� ���
	1 - �� ���� ���
	2 - ���� ���� �뿩���� ���� ��� ���
	*/

	//��������͸� �ջ��Ű�� �ʰ� Ž���ϱ� ���� �ε���
	Video_Info *vid_indexer = NULL;
	Person_Info *person_indexer = NULL;

	switch(option)
	{
	case 0: //���� ���� ���
		if (*head_vid != NULL) { //����� ������ ��������
			vid_indexer = *head_vid; //���� DB �ε���
			while (vid_indexer != NULL)
			{
				std::cout << "=================================" << std::endl;
				std::cout << "���� �̸� : " << vid_indexer->vid_name << std::endl;
				std::cout << "���� �߰� ��¥ : " << vid_indexer->vid_added_date << std::endl;
				std::cout << "���� �뿩 ���� : ";
				if (vid_indexer->vid_rental == 0) std::cout << "�뿩���� ����" << std::endl;
				else std::cout << "�뿩��" << std::endl;
				std::cout << "VID_NUM : " << vid_indexer->get_vid_num() << std::endl;
				std::cout << "=================================" << std::endl;
				vid_indexer = vid_indexer-> next;
			}
			return 1;
		}
		else return 0;

	case 1: //����� ���� ���
		if (*head_person != NULL) { //����� ������ ��������
			person_indexer = *head_person; //���� DB �ε���
			vid_indexer = *head_vid; //���� DB �ε���
			while (1)
			{
				std::cout << "=================================" << std::endl;
				std::cout << "�� �̸� : " << person_indexer->name << std::endl;
				std::cout << "��ȭ��ȣ : " << person_indexer->phone_num << std::endl;
				std::cout << "�뿩�� ���� ��� : ";
				if (person_indexer->rental_list[0] == 0) std::cout << "�뿩�� ������ �����ϴ�.";
				else 
				{
					for (int i = 0; i < MAX_RENTAL_COUNT; i++)
					{
						vid_indexer = *head_vid; //���� DB �ε���

						while (1) //���� DB�󿡼� �ش��ϴ� ������ �̸��� ã�Ƽ� ���
						{	
							if(vid_indexer->get_vid_num() == person_indexer->rental_list[i]) //���� vid_num�� �뿩�� ���� ����� vid_num�� ��ġ�ϸ� ���
								std::cout << vid_indexer->vid_name<<" ";
							vid_indexer = vid_indexer->next; //�̵�
							if (vid_indexer == NULL) break;
						}
					}
				}
				std::cout << std::endl;
				std::cout << "PERSON_NUM : " << person_indexer->get_person_num() << std::endl;
				std::cout << "=================================" << std::endl;
				person_indexer = person_indexer->next; //�̵�
				if (person_indexer == NULL) break; //�̵��ߴµ� NULL�ϰ�� ����
			}
			return 1;
		}
		else return 0;

	case 2: //���� ���� �뿩���� ���� ��� ���
		if (*head_person != NULL && *head_vid != NULL) //����� ������ ��������
		{
			vid_indexer = *head_vid; //���� DB �ε���
			person_indexer = *head_person; //����ڷκ��� ���� ���� �� ����

			while (1)
			{
				for (int i = 0; i < MAX_RENTAL_COUNT; i++) //���� �뿩���� ���� ��Ͽ� ���� �ݺ�
				{
					if (person_indexer->rental_list[i] == vid_indexer->get_vid_num()) //���� �뿩�� ������ ������� ���
					{
						std::cout << "=================================" << std::endl;
						std::cout << "���� �̸� : " << vid_indexer->vid_name << std::endl;
						std::cout << "���� �߰� ��¥ : " << vid_indexer->vid_added_date << std::endl;
						std::cout << "���� �뿩 ���� : ";
						if (vid_indexer->vid_rental == 0) std::cout << "�뿩���� ����" << std::endl;
						else std::cout << "�뿩��" << std::endl;
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
int add_del_info(Video_Info **head_vid,Person_Info **head_person,int option) //�߰�,���� �Լ�
{
	/* add_del_info option
	0 - ���� ���� �߰�
	1 - �� ���� �߰�
	2 - ���� ���� ����
	3 - �� ���� ����
	*/

	//���� �߰��ÿ� ���� DB�󿡼� �̸��� ���������� �����Ͽ� �߰�
	//���� �����ÿ� �� �ڳ���� next,pre���� �� free
	//�̹� �뿩���� ���� �� ������ �뿩���� ���� �����Ұ�

	
	Video_Info *new_vid = NULL; //���� ������ ����� ������ ����Ŵ
	Video_Info *tmp_head_vid = NULL; //�������� ���� ���� DB�� ��� �ӽ�����
	Video_Info *search_vid_result = NULL; //�˻� ����� ����Ŵ
	Video_Info *search_vid_result_indexer = NULL; //�˻� ����� �޸� ������ ���� ��������͸� �ǵ帮�� �ʰ� �ε����ϱ� ���� ������

	Person_Info *new_person = NULL; //���� ������ ����� ������ ����Ŵ
	Person_Info *tmp_head_person = NULL; //�������� ���� ���� DB�� ��� �ӽ�����
	Person_Info *search_person_result = NULL; //�˻� ����� ����Ŵ
	Person_Info *search_person_result_indexer = NULL; //�˻� ����� �޸� ������ ���� ��������͸� �ǵ帮�� �ʰ� �ε����ϱ� ���� ������

	//string�� length��� ���̰˻�
	std::string tmp_name;
	std::string tmp_phone_num;

	int choice; //����ڷκ��� ���ð�
	char choice_buffer[MAX_NUM_LENGTH] = { 0 }; //����ڷκ��� ���ð��� ���ڷ� ��ȯ�Ͽ� �˻��� �μ��� �ֱ����� ����

	Video_Info *choiced_vid = NULL; //����ڰ� ������ ���� ���� �ּ� �ӽ�����
	Person_Info *choiced_person = NULL; //����ڰ� ������ �� ���� �ּ� �ӽ�����

	switch(option)
	{
	case 0: //���� ���� �߰�
		new_vid = new Video_Info; //���� �߰��� ����� ���� �Ҵ�

		while (1)
		{
			std::cout << "�߰��ϰ��� �ϴ� ������ �̸��� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
			std::cin >> tmp_name;

			if (tmp_name.compare("-1") == 0)
			{
				delete new_vid; //���� �߰��� ���� �Ҵ��� ���� ����
				return -1;
			}

			if (tmp_name.length() > MAX_CHAR_LENGTH)
			{
				std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�� �Ǵ� " << "����: " << MAX_NUM_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
			}

			else
				break;
		}
		new_vid->init_num_count(); //vid_num�� ���� �̴ϼȶ���¡
		strcpy(new_vid->vid_name, tmp_name.c_str()); //string ���ڿ��� const char������ �ٲپ� �Է�
		strcpy(new_vid->vid_added_date, get_time().c_str());  //�ý������κ��� ���� �ð��� �˾Ƴ��� ���� �߰� ��¥ �Է�
		
		//��尡 �����ϴ� ��� �̸��� ���������� �տ� ���� ����
		if (*head_vid != NULL) //��尡 �����Ұ��
		{
			tmp_head_vid = *head_vid; //���� ��� �ӽ�����
			
			while(1) //����� ������ ����
			{ 
				//strcmp(A,B) < 0 (����) A < B
				//strcmp(B,A) > 0 (���) 
				if (strcmp(new_vid->vid_name, (*head_vid)->vid_name) < 0) //�տ� ���ڿ��� ���������� ��������
				{
					//new_vid�� head_vid�� �տ� ����
					new_vid->next = *head_vid;
					if ((*head_vid)->pre != NULL) //���� ����� ������尡 �����ϸ�
					{
						new_vid->pre = (*head_vid)->pre;
						(*head_vid)->pre->next = new_vid;
					}
					(*head_vid)->pre = new_vid;
					
					if (new_vid->pre == NULL) //new_vid�� ���Ե� ��ġ�� �� ó���� ���
						*head_vid = new_vid; //��������͸� ���ο� ���� ����
					else //new_vid�� �߰��� ���Ե� ���
						*head_vid = tmp_head_vid; //��������͸� ���� ���� �ٽ� ����
					break;
				}
				if ((*head_vid)->next != NULL)
					*head_vid = (*head_vid)->next;
				else break;
			}
			//��� ������ ���Ͽ� ������ ���� ���� ��� �� �ڿ� ����
			if (new_vid->next == NULL && new_vid->pre == NULL)
			{
				new_vid->pre = *head_vid;
				(*head_vid)->next = new_vid;
				*head_vid = tmp_head_vid; //��������͸� ���� ���� �ٽ� ����
			}
		}
		//��尡 �������� �ʴ°��
		else *head_vid = new_vid; //��������Ͱ� new_vid�� ����Ű�� ��

		break;

	case 1: //�� ���� �߰�
		new_person = new Person_Info; //���� �߰��� ����� ���� �Ҵ�

		while (1)
		{
			std::cout << "�߰��ϰ��� �ϴ� ���� ����(�̸�, ��ȭ��ȣ)�� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
			std::cin >> tmp_name>>tmp_phone_num;

			if (tmp_name.compare("-1") == 0 || tmp_phone_num.compare("-1") == 0)
			{
				delete new_person; //���� �߰��� ���� �Ҵ��� ���� ����
				return -1;
			}
			if (tmp_name.length() > MAX_CHAR_LENGTH || tmp_phone_num.length() > MAX_NUM_LENGTH)
			{
				std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�� �Ǵ� " << "����: " << MAX_NUM_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
			}
			else
			{
				strcpy(new_person->name, tmp_name.c_str()); //string ���ڿ��� char*������ �ٲپ� �Է�
				strcpy(new_person->phone_num, tmp_phone_num.c_str());
			}
				break;
		}

		new_person->init_num_count(); //person_num�� ���� �̴ϼȶ���¡
		if (*head_person != NULL) //��尡 �����Ұ��
		{
			tmp_head_person = *head_person; //���� ��� �ӽ�����

			while (1) //����� ������ ����
			{
				//strcmp(A,B) < 0 (����) A < B
				//strcmp(B,A) > 0 (���) 
				if (strcmp(new_person->name, (*head_person)->name) < 0) //�տ� ���ڿ��� ���������� ��������
				{
					//new_person�� head_person�� �տ� ����
					new_person->next = *head_person;
					if ((*head_person)->pre != NULL) //���� ����� ������尡 �����ϸ�
					{
						new_person->pre = (*head_person)->pre;
						(*head_person)->pre->next = new_person;
					}
					(*head_person)->pre = new_person;

					if (new_person->pre == NULL) //new_person�� ���Ե� ��ġ�� �� ó���� ���
						*head_person = new_person; //��������͸� ���ο� ���� ����
					else //new_person�� �߰��� ���Ե� ���
						*head_person = tmp_head_person; //��������͸� ���� ���� �ٽ� ����
					break;
				}
				if ((*head_person)->next != NULL)
					*head_person = (*head_person)->next;
				else break;
			}
			//��� ������ ���Ͽ� ������ ���� ���� ��� �� �ڿ� ����
			if (new_person->next == NULL && new_person->pre == NULL)
			{
				new_person->pre = *head_person;
				(*head_person)->next = new_person;
				*head_person = tmp_head_person; //��������͸� ���� ���� �ٽ� ����
			}
		}
		//��尡 �������� �ʴ°��
		else *head_person = new_person; //��������Ͱ� new_person�� ����Ű�� ��
		break;

	case 2: //���� ���� ����
		
		if (*head_vid != NULL) { //��尡 ������ ��쿡��
			while (1)
			{
				std::cout << "�����ϰ��� �ϴ� ������ �̸��� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_name;

				if (tmp_name.compare("-1") == 0)
					return -1;
				if (tmp_name.length() > MAX_CHAR_LENGTH)
					std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
				break;
			}

			//�˻��Ͽ� �����̸� ��� ���
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 0); //���� �˻�
			if (search_vid_result != NULL) //�˻� ����� �����ϸ� ��� ���
			{
				search_vid_result_indexer = search_vid_result; //�ε����� �˻������ ��带 ����Ű����
				print_info(&search_vid_result, &search_person_result, 0);

				while (1) {
					std::cout << "������ ������ VID_NUM�� �Է��ϼ���. �뿩���� ������ ���� �� �� �����ϴ�." << std::endl;
					std::cout << "��� : -1 �Է�" << std::endl;
					std::cout << ">>";
					std::cin >> choice;
					if (choice == -1) return -1;

					if(choice < 1 || choice >last_vid_num) //�߸��� ���� �Ǵ� �Է¹����� �ʰ��� ���
					{
						std::cout << "���ڸ� �Է� �����մϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}

					while (search_vid_result_indexer != NULL)  //�ùٸ��� �����Ͽ����� �˻�
					{
						if (choice == search_vid_result_indexer->get_vid_num() && search_vid_result_indexer->vid_rental == 0) //�˻������ ���ϴ� vid_num�� �°� �Է��Ͽ�����, �ش� ������ �뿩�������� �˻�
						{
							itoa(choice, choice_buffer, 10); //����ڰ� �Է��� vid_num���� ���������� ��ȯ
							//����ڰ� ������ vid_num���� ���� DB���� �ش� ������ ã�� choiced_vid�� ����Ű����
							search_db(head_vid, head_person, &choiced_vid, &search_person_result,choice_buffer, 4);
							break;
						}
						search_vid_result_indexer = search_vid_result_indexer->next;
					}

					if (choiced_vid == NULL)
					{
						//������ ��ȣ�� ����߿��� ���õ����ʾ��� ���
						std::cout << "�뿩���� ������ �����Ͽ��ų� ��Ͽ��� �������� �ʾҽ��ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					}
					else break;
				}
			}
			else
			{
				std::cout << "�ش��ϴ� ������ �������� �ʽ��ϴ�." << std::endl;
				free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
				return 0;
			}

			//�����Ϸ��� ��尡 ����������� ��� ��������͸� �����Ѵ�
			if (*head_vid == choiced_vid)
				*head_vid = (*head_vid)->next;

			if(choiced_vid->pre != NULL) //�����Ϸ��� ����� ������尡 ���� ��쿡��
				choiced_vid->pre->next = choiced_vid->next; //�����Ϸ��� ����� ��������� next��ũ�� �����Ϸ��� ����� ������带 ����Ű����
			if(choiced_vid->next != NULL) //�����Ϸ��� ����� ������尡 ���� ��쿡��
				choiced_vid->next->pre = choiced_vid->pre; //�����Ϸ��� ����� ��������� pre��ũ�� �����Ϸ��� ����� ������带 ����Ű����
			delete(choiced_vid);
			free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
			break;
		}
		else return 0;
		break;

	case 3: //�� ���� ����
		if (*head_person != NULL) { //��尡 ������ ��쿡��
			while (1)
			{
				std::cout << "�����ϰ��� �ϴ� ���� �̸��� �Է��ϼ���. ��� : -1 �Է�" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_name;

				if (tmp_name.compare("-1") == 0)
					return -1;
				if (tmp_name.length() > MAX_CHAR_LENGTH)
					std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
				break;
			}

			//�˻��Ͽ� �����̸� ��� ���
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_name.c_str(), 1); //�˻� ����
			if (search_person_result != NULL) //�˻� ����� �����ϸ� ��� ���
			{
				search_person_result_indexer = search_person_result; //�ε����� �˻������ ��带 ����Ű����
				print_info(head_vid, &search_person_result, 1);

				while (1) {
					std::cout << "������ ���� PERSON_NUM�� �Է��ϼ���. �뿩���� ���� ���� �� �� �����ϴ�." << std::endl;
					std::cout << "��� : -1 �Է�" << std::endl;
					std::cout << ">>";
					std::cin >> choice;
					if (choice == -1) return -1;

					if(choice < 0 || choice > last_person_num) //�߸��� ���� �Ǵ� �Է¹����� �ʰ��� ���
					{
						std::cout << "���ڸ� �Է� �����մϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}

					while (search_person_result_indexer != NULL)  //�ùٸ��� �����Ͽ����� �˻�
					{

						if (choice == search_person_result_indexer->get_person_num() && search_person_result_indexer->rental_list[0] == 0) //�˻������ ���ϴ� person_num�� �°� �Է��Ͽ�����, �˻������ ���� �뿩���� ������ �ִ��� �˻�
						{
							itoa(choice, choice_buffer, 10); //����ڰ� �Է��� person_num���� ���������� ��ȯ
							//����ڰ� ������ person_num���� ���� DB���� �ش� ���� ã�� choiced_person�� ����Ű����
							search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5);
							break;
						}
						search_person_result_indexer = search_person_result_indexer->next;
					}

					if (choiced_person == NULL)
					{
						//������ ��ȣ�� ����߿��� ���õ����ʾ��� ���
						std::cout << "�뿩���� ���� �����Ͽ��ų� ��Ͽ��� �������� �ʾҽ��ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					}

					else break;
				}
			}
			else
			{
				std::cout << "�ش��ϴ� ���� �������� �ʽ��ϴ�." << std::endl;
				free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
				return 0;
			}

			//�����Ϸ��� ��尡 ����������� ��� ��������͸� �����Ѵ�
			if (*head_person == choiced_person)
				*head_person = (*head_person)->next;

			if (choiced_person->pre != NULL) //�����Ϸ��� ����� ������尡 ���� ��쿡��
				choiced_person->pre->next = choiced_person->next; //�����Ϸ��� ����� ��������� next��ũ�� �����Ϸ��� ����� ������带 ����Ű����
			if (choiced_person->next != NULL) //�����Ϸ��� ����� ������尡 ���� ��쿡��
				choiced_person->next->pre = choiced_person->pre; //�����Ϸ��� ����� ��������� pre��ũ�� �����Ϸ��� ����� ������带 ����Ű����
			delete(choiced_person);
			free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
			break;
		}
		else return 0;
		break;
	}

	return 1;
}


int rental_return(Video_Info **head_vid,Person_Info **head_person,int option) //�뿩,�ݳ� �Լ�
{
	/* rental_return option
	0 - ���� �뿩
	1 - ���� �ݳ�
	*/

	//�뿩�ÿ� ������ vid_rental �� ����, ���� rental_list[]�� ������� �߰�
	//�뿩 �ѵ��� �ѱ� ���� �뿩�Ұ���
	//�ݳ��ÿ� ������ vid_rental �� ����, ���� rental_list[]���� ���� �� ����
	//�ߺ��� ������ ������� ���ù���

	Video_Info *search_vid_result = NULL; //�˻� ����� ����Ű�� ������
	Person_Info *search_person_result = NULL; //�˻� ����� ����Ű�� ������
	Video_Info *search_vid_result_indexer = NULL; //�˻� ����� �޸� ������ ���� ��������͸� �ǵ帮�� �ʰ� �ε����ϱ� ���� ������
	Person_Info *search_person_result_indexer = NULL; //�˻� ����� �޸� ������ ���� ��������͸� �ǵ帮�� �ʰ� �ε����ϱ� ���� ������

	//string�� length��� ���̰˻�
	std::string tmp_person_name;
	std::string tmp_vid_name;

	int vid_choice,person_choice; //����ڷκ��� ���ð�
	char choice_buffer[MAX_NUM_LENGTH] = { 0 }; //����ڷκ��� ���ð��� ���ڷ� ��ȯ�Ͽ� �˻��� �μ��� �ֱ����� ����
	Video_Info *choiced_vid = NULL; //����ڰ� ������ ���� ���� �ּ� �ӽ�����
	Person_Info *choiced_person = NULL; //����ڰ� ������ �� ���� �ּ� �ӽ�����
	
	switch(option)
	{
	case 0: //���� �뿩
		if (*head_vid!= NULL && *head_person != NULL) //������ ���� ������ ������� ��������
		{ 
			while (1) {
				std::cout << "�뿩�� ���ϴ� ���� �̸��� ������ �̸��� �Է��ϼ���. (�� �̸�, ���� �̸�)" << std::endl;
				std::cout << "��� : -1 �Է�" << std::endl;
				 std::cout << ">>";
				std::cin >> tmp_person_name>>tmp_vid_name;

				if (tmp_person_name.compare("-1") == 0 || tmp_vid_name.compare("-1") == 0)
					return -1;
				else if (tmp_person_name.length() > MAX_CHAR_LENGTH || tmp_vid_name.length() > MAX_CHAR_LENGTH)
					std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
				else break;
			}
			
			//���̸��� �����̸� �˻� �� ���ù���
			
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_person_name.c_str(), 2); //�뿩 �ѵ��� �ѱ��� ���� �� �˻�
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_vid_name.c_str(), 3); //�뿩������ ���� ���� �˻�

			if (search_person_result != NULL && search_vid_result != NULL) //�˻� ����� �����ϸ� ��� ���
			{
				search_vid_result_indexer = search_vid_result; //�ε����� �˻������ ��带 ����Ű����
				search_person_result_indexer = search_person_result; //�ε����� �˻������ ��带 ����Ű����

				std::cout << "< �� ��� >" << std::endl;
				print_info(head_vid, &search_person_result, 1); //�˻��� �� ���� ���
				std::cout<<std::endl;
				std::cout << "< ���� ��� >" << std::endl;
				print_info(&search_vid_result, &search_person_result, 0); //�˻��� ���� ���� ���

				while (1) {
					std::cout << "�뿩�� ������� PERSON_NUM �� �뿩�� ������ VID_NUM�� �Է��ϼ���." << std::endl;
					std::cout << "�뿩�ѵ� " << MAX_RENTAL_COUNT << "���� �ѱ� ���� �뿩�� �� �����ϴ�." << std::endl;
					std::cout << "��� : -1 �Է�" << std::endl;
					std::cout << ">>";
					std::cin >> person_choice >> vid_choice;

					if (person_choice == -1 || vid_choice == -1) return -1;

					if (person_choice < 0 || person_choice > last_person_num || vid_choice < 1 || vid_choice >last_vid_num)  //�߸��� ���� �Ǵ� �Է¹����� �ʰ��� ���
					{
						std::cout << "�߸��� ���ڸ� �Է��Ͽ��ų� �����ѵ��� ������ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}

						while (search_person_result_indexer != NULL) //���� ���� person_num ���� ���Ͽ� �˻�
						{
							if (person_choice == search_person_result_indexer->get_person_num())
							{
								itoa(person_choice, choice_buffer, 10); //����ڰ� �Է��� vid_num���� ���������� ��ȯ
								//����ڰ� ������ �� ������ person_num���� ���� DB�󿡼� ã�� choiced_person�� �ּҸ� �޾ƿ´�
								search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5);
								break;
							}
							search_person_result_indexer = search_person_result_indexer->next;
						}

						while(search_vid_result_indexer != NULL)
						{
							if (vid_choice == search_vid_result_indexer->get_vid_num()) //������ ���� vid_num���� ���Ͽ� �˻�
							{
								itoa(vid_choice,choice_buffer,10); //����ڰ� �Է��� vid_num���� ���������� ��ȯ
								//����ڰ� ������ ���� ������ vid_num���� ���� DB�󿡼� ã�� choiced_vid�� �ּҸ� �޾ƿ´�
								search_db(head_vid, head_person, &choiced_vid, &search_person_result, choice_buffer, 4);
								break;
							}
							search_vid_result_indexer = search_vid_result_indexer->next;
						}

					if (choiced_person == NULL || choiced_vid == NULL) //����߿��� �Է������ʾ��� ��� search_db�� ȣ����� �ʾ� NULL���� ����Ű�Ե�
					{
						//������ ��ȣ�� ����߿��� ���õ����ʾ��� ���
						std::cout << "��Ͽ��� �������� �ʾҽ��ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					}
					else break;
				}
				//�뿩�ÿ� ������ vid_rental �� ����, ���� rental_list[]�� ������� �߰�
				//�뿩 �ѵ��� �ѱ� ���� �뿩�Ұ���
				choiced_vid->vid_rental = 1;
				for (int i = 0; i < MAX_RENTAL_COUNT; i++)
				{
					if (choiced_person->rental_list[i] == 0) //�� ������ ����
					{
						choiced_person->rental_list[i] = choiced_vid->get_vid_num();
						free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
						return 1;
					}
				}

			}
			else
			{
				std::cout << "�������� �ʴ� ��,������ �Է��Ͽ��ų� �ִ� �뿩 �ѵ�: " << MAX_RENTAL_COUNT << "�� �ѱ� �� �Ǵ� �̹� �뿩���� �����Դϴ�." << std::endl;
				free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
				return 0;
			}
		}
		else
		{
			std::cout << "�����ͺ��̽��� ����� ������ ���� ������ �����ϴ�." << std::endl;
			return 0;
		}

		break;

	case 1: //���� �ݳ�
		//�ݳ��� ���ϴ� ���� �̸��� ������ �̸��� �Է¹޴´�
		//�̸��� �ش��ϴ� ���� ����� ����ϰ� ����
		//�ش� ���� �뿩���� ���� ����� ����ϰ� ����
		if (*head_vid != NULL && *head_person != NULL) //������ ���� ������ ������� ��������
		{ 
			while (1) {
				std::cout << "�ݳ��� ���ϴ� ���� �̸��� �Է��ϼ���." << std::endl;
				std::cout << "��� : -1 �Է�" << std::endl;
				std::cout << ">>";
				std::cin >> tmp_person_name;

				if (tmp_person_name.compare("-1") == 0 || tmp_vid_name.compare("-1") == 0)
					return -1;
				else if (tmp_person_name.length() > MAX_CHAR_LENGTH || tmp_vid_name.length() > MAX_CHAR_LENGTH)
					std::cout << "�ִ���� ���� " << "����: " << MAX_CHAR_LENGTH << "�ڸ� �ʰ��߽��ϴ�!" << std::endl;
				else break;
			}
			
			//���̸� �˻� �� ���ù���
			search_db(head_vid, head_person, &search_vid_result, &search_person_result, tmp_person_name.c_str(), 1); //�̸����� �� �˻�

			if (search_person_result != NULL) //�˻� ����� �����ϸ� ��� ���
			{
				search_person_result_indexer = search_person_result; //�ε����� ��带 ����Ű����
				print_info(head_vid, &search_person_result, 1); //�� ��� ���(���� �뿩�� ��ϵ� ����ϱ����� �μ��� ���� ��������� ����)

				while (1) {
					std::cout << "�ݳ��� ������� PERSON_NUM�� �Է��ϼ���." << std::endl;
					std::cout << "��� : -1 �Է�" << std::endl;
					std::cout << ">>";
					std::cin >> person_choice;

					if (person_choice == -1) return -1;

					if(person_choice < 0 || person_choice > last_person_num) //�߸��� ���� �Ǵ� �Է¹����� �ʰ��� ���
					{
						std::cout << "�߸��� ���ڸ� �Է��Ͽ��ų� �����ѵ��� ������ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}

						while(search_person_result_indexer != NULL) //���� ���� �ùٸ��� �����Ͽ����� �˻�
						{ 
							if (person_choice == search_person_result_indexer->get_person_num())
							{
								itoa(person_choice,choice_buffer,10); //����ڰ� �Է��� person_num���� ���������� ��ȯ
								//����ڰ� ������ �� ������ person_num���� ���� DB�󿡼� ã�� choiced_person�� �ּҸ� �޾ƿ´�
								search_db(head_vid, head_person, &search_vid_result, &choiced_person, choice_buffer, 5); 
								break;
							}
							search_person_result_indexer = search_person_result_indexer->next;
						}

					if (choiced_person == NULL)
					{
						//������ ��ȣ�� ����߿��� ���õ����ʾ��� ���
						std::cout << "��Ͽ��� �������� �ʾҽ��ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					}
					else break;
				}
				//�ش� ���� �뿩���� ��� ��� �� ����
				std::cout << choiced_person->name << "���� �뿩���� ��������Դϴ�." << std::endl;
				print_info(head_vid,&choiced_person, 2); //�ش� ���� �뿩���� ��� ���
				
				while(1)
				{
					std::cout<< "�ݳ��� ������ VID_NUM�� �Է��ϼ���." <<std::endl;
					std::cout << "��� : -1 �Է�" << std::endl;
					std::cout << ">>";
					std::cin >> vid_choice;

					if (vid_choice == -1) return -1;

					if(vid_choice < 1 || vid_choice > last_vid_num) //�߸��� ���� �Ǵ� �Է¹����� �ʰ��� ���
					{
						std::cout << "�߸��� ���ڸ� �Է��Ͽ��ų� �����ѵ��� ������ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
						continue;
					}
	
	
						for (int i = 0; i < MAX_RENTAL_COUNT; i++) //�Է°��� ���� �뿩�� ����� vid_num�� ��ġ�ϴ��� �˻�
						{
							if (vid_choice == choiced_person->rental_list[i])
							{
								itoa(vid_choice, choice_buffer, 10); //����ڰ� �Է��� person_num���� ���������� ��ȯ
								//����ڰ� ������ vid_num���� ���� DB���� �ش� ������ ã�� choiced_vid�� ����Ű����
								search_db(head_vid, head_person, &choiced_vid, &search_person_result, choice_buffer, 4);
								break;
							}
						}
				

					if (choiced_vid == NULL)
					{
						//������ ��ȣ�� ����߿��� ���õ����ʾ��� ���
						std::cout << "��Ͽ��� �������� �ʾҽ��ϴ�!!" << std::endl;
						std::cin.clear(); //������Ʈ�� �ʱ�ȭ
						std::cin.ignore(INT_MAX, '\n'); //�Է¹��ۺ���
					}
					else break;
				}

				//�ݳ��ÿ� ������ vid_rental �� ����, ���� rental_list[]���� ���� �� ����
				choiced_vid->vid_rental = 0;
				//�뿩��Ͽ� ���� ����
				for(int i = 0; i < MAX_RENTAL_COUNT;i++)
				{
					if(choiced_person->rental_list[i] == vid_choice) //�ش� ��ġ���� ����
					{
						//���� ���� �տ� ������
						for(int j = i ; j < MAX_RENTAL_COUNT ; j++)
						{
							choiced_person->rental_list[j]=choiced_person->rental_list[j+1];
						}
					}
				}
				//�뿩����� ������ ���� �迭�� �ִ� ���� �Ѵ� ������ �о�� �߸��� ���� ���ԵǹǷ� 0���� �ٲ�
				if (choiced_person->rental_list[MAX_RENTAL_COUNT - 1] != 0)
					choiced_person->rental_list[MAX_RENTAL_COUNT - 1] = 0;
			
				free_list(&search_vid_result, &search_person_result); //�˻��� ����� �޸𸮰��� ��ȯ
				return 1;
			}
			else
			{
				std::cout << "���� �������� �ʽ��ϴ�." << std::endl;
				return 0;
			}

		}
		else
		{
			std::cout << "�����ͺ��̽��� ����� ������ ���� ������ �����ϴ�." << std::endl;
			return 0;
		}

	break;

	}
	return 1;
}