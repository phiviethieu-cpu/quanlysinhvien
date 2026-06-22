#ifndef HASHMAP_H
#define HASHMAP_H

#include "types.h"

// bang bam lop
void hmLopKhoiTao(HashMapLop *hm);
void hmLopThem(HashMapLop *hm, Lop *lop);
Lop *hmLopTimKiem(HashMapLop *hm, const char *maLop);
void hmLopXoa(HashMapLop *hm, const char *maLop);
void hmLopHuy(HashMapLop *hm);

// bang bam sinh vien
void hmSVKhoiTao(HashMapSV *hm);
void hmSVThem(HashMapSV *hm, SinhVien *sv);
SinhVien *hmSVTimKiem(HashMapSV *hm, const char *mssv);
void hmSVXoa(HashMapSV *hm, const char *mssv);
void hmSVHuy(HashMapSV *hm);

// bang bam mon hoc
void hmMonHocKhoiTao(HashMapMonHoc *hm);
void hmMonHocThem(HashMapMonHoc *hm, MonHoc *mh);
MonHoc *hmMonHocTimKiem(HashMapMonHoc *hm, const char *maMon);
void hmMonHocXoa(HashMapMonHoc *hm, const char *maMon);
void hmMonHocHuy(HashMapMonHoc *hm);

#endif
