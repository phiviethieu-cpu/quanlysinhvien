#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "inRaManHinh.h"
#include "chucNang.h"
#include "validate.h"
#include "diemso.h"

// xoa bo dem stdin sau khi dung scanf
void xoaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// in menu chinh cua chuong trinh
void inMenu(void)
{
    printf("\n");
    printf("========================================================\n");
    printf("        QUAN LY SINH VIEN VA DIEM SO - NHOM 83\n");
    printf("========================================================\n");
    printf("  --- Quan ly danh muc ---\n");
    printf("   1. Them lop hoc phan\n");
    printf("   2. In danh sach lop hoc phan\n");
    printf("   3. Them mon hoc\n");
    printf("   4. In danh sach mon hoc\n");
    printf("   5. Them sinh vien\n");
    printf("   6. Xoa sinh vien\n");
    printf("   7. Cap nhat thong tin sinh vien\n");
    printf("   8. Tim sinh vien theo MSSV\n");
    printf("  --- Quan ly diem ---\n");
    printf("   9. Nhap diem cho sinh vien\n");
    printf("  10. Cap nhat diem\n");
    printf("  --- Bao cao ---\n");
    printf("  11. Bang diem cua mot sinh vien\n");
    printf("  12. Bang diem lop hoc phan\n");
    printf("  13. Sap xep danh sach sinh vien\n");
    printf("   0. Thoat\n");
    printf("========================================================\n");
    printf("Lua chon: ");
}

// 1. them lop hoc phan moi
void chucNang_ThemLop(Lop **headLop, Lop **tailLop, HashMapLop *hmLop)
{
    Lop lopMoi;
    memset(&lopMoi, 0, sizeof(lopMoi));

    do {
        printf("Nhap ma lop: ");
        if (scanf("%19s", lopMoi.maLop) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMaLop(lopMoi.maLop));

    if (hmLopTimKiem(hmLop, lopMoi.maLop)) {
        printf("Ma lop '%s' da ton tai roi.\n", lopMoi.maLop);
        return;
    }

    do {
        printf("Nhap ten lop: ");
        if (scanf(" %99[^\n]", lopMoi.tenLop) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidHoVaTen(lopMoi.tenLop));

    do {
        printf("Nhap ten chu nhiem lop: ");
        if (scanf(" %99[^\n]", lopMoi.chuNhiemLop) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidHoVaTen(lopMoi.chuNhiemLop));

    lopMoi.soLuongSinhVien = 0;
    lopMoi.danhSachSV = NULL;
    lopMoi.tailSV = NULL;

    Lop *node = taoNodeLop(lopMoi);
    if (!node) { printf("Khong du bo nho de them lop.\n"); return; }
    themVaoLLLop(headLop, tailLop, node);
    hmLopThem(hmLop, node);
    printf("Them lop '%s' - %s thanh cong.\n", node->maLop, node->tenLop);
}

// 2. in toan bo danh sach lop
void chucNang_InToanBoLop(const Lop *headLop)
{
    if (!headLop) {
        printf("Hien chua co lop nao trong he thong.\n");
        return;
    }
    printf("\n=== DANH SACH TAT CA CAC LOP ===\n");
    inToanBoLop(headLop);
}

// 3. them mon hoc moi
void chucNang_ThemMonHoc(MonHoc **headMH, MonHoc **tailMH, HashMapMonHoc *hmMH)
{
    MonHoc mhMoi;
    char buf[20];
    memset(&mhMoi, 0, sizeof(mhMoi));

    do {
        printf("Nhap ma mon: ");
        if (scanf("%19s", mhMoi.maMon) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMaMon(mhMoi.maMon));

    if (hmMonHocTimKiem(hmMH, mhMoi.maMon)) {
        printf("Ma mon '%s' da ton tai roi.\n", mhMoi.maMon);
        return;
    }

    do {
        printf("Nhap ten mon: ");
        if (scanf(" %99[^\n]", mhMoi.tenMon) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidHoVaTen(mhMoi.tenMon));

    do {
        printf("Nhap so tin chi (1-10): ");
        if (scanf("%19s", buf) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidSoTinChi(buf, &mhMoi.soTinChi));

    MonHoc *node = taoNodeMonHoc(mhMoi);
    if (!node) { printf("Khong du bo nho de them mon hoc.\n"); return; }
    themVaoLLMonHoc(headMH, tailMH, node);
    hmMonHocThem(hmMH, node);
    printf("Them mon hoc '%s' - %s (%d tin chi) thanh cong.\n",
           node->maMon, node->tenMon, node->soTinChi);
}

// 4. in danh sach mon hoc
void chucNang_InDanhSachMonHoc(const MonHoc *headMH)
{
    if (!headMH) {
        printf("Hien chua co mon hoc nao trong he thong.\n");
        return;
    }
    printf("\n=== DANH SACH MON HOC ===\n");
    inDanhSachMonHoc(headMH);
}

// 5. them sinh vien moi vao lop
void chucNang_ThemSinhVien(Lop **headLop, Lop **tailLop,
                            HashMapLop *hmLop, HashMapSV *hmSV)
{
    SinhVien sv;
    memset(&sv, 0, sizeof(sv));

    do {
        printf("Nhap MSSV: ");
        if (scanf("%19s", sv.mssv) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMSSV(sv.mssv));

    if (hmSVTimKiem(hmSV, sv.mssv)) {
        printf("MSSV '%s' da ton tai roi.\n", sv.mssv);
        return;
    }

    do {
        printf("Nhap ho va ten: ");
        if (scanf(" %99[^\n]", sv.hoVaTen) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidHoVaTen(sv.hoVaTen));

    do {
        printf("Nhap ngay sinh (DD/MM/YYYY): ");
        if (scanf("%10s", sv.ngaySinh) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidNgaySinh(sv.ngaySinh));

    do {
        printf("Nhap email: ");
        if (scanf("%99s", sv.email) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidEmail(sv.email));

    do {
        printf("Nhap so dien thoai: ");
        if (scanf("%14s", sv.sdt) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidSDT(sv.sdt));

    do {
        printf("Nhap ma lop: ");
        if (scanf("%19s", sv.maLop) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidMaLop(sv.maLop));

    // kiem tra lop co ton tai khong, neu chua thi hoi tao moi
    Lop *lop = hmLopTimKiem(hmLop, sv.maLop);
    if (!lop) {
        printf("Lop '%s' chua ton tai. Ban co muon tao lop moi khong? (c/k): ", sv.maLop);
        char choice;
        if (scanf(" %c", &choice) != 1) { xoaBuffer(); return; }
        xoaBuffer();

        if (choice == 'c' || choice == 'C') {
            Lop lopMoi;
            memset(&lopMoi, 0, sizeof(lopMoi));
            strncpy(lopMoi.maLop, sv.maLop, sizeof(lopMoi.maLop) - 1);

            do {
                printf("Nhap ten lop: ");
                if (scanf(" %99[^\n]", lopMoi.tenLop) != 1) { xoaBuffer(); return; }
                xoaBuffer();
            } while (!isValidHoVaTen(lopMoi.tenLop));

            do {
                printf("Nhap ten chu nhiem lop: ");
                if (scanf(" %99[^\n]", lopMoi.chuNhiemLop) != 1) { xoaBuffer(); return; }
                xoaBuffer();
            } while (!isValidHoVaTen(lopMoi.chuNhiemLop));

            Lop *nodeLop = taoNodeLop(lopMoi);
            if (!nodeLop) { printf("Khong du bo nho.\n"); return; }
            themVaoLLLop(headLop, tailLop, nodeLop);
            hmLopThem(hmLop, nodeLop);
            lop = nodeLop;
            printf("Da tao lop '%s'.\n", lop->maLop);
        } else {
            printf("Da huy them sinh vien.\n");
            return;
        }
    }

    sv.danhSachDiem = NULL;
    sv.tailDiem = NULL;

    SinhVien *node = taoNodeSinhVien(sv);
    if (!node) { printf("Khong du bo nho.\n"); return; }
    themVaoLLSV(&lop->danhSachSV, &lop->tailSV, node);
    lop->soLuongSinhVien++;
    hmSVThem(hmSV, node);

    printf("Them sinh vien '%s' - %s vao lop %s thanh cong.\n",
           node->mssv, node->hoVaTen, node->maLop);
}

// 6. xoa sinh vien theo MSSV
void chucNang_XoaSinhVien(Lop **headLop, Lop **tailLop,
                           HashMapLop *hmLop, HashMapSV *hmSV)
{
    char mssv[20];
    char choice;
    Lop *lop;
    SinhVien *sv;

    printf("Nhap MSSV can xoa: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    if (!isValidMSSV(mssv)) return;

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }

    printf("\nThong tin sinh vien sap xoa:\n");
    inThongTinSV(sv);
    printf("Ban co chac chan muon xoa khong? (c/k): ");
    if (scanf(" %c", &choice) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    if (choice != 'c' && choice != 'C') {
        printf("Da huy thao tac xoa.\n");
        return;
    }

    lop = hmLopTimKiem(hmLop, sv->maLop);
    if (lop) {
        xoaSinhVien(&lop->danhSachSV, &lop->tailSV, sv);
        if (lop->soLuongSinhVien > 0)
            lop->soLuongSinhVien--;
    } else {
        // lop khong ton tai thi free truc tiep
        BangDiem *bd = sv->danhSachDiem;
        while (bd) { BangDiem *tmp = bd->next; free(bd); bd = tmp; }
        free(sv);
    }
    hmSVXoa(hmSV, mssv);
    printf("Da xoa sinh vien MSSV = '%s'.\n", mssv);
}

// 7. cap nhat thong tin sv (nhan Enter de bo qua truong khong muon sua)
void chucNang_CapNhatSV(HashMapSV *hmSV)
{
    char mssv[20], buf[100];
    SinhVien *sv;

    printf("Nhap MSSV can cap nhat: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }

    printf("\nThong tin hien tai:\n");
    inThongTinSV(sv);
    printf("\n--- Nhan Enter neu khong muon thay doi ---\n");

    printf("Ho va ten [%s]: ", sv->hoVaTen);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidHoVaTen(buf))
            strncpy(sv->hoVaTen, buf, sizeof(sv->hoVaTen) - 1);
        else
            printf("  -> Giu nguyen.\n");
    }

    printf("Ngay sinh [%s]: ", sv->ngaySinh);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidNgaySinh(buf))
            strncpy(sv->ngaySinh, buf, sizeof(sv->ngaySinh) - 1);
        else
            printf("  -> Giu nguyen.\n");
    }

    printf("Email [%s]: ", sv->email);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidEmail(buf))
            strncpy(sv->email, buf, sizeof(sv->email) - 1);
        else
            printf("  -> Giu nguyen.\n");
    }

    printf("SDT [%s]: ", sv->sdt);
    if (fgets(buf, sizeof(buf), stdin) && buf[0] != '\n') {
        buf[strcspn(buf, "\n")] = '\0';
        if (isValidSDT(buf))
            strncpy(sv->sdt, buf, sizeof(sv->sdt) - 1);
        else
            printf("  -> Giu nguyen.\n");
    }

    printf("Cap nhat thong tin sinh vien '%s' thanh cong.\n", sv->mssv);
}

// 8. tim kiem sv theo MSSV, hien thi thong tin + GPA
void chucNang_TimSVTheoMSSV(HashMapSV *hmSV, HashMapMonHoc *hmMH)
{
    char mssv[20];
    SinhVien *sv;

    printf("Nhap MSSV: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }

    printf("\n--- Ket qua tim kiem ---\n");
    inThongTinSV(sv);

    float gpa = tinhGPA(sv, hmMH);
    printf("  GPA(4)   : %.2f\n", gpa);
    printf("  Xep loai : %s\n", xepLoaiHocLuc(gpa));
}

// 9. nhap diem cho sv theo ma mon
void chucNang_NhapDiem(HashMapSV *hmSV, HashMapMonHoc *hmMH)
{
    char mssv[20], maMon[20], buf[20];
    float diem;
    SinhVien *sv;
    MonHoc *mh;
    BangDiem *existing, *node;

    printf("Nhap MSSV: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }
    printf("  -> Sinh vien: %s - %s\n", sv->mssv, sv->hoVaTen);

    printf("Nhap ma mon hoc: ");
    if (scanf("%19s", maMon) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    mh = hmMonHocTimKiem(hmMH, maMon);
    if (!mh) {
        printf("Khong tim thay mon hoc '%s'.\n", maMon);
        return;
    }
    printf("  -> Mon hoc: %s - %s (%d TC)\n", mh->maMon, mh->tenMon, mh->soTinChi);

    // neu da co diem mon nay roi thi bao dung chuc nang cap nhat
    existing = timDiemTheoMon(sv, maMon);
    if (existing) {
        printf("Sinh vien da co diem mon '%s' (%.2f). Hay dung chuc nang Cap nhat diem.\n",
               maMon, existing->diemHe10);
        return;
    }

    do {
        printf("Nhap diem he 10 (0.0 - 10.0): ");
        if (scanf("%19s", buf) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidDiem(buf, &diem));

    node = taoNodeBangDiem(maMon, diem);
    if (!node) { printf("Khong du bo nho.\n"); return; }
    themVaoLLBangDiem(&sv->danhSachDiem, &sv->tailDiem, node);

    printf("Nhap diem mon '%s' = %.2f cho SV '%s' thanh cong.\n",
           maMon, diem, sv->mssv);
    {
        float gpa = tinhGPA(sv, hmMH);
        printf("  -> Diem he 4: %.1f | GPA tich luy: %.2f | Xep loai: %s\n",
               chuyenDiemHe10SangHe4(diem), gpa, xepLoaiHocLuc(gpa));
    }
}

// 10. sua diem da nhap cua sv
void chucNang_CapNhatDiem(HashMapSV *hmSV, HashMapMonHoc *hmMH)
{
    char mssv[20], maMon[20], buf[20];
    float diemMoi;
    SinhVien *sv;
    BangDiem *bd;

    printf("Nhap MSSV: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }
    printf("  -> Sinh vien: %s - %s\n", sv->mssv, sv->hoVaTen);

    if (!sv->danhSachDiem) {
        printf("Sinh vien nay chua co diem mon nao.\n");
        return;
    }

    // in ra cac mon da co diem de nguoi dung chon
    printf("\nDiem hien tai:\n");
    bd = sv->danhSachDiem;
    while (bd) {
        MonHoc *mh = hmMonHocTimKiem(hmMH, bd->maMon);
        printf("  [%s] %s: %.2f\n", bd->maMon,
               mh ? mh->tenMon : "(Khong ro)", bd->diemHe10);
        bd = bd->next;
    }

    printf("\nNhap ma mon can cap nhat: ");
    if (scanf("%19s", maMon) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    bd = timDiemTheoMon(sv, maMon);
    if (!bd) {
        printf("Sinh vien chua co diem mon '%s'.\n", maMon);
        return;
    }

    printf("Diem hien tai: %.2f\n", bd->diemHe10);
    do {
        printf("Nhap diem moi (0.0 - 10.0): ");
        if (scanf("%19s", buf) != 1) { xoaBuffer(); return; }
        xoaBuffer();
    } while (!isValidDiem(buf, &diemMoi));

    bd->diemHe10 = diemMoi;
    printf("Cap nhat diem mon '%s' = %.2f thanh cong.\n", maMon, diemMoi);
    {
        float gpa = tinhGPA(sv, hmMH);
        printf("  -> GPA tich luy: %.2f | Xep loai: %s\n", gpa, xepLoaiHocLuc(gpa));
    }
}

// 11. xem bang diem chi tiet cua 1 sv
void chucNang_BangDiemSV(HashMapSV *hmSV, HashMapMonHoc *hmMH)
{
    char mssv[20];
    SinhVien *sv;

    printf("Nhap MSSV: ");
    if (scanf("%19s", mssv) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    sv = hmSVTimKiem(hmSV, mssv);
    if (!sv) {
        printf("Khong tim thay sinh vien co MSSV = '%s'.\n", mssv);
        return;
    }
    inBangDiemSV(sv, hmMH);
}

// 12. xem bang diem toan bo lop (GPA + xep loai tung sv)
void chucNang_BangDiemLopHP(HashMapLop *hmLop, HashMapMonHoc *hmMH)
{
    char maLop[20];
    Lop *lop;

    printf("Nhap ma lop: ");
    if (scanf("%19s", maLop) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    lop = hmLopTimKiem(hmLop, maLop);
    if (!lop) {
        printf("Khong tim thay lop '%s'.\n", maLop);
        return;
    }
    inBangDiemLopHP(lop, hmMH);
}

// 13. sap xep sv theo ten, MSSV hoac GPA
// dung mang tam + qsort, khong thay doi thu tu trong linked list

typedef struct {
    SinhVien *sv;
    float gpa4;
} SVSort;

int cmpTheoTen(const void *a, const void *b)
{
    const SVSort *sa = (const SVSort *)a;
    const SVSort *sb = (const SVSort *)b;
    return strcmp(sa->sv->hoVaTen, sb->sv->hoVaTen);
}

int cmpTheoMSSV(const void *a, const void *b)
{
    const SVSort *sa = (const SVSort *)a;
    const SVSort *sb = (const SVSort *)b;
    return strcmp(sa->sv->mssv, sb->sv->mssv);
}

int cmpTheoGPA(const void *a, const void *b)
{
    const SVSort *sa = (const SVSort *)a;
    const SVSort *sb = (const SVSort *)b;
    if (sb->gpa4 > sa->gpa4) return 1;
    if (sb->gpa4 < sa->gpa4) return -1;
    return 0;
}

void chucNang_SapXepSV(Lop *headLop, HashMapMonHoc *hmMH)
{
    int luaChon, soSV, i, stt;
    Lop *lop;
    SinhVien *sv;
    SVSort *arr;

    if (!headLop) {
        printf("Chua co du lieu sinh vien nao.\n");
        return;
    }

    printf("\nSap xep theo:\n");
    printf("  1. Ho va ten (A-Z)\n");
    printf("  2. MSSV (A-Z)\n");
    printf("  3. GPA he 4 (cao -> thap)\n");
    printf("Lua chon: ");
    if (scanf("%d", &luaChon) != 1) { xoaBuffer(); return; }
    xoaBuffer();

    if (luaChon < 1 || luaChon > 3) {
        printf("Lua chon khong hop le, vui long chon 1-3.\n");
        return;
    }

    // dem tong so sv de cap phat mang
    soSV = 0;
    lop = headLop;
    while (lop) {
        sv = lop->danhSachSV;
        while (sv) { soSV++; sv = sv->next; }
        lop = lop->next;
    }

    if (soSV == 0) {
        printf("Khong co sinh vien nao de sap xep.\n");
        return;
    }

    arr = (SVSort *)malloc(soSV * sizeof(SVSort));
    if (!arr) { printf("Khong du bo nho.\n"); return; }

    // copy con tro sv vao mang de sort
    i = 0;
    lop = headLop;
    while (lop) {
        sv = lop->danhSachSV;
        while (sv) {
            arr[i].sv = sv;
            arr[i].gpa4 = tinhGPA(sv, hmMH);
            i++;
            sv = sv->next;
        }
        lop = lop->next;
    }

    switch (luaChon) {
    case 1: qsort(arr, soSV, sizeof(SVSort), cmpTheoTen);  break;
    case 2: qsort(arr, soSV, sizeof(SVSort), cmpTheoMSSV); break;
    case 3: qsort(arr, soSV, sizeof(SVSort), cmpTheoGPA);  break;
    }

    printf("\n%-5s %-15s %-25s %-8s %8s %-12s\n",
           "STT", "MSSV", "Ho va ten", "Lop", "GPA(4)", "Xep loai");
    printf("--------------------------------------------------------------------------\n");

    for (stt = 0; stt < soSV; stt++) {
        printf("%-5d %-15s %-25s %-8s %8.2f %-12s\n",
               stt + 1,
               arr[stt].sv->mssv,
               arr[stt].sv->hoVaTen,
               arr[stt].sv->maLop,
               arr[stt].gpa4,
               xepLoaiHocLuc(arr[stt].gpa4));
    }
    printf("--------------------------------------------------------------------------\n");
    printf("Tong cong: %d sinh vien.\n", soSV);

    free(arr);
}

// luu toan bo du lieu ra 4 file csv
void chucNang_LuuFile(const Lop *headLop, const MonHoc *headMH)
{
    luuLopRaFile(headLop,  "danh_sach_lop.csv");
    luuSVRaFile(headLop,   "danh_sach_sinh_vien.csv");
    luuMonHocRaFile(headMH, "danh_sach_mon_hoc.csv");
    luuDiemRaFile(headLop, "danh_sach_diem.csv");
    printf("Da luu xong toan bo du lieu vao file.\n");
}
