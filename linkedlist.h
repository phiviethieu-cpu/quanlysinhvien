#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

// doc 1 ban ghi tu file csv
Lop      layThongTinLop(FILE *file);
SinhVien layThongTinSinhVien(FILE *file);
MonHoc   layThongTinMonHoc(FILE *file);

// cap phat node moi
Lop      *taoNodeLop(Lop c);
SinhVien *taoNodeSinhVien(SinhVien c);
MonHoc   *taoNodeMonHoc(MonHoc c);
BangDiem *taoNodeBangDiem(const char *maMon, float diemHe10);

// them node vao cuoi danh sach lien ket
void themVaoLLLop(Lop **head, Lop **tail, Lop *newNode);
void themVaoLLSV(SinhVien **head, SinhVien **tail, SinhVien *newNode);
void themVaoLLMonHoc(MonHoc **head, MonHoc **tail, MonHoc *newNode);
void themVaoLLBangDiem(BangDiem **head, BangDiem **tail, BangDiem *newNode);

// xoa node khoi danh sach lien ket (co free bo nho)
void xoaSinhVien(SinhVien **head, SinhVien **tail, SinhVien *node);
void xoaLop(Lop **head, Lop **tail, Lop *node);
void xoaMonHoc(MonHoc **head, MonHoc **tail, MonHoc *node);

// duyet danh sach diem cua 1 sv, tim theo ma mon
BangDiem *timDiemTheoMon(SinhVien *sv, const char *maMon);

// ghi du lieu ra file csv
void luuSVRaFile(const Lop *headLop, const char *filePath);
void luuLopRaFile(const Lop *headLop, const char *filePath);
void luuMonHocRaFile(const MonHoc *headMH, const char *filePath);
void luuDiemRaFile(const Lop *headLop, const char *filePath);

#endif
