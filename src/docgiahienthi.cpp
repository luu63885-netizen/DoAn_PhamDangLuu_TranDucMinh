#include "thuvien.h"

void inMotDocGia(const docGia& dg) {
    cout << "\nCMND: " << dg.CMND;
    cout << "\nHo ten: " << dg.hoten;
    cout << "\nEmail: " << dg.email;
    cout << "\nSo dien thoai: " << dg.sdt;
    cout << "\nLoai the: " << dg.loaithe;
    cout << "\n--------------------------";
}

void hienThiDocGia(HashTable& ht) {
    int dem = 0;
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        for (NodeDocGia* p = ht.buckets[i]; p != NULL; p = p->next) {
            inMotDocGia(p->data);
            dem++;
        }
    }
    if (dem == 0) {
        cout << "Danh sach doc gia dang rong!" << endl;
    }
    else {
        cout << "\nTong cong: " << dem << " doc gia" << endl;
    }
}

void thongKeDocGia(HashTable& ht) {
    int soThuong = 0, soVIP = 0;

    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        for (NodeDocGia* p = ht.buckets[i]; p != NULL; p = p->next) {
            if (p->data.loaithe == "Thuong") soThuong++;
            else if (p->data.loaithe == "VIP") soVIP++;
        }
    }

    cout << "\n===== THONG KE DOC GIA =====" << endl;
    cout << "So doc gia the Thuong: " << soThuong << endl;
    cout << "So doc gia the VIP: " << soVIP << endl;
    cout << "Tong so doc gia: " << soThuong + soVIP << endl;
}
