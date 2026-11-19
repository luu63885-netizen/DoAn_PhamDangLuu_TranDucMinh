#include "thuvien.h"

int QuanLySach::chieuCao(NodeAVL* p) {
    if (p == NULL)
        return 0;
    return p->height;
}

int QuanLySach::doLech(NodeAVL* p)
{
    if (p == NULL)
        return 0;

    return chieuCao(p->left) - chieuCao(p->right);
}

NodeAVL* QuanLySach::taoNodeAVL(Sach s) {
    NodeAVL* p = new NodeAVL;
    p->data = s;
    p->left = NULL;
    p->right = NULL;
    p->height = 1;
    return p;
}

NodeAVL* QuanLySach::xoayPhai(NodeAVL* p)
{
    NodeAVL* q = p->left;
    NodeAVL* T2 = q->right;

    q->right = p;
    p->left = T2;

    p->height = 1 + max(chieuCao(p->left), chieuCao(p->right));
    q->height = 1 + max(chieuCao(q->left), chieuCao(q->right));

    return q;
}

NodeAVL* QuanLySach::xoayTrai(NodeAVL* p)
{
    NodeAVL* q = p->right;
    NodeAVL* T2 = q->left;

    q->left = p;
    p->right = T2;

    p->height = 1 + max(chieuCao(p->left), chieuCao(p->right));
    q->height = 1 + max(chieuCao(q->left), chieuCao(q->right));

    return q;
}

NodeAVL* QuanLySach::canBang(NodeAVL* p)
{
    if (p == NULL)
        return p;

    p->height = 1 + max(chieuCao(p->left), chieuCao(p->right));

    int balance = doLech(p);


    if (balance > 1 && doLech(p->left) >= 0)
        return xoayPhai(p);


    if (balance > 1 && doLech(p->left) < 0)
    {
        p->left = xoayTrai(p->left);
        return xoayPhai(p);
    }
    if (balance < -1 && doLech(p->right) <= 0)
        return xoayTrai(p);
    if (balance < -1 && doLech(p->right) > 0)
    {
        p->right = xoayPhai(p->right);
        return xoayTrai(p);
    }

    return p;
}
NodeAVL* QuanLySach::themAVL(NodeAVL* p, Sach s)
{
    if (p == NULL)
        return taoNodeAVL(s);

    if (s.ISBN < p->data.ISBN)
        p->left = themAVL(p->left, s);

    else if (s.ISBN > p->data.ISBN)
        p->right = themAVL(p->right, s);

    else
        return p;

    return canBang(p);
}


NodeAVL* QuanLySach::timMin(NodeAVL* p)
{
    while (p->left != NULL)
        p = p->left;

    return p;
}


NodeAVL* QuanLySach::xoaAVL(NodeAVL* p, string ISBN)
{
    if (p == NULL)
        return NULL;

    if (ISBN < p->data.ISBN)
        p->left = xoaAVL(p->left, ISBN);

    else if (ISBN > p->data.ISBN)
        p->right = xoaAVL(p->right, ISBN);

    else
    {

        if (p->left == NULL || p->right == NULL)
        {
            NodeAVL* temp;

            if (p->left != NULL)
                temp = p->left;
            else
                temp = p->right;

            delete p;

            return temp;
        }


        NodeAVL* temp = timMin(p->right);

        p->data = temp->data;

        p->right = xoaAVL(p->right, temp->data.ISBN);
    }

    return canBang(p);
}


NodeAVL* QuanLySach::timAVL(NodeAVL* p, string ISBN)
{
    if (p == NULL)
        return NULL;

    if (ISBN == p->data.ISBN)
        return p;

    if (ISBN < p->data.ISBN)
        return timAVL(p->left, ISBN);

    return timAVL(p->right, ISBN);
}


void QuanLySach::duyetISBN(NodeAVL* p)
{
    if (p == NULL)
        return;

    duyetISBN(p->left);

    cout << p->data.ISBN << "\t"
        << p->data.tenSach << "\t"
        << p->data.tacGia << "\t"
        << p->data.theLoai << "\t"
        << p->data.namXuatBan << "\t"
        << p->data.soLuong << endl;

    duyetISBN(p->right);
}


void QuanLySach::giaiPhongAVL(NodeAVL* p)
{
    if (p == NULL)
        return;

    giaiPhongAVL(p->left);
    giaiPhongAVL(p->right);

    delete p;
}
