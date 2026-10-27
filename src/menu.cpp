#include <iostream>
using namespace std;

// Menu chinh
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
    cout << "0. Thoat chuong trinh\n";
    cout << "========================================\n";
    cout << "Nhap lua chon: ";
}

// Menu 1: Quan ly sach
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

// Menu 2: Quan ly doc gia
void menuQuanLyDocGia() {
    cout << "\n========== QUAN LY DOC GIA ==========\n";
    cout << "1. Them doc gia\n";
    cout << "2. Xoa doc gia\n";
    cout << "3. Sua thong tin doc gia\n";
    cout << "4. Tim doc gia theo CMND\n";
    cout << "5. Thong ke doc gia theo loai the\n";
    cout << "0. Quay lai\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

// Menu 3: Muon - tra sach
void menuMuonTraSach() {
    cout << "\n========== MUON - TRA SACH ==========\n";
    cout << "1. Lap phieu muon\n";
    cout << "2. Tra sach\n";
    cout << "3. Xem danh sach phieu muon\n";
    cout << "4. Kiem tra sach qua han\n";
    cout << "5. Tinh tien phat\n";
    cout << "0. Quay lai\n";
    cout << "=====================================\n";
    cout << "Nhap lua chon: ";
}

// Menu 4: Thong ke - bao cao
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
