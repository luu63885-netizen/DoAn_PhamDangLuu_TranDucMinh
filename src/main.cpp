#include <iostream>
using namespace std;

// Khai bao cac ham menu
void menuChinh();
void menuQuanLySach();
void menuQuanLyDocGia();
void menuMuonTraSach();
void menuThongKeBaoCao();

int main() {
    int luaChon;

    do {
        menuChinh();
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            int chon;
            do {
                menuQuanLySach();
                cin >> chon;

                if (chon >= 1 && chon <= 9) {
                    cout << "Chuc nang quan ly sach se duoc cai dat sau!\n";
                }
                else if (chon != 0) {
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chon != 0);
            break;
        }

        case 2: {
            int chon;
            do {
                menuQuanLyDocGia();
                cin >> chon;

                if (chon >= 1 && chon <= 5) {
                    cout << "Chuc nang quan ly doc gia se duoc cai dat sau!\n";
                }
                else if (chon != 0) {
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chon != 0);
            break;
        }

        case 3: {
            int chon;
            do {
                menuMuonTraSach();
                cin >> chon;

                if (chon >= 1 && chon <= 5) {
                    cout << "Chuc nang muon - tra se duoc cai dat sau!\n";
                }
                else if (chon != 0) {
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chon != 0);
            break;
        }

        case 4: {
            int chon;
            do {
                menuThongKeBaoCao();
                cin >> chon;

                if (chon >= 1 && chon <= 5) {
                    cout << "Chuc nang thong ke se duoc cai dat sau!\n";
                }
                else if (chon != 0) {
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chon != 0);
            break;
        }

        case 5:
            cout << "Chuc nang goi y sach se duoc cai dat sau!\n";
            break;

        case 6:
            cout << "Chuc nang tim kiem sach nang cao se duoc cai dat sau!\n";
            break;

        case 7:
            cout << "Chuc nang sao luu du lieu se duoc cai dat sau!\n";
            break;

        case 0:
            cout << "Da thoat chuong trinh!\n";
            break;

        default:
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

    } while (luaChon != 0);

    return 0;
}