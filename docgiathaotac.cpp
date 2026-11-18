#include "thuvien.h"

bool themDocGia(HashTable& ht, const docGia& dg) {
    if (timDocGia(ht, dg.CMND) != NULL) {
        return false;
    }

    int vitri = hamBam(dg.CMND);
    NodeDocGia* node = new NodeDocGia;
    node->data = dg;
    node->next = ht.buckets[vitri];
    ht.buckets[vitri] = node;
    return true;
}

NodeDocGia* timDocGia(HashTable& ht, const string& CMND) {
    NodeDocGia* p = ht.buckets[hamBam(CMND)];
    while (p != NULL) {
        if (p->data.CMND == CMND) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool xoaDocGia(HashTable& ht, const string& CMND) {
    int vitri = hamBam(CMND);
    NodeDocGia* p = ht.buckets[vitri];
    NodeDocGia* truoc = NULL;

    while (p != NULL) {
        if (p->data.CMND == CMND) {
            if (truoc == NULL) {
                ht.buckets[vitri] = p->next;            }
            else {
                truoc->next = p->next;
            }
            delete p;
            return true;
        }
        truoc = p;
        p = p->next;
    }
    return false;
}

bool suaDocGia(HashTable& ht, const string& CMND, const docGia& moi) {
    NodeDocGia* p = timDocGia(ht, CMND);
    if (p == NULL) {
        return false;
    }
    p->data.hoten = moi.hoten;
    p->data.email = moi.email;
    p->data.sdt = moi.sdt;
    p->data.loaithe = moi.loaithe;
    return true;
}
