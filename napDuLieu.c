#include "napDuLieu.h"
#include "hashmap.h"
#include "types.h"
#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void napFileLop(const char *path, Lop **headLop, Lop **tailLop,
                       HashMapLop *hmLop)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Khong tim thay file: %s\n", path);
        return;
    }
    char line[300];
    if (fgets(line, sizeof(line), f) == NULL) { fclose(f); return; }

    while (!feof(f)) {
        Lop tmp = layThongTinLop(f);
        if (tmp.maLop[0] == '\0') continue;
        Lop *node = taoNodeLop(tmp);
        if (!node) continue;
        themVaoLLLop(headLop, tailLop, node);
        hmLopThem(hmLop, node);
    }
    fclose(f);
    printf("Da doc file lop: %s\n", path);
}

void napFileSV(const char *path, HashMapLop *hmLop, HashMapSV *hmSV)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Khong tim thay file: %s\n", path);
        return;
    }
    char line[400];
    if (fgets(line, sizeof(line), f) == NULL) { fclose(f); return; }

    while (!feof(f)) {
        SinhVien tmp = layThongTinSinhVien(f);
        if (tmp.mssv[0] == '\0') continue;
        SinhVien *node = taoNodeSinhVien(tmp);
        if (!node) continue;

        Lop *lop = hmLopTimKiem(hmLop, node->maLop);
        if (lop) {
            themVaoLLSV(&lop->danhSachSV, &lop->tailSV, node);
            lop->soLuongSinhVien++;
        } else {
            printf("Luu y: khong tim thay lop '%s' cho SV %s\n",
                   node->maLop, node->mssv);
        }
        hmSVThem(hmSV, node);
    }
    fclose(f);
    printf("Da doc file sinh vien: %s\n", path);
}

void napFileMonHoc(const char *path, MonHoc **headMH, MonHoc **tailMH,
                          HashMapMonHoc *hmMH)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Khong tim thay file: %s\n", path);
        return;
    }
    char line[300];
    if (fgets(line, sizeof(line), f) == NULL) { fclose(f); return; }

    while (!feof(f)) {
        MonHoc tmp = layThongTinMonHoc(f);
        if (tmp.maMon[0] == '\0') continue;
        MonHoc *node = taoNodeMonHoc(tmp);
        if (!node) continue;
        themVaoLLMonHoc(headMH, tailMH, node);
        hmMonHocThem(hmMH, node);
    }
    fclose(f);
    printf("Da doc file mon hoc: %s\n", path);
}

void napFileDiem(const char *path, HashMapSV *hmSV)
{
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Khong tim thay file: %s\n", path);
        return;
    }
    char line[200];
    if (fgets(line, sizeof(line), f) == NULL) { fclose(f); return; }

    while (fgets(line, sizeof(line), f)) {
        char mssv[20] = "", maMon[20] = "";
        float diem = 0;
        char *token;

        line[strcspn(line, "\n\r")] = '\0';
        if (line[0] == '\0') continue;

        token = strtok(line, ",");
        if (token) strncpy(mssv, token, sizeof(mssv) - 1);

        token = strtok(NULL, ",");
        if (token) strncpy(maMon, token, sizeof(maMon) - 1);

        token = strtok(NULL, ",");
        if (token) diem = (float)atof(token);

        if (mssv[0] == '\0' || maMon[0] == '\0') continue;

        SinhVien *sv = hmSVTimKiem(hmSV, mssv);
        if (!sv) {
            printf("Luu y: khong tim thay SV %s khi doc diem.\n", mssv);
            continue;
        }
        BangDiem *node = taoNodeBangDiem(maMon, diem);
        if (node)
            themVaoLLBangDiem(&sv->danhSachDiem, &sv->tailDiem, node);
    }
    fclose(f);
    printf("Da doc file diem: %s\n", path);
}

void napDuLieu(const char *fileLopPath, const char *fileSVPath,
               const char *fileMHPath, const char *fileDiemPath,
               Lop **headLop, Lop **tailLop,
               MonHoc **headMH, MonHoc **tailMH,
               HashMapLop *hmLop, HashMapSV *hmSV,
               HashMapMonHoc *hmMH)
{
    napFileLop(fileLopPath, headLop, tailLop, hmLop);
    napFileSV(fileSVPath, hmLop, hmSV);
    napFileMonHoc(fileMHPath, headMH, tailMH, hmMH);
    napFileDiem(fileDiemPath, hmSV);
}
