#ifndef CHUCNANG_H
#define CHUCNANG_H

#include "types.h"
#include "hashmap.h"

void inMenu(void);
void xoaBuffer(void);

/* 1. Them lop hoc phan */
void chucNang_ThemLop(Lop **headLop, Lop **tailLop, HashMapLop *hmLop);

/* 2. In danh sach lop */
void chucNang_InToanBoLop(const Lop *headLop);

/* 3. Them mon hoc */
void chucNang_ThemMonHoc(MonHoc **headMH, MonHoc **tailMH, HashMapMonHoc *hmMH);

/* 4. In danh sach mon hoc */
void chucNang_InDanhSachMonHoc(const MonHoc *headMH);

/* 5. Them sinh vien */
void chucNang_ThemSinhVien(Lop **headLop, Lop **tailLop,
                            HashMapLop *hmLop, HashMapSV *hmSV);

/* 6. Xoa sinh vien */
void chucNang_XoaSinhVien(Lop **headLop, Lop **tailLop,
                           HashMapLop *hmLop, HashMapSV *hmSV);

/* 7. Cap nhat thong tin sinh vien */
void chucNang_CapNhatSV(HashMapSV *hmSV);

/* 8. Tim sinh vien theo MSSV */
void chucNang_TimSVTheoMSSV(HashMapSV *hmSV, HashMapMonHoc *hmMH);

/* 9. Nhap diem */
void chucNang_NhapDiem(HashMapSV *hmSV, HashMapMonHoc *hmMH);

/* 10. Cap nhat diem */
void chucNang_CapNhatDiem(HashMapSV *hmSV, HashMapMonHoc *hmMH);

/* 11. Bang diem sinh vien */
void chucNang_BangDiemSV(HashMapSV *hmSV, HashMapMonHoc *hmMH);

/* 12. Bang diem lop hoc phan */
void chucNang_BangDiemLopHP(HashMapLop *hmLop, HashMapMonHoc *hmMH);

/* 13. Sap xep danh sach sinh vien */
void chucNang_SapXepSV(Lop *headLop, HashMapMonHoc *hmMH);

/* 14. Luu du lieu */
void chucNang_LuuFile(const Lop *headLop, const MonHoc *headMH);

#endif
