#include "thuvien.h"

// Doi chu in hoa A-Z thanh chu thuong (chi ky tu ASCII)
static string chuThuong(string s)
{
    for (size_t i = 0; i < s.size(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    return s;
}

// true neu sach a dung truoc sach b: so ten khong phan biet hoa/thuong, trung ten thi so ISBN
static bool truocTen(const Sach& a, const Sach& b)
{
    string x = chuThuong(a.tenSach), y = chuThuong(b.tenSach);
    if (x != y)
        return x < y;
    return a.ISBN < b.ISBN;
}
NodeBST* QuanLySach::taoNodeBST(Sach s)
{
    NodeBST* p = new NodeBST;

    p->data = s;
    p->left = NULL;
    p->right = NULL;

    return p;
}
NodeBST* QuanLySach::themBST(NodeBST* p, Sach s)
{
    if (p == NULL)
        return taoNodeBST(s);

    if (truocTen(s, p->data))
        p->left = themBST(p->left, s);
    else
        p->right = themBST(p->right, s);

    return p;
}
void QuanLySach::duyetTen(NodeBST* p)
{
    if (p == NULL)
        return;

    duyetTen(p->left);

    cout << p->data.tenSach << "\t"
        << p->data.ISBN << "\t"
        << p->data.tacGia << "\t"
        << p->data.theLoai << "\t"
        << p->data.namXuatBan << "\t"
        << p->data.soLuong << endl;

    duyetTen(p->right);
}


void QuanLySach::giaiPhongBST(NodeBST* p)
{
    if (p == NULL)
        return;

    giaiPhongBST(p->left);
    giaiPhongBST(p->right);

    delete p;
}

NodeBST* QuanLySach::timMinBST(NodeBST* p)
{
    while (p->left != NULL)
        p = p->left;

    return p;
}

NodeBST* QuanLySach::xoaBST(NodeBST* p, const Sach& s)
{
    if (p == NULL)
        return NULL;

    if (truocTen(s, p->data))
        p->left = xoaBST(p->left, s);
    else if (truocTen(p->data, s))
        p->right = xoaBST(p->right, s);
    else
    {
        if (p->left == NULL || p->right == NULL)
        {
            NodeBST* con = (p->left != NULL) ? p->left : p->right;
            delete p;
            return con;
        }

        NodeBST* ke = timMinBST(p->right);
        p->data = ke->data;
        p->right = xoaBST(p->right, ke->data);
    }

    return p;
}