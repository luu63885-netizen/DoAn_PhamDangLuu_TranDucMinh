#include "thuvien.h"

const string FILE_DOC_GIA = "docgia.txt";

// ===================== QUAN LY SACH =====================
void xuLyQuanLySach(DuLieu& dl)
{
    QuanLySach& ql = dl.sach;
    int chon;

    do
    {
        menuQuanLySach();
        chon = nhapLuaChon();

        switch (chon)
        {
        case 1:
        {
            Sach s;

            cout << "\n========== THEM SACH ==========\n";

            s.ISBN = nhapChuoi("Nhap ISBN: ");
            if (ql.kiemTraISBN(s.ISBN))
            {
                cout << "ISBN da ton tai!\n";
                break;
            }
            s.tenSach = nhapChuoi("Nhap ten sach: ");
            s.tacGia = nhapChuoi("Nhap tac gia: ");
            s.theLoai = nhapChuoi("Nhap the loai: ");
            s.namXuatBan = nhapSo("Nhap nam xuat ban: ", 1, namHienTai());
            s.soLuong = nhapSo("Nhap so luong: ", 0, 1000000);

            if (!cin)
            {
                cout << "Het du lieu nhap, huy them sach!\n";
                break;
            }

            ql.themSach(s);
            luuSach(dl);    // tu dong ghi file khi co thay doi

            break;
        }

        case 2:
        {
            cout << "\n========== XOA SACH ==========\n";

            string ISBN = nhapChuoi("Nhap ISBN can xoa: ");
            if (!ISBN.empty())
            {
                ql.xoaSach(ISBN);
                luuSach(dl);
            }

            break;
        }

        case 3:
        {
            cout << "\n========== SUA THONG TIN SACH ==========\n";

            string ISBN = nhapChuoi("Nhap ISBN can sua: ");
            if (ISBN.empty())
                break;
            if (!ql.kiemTraISBN(ISBN))
            {
                cout << "Khong tim thay sach!\n";
                break;
            }

            Sach moi;
            moi.ISBN = ISBN;
            moi.tenSach = nhapChuoi("Nhap ten sach moi: ");
            moi.tacGia = nhapChuoi("Nhap tac gia moi: ");
            moi.theLoai = nhapChuoi("Nhap the loai moi: ");
            moi.namXuatBan = nhapSo("Nhap nam xuat ban moi: ", 1, namHienTai());
            moi.soLuong = nhapSo("Nhap so luong moi: ", 0, 1000000);

            if (!cin)
            {
                cout << "Het du lieu nhap, huy sua sach!\n";
                break;
            }

            ql.suaSach(ISBN, moi);
            cout << "Sua sach thanh cong!\n";
            luuSach(dl);

            break;
        }

        case 4:
        {
            cout << "\n========== TIM SACH ==========\n";

            string ISBN = nhapChuoi("Nhap ISBN can tim: ");
            if (!ISBN.empty())
                ql.timSach(ISBN);

            break;
        }

        case 5:
        {
            cout << "\n========== DANH SACH THEO ISBN ==========\n";

            ql.inTheoISBN();

            break;
        }

        case 6:
        {
            cout << "\n========== DANH SACH THEO TEN ==========\n";

            ql.inTheoTen();

            break;
        }

        case 7:
        case 8:
        case 9:
        {
            cout << "Chuc nang nay se duoc cai dat sau!\n";

            break;
        }

        case 0:
        {
            break;
        }

        default:
        {
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";

            break;
        }
        }

    } while (chon != 0);
}

// ===================== QUAN LY DOC GIA =====================
void xuLyQuanLyDocGia(DuLieu& dl) {
    HashTable& ht = dl.docGia;
    int chon;
    do {
        menuQuanLyDocGia();
        chon = nhapLuaChon();

        switch (chon) {
        case 1: {
            docGia dg;
            dg.CMND = nhapCMND("Nhap CMND (9 hoac 12 so): ");
            if (timDocGia(ht, dg.CMND) != NULL) {
                cout << "CMND da ton tai!\n";
                break;
            }
            dg.hoten = nhapChuoi("Nhap ho ten: ");
            dg.email = nhapEmail("Nhap email: ");
            dg.sdt = nhapSDT("Nhap so dien thoai: ");
            dg.loaithe = nhapLoaiThe("Nhap loai the (Thuong/VIP): ");
            if (!cin) {
                cout << "Het du lieu nhap, huy them doc gia!\n";
                break;
            }
            themDocGia(ht, dg);
            cout << "Them doc gia thanh cong!\n";
            luuDocGia(dl);
            break;
        }
        case 2: {
            string cmnd = nhapCMND("Nhap CMND can xoa: ");
            if (xoaDocGia(ht, cmnd)) {
                cout << "Xoa doc gia thanh cong!\n";
                luuDocGia(dl);
            }
            else cout << "Khong tim thay doc gia!\n";
            break;
        }
        case 3: {
            string cmnd = nhapCMND("Nhap CMND can sua: ");
            if (timDocGia(ht, cmnd) == NULL) {
                cout << "Khong tim thay doc gia!\n";
                break;
            }
            docGia moi;
            moi.hoten = nhapChuoi("Nhap ho ten moi: ");
            moi.email = nhapEmail("Nhap email moi: ");
            moi.sdt = nhapSDT("Nhap so dien thoai moi: ");
            moi.loaithe = nhapLoaiThe("Nhap loai the moi (Thuong/VIP): ");
            if (!cin) {
                cout << "Het du lieu nhap, huy sua doc gia!\n";
                break;
            }
            suaDocGia(ht, cmnd, moi);
            cout << "Sua doc gia thanh cong!\n";
            luuDocGia(dl);
            break;
        }
        case 4: {
            string cmnd = nhapCMND("Nhap CMND can tim: ");
            NodeDocGia* p = timDocGia(ht, cmnd);
            if (p == NULL) cout << "Khong tim thay doc gia!\n";
            else {
                inMotDocGia(p->data);
                cout << endl;
            }
            break;
        }
        case 5:
            thongKeDocGia(ht);
            break;
        case 6:
            hienThiDocGia(ht);
            break;
        case 7:
            soSanhHashVaTuanTu();
            break;
        case 8:
            nhapFileDocGia(ht, FILE_DOC_GIA);
            luuDocGia(dl);
            break;
        case 9:
            xuatFileDocGia(ht, FILE_DOC_GIA);
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}

// ===================== MUON - TRA (Tuan 5: chi them/xoa/xem phieu va xem lich su) =====================
void xuLyMuonTra(DuLieu& dl) {
    int chon;
    do {
        menuMuonTraSach();
        chon = nhapLuaChon();

        switch (chon) {
        case 1: {
            cout << "\n========== THEM PHIEU MUON ==========\n";
            Phieumuon pm;
            pm.maPhieu = nhapChuoi("Nhap ma phieu: ");
            if (pm.maPhieu.empty()) break;
            if (timPhieuMuon(dl.phieuMuon, pm.maPhieu) != NULL) {
                cout << "Ma phieu da ton tai!\n";
                break;
            }
            pm.CMND = nhapCMND("Nhap CMND doc gia (9 hoac 12 so): ");
            pm.ISBN = nhapChuoi("Nhap ISBN sach: ");
            pm.ngayMuon = nhapNgay("Nhap ngay muon (dd/mm/yyyy): ");
            pm.ngayHentra = nhapNgay("Nhap ngay hen tra (dd/mm/yyyy): ");
            pm.ngayTra = "";
            pm.daTra = false;
            if (!cin) {
                cout << "Het du lieu nhap, huy them phieu muon!\n";
                break;
            }

            themPhieuMuon(dl.phieuMuon, pm);

            Giaodich gd;
            gd.maPhieu = pm.maPhieu;
            gd.CMND = pm.CMND;
            gd.ISBN = pm.ISBN;
            gd.ngayGiaoDich = pm.ngayMuon;
            gd.loaiGiaoDich = "MUON";
            themGiaoDich(dl.giaoDich, gd);

            cout << "Them phieu muon thanh cong!\n";
            luuPhieuMuon(dl);
            luuGiaoDich(dl);
            break;
        }
        case 2: {
            cout << "\n========== XOA PHIEU MUON ==========\n";
            string ma = nhapChuoi("Nhap ma phieu can xoa: ");
            if (ma.empty()) break;
            if (xoaPhieuMuon(dl.phieuMuon, ma)) {
                cout << "Xoa phieu muon thanh cong!\n";
                luuPhieuMuon(dl);
            }
            else cout << "Khong tim thay phieu muon!\n";
            break;
        }
        case 3:
            hienThiPhieuMuon(dl.phieuMuon);
            break;
        case 4:
            hienThiGiaoDich(dl.giaoDich);
            break;
        case 5:
            cout << "Chuc nang tra sach, kiem tra qua han, tinh tien phat se duoc cai dat sau!\n";
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}

// ===================== LUU TRU =====================
void xuLyLuuTru(DuLieu& dl) {
    int chon;
    do {
        menuLuuTru();
        chon = nhapLuaChon();
        switch (chon) {
        case 1:
            if (luuTatCa(dl)) cout << "Da luu tat ca du lieu.\n";
            break;
        case 2:
            docTatCa(dl);
            break;
        case 0:
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}

void xuLyMenuChuaCaiDat(void (*hienMenu)(), int maxChon, const string& thongBao) {
    int chon;
    do {
        hienMenu();
        chon = nhapLuaChon();
        if (chon >= 1 && chon <= maxChon) cout << thongBao << endl;
        else if (chon != 0) cout << "Lua chon khong hop le!\n";
    } while (chon != 0);
}

int main() {
    DuLieu dl;

    docTatCa(dl);   // tu dong doc du lieu tu file khi khoi dong

    int luaChon;
    do {
        menuChinh();
        luaChon = nhapLuaChon();

        switch (luaChon) {
        case 1:
            xuLyQuanLySach(dl);
            break;
        case 2:
            xuLyQuanLyDocGia(dl);
            break;
        case 3:
            xuLyMuonTra(dl);
            break;
        case 4:
            xuLyMenuChuaCaiDat(menuThongKeBaoCao, 5, "Chuc nang thong ke se duoc cai dat sau!");
            break;
        case 5:
            cout << "Chuc nang goi y sach se duoc cai dat sau!\n";
            break;
        case 6:
            cout << "Chuc nang tim kiem sach nang cao se duoc cai dat sau!\n";
            break;
        case 7:
            cout << "Chuc nang sao luu du lieu se duoc cai dat sau!\n";
            break;
        case 8:
            xuLyLuuTru(dl);
            break;
        case 0:
            cout << "Dang luu du lieu...\n";
            luuTatCa(dl);   // tu dong ghi du lieu ra file khi thoat
            cout << "Da thoat chuong trinh!\n";
            break;
        default:
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }
    } while (luaChon != 0);

    return 0;
}