#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "linkedlist.h"

// doc 1 dong csv, tach theo dau phay va gan vao struct tuong ung

Lop layThongTinLop(FILE *file)
{
    Lop c;
    char temp[300];
    char *token;

    memset(&c, 0, sizeof(c));
    if (!fgets(temp, sizeof(temp), file))
        return c;
    temp[strcspn(temp, "\n\r")] = '\0';

    token = strtok(temp, ",");
    if (!token) return c;
    strncpy(c.maLop, token, sizeof(c.maLop) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(c.tenLop, token, sizeof(c.tenLop) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(c.chuNhiemLop, token, sizeof(c.chuNhiemLop) - 1);

    token = strtok(NULL, ",");
    c.soLuongSinhVien = token ? atoi(token) : 0;

    c.danhSachSV = NULL;
    c.tailSV = NULL;
    c.next = NULL;
    c.prev = NULL;
    return c;
}

SinhVien layThongTinSinhVien(FILE *file)
{
    SinhVien sv;
    char temp[400];
    char *token;

    memset(&sv, 0, sizeof(sv));
    if (!fgets(temp, sizeof(temp), file))
        return sv;
    temp[strcspn(temp, "\n\r")] = '\0';

    token = strtok(temp, ",");
    if (token) strncpy(sv.mssv, token, sizeof(sv.mssv) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(sv.hoVaTen, token, sizeof(sv.hoVaTen) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(sv.ngaySinh, token, sizeof(sv.ngaySinh) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(sv.email, token, sizeof(sv.email) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(sv.sdt, token, sizeof(sv.sdt) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(sv.maLop, token, sizeof(sv.maLop) - 1);

    sv.danhSachDiem = NULL;
    sv.tailDiem = NULL;
    sv.next = NULL;
    sv.prev = NULL;
    return sv;
}

MonHoc layThongTinMonHoc(FILE *file)
{
    MonHoc mh;
    char temp[300];
    char *token;

    memset(&mh, 0, sizeof(mh));
    if (!fgets(temp, sizeof(temp), file))
        return mh;
    temp[strcspn(temp, "\n\r")] = '\0';

    token = strtok(temp, ",");
    if (token) strncpy(mh.maMon, token, sizeof(mh.maMon) - 1);

    token = strtok(NULL, ",");
    if (token) strncpy(mh.tenMon, token, sizeof(mh.tenMon) - 1);

    token = strtok(NULL, ",");
    mh.soTinChi = token ? atoi(token) : 0;

    mh.next = NULL;
    mh.prev = NULL;
    return mh;
}

// cap phat bo nho cho 1 node moi, copy du lieu vao

Lop *taoNodeLop(Lop c)
{
    Lop *node = (Lop *)malloc(sizeof(Lop));
    if (!node) return NULL;
    *node = c;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

SinhVien *taoNodeSinhVien(SinhVien c)
{
    SinhVien *node = (SinhVien *)malloc(sizeof(SinhVien));
    if (!node) return NULL;
    *node = c;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

MonHoc *taoNodeMonHoc(MonHoc c)
{
    MonHoc *node = (MonHoc *)malloc(sizeof(MonHoc));
    if (!node) return NULL;
    *node = c;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

BangDiem *taoNodeBangDiem(const char *maMon, float diemHe10)
{
    BangDiem *node = (BangDiem *)malloc(sizeof(BangDiem));
    if (!node) return NULL;
    strncpy(node->maMon, maMon, sizeof(node->maMon) - 1);
    node->maMon[sizeof(node->maMon) - 1] = '\0';
    node->diemHe10 = diemHe10;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// them node vao cuoi danh sach lien ket

void themVaoLLLop(Lop **head, Lop **tail, Lop *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

void themVaoLLSV(SinhVien **head, SinhVien **tail, SinhVien *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

void themVaoLLMonHoc(MonHoc **head, MonHoc **tail, MonHoc *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

void themVaoLLBangDiem(BangDiem **head, BangDiem **tail, BangDiem *newNode)
{
    if (!newNode) return;
    newNode->next = NULL;
    newNode->prev = *tail;
    if (*tail) (*tail)->next = newNode;
    else       *head = newNode;
    *tail = newNode;
}

// go node ra khoi danh sach, free bo nho (ke ca diem cua sv)

void xoaSinhVien(SinhVien **head, SinhVien **tail, SinhVien *node)
{
    if (!node) return;
    if (node->prev) node->prev->next = node->next; else *head = node->next;
    if (node->next) node->next->prev = node->prev; else *tail = node->prev;
    // free het diem cua sv truoc khi free sv
    BangDiem *bd = node->danhSachDiem;
    while (bd) {
        BangDiem *tmp = bd->next;
        free(bd);
        bd = tmp;
    }
    free(node);
}

void xoaLop(Lop **head, Lop **tail, Lop *node)
{
    if (!node) return;
    // free het sv trong lop (va diem cua tung sv)
    SinhVien *sv = node->danhSachSV;
    while (sv) {
        SinhVien *tmp = sv->next;
        BangDiem *bd = sv->danhSachDiem;
        while (bd) {
            BangDiem *tmpBD = bd->next;
            free(bd);
            bd = tmpBD;
        }
        free(sv);
        sv = tmp;
    }
    if (node->prev) node->prev->next = node->next; else *head = node->next;
    if (node->next) node->next->prev = node->prev; else *tail = node->prev;
    free(node);
}

void xoaMonHoc(MonHoc **head, MonHoc **tail, MonHoc *node)
{
    if (!node) return;
    if (node->prev) node->prev->next = node->next; else *head = node->next;
    if (node->next) node->next->prev = node->prev; else *tail = node->prev;
    free(node);
}

// duyet danh sach diem cua sv, tim theo ma mon
BangDiem *timDiemTheoMon(SinhVien *sv, const char *maMon)
{
    BangDiem *bd = sv->danhSachDiem;
    while (bd) {
        if (strcmp(bd->maMon, maMon) == 0)
            return bd;
        bd = bd->next;
    }
    return NULL;
}

// ghi du lieu ra file csv

void luuLopRaFile(const Lop *headLop, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
    fprintf(f, "MaLop,TenLop,ChuNhiemLop,SoLuongSinhVien\n"); // dong tieu de
    const Lop *lop = headLop;
    while (lop) {
        fprintf(f, "%s,%s,%s,%d\n",
                lop->maLop, lop->tenLop, lop->chuNhiemLop,
                lop->soLuongSinhVien);
        lop = lop->next;
    }
    fclose(f);
    printf("Da luu file lop: %s\n", filePath);
}

void luuSVRaFile(const Lop *headLop, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
    fprintf(f, "MSSV,HoVaTen,NgaySinh,Email,SDT,MaLop\n");
    const Lop *lop = headLop;
    while (lop) {
        const SinhVien *sv = lop->danhSachSV;
        while (sv) {
            fprintf(f, "%s,%s,%s,%s,%s,%s\n",
                    sv->mssv, sv->hoVaTen, sv->ngaySinh,
                    sv->email, sv->sdt, sv->maLop);
            sv = sv->next;
        }
        lop = lop->next;
    }
    fclose(f);
    printf("Da luu file sinh vien: %s\n", filePath);
}

void luuMonHocRaFile(const MonHoc *headMH, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
    fprintf(f, "MaMon,TenMon,SoTinChi\n");
    const MonHoc *mh = headMH;
    while (mh) {
        fprintf(f, "%s,%s,%d\n", mh->maMon, mh->tenMon, mh->soTinChi);
        mh = mh->next;
    }
    fclose(f);
    printf("Da luu file mon hoc: %s\n", filePath);
}

void luuDiemRaFile(const Lop *headLop, const char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f) {
        printf("Khong mo duoc file de ghi: %s\n", filePath);
        return;
    }
    fprintf(f, "MSSV,MaMon,DiemHe10\n");
    const Lop *lop = headLop;
    while (lop) {
        const SinhVien *sv = lop->danhSachSV;
        while (sv) {
            const BangDiem *bd = sv->danhSachDiem;
            while (bd) {
                fprintf(f, "%s,%s,%.2f\n", sv->mssv, bd->maMon, bd->diemHe10);
                bd = bd->next;
            }
            sv = sv->next;
        }
        lop = lop->next;
    }
    fclose(f);
    printf("Da luu file diem: %s\n", filePath);
}
