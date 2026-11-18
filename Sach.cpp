#include "thuvien.h"

QuanLySach::QuanLySach()
{
    rootAVL = NULL;
    rootBST = NULL;
}


QuanLySach::~QuanLySach()
{
    giaiPhongAVL(rootAVL);
    giaiPhongBST(rootBST);
}


bool QuanLySach::kiemTraISBN(string ISBN)
{
    return timAVL(rootAVL, ISBN) != NULL;
}


void QuanLySach::themSach(Sach s)
{
    if (kiemTraISBN(s.ISBN))
    {
        cout << "ISBN da ton tai!\n";
        return;
    }

    rootAVL = themAVL(rootAVL, s);
    rootBST = themBST(rootBST, s);

    cout << "Them sach thanh cong!\n";
}


void QuanLySach::xoaSach(string ISBN)
{
    NodeAVL* p = timAVL(rootAVL, ISBN);
    if (p == NULL)
    {
        cout << "Khong tim thay sach!\n";
        return;
    }

    Sach can = p->data;

    rootAVL = xoaAVL(rootAVL, ISBN);
    rootBST = xoaBST(rootBST, can);

    cout << "Xoa sach thanh cong!\n";
}

bool QuanLySach::suaSach(string ISBN, const Sach& moi)
{
    NodeAVL* p = timAVL(rootAVL, ISBN);
    if (p == NULL)
        return false;

    Sach cu = p->data;
    Sach capNhat = moi;
    capNhat.ISBN = ISBN;

    rootBST = xoaBST(rootBST, cu);
    p->data = capNhat;
    rootBST = themBST(rootBST, capNhat);

    return true;
}

void QuanLySach::timSach(string ISBN)
{
    NodeAVL* p = timAVL(rootAVL, ISBN);

    if (p == NULL)
    {
        cout << "Khong tim thay sach!\n";
        return;
    }

    cout << "\n===== THONG TIN SACH =====\n";
    cout << "ISBN: " << p->data.ISBN << endl;
    cout << "Ten sach: " << p->data.tenSach << endl;
    cout << "Tac gia: " << p->data.tacGia << endl;
    cout << "The loai: " << p->data.theLoai << endl;
    cout << "Nam xuat ban: " << p->data.namXuatBan << endl;
    cout << "So luong: " << p->data.soLuong << endl;
}


void QuanLySach::inTheoISBN()
{
    if (rootAVL == NULL)
    {
        cout << "Danh sach sach rong!\n";
        return;
    }

    cout << "\n===== DANH SACH SACH THEO ISBN =====\n";
    cout << "ISBN\tTen sach\tTac gia\tSo luong\n";

    duyetISBN(rootAVL);
}

void QuanLySach::inTheoTen()
{
    if (rootBST == NULL)
    {
        cout << "Danh sach sach rong!\n";
        return;
    }

    cout << "\n===== DANH SACH SACH THEO TEN =====\n";
    cout << "Ten sach\tISBN\tTac gia\tSo luong\n";

    duyetTen(rootBST);
}