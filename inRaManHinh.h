#ifndef INRAMANHINH_H
#define INRAMANHINH_H

#include "types.h"
#include "hashmap.h"

void inThongTinSV(const SinhVien *sv);
void inDanhSachLop(const Lop *lop);
void inToanBoLop(const Lop *headLop);
void inThongTinMonHoc(const MonHoc *mh);
void inDanhSachMonHoc(const MonHoc *headMH);
void inBangDiemSV(SinhVien *sv, HashMapMonHoc *hmMH);
void inBangDiemLopHP(Lop *lop, HashMapMonHoc *hmMH);

#endif
