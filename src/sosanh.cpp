#include "thuvien.h"

int timTuanTu(docGia* mang, int n, const string& CMND) {
    for (int i = 0; i < n; i++) {
        if (mang[i].CMND == CMND) {
            return i;
        }
    }
    return -1;
}

void soSanhHashVaTuanTu() {
    int cacSoLuong[4] = { 1000, 5000, 10000, 50000 };
    int soLanTimHash = 100000;
    int soLanTimTuanTu = 1000;
    double tiSoCuoi = 0;      
    cout << "\n===== SO SANH HASH TABLE VA TIM TUAN TU =====" << endl;
    cout << "Thoi gian trung binh cho 1 lan tim (don vi: micro giay)" << endl;
    cout << "(Bang bam co dinh " << KICH_THUOC_BANG_BAM << " bucket, chua rehash)\n" << endl;
    cout << "      n | Load factor |    Hash |  Tuan tu | Nhanh hon (lan)" << endl;
    cout << "--------+-------------+---------+----------+----------------" << endl;

    for (int lan = 0; lan < 4; lan++) {
        int n = cacSoLuong[lan];


        docGia* mang = new docGia[n];
        HashTable bang;
        khoiTaoHashTable(bang);
        for (int i = 0; i < n; i++) {
            mang[i].CMND = to_string(100000000 + i * 7);
            mang[i].hoten = "Doc gia " + to_string(i);
            themDocGia(bang, mang[i]);
        }

        volatile int ketQua = 0;

        clock_t batDau = clock();
        for (int i = 0; i < soLanTimHash; i++) {
            string cmndCanTim = mang[(i * 37) % n].CMND;
            if (timDocGia(bang, cmndCanTim) != NULL) ketQua = ketQua + 1;
        }
        double giayHash = (double)(clock() - batDau) / CLOCKS_PER_SEC;

        batDau = clock();
        for (int i = 0; i < soLanTimTuanTu; i++) {
            string cmndCanTim = mang[(i * 37) % n].CMND;
            if (timTuanTu(mang, n, cmndCanTim) >= 0) ketQua = ketQua + 1;
        }
        double giayTuanTu = (double)(clock() - batDau) / CLOCKS_PER_SEC;
        double usMotLanHash = giayHash * 1000000 / soLanTimHash;
        double usMotLanTuanTu = giayTuanTu * 1000000 / soLanTimTuanTu;
        double soLanNhanhHon = 0;
        if (usMotLanHash > 0) {
            soLanNhanhHon = usMotLanTuanTu / usMotLanHash;
        }

        double loadFactor = (double)n / KICH_THUOC_BANG_BAM;
        tiSoCuoi = soLanNhanhHon;
        printf("%7d | %11.2f | %7.3f | %8.3f | %14.1f\n", n, loadFactor, usMotLanHash, usMotLanTuanTu, soLanNhanhHon);

        giaiPhongHashTable(bang);
        delete[] mang;
    }

    cout << "\nNhan xet: do phuc tap tim kiem cua Hash la O(1 + load factor)." << endl;
    cout << "Bang co dinh so bucket nen n cang lon, chuoi cang dai (load factor tang)" << endl;
    cout << "va Hash khong con O(1) thuan tuy, nhung van nhanh hon tim tuan tu O(n)." << endl;
    cout << "Voi n = " << cacSoLuong[3] << ", Hash nhanh hon tim tuan tu khoang " << tiSoCuoi << " lan." << endl;
    cout << "Huong cai thien: rehash (tang so bucket) khi load factor vuot nguong." << endl;
}
