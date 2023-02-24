#include "GAME.h"
#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
using namespace std;
int step = 0;                                  //Tạo biến lưu các nước đã đi trong bàn cờ
int arr[100][2];                               //Mảng lưu giá trị nước đi trong bàn cờ
//Hàm khởi tạo Game gán giá trị thuộc tính về giá trị mặc định mong muốn
GAME::GAME()
{
	for (int i = 0; i < 10; i++) // Vòng lặp trong mảng 2 chiều
	{
		for (int j = 0; j < 10; j++)
		{
			Luoi[i][j] = 'A'; // Gán giá trị ban đầu cho Lưới cờ là ‘A’
		}
	}
	NguoiChoi = 'O';         // Setup người chơi mặc định là O         (NEW)
	NguoiThangCuoc = false;  // Setup không có người thắng mặc định    (NEW_1)
	HoaNhau = false;         // Gán giá trị cho HoaNhau là false       (NEW_2)
}
GAME::~GAME()
{
}

void GAME::BangIn()
{
	char c;
	cout << "=> Player 1 = X, Player 2 = O:" << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)       //Vòng lặp có chức năng đánh số cột
		{
			if (j == 0) {
				cout << "    ";           //Căn dòng cho số 0
			}
			if (i == 0) {
				cout << j << "   ";      // Hiển thị các tương ứng với số cột
			}
		}
		cout << endl;
		for (int j = 0; j < 10; j++) {   //Vòng lặp có chức năng kẻ các ô lưới 10x10
			if (j == 0) {
				cout << "  ";              //Lùi vào 1 ô theo hàng ngang
			}
			cout << "|---";
			if (j == 9) cout << "|";
		}
		cout << endl;
		cout << i << " |";

		for (int j = 0; j < 10; j++) {
			c = (Luoi[i][j] == 'A') ? (' ') : Luoi[i][j];
			cout << " " << c << " |";
		}
		if (i == 9) cout << endl << "  " << "|---|---|---|---|---|---|---|---|---|---|";
	}
}


char GAME::LayNguoiChoi()
{
	return NguoiChoi;      // Trả về giá trị hiện hành của người chơi
}

void GAME::DiChuyenCuaNguoiChoi()
{
	int hang, cot;
	BangIn();
	LatNguoiChoi();
	do {
		if (NguoiChoi == 'X') {
			cout << "\nPlayer " << 1 << "'s turn: ";
		}
		else {
			cout << "\nPlayer " << 2 << "'s turn: ";
		}
		cin >> hang >> cot;
		cout << endl;
	} while (hang > 10 || hang < 0 || cot>10 || cot < 0);
	char valid = KtraDiChuyen(hang, cot);               //Khởi tạo biến kiểu char. Ktra gia trị hàng, cột có trùng giá trị đã điền trong bảng chưa
	while (valid != 'Y')
	{
		cout << "Di chuyen khong hop le !!!";          //Khi vi tri di chuyen trung gia tri da di thi hien thi thong bao
		cout << "\nChon vi tri khac: ";
		if (NguoiChoi == 'X') {
			cout << "\nPlayer " << 1 << "'s turn: ";
		}
		else {
			cout << "\nPlayer " << 2 << "'s turn: ";
		}
		cin >> hang >> cot;
		cout << endl;
		valid = KtraDiChuyen(hang, cot);
	}

	//Code thêm
	//char arr[100][2];                               //Mảng lưu giá trị nước đi trong bàn cờ
	step++;
	arr[step][0] = hang;
	arr[step][1] = cot;
	//
	CapNhatBangIn(hang, cot);                           
	NguoiThangCuoc = KtraNguoiThangCuoc();              //Dong nay tim nguoi thang cuoc
	if (NguoiThangCuoc != 1)                                          // Nếu không ai thắng thì sẽ vào ktra hòa
	{
		if (KtraHoaNhau())											 // Ktra 2 người hòa nhau
		{
			HoaNhau = true;
			cout << "2 nguoi choi hoa nhau." << endl;
			string name;
			cin.ignore(256, '\n');
			cout << "Nhap ten nguoi choi mot: ";
			getline(cin, name);
			LuuThongTin(name, 3);
			cout << "Nhap ten nguoi choi hai: ";
			getline(cin, name);
			LuuThongTin(name, 2);
			return;
		}
	}
	else if (NguoiThangCuoc == 1)
	{
		BangIn();
		string name;
		cin.ignore(256, '\n');
		cout << "\nNhap ten nguoi choi thang: ";
		getline(cin, name);
		LuuThongTin(name, 1);
		cout << "Nhap ten nguoi choi thua: ";
		getline(cin, name);
		LuuThongTin(name, 2);
	}
}
void GAME::CapNhatBangIn(int hang, int cot)
{
	Luoi[hang % 10][cot % 10] = NguoiChoi;
}

void GAME::CapNhatBangInReplay(int hang, int cot)
{
	if (NguoiChoi == 'O')           // Điều kiện xác định người chơi là X hay là O
	{
		NguoiChoi = 'X';
		Luoi[hang % 10][cot % 10] = NguoiChoi;
	}
	else
	{
		NguoiChoi = 'O';
		Luoi[hang % 10][cot % 10] = NguoiChoi;
	}
}

//<--- NEW_2--->
void GAME::LatNguoiChoi()
{
	if (NguoiChoi == 'O')       // Điều kiện xác định người chơi là X hay là O
	{
		NguoiChoi = 'X';
	}
	else
	{
		NguoiChoi = 'O';
	}
}

void GAME::Replay()
{
	for (int i = 0; i < 10; i++)             // Vòng lặp trong mảng 2 chiều
	{
		for (int j = 0; j < 10; j++)
		{
			Luoi[i][j] = 'A';               // Gán giá trị ban đầu cho Lưới cờ là ‘A’
		}
	}
	for (int i = 1; i <= step; i++) {
		system("cls");
		CapNhatBangInReplay(arr[i][0], arr[i][1]);
		BangIn();
		Sleep(1000);
	}
}
//Hàm dùng để khởi tạo lại giá trị Step về 0 để lưu Step ván cờ người chơi gần nhất
void GAME::ResetStep() {
	step = 0;
}

char GAME::KtraDiChuyen(int hang, int cot)
{
	char gridVal = Luoi[hang % 10][cot % 10];
	if (hang >= 0 && hang < 10 && cot >= 0 && cot < 10 && gridVal == 'A')  //Kiem tra gia tri hang, cot nhap vao co trong khoang [0;9] va gia tri co phai la 'A'
	{
		return 'Y';                                                        //Neu dung thi tra ve o vua nhap thoa man
	}
	else
	{
		return 'N';
	}
}

//Hàm kiểm tra điều kiện thắng trong bàn cờ
bool GAME::KtraNguoiThangCuoc()
{
	int demO, demX;

	// Kiểm tra đk thắng theo hàng
	for (int i = 0; i < 10; i++)
	{
		// Cho số kí hiệu ban đầu là 0
		demO = 0;
		demX = 0;
		for (int j = 0; j < 10; j++)
		{
			if (Luoi[i][j] == 'O')      // Lưới[i][j] hàng ký tự O
				demO++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
			else
			{
				if (Luoi[i][j] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[i][j] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[i][j] == 'X')      // Lưới[i][j] hàng ký tự X
				demX++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
			else
			{
				if (Luoi[i][j] == 'O')
				{
					if (demX >= 4)   demX = 4;
					else             demX = 0;
				}
				if (Luoi[i][j] == 'A')
					if (demX >= 4)   demX = 4;
					else             demX = 0;
			}
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}

	// Kiểm tra đk thắng theo cột
	for (int j = 0; j < 10; j++)
	{
		// Cho số kí hiệu ban đầu là 0
		demO = 0;
		demX = 0;
		for (int i = 0; i < 10; i++)
		{
			if (Luoi[i][j] == 'O')      // Lưới[i][j] theo cột ký tự O
				demO++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
			else
			{
				if (Luoi[i][j] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[i][j] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[i][j] == 'X')      // Lưới[i][j] theo cột ký tự X
				demX++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
			else
			{
				if (Luoi[i][j] == 'O')
				{
					if (demX >= 4)   demX = 4;
					else             demX = 0;
				}
				if (Luoi[i][j] == 'A')
					if (demX >= 4)   demX = 4;
					else             demX = 0;
			}
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}

	//Kiểm tra đk đường chéo chính và phụ đi qua tâm ma trận
	//Đường chéo chính
	int a = 0;                        //Biến a tọa độ trên đường chéo chính
	int b = 9;                        //Biến b tọa độ trên đường chéo phụ
	for (int i = 0; i < 10; i++, a++) {
		if (Luoi[i][a] == 'O')      // Lưới[i][j] đường chéo chính ký tự O
			demO++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
		else
		{
			if (Luoi[i][a] == 'X')
			{
				if (demO >= 4) demO = 4;
				else           demO = 0;
			}
			if (Luoi[i][a] == 'A')
				if (demO >= 4) demO = 4;
				else           demO = 0;
		}

		if (Luoi[i][a] == 'X')      // Lưới[i][j] đường chéo chính ký tự X
			demX++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
		else
		{
			if (Luoi[i][a] == 'O')
			{
				if (demX >= 4)   demX = 4;
				else             demX = 0;
			}
			if (Luoi[i][a] == 'A')
				if (demX >= 4)   demX = 4;
				else             demX = 0;
		}
	}
	if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
		return true;

	//Đường chéo phụ:
	for (int i = 0; i < 10; i++, b--) {
		if (Luoi[i][b] == 'O')      // Lưới[i][j] đường chéo chính ký tự O
			demO++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
		else
		{
			if (Luoi[i][b] == 'X')
			{
				if (demO >= 4) demO = 4;
				else           demO = 0;
			}
			if (Luoi[i][b] == 'A')
				if (demO >= 4) demO = 4;
				else           demO = 0;
		}

		if (Luoi[i][b] == 'X')      // Lưới[i][j] đường chéo chính ký tự X
			demX++;                 // Số kí hiệu tăng lên sau mỗi lần lặp
		else
		{
			if (Luoi[i][b] == 'O')
			{
				if (demX >= 4)   demX = 4;
				else             demX = 0;
			}
			if (Luoi[i][b] == 'A')
				if (demX >= 4)   demX = 4;
				else             demX = 0;
		}
	}
	if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
		return true;
	// Kiểm tra điều kiện thắng đường chéo
	int i, k, j;
	//1.Đường chéo trên chính (Cách nhận biết: điểm đầu (0;1) - điểm cuối (8;9))
	for (int j = 1; j < 10; j++)
	{
		demO = 0;
		demX = 0;

		k = j;
		i = 0;
		while (k < 10)
		{
			if (Luoi[i][k] == 'O')
				demO++;
			else
			{
				if (Luoi[i][k] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[i][k] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[i][k] == 'X')
				demX++;
			else
			{
				if (Luoi[i][k] == 'O')
				{
					if (demX >= 4) demX = 4;
					else           demX = 0;
				}
				if (Luoi[i][k] == 'A')
					if (demX >= 4) demX = 4;
					else           demX = 0;
			}
			k++;
			i++;
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}
	//2.Kiểm tra đường chéo dưới chính (Cách nhận biết điểm xét từ trái qua phải: điểm đầu (1;0) - điểm cuối (9;8))
	for (int i = 1; i < 10; i++)
	{
		demO = 0;
		demX = 0;

		k = i;
		j = 0;
		while (k < 10)
		{
			if (Luoi[k][j] == 'O')
				demO++;
			else
			{
				if (Luoi[k][j] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[k][j] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[k][j] == 'X')
				demX++;
			else
			{
				if (Luoi[k][j] == 'O')
				{
					if (demX >= 4) demX = 4;
					else           demX = 0;
				}
				if (Luoi[k][j] == 'A')
					if (demX >= 4) demX = 4;
					else           demX = 0;
			}
			k++;
			j++;
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}
	//3.Kiểm tra đường chéo trên phụ (Cách nhận biết: điểm đầu (8;0) - điểm cuối (0;8))
	for (int j = 8; j >= 0; j--)
	{
		demO = 0;
		demX = 0;

		k = j;
		i = 0;
		while (k >= 0)
		{
			if (Luoi[i][k] == 'O')
				demO++;
			else
			{
				if (Luoi[i][k] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[i][k] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[i][k] == 'X')
				demX++;
			else
			{
				if (Luoi[i][k] == 'O')
				{
					if (demX >= 4) demX = 4;
					else           demX = 0;
				}
				if (Luoi[i][k] == 'A')
					if (demX >= 4) demX = 4;
					else           demX = 0;
			}
			k--;
			i++;
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}
	//4.Kiểm tra đường chéo dưới phụ (Cách nhận biết: điểm đầu (9;1) - điểm cuối (1;9))
	for (int i = 1; i < 10; i++)
	{
		demO = 0;
		demX = 0;

		k = i;
		j = 9;
		while (k < 10)
		{
			if (Luoi[k][j] == 'O')
				demO++;
			else
			{
				if (Luoi[k][j] == 'X')
				{
					if (demO >= 4) demO = 4;
					else           demO = 0;
				}
				if (Luoi[k][j] == 'A')
					if (demO >= 4) demO = 4;
					else           demO = 0;
			}

			if (Luoi[k][j] == 'X')
				demX++;
			else
			{
				if (Luoi[k][j] == 'O')
				{
					if (demX >= 4) demX = 4;
					else           demX = 0;
				}
				if (Luoi[k][j] == 'A')
					if (demX >= 4) demX = 4;
					else           demX = 0;
			}
			k++;
			j--;
		}
		if (demO == 4 || demX == 4)                  // Nếu đủ số kí hiệu = 4 thì trả về true
			return true;
	}

	return false;                                   //Không có ai thắng
}

bool GAME::KtraHoaNhau()
{
	int count = 0;                                 // Khởi tạo biến đếm bằng 0
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Luoi[i][j] == 'X' || Luoi[i][j] == 'O')
				count++;                        // Tăng biến đếm lên 1 sau mỗi lần lặp
		}
	}
	return (count == 100);             // Gán kết quả trả về cho biến đếm bằng 100. Vì bàn cờ có 100 vị trí đánh
}

void GAME::LuuThongTin(string ten, int trangThai)
{
	ofstream outFile("temp.txt");
	ifstream inFile(this->fileName.c_str());
	string line;
	bool isFound = false;
	int win = 0, lose = 0, draw =0 ;
	while (getline(inFile, line) && line != "")
	{
		if (line == ten)
		{
			inFile >> win;
			inFile >> lose;
			inFile >> draw;
			if (trangThai == 1)
			{
				win++;
			}
			else if (trangThai == 2)
			{
				lose++;
			}
			else
			{
				draw++;
			}
			outFile << ten << endl;
			outFile << win << endl;
			outFile << lose << endl;
			outFile << draw << endl;
			isFound = true;
		}
		else
		{
			inFile >> win;
			inFile >> lose;
			inFile >> draw;
			outFile << line << endl;
			outFile << win << endl;
			outFile << lose << endl;
			outFile << draw << endl;
		}
	}
	inFile.close();
	outFile.close();
	if (!isFound)
	{
		outFile.open(this->fileName.c_str(), ios::app);
		win = lose = draw = 0;
		if (trangThai == 1)
		{
			win++;
		}
		else if (trangThai == 2)
		{
			lose++;
		}
		else
		{
			draw++;
		}
		outFile << ten << endl
			<< win << endl
			<< lose << endl
			<< draw << endl;
	}
	else
	{
		inFile.open("temp.txt");
		outFile.open(this->fileName.c_str());
		while (getline(inFile, line))
		{
			outFile << line << endl;
		}

		inFile.close();
		outFile.close();
	}

	system("del temp.txt");
}
void GAME::xuatThongTinNguoiChoi()
{
	cout << "Danh sach thong tin nguoi choi:\n";
	cout << "Ten\tThang\tThua\tHoa\n";
	ifstream inFile(this->fileName.c_str());
	string line;
	int win, lose, draw;
	while (!inFile.eof())
	{
		getline(inFile, line);
		if (line == "")
		{
			break;
		}
		inFile >> win;
		inFile >> lose;
		inFile >> draw;
		inFile.ignore();
		cout << line << "\t" << win << "\t" << lose << "\t" << draw << "\n";
	}

	inFile.close();
}

