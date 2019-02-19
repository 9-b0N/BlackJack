#include "Card.h"


CCard::CCard()
{
	for (int i = 0; i <= 13; i++)
		card_num[i] = 4;
}
CCard::~CCard()
{
}

void CCard::sc_reset()
{
	sc1 = ' ';
	sc2 = ' ';
	sc3 = ' ';
	sc4 = ' ';
	sc5 = ' ';
}
//ī���� ���Ǵ� ��Ʈ���� ' '���� �ʱ�ȭ�մϴ�

void CCard::card_sc(int num)
{
	if (num == -1)
	{
		sc1+="********* ";
		sc2+="********* ";
		sc3+="********* ";
		sc4+="********* ";
		sc5+="********* ";
	}
	else
	{
		char m, nn;
		switch (num / 100)
		{
		case 1:
			m = 'S';
			break;
		case 2:
			m = 'D';
			break;
		case 3:
			m = 'C';
			break;
		case 4:
			m = 'H';
			break;
		}
		if (num % 100 == 11)
			nn = 'J';
		else if (num % 100 == 12)
			nn = 'Q';
		else if (num % 100 == 13)
			nn = 'K';
		else if (num % 100 == 1)
			nn = 'A';
		else
		{
			if (num % 100 == 10)
				nn = 'T';
			else
				nn = (num % 100) + 48;
		}
		sc1 += "*"; sc1 += nn; sc1 += "******* ";
		//printf("*%c******* ", nn);
		sc2 += "*       * ";
		//printf("*       * ");
		sc3 += "*   "; sc3 += m; sc3 += "   * ";
		//printf("*   %c   * ",m);
		sc4 += "*       * ";
		//printf("*       * ");
		sc5 += "*******"; sc5 += nn; sc5 += "* ";
		//printf("*******%c* ", nn);
	}
}
//ī�带 ī�� ���ؼ� ��Ʈ���� �ִ� �Լ�, -1�� ������ �޸�

void CCard::card_show()
{
	cout << sc1 << endl;
	cout << sc2 << endl;
	cout << sc3 << endl;
	cout << sc4 << endl;
	cout << sc5 << endl;
	putchar('\n');
}
//��Ʈ�� 11���� ����ϴ� �Լ�

int CCard::card_drow()
{
	CUtil u;
	int sum = 0;
	for (int i = 1; i <= 13; i++)//ī�尡 � �ִ°�?
		sum += card_num[i];
	int l = u.luck(sum);//1~sum���� ���� �ϳ� ����
	sum = 0;
	for (int i = 1; i <= 13; i++)
	{
		//sum 4 16 20 24
		//���� ���ڰ� �ִ� ī���� ���� ������ ����
		sum += card_num[i];
		if (l <= sum)
		{
			//i=���� ����
			while (1)
			{
				int mark = u.luck(card_num[i]--);
				if (card[mark][i] != 1)
				{
					card[mark][i] = 1;
					return (mark * 100) + i;
				}
			}	
		}
	}
}
//ī�带 �̴� �Լ�, ���ϰ��� ī�带 ������ ǥ���� ��

void CCard::P2start(int r)
{
	CUtil u;
	for (int rr = 0; rr < r; rr++)
	{
		int card[5][14] = { 0, }, player_hand[17] = { 0, }, player2_hand[17] = { 0, }, ai_hand[17] = { 0, };
		int player_hand_i = 0, player2_hand_i = 0, ai_hand_i = 0;
		bool player_giveup = false, player2_giveup = false, ai_giveup = false;
		int card_num[14];
		int player_card_num = 0, player2_card_num = 0, ai_card_num = 0;
		printf("�÷��̾� 1�� %d�� �̱�� %d�� �����ϴ�.\n", win, lose);
		printf("�÷��̾� 2�� %d�� �̱�� %d�� �����ϴ�.\n", lose, win);
		printf("%d��° �����Դϴ�.\nī�带 ���� ���� �̽��ϴ�\n", rr + 1);
		for (int i = 0; i < 2; i++)
		{
			player_hand[player_hand_i] = card_drow();
			if ((player_hand[player_hand_i] % 100) > 10)
			{
				player_card_num += 10;
				player_hand_i++;
			}
			else
				player_card_num += player_hand[player_hand_i++]%100;
			player2_hand[player2_hand_i] = card_drow();
			if ((player2_hand[player2_hand_i] % 100) > 10)
			{
				player2_card_num += 10;
				player2_hand_i++;
			}
			else
				player2_card_num += player2_hand[player2_hand_i++]%100;
		}
		while (!(player_giveup&&player2_giveup))
		{
			if (player_card_num > 21)
			{
				printf("�÷��̾� 1�� 21�� �Ѿ� �ڵ� ���� ����ϴ�.\n");
				player_giveup = true;
			}
			if (player2_card_num > 21)
			{
				printf("�÷��̾� 2�� 21�� �Ѿ� �ڵ� ���� ����ϴ�.\n");
				player2_giveup = true;
			}
			if (!player_giveup)
			{
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(player_hand[i]);
				card_show();
				printf("�÷��̾� 1�� �����Դϴ�.\n");
				switch (u.FSelect("ī�带 �����ðڽ��ϱ�. �����Ͻðڽ��ϱ�?\n1)ī�带 ���� �̴´�.\n2)�����Ѵ�\n", 1, 2))
				{
				case 1:
					printf("ī�带 ���� �����̽��ϴ�.\n");
					player_hand[player_hand_i] = card_drow();
					if ((player_hand[player_hand_i] % 100) > 10)
					{
						player_card_num += 10;
						player_hand_i++;
					}
					else
						player_card_num += player_hand[player_hand_i++]%100;
					break;
				case 2:
					printf("�����ϼ̽��ϴ�.");
					player_giveup = true;
					break;
				}
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(player_hand[i]);
				card_show();
			}
			if (!player2_giveup)
			{
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(player2_hand[i]);
				card_show();
				printf("�÷��̾� 2�� �����Դϴ�.\n");
				switch (u.FSelect("ī�带 �����ðڽ��ϱ�. �����Ͻðڽ��ϱ�?\n1)ī�带 ���� �̴´�.\n2)�����Ѵ�\n", 1, 2))
				{
				case 1:
					printf("ī�带 ���� �����̽��ϴ�.\n");
					player2_hand[player2_hand_i] = card_drow();
					if ((player2_hand[player2_hand_i] % 100) > 10)
					{
						player2_card_num += 10;
						player2_hand_i++;
					}
					else
						player2_card_num += player2_hand[player2_hand_i++]%100;
					break;
				case 2:
					printf("�����ϼ̽��ϴ�.");
					player2_giveup = true;
					break;
				}
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(player2_hand[i]);
				card_show();
			}
		}
		if (player_card_num > 21 && player2_card_num > 21)
		{
			printf("�÷��̾� 1�� �¸��Դϴ�.\n�� �� �ʰ�, �����¸�\n");
			win++;
		}
		else if (player_card_num > 21)
		{
			printf("�÷��̾� 2�� �¸��Դϴ�.\n�÷��̾� 1 �� 21�� �Ѿ\n");
			lose++;
		}
		else if (player2_card_num > 21)
		{
			printf("�÷��̾� 1�� �¸��Դϴ�.\n�÷��̾� 2 �� 21�� �Ѿ\n");
			lose++;
		}
		else if (player_card_num == 21 && player2_card_num == 21)
		{
			printf("�÷��̾� 1�� �¸��Դϴ�.\n����, �����¸�\n");
			win++;
		}
		else if (player_card_num == 21)
		{
			printf("�÷��̾� 1�� �¸��Դϴ�.\n�÷��̾� 1 ī�� ���� 21\n");
			win++;
		}
		else if (player2_card_num == 21)
		{
			printf("�÷��̾� 2�� �¸��Դϴ�.\n�÷��̾� 2 ī�� ���� 21\n");
			lose++;
		}
		else if (player_card_num > player2_card_num)
		{
			printf("�÷��̾� 1�� �¸��Դϴ�.\n�÷��̾� 1 �� �� 21�� �����\n");
			win++;
		}
		else
		{
			printf("�÷��̾� 2�� �¸��Դϴ�.\n�÷��̾� 2 �� �� 21�� �����\n");
			lose++;
		}
		Sleep(5000);//2sec
		system("cls");
	}
}

void CCard::AIstart(int r, int f)
{
	printf("ù ���Դϴ�.\n ī�带 ���� ���� �̽��ϴ�.\n");
	Sleep(2000);//2sec
	system("cls");
	for (int rr = 0; rr < r; rr++)
	{
		
		Sleep(2000);//2sec
	}
}