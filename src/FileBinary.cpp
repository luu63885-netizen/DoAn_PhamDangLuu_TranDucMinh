#include "thuvien.h"
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
// ============================================================
//                 DOC / GHI FILE NHI PHAN
// ============================================================

static const char MAGIC_SACH[4] = { 'T', 'V', 'S', 'A' };
static const char MAGIC_DOCGIA[4] = { 'T', 'V', 'D', 'G' };
static const char MAGIC_PHIEUMUON[4] = { 'T', 'V', 'P', 'M' };
static const char MAGIC_GIAODICH[4] = { 'T', 'V', 'G', 'D' };

static const int32_t PHIEN_BAN = 1;
static const uint32_t DO_DAI_CHUOI_TOI_DA = 100000;
static const int32_t SO_BAN_GHI_TOI_DA = 10000000;

// ---------- ham co ban ----------

static bool ghiSo(ofstream& f, int32_t v) {
    f.write(reinterpret_cast<const char*>(&v), sizeof(v));
    return f.good();
}

static bool docSo(ifstream& f, int32_t& v) {
    f.read(reinterpret_cast<char*>(&v), sizeof(v));
    return f.good();
}

static bool ghiChuoi(ofstream& f, const string& s) {
    uint32_t n = (uint32_t)s.size();
    f.write(reinterpret_cast<const char*>(&n), sizeof(n));
    if (n > 0) {
        f.write(s.data(), n);
    }
    return f.good();
}

static bool docChuoi(ifstream& f, string& s) {
    uint32_t n = 0;
    f.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (!f.good() || n > DO_DAI_CHUOI_TOI_DA) {
        return false;
    }
    s.assign(n, '\0');
    if (n > 0) {
        f.read(&s[0], n);
        if (!f.good()) return false;
    }
    return true;
}

static bool ghiDauFile(ofstream& f, const char magic[4], int32_t soBanGhi) {
    f.write(magic, 4);
    return ghiSo(f, PHIEN_BAN) && ghiSo(f, soBanGhi);
}

static bool docDauFile(ifstream& f, const char magic[4], int32_t& soBanGhi) {
    char doc[4];
    f.read(doc, 4);
    if (!f.good()) return false;
    for (int i = 0; i < 4; i++) {
        if (doc[i] != magic[i]) return false;
    }
    int32_t phienBan = 0;
    if (!docSo(f, phienBan) || phienBan != PHIEN_BAN) return false;
    if (!docSo(f, soBanGhi)) return false;
    return soBanGhi >= 0 && soBanGhi <= SO_BAN_GHI_TOI_DA;
}

// Dong file tam, thay file that bang file tam. Tra ve true neu thanh cong.
static bool hoanTatGhi(ofstream& f, const string& tenTam, const string& tenFile) {
    bool ok = f.good();
    f.close();
    ok = ok && !f.fail();
    if (!ok) {
        remove(tenTam.c_str());
        return false;
    }
#ifdef _WIN32
    // Thay file cu bang file tam trong 1 thao tac, khong co luc nao thieu file
    return MoveFileExA(tenTam.c_str(), tenFile.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    return rename(tenTam.c_str(), tenFile.c_str()) == 0;   // Linux/macOS: rename ghi de nguyen tu
#endif
}

// ---------- tung kieu ban ghi ----------

static bool ghiSach(ofstream& f, const Sach& s) {
    return ghiChuoi(f, s.ISBN) && ghiChuoi(f, s.tenSach) && ghiChuoi(f, s.tacGia)
        && ghiChuoi(f, s.theLoai) && ghiSo(f, s.namXuatBan) && ghiSo(f, s.soLuong);
}

static bool docSach(ifstream& f, Sach& s) {
    int32_t nam = 0, soLuong = 0;
    if (!(docChuoi(f, s.ISBN) && docChuoi(f, s.tenSach) && docChuoi(f, s.tacGia)
        && docChuoi(f, s.theLoai) && docSo(f, nam) && docSo(f, soLuong))) {
        return false;
    }
    s.namXuatBan = nam;
    s.soLuong = soLuong;
    return true;
}

static bool ghiDocGia(ofstream& f, const docGia& d) {
    return ghiChuoi(f, d.CMND) && ghiChuoi(f, d.hoten) && ghiChuoi(f, d.email)
        && ghiChuoi(f, d.sdt) && ghiChuoi(f, d.loaithe);
}

static bool docDocGia(ifstream& f, docGia& d) {
    return docChuoi(f, d.CMND) && docChuoi(f, d.hoten) && docChuoi(f, d.email)
        && docChuoi(f, d.sdt) && docChuoi(f, d.loaithe);
}

static bool ghiPhieuMuon(ofstream& f, const Phieumuon& p) {
    return ghiChuoi(f, p.maPhieu) && ghiChuoi(f, p.CMND) && ghiChuoi(f, p.ISBN)
        && ghiChuoi(f, p.ngayMuon) && ghiChuoi(f, p.ngayHentra) && ghiChuoi(f, p.ngayTra)
        && ghiSo(f, p.daTra ? 1 : 0);
}

static bool docPhieuMuon(ifstream& f, Phieumuon& p) {
    int32_t daTra = 0;
    if (!(docChuoi(f, p.maPhieu) && docChuoi(f, p.CMND) && docChuoi(f, p.ISBN)
        && docChuoi(f, p.ngayMuon) && docChuoi(f, p.ngayHentra) && docChuoi(f, p.ngayTra)
        && docSo(f, daTra))) {
        return false;
    }
    p.daTra = (daTra != 0);
    return true;
}

static bool ghiGiaoDich(ofstream& f, const Giaodich& g) {
    return ghiChuoi(f, g.maPhieu) && ghiChuoi(f, g.CMND) && ghiChuoi(f, g.ISBN)
        && ghiChuoi(f, g.ngayGiaoDich) && ghiChuoi(f, g.loaiGiaoDich);
}

static bool docGiaoDich(ifstream& f, Giaodich& g) {
    return docChuoi(f, g.maPhieu) && docChuoi(f, g.CMND) && docChuoi(f, g.ISBN)
        && docChuoi(f, g.ngayGiaoDich) && docChuoi(f, g.loaiGiaoDich);
}

// ============================================================
// SACH (duyet in-order cay AVL de ghi => file da sap theo ISBN)
// ============================================================

int QuanLySach::demAVL(NodeAVL* p) {
    if (p == NULL) return 0;
    return 1 + demAVL(p->left) + demAVL(p->right);
}

void QuanLySach::ghiAVL(NodeAVL* p, ofstream& f) {
    if (p == NULL || !f.good()) return;
    ghiAVL(p->left, f);
    ghiSach(f, p->data);
    ghiAVL(p->right, f);
}

void QuanLySach::xoaHet() {
    giaiPhongAVL(rootAVL);
    giaiPhongBST(rootBST);
    rootAVL = NULL;
    rootBST = NULL;
}

bool QuanLySach::luuNhiPhan(const string& tenFile) {
    string tenTam = tenFile + ".tmp";
    ofstream f(tenTam.c_str(), ios::binary);
    if (!f.is_open()) return false;

    ghiDauFile(f, MAGIC_SACH, demAVL(rootAVL));
    ghiAVL(rootAVL, f);
    return hoanTatGhi(f, tenTam, tenFile);
}

KetQuaDoc QuanLySach::docNhiPhan(const string& tenFile, int& soDoc) {
    soDoc = 0;
    ifstream f(tenFile.c_str(), ios::binary);
    if (!f.is_open()) return DOC_KHONG_CO_FILE;

    int32_t n = 0;
    if (!docDauFile(f, MAGIC_SACH, n)) return DOC_FILE_LOI;

    vector<Sach> ds;
    for (int32_t i = 0; i < n; i++) {
        Sach s;
        if (!docSach(f, s)) return DOC_FILE_LOI;
        ds.push_back(s);
    }

    xoaHet();
    for (size_t i = 0; i < ds.size(); i++) {
        if (timAVL(rootAVL, ds[i].ISBN) == NULL) {   // bo qua ISBN trung (neu file bi sua tay)
            rootAVL = themAVL(rootAVL, ds[i]);
            rootBST = themBST(rootBST, ds[i]);
            soDoc++;
        }
    }
    return DOC_OK;
}

// ============================================================
// DOC GIA (duyet tung bucket cua bang bam)
// ============================================================

bool luuNhiPhanDocGia(HashTable& ht, const string& tenFile) {
    string tenTam = tenFile + ".tmp";
    ofstream f(tenTam.c_str(), ios::binary);
    if (!f.is_open()) return false;

    int dem = 0;
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        for (NodeDocGia* p = ht.buckets[i]; p != NULL; p = p->next) dem++;
    }

    ghiDauFile(f, MAGIC_DOCGIA, dem);
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        for (NodeDocGia* p = ht.buckets[i]; p != NULL; p = p->next) {
            ghiDocGia(f, p->data);
        }
    }
    return hoanTatGhi(f, tenTam, tenFile);
}

KetQuaDoc docNhiPhanDocGia(HashTable& ht, const string& tenFile, int& soDoc) {
    soDoc = 0;
    ifstream f(tenFile.c_str(), ios::binary);
    if (!f.is_open()) return DOC_KHONG_CO_FILE;

    int32_t n = 0;
    if (!docDauFile(f, MAGIC_DOCGIA, n)) return DOC_FILE_LOI;

    vector<docGia> ds;
    for (int32_t i = 0; i < n; i++) {
        docGia d;
        if (!docDocGia(f, d)) return DOC_FILE_LOI;
        ds.push_back(d);
    }

    giaiPhongHashTable(ht);
    for (size_t i = 0; i < ds.size(); i++) {
        if (themDocGia(ht, ds[i])) soDoc++;
    }
    return DOC_OK;
}

// ============================================================
// PHIEU MUON (duyet danh sach lien ket tu head)
// ============================================================

bool luuNhiPhanPhieuMuon(DanhSachPhieuMuon& ds, const string& tenFile) {
    string tenTam = tenFile + ".tmp";
    ofstream f(tenTam.c_str(), ios::binary);
    if (!f.is_open()) return false;

    ghiDauFile(f, MAGIC_PHIEUMUON, ds.soLuong);
    for (NodePhieumuon* p = ds.head; p != NULL; p = p->next) {
        ghiPhieuMuon(f, p->data);
    }
    return hoanTatGhi(f, tenTam, tenFile);
}

KetQuaDoc docNhiPhanPhieuMuon(DanhSachPhieuMuon& ds, const string& tenFile, int& soDoc) {
    soDoc = 0;
    ifstream f(tenFile.c_str(), ios::binary);
    if (!f.is_open()) return DOC_KHONG_CO_FILE;

    int32_t n = 0;
    if (!docDauFile(f, MAGIC_PHIEUMUON, n)) return DOC_FILE_LOI;

    vector<Phieumuon> v;
    for (int32_t i = 0; i < n; i++) {
        Phieumuon p;
        if (!docPhieuMuon(f, p)) return DOC_FILE_LOI;
        v.push_back(p);
    }

    giaiPhongDSPhieuMuon(ds);
    for (size_t i = 0; i < v.size(); i++) {
        if (themPhieuMuon(ds, v[i])) soDoc++;
    }
    return DOC_OK;
}

// ============================================================
// GIAO DICH (duyet mang dong)
// ============================================================

bool luuNhiPhanGiaoDich(MangGiaoDich& m, const string& tenFile) {
    string tenTam = tenFile + ".tmp";
    ofstream f(tenTam.c_str(), ios::binary);
    if (!f.is_open()) return false;

    ghiDauFile(f, MAGIC_GIAODICH, m.soLuong);
    for (int i = 0; i < m.soLuong; i++) {
        ghiGiaoDich(f, m.data[i]);
    }
    return hoanTatGhi(f, tenTam, tenFile);
}

KetQuaDoc docNhiPhanGiaoDich(MangGiaoDich& m, const string& tenFile, int& soDoc) {
    soDoc = 0;
    ifstream f(tenFile.c_str(), ios::binary);
    if (!f.is_open()) return DOC_KHONG_CO_FILE;

    int32_t n = 0;
    if (!docDauFile(f, MAGIC_GIAODICH, n)) return DOC_FILE_LOI;

    vector<Giaodich> v;
    for (int32_t i = 0; i < n; i++) {
        Giaodich g;
        if (!docGiaoDich(f, g)) return DOC_FILE_LOI;
        v.push_back(g);
    }

    giaiPhongMangGD(m);
    khoiTaoMangGD(m);
    for (size_t i = 0; i < v.size(); i++) {
        themGiaoDich(m, v[i]);
        soDoc++;
    }
    return DOC_OK;
}

// ============================================================
// TOAN BO DU LIEU
// ============================================================

DuLieu::DuLieu() {
    khoiTaoHashTable(docGia);
    khoiTaoDSPhieuMuon(phieuMuon);
    khoiTaoMangGD(giaoDich);
}

DuLieu::~DuLieu() {
    giaiPhongHashTable(docGia);
    giaiPhongDSPhieuMuon(phieuMuon);
    giaiPhongMangGD(giaoDich);
}

static bool baoLoiGhi(bool ok, const string& tenFile) {
    if (!ok) {
        cout << "Khong the ghi file " << tenFile << "!" << endl;
    }
    return ok;
}

bool luuSach(DuLieu& dl) {
    return baoLoiGhi(dl.sach.luuNhiPhan(FILE_SACH_DAT), FILE_SACH_DAT);
}

bool luuDocGia(DuLieu& dl) {
    return baoLoiGhi(luuNhiPhanDocGia(dl.docGia, FILE_DOCGIA_DAT), FILE_DOCGIA_DAT);
}

bool luuPhieuMuon(DuLieu& dl) {
    return baoLoiGhi(luuNhiPhanPhieuMuon(dl.phieuMuon, FILE_PHIEUMUON_DAT), FILE_PHIEUMUON_DAT);
}

bool luuGiaoDich(DuLieu& dl) {
    return baoLoiGhi(luuNhiPhanGiaoDich(dl.giaoDich, FILE_GIAODICH_DAT), FILE_GIAODICH_DAT);
}

bool luuTatCa(DuLieu& dl) {
    bool a = luuSach(dl);
    bool b = luuDocGia(dl);
    bool c = luuPhieuMuon(dl);
    bool d = luuGiaoDich(dl);
    return a && b && c && d;
}

// In ket qua doc. File hong thi doi ten thanh <ten>.loi de khong bi ghi de mat,
// du lieu dang co trong bo nho duoc giu nguyen.
static void baoKetQuaDoc(KetQuaDoc kq, const string& tenFile, const string& nhan, int so) {
    if (kq == DOC_OK) {
        cout << "Da doc " << so << " " << nhan << " tu " << tenFile << "." << endl;
    }
    else if (kq == DOC_KHONG_CO_FILE) {
        cout << "Chua co file " << tenFile << " (se duoc tao khi luu)." << endl;
    }
    else {
        string tenLoi = tenFile + ".loi";
        remove(tenLoi.c_str());
        rename(tenFile.c_str(), tenLoi.c_str());
        cout << "File " << tenFile << " bi hong hoac sai dinh dang, da doi ten thanh "
            << tenLoi << ". Du lieu " << nhan << " trong bo nho giu nguyen." << endl;
    }
}

void docTatCa(DuLieu& dl) {
    int so = 0;
    KetQuaDoc kq;

    kq = dl.sach.docNhiPhan(FILE_SACH_DAT, so);
    baoKetQuaDoc(kq, FILE_SACH_DAT, "sach", so);

    kq = docNhiPhanDocGia(dl.docGia, FILE_DOCGIA_DAT, so);
    baoKetQuaDoc(kq, FILE_DOCGIA_DAT, "doc gia", so);

    kq = docNhiPhanPhieuMuon(dl.phieuMuon, FILE_PHIEUMUON_DAT, so);
    baoKetQuaDoc(kq, FILE_PHIEUMUON_DAT, "phieu muon", so);

    kq = docNhiPhanGiaoDich(dl.giaoDich, FILE_GIAODICH_DAT, so);
    baoKetQuaDoc(kq, FILE_GIAODICH_DAT, "giao dich", so);
}