#include "thuvien.h"

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

    if (s.tenSach < p->data.tenSach ||
        (s.tenSach == p->data.tenSach &&
            s.ISBN < p->data.ISBN))
    {
        p->left = themBST(p->left, s);
    }
    else
    {
        p->right = themBST(p->right, s);
    }

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

    if (s.tenSach < p->data.tenSach ||
        (s.tenSach == p->data.tenSach && s.ISBN < p->data.ISBN))
    {
        p->left = xoaBST(p->left, s);
    }
    else if (s.tenSach > p->data.tenSach ||
        (s.tenSach == p->data.tenSach && s.ISBN > p->data.ISBN))
    {
        p->right = xoaBST(p->right, s);
    }
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