#include "thuvien.h"

void menuChinh() {
    cout << "\n========================================\n";
    cout << "           QUAN LY THU VIEN             \n";
    cout << "========================================\n";
    cout << "1. Quan ly sach\n";
    cout << "2. Quan ly doc gia\n";
    cout << "3. Quan ly muon - tra sach\n";
    cout << "4. Thong ke - bao cao\n";
    cout << "5. Goi y sach\n";
    cout << "6. Tim kiem sach nang cao\n";
    cout << "7. Sao luu du lieu\n";
    cout << "8. Luu tru du lieu (file nhi phan)\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "========================================\n";
    cout << "Nhap lua chon: ";
}

void menuQuanLySach() {
    cout << "\n========== QUAN LY SACH ==========\n";
    cout << "1. Them sach\n";
    cout << "2. Xoa sach\n";
    cout << "3. Sua thong tin sach\n";
    cout << "4. Tim sach theo ISBN\n";
    cout << "5. In danh sach sach theo ISBN\n";
    cout << "6. In danh sach sach theo ten\n";
    cout << "7. Tim sach theo tien to ten\n";
    cout << "8. Nhap danh sach sach\n";
    cout << "9. Xuat danh sach sach\n";
    cout << "0. Quay lai\n";
    cout << "==================================\n";
    cout << "Nhap lua chon: ";
}

void menuQuanLyDocGia() {
    cout << "\n========== QUAN LY DOC GIA ==========\n";
    cout << "1. Them doc gia\n";
    cout << "2. Xoa doc gia\n";
    cout << "3. Sua thong tin doc gia\n";
    cout << "4. Tim doc gia theo CMND\n";
    cout << "5. Thong ke doc gia theo loai the\n";
    cout << "6. Hien thi danh sach doc gia\n";
    cout << "7. So sanh Hash Table va tim tuan tu\n";
    cout << "8. Nhap danh sach doc gia tu file (.txt)\n";
    cout << "9. Xuat danh sach doc gia ra file (.txt)\n";
    cout << "0. Quay lai\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

void menuMuonTraSach() {
    cout << "\n========== MUON - TRA SACH ==========\n";
    cout << "1. Them phieu muon (co ban)\n";
    cout << "2. Xoa phieu muon\n";
    cout << "3. Xem danh sach phieu muon\n";
    cout << "4. Xem lich su giao dich\n";
    cout << "5. Tra sach / qua han / tien phat\n";
    cout << "0. Quay lai\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

void menuLuuTru() {
    cout << "\n========== LUU TRU DU LIEU ==========\n";
    cout << "1. Luu tat ca du lieu ra file ngay\n";
    cout << "2. Doc lai tat ca du lieu tu file\n";
    cout << "0. Quay lai\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

void menuThongKeBaoCao() {
    cout << "\n========== THONG KE - BAO CAO ==========\n";
    cout << "1. Thong ke luot muon theo thang\n";
    cout << "2. Thong ke luot muon theo the loai\n";
    cout << "3. Top 10 sach duoc muon nhieu nhat\n";
    cout << "4. Top 10 doc gia muon nhieu nhat\n";
    cout << "5. Xuat bao cao ra file\n";
    cout << "0. Quay lai\n";
    cout << "========================================\n";
    cout << "Nhap lua chon: ";
}