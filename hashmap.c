#include "types.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ham bam djb2 - chuyen chuoi thanh chi so trong bang bam
unsigned int hashStr(const char *key)
{
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char)*key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % HASH_SIZE;
}

// bang bam lop

void hmLopKhoiTao(HashMapLop *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        hm->buckets[i] = NULL;
}

void hmLopThem(HashMapLop *hm, Lop *lop)
{
    unsigned int idx = hashStr(lop->maLop);
    EntryLop *entry = (EntryLop *)malloc(sizeof(EntryLop));
    if (!entry) return;
    strncpy(entry->key, lop->maLop, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->lop = lop;
    entry->next = hm->buckets[idx]; // chen vao dau chuoi
    hm->buckets[idx] = entry;
}

// tra ve NULL neu khong tim thay
Lop *hmLopTimKiem(HashMapLop *hm, const char *maLop)
{
    unsigned int idx = hashStr(maLop);
    EntryLop *cur = hm->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, maLop) == 0)
            return cur->lop;
        cur = cur->next;
    }
    return NULL;
}

// chi xoa entry trong bang bam, khong free node Lop
void hmLopXoa(HashMapLop *hm, const char *maLop)
{
    unsigned int idx = hashStr(maLop);
    EntryLop *cur = hm->buckets[idx];
    EntryLop *prev = NULL;
    while (cur) {
        if (strcmp(cur->key, maLop) == 0) {
            if (prev)
                prev->next = cur->next;
            else
                hm->buckets[idx] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

// giai phong toan bo bang bam lop
void hmLopHuy(HashMapLop *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        EntryLop *cur = hm->buckets[i];
        while (cur) {
            EntryLop *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        hm->buckets[i] = NULL;
    }
}

// bang bam sinh vien

void hmSVKhoiTao(HashMapSV *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        hm->buckets[i] = NULL;
}

void hmSVThem(HashMapSV *hm, SinhVien *sv)
{
    unsigned int idx = hashStr(sv->mssv);
    EntrySV *entry = (EntrySV *)malloc(sizeof(EntrySV));
    if (!entry) return;
    strncpy(entry->key, sv->mssv, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->sv = sv;
    entry->next = hm->buckets[idx];
    hm->buckets[idx] = entry;
}

SinhVien *hmSVTimKiem(HashMapSV *hm, const char *mssv)
{
    unsigned int idx = hashStr(mssv);
    EntrySV *cur = hm->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, mssv) == 0)
            return cur->sv;
        cur = cur->next;
    }
    return NULL;
}

void hmSVXoa(HashMapSV *hm, const char *mssv)
{
    unsigned int idx = hashStr(mssv);
    EntrySV *cur = hm->buckets[idx];
    EntrySV *prev = NULL;
    while (cur) {
        if (strcmp(cur->key, mssv) == 0) {
            if (prev)
                prev->next = cur->next;
            else
                hm->buckets[idx] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void hmSVHuy(HashMapSV *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        EntrySV *cur = hm->buckets[i];
        while (cur) {
            EntrySV *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        hm->buckets[i] = NULL;
    }
}

// bang bam mon hoc

void hmMonHocKhoiTao(HashMapMonHoc *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++)
        hm->buckets[i] = NULL;
}

void hmMonHocThem(HashMapMonHoc *hm, MonHoc *mh)
{
    unsigned int idx = hashStr(mh->maMon);
    EntryMonHoc *entry = (EntryMonHoc *)malloc(sizeof(EntryMonHoc));
    if (!entry) return;
    strncpy(entry->key, mh->maMon, sizeof(entry->key) - 1);
    entry->key[sizeof(entry->key) - 1] = '\0';
    entry->monHoc = mh;
    entry->next = hm->buckets[idx];
    hm->buckets[idx] = entry;
}

MonHoc *hmMonHocTimKiem(HashMapMonHoc *hm, const char *maMon)
{
    unsigned int idx = hashStr(maMon);
    EntryMonHoc *cur = hm->buckets[idx];
    while (cur) {
        if (strcmp(cur->key, maMon) == 0)
            return cur->monHoc;
        cur = cur->next;
    }
    return NULL;
}

void hmMonHocXoa(HashMapMonHoc *hm, const char *maMon)
{
    unsigned int idx = hashStr(maMon);
    EntryMonHoc *cur = hm->buckets[idx];
    EntryMonHoc *prev = NULL;
    while (cur) {
        if (strcmp(cur->key, maMon) == 0) {
            if (prev)
                prev->next = cur->next;
            else
                hm->buckets[idx] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void hmMonHocHuy(HashMapMonHoc *hm)
{
    int i;
    for (i = 0; i < HASH_SIZE; i++) {
        EntryMonHoc *cur = hm->buckets[i];
        while (cur) {
            EntryMonHoc *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        hm->buckets[i] = NULL;
    }
}
