#include "thuvien.h"

// Danh sach lien ket don quan ly phieu muon.
// Them vao cuoi (giu thu tu lap phieu): O(1) nhat nho con tro tail.
// Tim / xoa theo ma phieu: O(n).

void khoiTaoDSPhieuMuon(DanhSachPhieuMuon& ds) {
    ds.head = NULL;
    ds.tail = NULL;
    ds.soLuong = 0;
}

void giaiPhongDSPhieuMuon(DanhSachPhieuMuon& ds) {
    NodePhieumuon* p = ds.head;
    while (p != NULL) {
        NodePhieumuon* temp = p;
        p = p->next;
        delete temp;
    }
    khoiTaoDSPhieuMuon(ds);
}

NodePhieumuon* timPhieuMuon(DanhSachPhieuMuon& ds, const string& maPhieu) {
    NodePhieumuon* p = ds.head;
    while (p != NULL) {
        if (p->data.maPhieu == maPhieu) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool themPhieuMuon(DanhSachPhieuMuon& ds, const Phieumuon& pm) {
    if (timPhieuMuon(ds, pm.maPhieu) != NULL) {
        return false;   // trung ma phieu
    }

    NodePhieumuon* node = new NodePhieumuon;
    node->data = pm;
    node->next = NULL;

    if (ds.head == NULL) {
        ds.head = node;
        ds.tail = node;
    }
    else {
        ds.tail->next = node;
        ds.tail = node;
    }
    ds.soLuong++;
    return true;
}

bool xoaPhieuMuon(DanhSachPhieuMuon& ds, const string& maPhieu) {
    NodePhieumuon* p = ds.head;
    NodePhieumuon* truoc = NULL;

    while (p != NULL) {
        if (p->data.maPhieu == maPhieu) {
            if (truoc == NULL) {
                ds.head = p->next;
            }
            else {
                truoc->next = p->next;
            }
            if (p == ds.tail) {
                ds.tail = truoc;     // xoa phan tu cuoi thi tail lui ve truoc
            }
            delete p;
            ds.soLuong--;
            return true;
        }
        truoc = p;
        p = p->next;
    }
    return false;
}

void inMotPhieuMuon(const Phieumuon& pm) {
    cout << "\nMa phieu: " << pm.maPhieu;
    cout << "\nCMND: " << pm.CMND;
    cout << "\nISBN: " << pm.ISBN;
    cout << "\nNgay muon: " << pm.ngayMuon;
    cout << "\nNgay hen tra: " << pm.ngayHentra;
    cout << "\nTrang thai: ";
    if (pm.daTra) cout << "Da tra (" << pm.ngayTra << ")";
    else cout << "Chua tra";
    cout << "\n--------------------------";
}

void hienThiPhieuMuon(DanhSachPhieuMuon& ds) {
    if (ds.head == NULL) {
        cout << "Danh sach phieu muon dang rong!" << endl;
        return;
    }
    for (NodePhieumuon* p = ds.head; p != NULL; p = p->next) {
        inMotPhieuMuon(p->data);
    }
    cout << "\nTong cong: " << ds.soLuong << " phieu muon" << endl;
}