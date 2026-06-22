#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "hashmap.h"
#include "linkedlist.h"
#include "inRaManHinh.h"
#include "napDuLieu.h"
#include "chucNang.h"

int main(void)
{
    // khoi tao cac danh sach va bang bam
    Lop         *headLop = NULL, *tailLop = NULL;
    MonHoc      *headMH  = NULL, *tailMH  = NULL;
    HashMapLop   hmLop;
    HashMapSV    hmSV;
    HashMapMonHoc hmMH;
    int          luaChon;

    hmLopKhoiTao(&hmLop);
    hmSVKhoiTao(&hmSV);
    hmMonHocKhoiTao(&hmMH);

    // doc du lieu tu 4 file csv khi khoi dong
    napDuLieu("danh_sach_lop.csv", "danh_sach_sinh_vien.csv",
              "danh_sach_mon_hoc.csv", "danh_sach_diem.csv",
              &headLop, &tailLop, &headMH, &tailMH,
              &hmLop, &hmSV, &hmMH);

    // vong lap menu chinh
    while (1) {
        inMenu();

        if (scanf("%d", &luaChon) != 1) {
            xoaBuffer();
            printf("Vui long nhap so.\n");
            continue;
        }
        xoaBuffer();

        switch (luaChon) {
        case 1:
            chucNang_ThemLop(&headLop, &tailLop, &hmLop);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 2:
            chucNang_InToanBoLop(headLop);
            break;
        case 3:
            chucNang_ThemMonHoc(&headMH, &tailMH, &hmMH);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 4:
            chucNang_InDanhSachMonHoc(headMH);
            break;
        case 5:
            chucNang_ThemSinhVien(&headLop, &tailLop, &hmLop, &hmSV);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 6:
            chucNang_XoaSinhVien(&headLop, &tailLop, &hmLop, &hmSV);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 7:
            chucNang_CapNhatSV(&hmSV);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 8:
            chucNang_TimSVTheoMSSV(&hmSV, &hmMH);
            break;
        case 9:
            chucNang_NhapDiem(&hmSV, &hmMH);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 10:
            chucNang_CapNhatDiem(&hmSV, &hmMH);
            chucNang_LuuFile(headLop, headMH);
            break;
        case 11:
            chucNang_BangDiemSV(&hmSV, &hmMH);
            break;
        case 12:
            chucNang_BangDiemLopHP(&hmLop, &hmMH);
            break;
        case 13:
            chucNang_SapXepSV(headLop, &hmMH);
            break;
        case 0:
            chucNang_LuuFile(headLop, headMH);
            printf("Tam biet!\n");

            // giai phong het bo nho truoc khi thoat
            hmLopHuy(&hmLop);
            hmSVHuy(&hmSV);
            hmMonHocHuy(&hmMH);
            while (headLop) {
                Lop *tmp = headLop->next;
                SinhVien *sv = headLop->danhSachSV;
                while (sv) {
                    SinhVien *tmpSV = sv->next;
                    BangDiem *bd = sv->danhSachDiem;
                    while (bd) {
                        BangDiem *tmpBD = bd->next;
                        free(bd);
                        bd = tmpBD;
                    }
                    free(sv);
                    sv = tmpSV;
                }
                free(headLop);
                headLop = tmp;
            }
            while (headMH) {
                MonHoc *tmp = headMH->next;
                free(headMH);
                headMH = tmp;
            }
            return 0;
        default:
            printf("Lua chon khong hop le, vui long chon tu 0 den 13.\n");
            break;
        }
    }
}
