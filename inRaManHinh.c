#include <stdio.h>
#include <string.h>
#include "types.h"
#include "hashmap.h"
#include "diemso.h"
#include "inRaManHinh.h"

void inThongTinSV(const SinhVien *sv)
{
    if (!sv) { printf("  [Khong tim thay]\n"); return; }
    printf("  MSSV     : %s\n", sv->mssv);
    printf("  Ho va ten: %s\n", sv->hoVaTen);
    printf("  Ngay sinh: %s\n", sv->ngaySinh);
    printf("  Email    : %s\n", sv->email);
    printf("  SDT      : %s\n", sv->sdt);
    printf("  Ma lop   : %s\n", sv->maLop);
}

void inDanhSachLop(const Lop *lop)
{
    int i;
    const SinhVien *sv;
    if (!lop) { printf("[Khong tim thay lop]\n"); return; }
    printf("=== Lop: %s | %s | CN: %s | SL: %d ===\n",
           lop->maLop, lop->tenLop, lop->chuNhiemLop, lop->soLuongSinhVien);
    sv = lop->danhSachSV;
    i = 1;
    while (sv) {
        printf("  %d. [%s] %s\n", i++, sv->mssv, sv->hoVaTen);
        sv = sv->next;
    }
    if (i == 1) printf("  (Chua co sinh vien)\n");
}

void inToanBoLop(const Lop *headLop)
{
    const Lop *lop = headLop;
    while (lop) {
        inDanhSachLop(lop);
        printf("\n");
        lop = lop->next;
    }
}

void inThongTinMonHoc(const MonHoc *mh)
{
    if (!mh) { printf("  [Khong tim thay mon hoc]\n"); return; }
    printf("  Ma mon  : %s\n", mh->maMon);
    printf("  Ten mon : %s\n", mh->tenMon);
    printf("  Tin chi : %d\n", mh->soTinChi);
}

void inDanhSachMonHoc(const MonHoc *headMH)
{
    int i = 1;
    const MonHoc *mh = headMH;
    if (!mh) { printf("Chua co mon hoc nao.\n"); return; }
    printf("\n%-5s %-15s %-40s %s\n", "STT", "Ma mon", "Ten mon", "Tin chi");
    printf("----------------------------------------------------------------------\n");
    while (mh) {
        printf("%-5d %-15s %-40s %d\n", i++, mh->maMon, mh->tenMon, mh->soTinChi);
        mh = mh->next;
    }
}

void inBangDiemSV(SinhVien *sv, HashMapMonHoc *hmMH)
{
    int tongTC = 0;
    BangDiem *bd;
    float gpa;

    if (!sv) { printf("[Khong tim thay sinh vien]\n"); return; }

    printf("\n============ BANG DIEM SINH VIEN ============\n");
    printf("  MSSV     : %s\n", sv->mssv);
    printf("  Ho va ten: %s\n", sv->hoVaTen);
    printf("  Lop      : %s\n", sv->maLop);
    printf("----------------------------------------------\n");
    printf("  %-15s %-30s %4s %8s %6s\n", "Ma mon", "Ten mon", "TC", "Diem", "He 4");
    printf("  -----------------------------------------------------------\n");

    bd = sv->danhSachDiem;
    if (!bd) {
        printf("  (Chua co diem)\n");
    }
    while (bd) {
        MonHoc *mh = hmMonHocTimKiem(hmMH, bd->maMon);
        float he4 = chuyenDiemHe10SangHe4(bd->diemHe10);
        if (mh) {
            printf("  %-15s %-30s %4d %8.2f %6.1f\n",
                   bd->maMon, mh->tenMon, mh->soTinChi, bd->diemHe10, he4);
            tongTC += mh->soTinChi;
        } else {
            printf("  %-15s %-30s %4s %8.2f %6.1f\n",
                   bd->maMon, "(Khong ro)", "?", bd->diemHe10, he4);
        }
        bd = bd->next;
    }

    gpa = tinhGPA(sv, hmMH);

    printf("  -----------------------------------------------------------\n");
    printf("  Tong tin chi: %d\n", tongTC);
    printf("  GPA he 4    : %.2f\n", gpa);
    printf("  Xep loai    : %s\n", xepLoaiHocLuc(gpa));
    printf("==============================================\n");
}

void inBangDiemLopHP(Lop *lop, HashMapMonHoc *hmMH)
{
    int stt;
    SinhVien *sv;

    if (!lop) { printf("[Khong tim thay lop]\n"); return; }

    printf("\n=========== BANG DIEM LOP %s - %s ===========\n", lop->maLop, lop->tenLop);
    printf("  Chu nhiem: %s\n\n", lop->chuNhiemLop);

    printf("  %-5s %-15s %-25s %8s %-12s\n",
           "STT", "MSSV", "Ho va ten", "GPA(4)", "Xep loai");
    printf("  ---------------------------------------------------------------------\n");

    sv = lop->danhSachSV;
    stt = 1;
    while (sv) {
        float gpa = tinhGPA(sv, hmMH);
        printf("  %-5d %-15s %-25s %8.2f %-12s\n",
               stt++, sv->mssv, sv->hoVaTen, gpa, xepLoaiHocLuc(gpa));
        sv = sv->next;
    }
    if (stt == 1) printf("  (Chua co sinh vien)\n");

    printf("  ---------------------------------------------------------------------\n");
}
