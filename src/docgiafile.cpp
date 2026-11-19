#include "thuvien.h"

void nhapFileDocGia(HashTable& ht, const string& tenFile) {
    ifstream file(tenFile.c_str());
    if (!file.is_open()) {
        cout << "Khong mo duoc file " << tenFile << "!" << endl;
        return;
    }

    vector<string> dong;
    string s;
    while (getline(file, s)) {
        dong.push_back(catKhoangTrang(s));
    }
    file.close();

    int soThem = 0, soTrung = 0, soSai = 0, soDongThua = 0;
    size_t n = dong.size();
    size_t i = 0;

    while (i < n) {
        if (dong[i].empty()) {
            i++;
            continue;
        }
        if (!laCMNDHopLe(dong[i])) {
            soDongThua++;
            i++;
            continue;
        }
        if (i + 4 >= n) {
            soSai++;
            break;
        }

        docGia dg;
        dg.CMND = dong[i];
        dg.hoten = dong[i + 1];
        dg.email = dong[i + 2];
        dg.sdt = dong[i + 3];
        dg.loaithe = dong[i + 4];

        if (dg.hoten.empty() || !laEmailHopLe(dg.email) ||
            !laSDTHopLe(dg.sdt) || !laLoaiTheHopLe(dg.loaithe)) {
            soSai++;
            i += 5;
            continue;
        }

        if (themDocGia(ht, dg)) soThem++;
        else soTrung++;
        i += 5;
    }

    cout << "Da them " << soThem << " doc gia";
    if (soTrung > 0) cout << ", bo qua " << soTrung << " trung CMND";
    if (soSai > 0) cout << ", bo qua " << soSai << " ban ghi sai du lieu";
    if (soDongThua > 0) cout << ", bo qua " << soDongThua << " dong khong hop le";
    cout << "." << endl;
}

void xuatFileDocGia(HashTable& ht, const string& tenFile) {
    ofstream file(tenFile.c_str());
    if (!file.is_open()) {
        cout << "Khong mo duoc file " << tenFile << "!" << endl;
        return;
    }

    int dem = 0;
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        for (NodeDocGia* p = ht.buckets[i]; p != NULL; p = p->next) {
            file << p->data.CMND << endl;
            file << p->data.hoten << endl;
            file << p->data.email << endl;
            file << p->data.sdt << endl;
            file << p->data.loaithe << endl;
            dem++;
        }
    }
    file.close();
    cout << "Da xuat " << dem << " doc gia ra file " << tenFile << "." << endl;
}
