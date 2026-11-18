#include "thuvien.h"

// ===================== HAM PHU =====================

// Kiem tra chuoi chi gom cac chu so 0-9 (va khong rong)
static bool toanChuSo(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

// Doi chuoi toan chu so thanh so nguyen (chi goi sau khi toanChuSo dung)
static int chuyenSo(const string& s) {
    int kq = 0;
    for (size_t i = 0; i < s.length(); i++) {
        kq = kq * 10 + (s[i] - '0');
    }
    return kq;
}

// Bo khoang trang o dau va cuoi chuoi
string catKhoangTrang(const string& s) {
    size_t dau = s.find_first_not_of(" \t\r\n");
    if (dau == string::npos) return "";
    size_t cuoi = s.find_last_not_of(" \t\r\n");
    return s.substr(dau, cuoi - dau + 1);
}

// Doc mot dong tu ban phim va bo khoang trang thua
static string docDong() {
    string s;
    getline(cin, s);
    return catKhoangTrang(s);
}

// Lay nam hien tai tu dong ho he thong
int namHienTai() {
    time_t bayGio = time(NULL);
    struct tm* t = localtime(&bayGio);
    return t->tm_year + 1900;
}

// ===================== KIEM TRA DU LIEU =====================

// CMND: 9 hoac 12 chu so
bool laCMNDHopLe(const string& s) {
    return toanChuSo(s) && (s.length() == 9 || s.length() == 12);
}

// Email: co dung 1 dau '@', khong o dau/cuoi, khong co khoang trang
bool laEmailHopLe(const string& s) {
    size_t at = s.find('@');
    if (at == string::npos || at == 0 || at + 1 >= s.length()) return false;
    if (s.find('@', at + 1) != string::npos) return false;
    if (s.find(' ') != string::npos) return false;
    return true;
}

// So dien thoai: 10 hoac 11 chu so
bool laSDTHopLe(const string& s) {
    return toanChuSo(s) && (s.length() == 10 || s.length() == 11);
}

// Loai the: chi nhan "Thuong" hoac "VIP"
bool laLoaiTheHopLe(const string& s) {
    return s == "Thuong" || s == "VIP";
}

// Ngay dang dd/mm/yyyy, co kiem tra so ngay trong thang va nam nhuan
bool laNgayHopLe(const string& s) {
    if (s.length() != 10 || s[2] != '/' || s[5] != '/') return false;

    string ngay = s.substr(0, 2);
    string thang = s.substr(3, 2);
    string nam = s.substr(6, 4);
    if (!toanChuSo(ngay) || !toanChuSo(thang) || !toanChuSo(nam)) return false;

    int d = chuyenSo(ngay);
    int m = chuyenSo(thang);
    int y = chuyenSo(nam);
    if (y < 1900 || y > 2100 || m < 1 || m > 12 || d < 1) return false;

    int soNgay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        soNgay[1] = 29;   // nam nhuan
    }
    return d <= soNgay[m - 1];
}

// ===================== NHAP DU LIEU =====================

// Doc lua chon menu; nhap sai tra ve -1, het du lieu nhap tra ve 0 (de thoat menu)
int nhapLuaChon() {
    if (!cin) return 0;
    string s = docDong();
    if (!toanChuSo(s) || s.length() > 6) return -1;
    return chuyenSo(s);
}

// Nhap chuoi, khong cho de trong
string nhapChuoi(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (!s.empty()) return s;
        if (!cin) return "";
        cout << "Khong duoc de trong!\n";
    }
}

// Nhap so nguyen trong khoang [nhoNhat, lonNhat]
int nhapSo(const string& loiNhac, int nhoNhat, int lonNhat) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (toanChuSo(s) && s.length() <= 9) {
            int v = chuyenSo(s);
            if (v >= nhoNhat && v <= lonNhat) return v;
        }
        if (!cin) return nhoNhat;
        cout << "Vui long nhap so nguyen tu " << nhoNhat << " den " << lonNhat << "!\n";
    }
}

string nhapCMND(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (laCMNDHopLe(s)) return s;
        if (!cin) return "";
        cout << "CMND phai gom 9 hoac 12 chu so!\n";
    }
}

string nhapEmail(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (laEmailHopLe(s)) return s;
        if (!cin) return "";
        cout << "Email khong hop le (vd: abc@gmail.com)!\n";
    }
}

string nhapSDT(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (laSDTHopLe(s)) return s;
        if (!cin) return "";
        cout << "So dien thoai phai gom 10 hoac 11 chu so!\n";
    }
}

string nhapLoaiThe(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (laLoaiTheHopLe(s)) return s;
        if (!cin) return "";
        cout << "Loai the chi duoc la Thuong hoac VIP!\n";
    }
}

string nhapNgay(const string& loiNhac) {
    while (true) {
        cout << loiNhac;
        string s = docDong();
        if (laNgayHopLe(s)) return s;
        if (!cin) return "";
        cout << "Ngay khong hop le (dinh dang dd/mm/yyyy, vd: 18/11/2026)!\n";
    }
}