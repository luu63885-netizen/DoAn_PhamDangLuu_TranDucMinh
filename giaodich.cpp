#include "thuvien.h"

// Mang dong luu lich su giao dich .
// Khi day, cap phat mang moi gap doi va sao chep sang => them vao cuoi
// co chi phi trung binh (amortized) O(1). Truy cap theo chi so O(1).

const int SUC_CHUA_BAN_DAU = 4;

void khoiTaoMangGD(MangGiaoDich& m) {
    m.soLuong = 0;
    m.sucChua = SUC_CHUA_BAN_DAU;
    m.data = new Giaodich[m.sucChua];
}

void giaiPhongMangGD(MangGiaoDich& m) {
    delete[] m.data;
    m.data = NULL;
    m.soLuong = 0;
    m.sucChua = 0;
}

void themGiaoDich(MangGiaoDich& m, const Giaodich& g) {
    if (m.soLuong == m.sucChua) {
        int sucChuaMoi = m.sucChua * 2;
        Giaodich* moi = new Giaodich[sucChuaMoi];
        for (int i = 0; i < m.soLuong; i++) {
            moi[i] = m.data[i];
        }
        delete[] m.data;
        m.data = moi;
        m.sucChua = sucChuaMoi;
    }
    m.data[m.soLuong] = g;
    m.soLuong++;
}

void hienThiGiaoDich(MangGiaoDich& m) {
    if (m.soLuong == 0) {
        cout << "Chua co giao dich nao!" << endl;
        return;
    }
    cout << "\n===== LICH SU GIAO DICH =====" << endl;
    for (int i = 0; i < m.soLuong; i++) {
        cout << (i + 1) << ". [" << m.data[i].ngayGiaoDich << "] "
            << m.data[i].loaiGiaoDich
            << " | Phieu: " << m.data[i].maPhieu
            << " | CMND: " << m.data[i].CMND
            << " | ISBN: " << m.data[i].ISBN << endl;
    }
    cout << "So giao dich: " << m.soLuong << " (suc chua mang: " << m.sucChua << ")" << endl;
}