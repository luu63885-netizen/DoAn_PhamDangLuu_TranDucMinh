#define _CRT_SECURE_NO_WARNINGS
#ifndef THUVIEN_H
#define THUVIEN_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <vector>

using namespace std;

// ======================= CAC STRUCT DU LIEU =======================

struct Sach
{
	string ISBN;
	string tenSach;
	string tacGia;
	string theLoai;
	int namXuatBan = 0;
	int soLuong = 0;
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
	bool daTra = false;
};

struct Giaodich {
	string maPhieu;
	string CMND;
	string ISBN;
	string ngayGiaoDich;
	string loaiGiaoDich;   // "MUON" hoac "TRA"
};

struct NodeAVL {
	Sach data;
	NodeAVL* left;
	NodeAVL* right;
	int height;
};

struct NodeBST {
	Sach data;
	NodeBST* left = NULL;
	NodeBST* right = NULL;
};

// Ket qua doc file nhi phan
enum KetQuaDoc {
	DOC_OK,
	DOC_KHONG_CO_FILE,
	DOC_FILE_LOI
};

// ======================= QUAN LY SACH (AVL + BST) =======================

class QuanLySach
{
private:
	NodeAVL* rootAVL;
	NodeBST* rootBST;

	int chieuCao(NodeAVL* p);
	int doLech(NodeAVL* p);
	NodeAVL* taoNodeAVL(Sach s);
	NodeAVL* xoayPhai(NodeAVL* p);
	NodeAVL* xoayTrai(NodeAVL* p);
	NodeAVL* canBang(NodeAVL* p);
	NodeAVL* themAVL(NodeAVL* p, Sach s);
	NodeAVL* timMin(NodeAVL* p);
	NodeAVL* xoaAVL(NodeAVL* p, string ISBN);
	NodeAVL* timAVL(NodeAVL* p, string ISBN);
	void duyetISBN(NodeAVL* p);
	void giaiPhongAVL(NodeAVL* p);

	NodeBST* taoNodeBST(Sach s);
	NodeBST* themBST(NodeBST* p, Sach s);
	NodeBST* timMinBST(NodeBST* p);
	NodeBST* xoaBST(NodeBST* p, const Sach& s);
	void duyetTen(NodeBST* p);
	void giaiPhongBST(NodeBST* p);

	// Phuc vu file nhi phan (cai dat trong filebinary.cpp)
	int demAVL(NodeAVL* p);
	void ghiAVL(NodeAVL* p, ofstream& f);

public:
	QuanLySach();
	~QuanLySach();
	QuanLySach(const QuanLySach&) = delete;              // khong cho sao chep (giu con tro tho)
	QuanLySach& operator=(const QuanLySach&) = delete;
	void themSach(Sach s);
	void xoaSach(string ISBN);
	bool suaSach(string ISBN, const Sach& moi);
	void timSach(string ISBN);
	bool kiemTraISBN(string ISBN);

	void inTheoISBN();
	void inTheoTen();

	void xoaHet();                                         // giai phong toan bo cay
	bool luuNhiPhan(const string& tenFile);                // ghi file .dat
	KetQuaDoc docNhiPhan(const string& tenFile, int& soDoc); // doc file .dat
};

// ======================= QUAN LY DOC GIA (HASH TABLE) =======================

struct NodeDocGia {
	docGia data;
	NodeDocGia* next;
};

const int KICH_THUOC_BANG_BAM = 1009;
struct HashTable {
	NodeDocGia* buckets[KICH_THUOC_BANG_BAM];
};

void khoiTaoHashTable(HashTable& ht);
int  hamBam(const string& CMND);
void giaiPhongHashTable(HashTable& ht);

bool themDocGia(HashTable& ht, const docGia& dg);
bool xoaDocGia(HashTable& ht, const string& CMND);
bool suaDocGia(HashTable& ht, const string& CMND, const docGia& moi);
NodeDocGia* timDocGia(HashTable& ht, const string& CMND);

void inMotDocGia(const docGia& dg);
void hienThiDocGia(HashTable& ht);
void thongKeDocGia(HashTable& ht);

void nhapFileDocGia(HashTable& ht, const string& tenFile);
void xuatFileDocGia(HashTable& ht, const string& tenFile);

int  timTuanTu(docGia* mang, int n, const string& CMND);
void soSanhHashVaTuanTu();

bool luuNhiPhanDocGia(HashTable& ht, const string& tenFile);
KetQuaDoc docNhiPhanDocGia(HashTable& ht, const string& tenFile, int& soDoc);

// ======================= PHIEU MUON (DANH SACH LIEN KET DON) =======================

struct NodePhieumuon {
	Phieumuon data;
	NodePhieumuon* next;
};

struct DanhSachPhieuMuon {
	NodePhieumuon* head;
	NodePhieumuon* tail;
	int soLuong;
};

void khoiTaoDSPhieuMuon(DanhSachPhieuMuon& ds);
void giaiPhongDSPhieuMuon(DanhSachPhieuMuon& ds);
bool themPhieuMuon(DanhSachPhieuMuon& ds, const Phieumuon& pm);   // them cuoi danh sach
NodePhieumuon* timPhieuMuon(DanhSachPhieuMuon& ds, const string& maPhieu);
bool xoaPhieuMuon(DanhSachPhieuMuon& ds, const string& maPhieu);
void inMotPhieuMuon(const Phieumuon& pm);
void hienThiPhieuMuon(DanhSachPhieuMuon& ds);

bool luuNhiPhanPhieuMuon(DanhSachPhieuMuon& ds, const string& tenFile);
KetQuaDoc docNhiPhanPhieuMuon(DanhSachPhieuMuon& ds, const string& tenFile, int& soDoc);

// ======================= LICH SU GIAO DICH (MANG DONG) =======================

struct MangGiaoDich {
	Giaodich* data;
	int soLuong;    // so phan tu dang co
	int sucChua;    // so phan tu toi da truoc khi phai cap phat lai
};

void khoiTaoMangGD(MangGiaoDich& m);
void giaiPhongMangGD(MangGiaoDich& m);
void themGiaoDich(MangGiaoDich& m, const Giaodich& g);   // day het thi nhan doi suc chua
void hienThiGiaoDich(MangGiaoDich& m);

bool luuNhiPhanGiaoDich(MangGiaoDich& m, const string& tenFile);
KetQuaDoc docNhiPhanGiaoDich(MangGiaoDich& m, const string& tenFile, int& soDoc);

// ======================= TOAN BO DU LIEU + LUU TRU =======================

const string FILE_SACH_DAT = "sach.dat";
const string FILE_DOCGIA_DAT = "docgia.dat";
const string FILE_PHIEUMUON_DAT = "phieumuon.dat";
const string FILE_GIAODICH_DAT = "giaodich.dat";

struct DuLieu {
	QuanLySach sach;
	HashTable docGia;
	DanhSachPhieuMuon phieuMuon;
	MangGiaoDich giaoDich;

	DuLieu();
	~DuLieu();

	DuLieu(const DuLieu&) = delete;              // khong cho sao chep
	DuLieu& operator=(const DuLieu&) = delete;
};

bool luuSach(DuLieu& dl);
bool luuDocGia(DuLieu& dl);
bool luuPhieuMuon(DuLieu& dl);
bool luuGiaoDich(DuLieu& dl);
bool luuTatCa(DuLieu& dl);
void docTatCa(DuLieu& dl);

// ======================= NHAP LIEU / TIEN ICH =======================

int    nhapLuaChon();
string nhapChuoi(const string& loiNhac);
int    nhapSo(const string& loiNhac, int nhoNhat, int lonNhat);
string nhapCMND(const string& loiNhac);
string nhapEmail(const string& loiNhac);
string nhapSDT(const string& loiNhac);
string nhapLoaiThe(const string& loiNhac);
string nhapNgay(const string& loiNhac);

string catKhoangTrang(const string& s);
int    namHienTai();
bool   laCMNDHopLe(const string& s);
bool   laEmailHopLe(const string& s);
bool   laSDTHopLe(const string& s);
bool   laLoaiTheHopLe(const string& s);
bool   laNgayHopLe(const string& s);

// ======================= MENU =======================

void menuChinh();
void menuQuanLySach();
void menuQuanLyDocGia();
void menuMuonTraSach();
void menuThongKeBaoCao();
void menuLuuTru();

#endif
