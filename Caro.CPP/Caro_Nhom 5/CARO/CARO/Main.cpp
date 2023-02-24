#include<iostream>
using namespace std;
#include"MENU.h"
#include"GAME.h"
#include "BOT.cpp"

int  main()
{
	char yc;
	MENU m1;
	GAME g;         
	BOT b1;
	m1.Luachon_Menu();
	do {
		GAME g1;
		cout << "Nhap yeu cau ban muon thuc hien: "; cin >> yc;
		cout << endl;
		switch (yc) {
		case '1':
			system("cls");
			g1.ResetStep();
			while (g1.NguoiThangCuoc != 1 && g1.HoaNhau != 1) {
				system("cls");
				g1.DiChuyenCuaNguoiChoi(); 
			}
			cout << endl;   
			g1.BangIn();     
			if (g1.NguoiThangCuoc == 1 && g1.LayNguoiChoi() == 'X') {
				cout << endl << endl << endl << "Player 1 " << " Chien Thang!" << endl;
			}
			else if(g1.NguoiThangCuoc == 1)
			{
				cout << endl << endl << endl << "Player 2 " << " Chien Thang!" << endl;
			}
			else {
				cout << endl << endl << endl << "Hai nguoi choi hoa nhau" << endl;
			}
			system("pause");
			m1.Luachon_Menu();
			break;
		case '2': {
				b1.play();
				break;
			}
		case '3':
			system("cls");
			g.Replay();
			cout << endl;
			m1.Luachon_Menu();
			break;
		case '4':
			system("cls");
			g1.xuatThongTinNguoiChoi();
			m1.Luachon_Menu();
			break;
		case'5':
			m1.Huongdan();
			cout << endl << endl;
			m1.Luachon_Menu();
			break;
		case'6':
			return 0;
		}
	} while (yc != 6);
	return 0;
}