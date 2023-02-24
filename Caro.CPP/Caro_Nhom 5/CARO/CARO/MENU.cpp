#include "MENU.h"
#include<iostream>
using namespace std;

MENU::MENU() {
}
MENU::~MENU() {
}
void MENU::Luachon_Menu() {
	cout << "*-------MAIN MENU-------*" << endl;
	cout << "1.Play with Other Player" << endl;
	cout << "2.Play with BOT" << endl;
	cout << "3.Replay" << endl;
	cout << "4.Player's Information" << endl;
	cout << "5.Guild" << endl;
	cout << "6.Exit" << endl;
}

void MENU::Luachon_BOT() {
	cout << "*-------Play with BOT-------*" << endl;
	cout << "1.Easy Mode" << endl;
	cout << "2.Normal Mode" << endl;
	cout << "3.Hard Mode" << endl;
	cout << "4.Back to MAIN MENU" << endl;
}

void  MENU::Huongdan() {
	cout << "1. Thuat ngu trong Game: " << endl;
	cout << "Quan co: trong game su dung bo dau ky hieu X/O" << endl;
	cout << "Ban co Caro: " << endl;
	cout << "\t Su dung ban co kich thuoc 10x10" << endl;
	cout << "\t Tren ban co chi co phep 2 nguoi choi" << endl;
	cout << endl << "2. Luat choi: " << endl;
	cout << "Trong tro choi nay se co 2 che do choi: " << endl;
	cout << "- Che do 1 la ban se choi voi mot nguoi choi khac" << endl;
	cout << "- Che do 2 la ban se choi voi may. Trong che do nay se duoc chia thanh 3 cap do choi:De (Easy), Trung Binh (Normal), Kho (Hard)" << endl;
	cout << "Sau khi ban chon duoc che do choi thi cach choi nhu sau: " << endl;
	cout << "- Ban lan luot nhap 2 so i va j. Voi i j tuong ung toa do dong va cot trong bang.VD ban nhap 3 3. Tuong ung o ban chon hang 3 cot 3" << endl;
	cout << "- Ban khong duoc nhap len toa do da nhap va gia tri i va j nhap phai nam trong khoang 0 -> 9,neu ban nhap sai se phai nhap lai" << endl;
	cout << "- Neu ben nao co 4 quan co lien tiep nhau cung nam tren hang ngang, hang doc hoac duong cheo thi se thang" << "VD:XOOOOX || XOOOO" << endl;
	cout << "- Neu tren ban co ma tat ca cac o bi danh ma chua co nguoi chien thang thi ket qua duoc tinh la hoa" << endl;
}
