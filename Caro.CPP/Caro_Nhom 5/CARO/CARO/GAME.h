#pragma once
#include<string>
using namespace std;
class GAME
{
private:
	string fileName = "info.txt";
	char NguoiChoi;       // Tạo ra biến NguoiChoi kiểu char
	char Luoi[10][10];    // Tạo ra 1 mảng tên Luoi[][] kiểu char
public:
	GAME();               // Hàm khởi tạo mặc định
	~GAME();              // Hàm hủy
	void BangIn();
	void DiChuyenCuaNguoiChoi();               // Tạo hàm để xác định di chuyển của người chơi
	void CapNhatBangIn(int hang, int cot);     // Tạo hàm Cập nhật lại bảng in với tham số truyền vào thuộc kiểu int
	void CapNhatBangInReplay(int hang, int cot);
	char LayNguoiChoi();                       // Tạo hàm lấy người chơi thuộc kiểu char
	void LatNguoiChoi();                       // Tạo hàm lật người chơi để thấy được X và O
	char KtraDiChuyen(int hang, int cot);      // Tạo hàm ktra thuộc kiểu char với tham số truyền vào thuộc kiểu int
	bool KtraNguoiThangCuoc();                 // Tạo hàm Ktra người thắng thuộc kiểu bool
	bool NguoiThangCuoc;                       // Tạo biến Người thắng cuộc kiểu bool
	bool HoaNhau;                              // Tạo biến HoaNhau kiểu bool
	bool KtraHoaNhau();                        // Tạo 1 hàm Ktra hòa nhau kiểu bool
	void Replay();
	void LuuThongTin(string ten, int trangThai);  	// lưu thông tin trận đấu
	void xuatThongTinNguoiChoi();              // xuat thong tin nguoi choi
	void ResetStep();
};

