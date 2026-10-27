
#define THUVIEN_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct Sach
{
	string ISBN;
	string tensach;
	string tacgia;
	string theloai;
	int namXB;
	int soLuong;
};

struct docGia {
	string CMND;
	string hoten;
	string email;
	string sdt;
	string loaithe;
};

struct Phieumuon {
	string maPhieu;
	string CMND;
	string ISBN;
	string ngayMuon;
	string ngayHentra;
	string ngayTra;
	bool daTra;
};
struct NodePhieumuon {
	Phieumuon data;
	NodePhieumuon* next;
};

struct Giaodich {
	string maPhieu;
	string CMND;
	string ISBN;
	string ngayGiaoDich;
	string loaiGiaoDich;
};

struct NodeAVL {
	Sach data;
	NodeAVL* left;
	NodeAVL* right;
	int height;
};

struct NodeBST {
	Sach data;
	NodeBST* left;
	NodeBST* right;
};

// cac ham
int chieuCao(NodeAVL* node);
int layCanBang(NodeAVL* node);
NodeAVL* taoNode(Sach s);