#include "thuvien.h"

void khoiTaoHashTable(HashTable& ht) {
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        ht.buckets[i] = NULL;
    }
}

int hamBam(const string& CMND) {
    unsigned int h = 0;
    for (size_t i = 0; i < CMND.length(); i++) {
        h = h * 31 + (unsigned char)CMND[i];
    }
    return h % KICH_THUOC_BANG_BAM;
}

void giaiPhongHashTable(HashTable& ht) {
    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        NodeDocGia* p = ht.buckets[i];
        while (p != NULL) {
            NodeDocGia* temp = p;
            p = p->next;
            delete temp;
        }
        ht.buckets[i] = NULL;
    }
}
