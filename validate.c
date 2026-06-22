#include "validate.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int laNamNhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

int soNgayHopLe(int ngay, int thang, int nam)
{
    int maxNgay[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (thang < 1 || thang > 12) return 0;
    if (thang == 2 && laNamNhuan(nam)) maxNgay[2] = 29;
    return ngay >= 1 && ngay <= maxNgay[thang];
}

int isValidMSSV(const char *mssv)
{
    int i, len;
    if (!mssv || mssv[0] == '\0') {
        printf("  Loi:MSSV khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(mssv);
    if (len < 1 || len > 19) {
        printf("  Loi:MSSV phai tu 1 den 19 ky tu (hien tai: %d).\n", len);
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = mssv[i];
        int isAlpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        int isDigit = (c >= '0' && c <= '9');
        if (!isAlpha && !isDigit) {
            printf("  Loi:MSSV chi duoc chua chu cai va chu so.\n");
            return 0;
        }
    }
    return 1;
}

int isValidHoVaTen(const char *ten)
{
    int i, len, coKyTuHopLe;
    if (!ten || ten[0] == '\0') {
        printf("  Loi:Khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(ten);
    if (len < 2) {
        printf("  Loi:Qua ngan (toi thieu 2 ky tu).\n");
        return 0;
    }
    if (len > 99) {
        printf("  Loi:Qua dai (toi da 99 ky tu).\n");
        return 0;
    }
    coKyTuHopLe = 0;
    for (i = 0; i < len; i++) {
        if (ten[i] != ' ') { coKyTuHopLe = 1; break; }
    }
    if (!coKyTuHopLe) {
        printf("  Loi:Khong hop le (chi co khoang trang).\n");
        return 0;
    }
    for (i = 0; i < len - 1; i++) {
        if (ten[i] == ' ' && ten[i+1] == ' ') {
            printf("  Loi:Khong duoc co 2 khoang trang lien tiep.\n");
            return 0;
        }
    }
    if (ten[0] == ' ' || ten[len-1] == ' ') {
        printf("  Loi:Khong duoc bat dau hoac ket thuc bang khoang trang.\n");
        return 0;
    }
    return 1;
}

int isValidNgaySinh(const char *ngay)
{
    int dd, mm, yyyy, len;
    if (!ngay || ngay[0] == '\0') {
        printf("  Loi:Ngay sinh khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(ngay);
    if (len != 10) {
        printf("  Loi:Ngay sinh phai dung dinh dang DD/MM/YYYY.\n");
        return 0;
    }
    if (ngay[2] != '/' || ngay[5] != '/') {
        printf("  Loi:Ngay sinh phai dung dinh dang DD/MM/YYYY.\n");
        return 0;
    }
    {
        int pos[] = {0,1,3,4,6,7,8,9};
        int i;
        for (i = 0; i < 8; i++) {
            if (ngay[pos[i]] < '0' || ngay[pos[i]] > '9') {
                printf("  Loi:Ngay sinh chua ky tu khong phai chu so.\n");
                return 0;
            }
        }
    }
    dd   = (ngay[0]-'0')*10 + (ngay[1]-'0');
    mm   = (ngay[3]-'0')*10 + (ngay[4]-'0');
    yyyy = (ngay[6]-'0')*1000 + (ngay[7]-'0')*100 + (ngay[8]-'0')*10 + (ngay[9]-'0');
    if (yyyy < 1900 || yyyy > 2099) {
        printf("  Loi:Nam sinh phai trong khoang 1900-2099.\n");
        return 0;
    }
    if (mm < 1 || mm > 12) {
        printf("  Loi:Thang phai tu 01 den 12.\n");
        return 0;
    }
    if (!soNgayHopLe(dd, mm, yyyy)) {
        printf("  Loi:Ngay %02d khong hop le voi thang %02d nam %04d.\n", dd, mm, yyyy);
        return 0;
    }
    return 1;
}

int isValidEmail(const char *email)
{
    int i, len, posAt, demAt, posDot;
    if (!email || email[0] == '\0') {
        printf("  Loi:Email khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(email);
    if (len > 99) {
        printf("  Loi:Email qua dai (toi da 99 ky tu).\n");
        return 0;
    }
    demAt = 0; posAt = -1;
    for (i = 0; i < len; i++) {
        if (email[i] == '@') { demAt++; posAt = i; }
    }
    if (demAt == 0) { printf("  Loi:Email thieu ky tu '@'.\n"); return 0; }
    if (demAt > 1)  { printf("  Loi:Email chi duoc co mot ky tu '@'.\n"); return 0; }
    if (posAt == 0) { printf("  Loi:Phan truoc '@' bi trong.\n"); return 0; }
    if (posAt >= len - 3) { printf("  Loi:Phan sau '@' qua ngan.\n"); return 0; }
    posDot = -1;
    for (i = posAt + 1; i < len; i++) {
        if (email[i] == '.') posDot = i;
    }
    if (posDot == -1)        { printf("  Loi:Phan domain thieu dau '.'.\n"); return 0; }
    if (posDot == posAt + 1) { printf("  Loi:Dau '.' ngay sau '@'.\n"); return 0; }
    if (posDot == len - 1)   { printf("  Loi:Dau '.' o cuoi.\n"); return 0; }
    for (i = 0; i < len; i++) {
        if (email[i] == ' ') { printf("  Loi:Email khong duoc chua khoang trang.\n"); return 0; }
    }
    return 1;
}

int isValidSDT(const char *sdt)
{
    int i, soDigit, batDau;
    const char *p;
    if (!sdt || sdt[0] == '\0') {
        printf("  Loi:So dien thoai khong duoc de trong.\n");
        return 0;
    }
    p = sdt;
    if (p[0] == '+') p++;
    soDigit = 0;
    for (i = 0; p[i] != '\0'; i++) {
        if (p[i] < '0' || p[i] > '9') {
            printf("  Loi:SDT chi duoc chua chu so va dau '+'.\n");
            return 0;
        }
        soDigit++;
    }
    if (soDigit < 9 || soDigit > 12) {
        printf("  Loi:SDT phai co 9-12 chu so (hien tai: %d).\n", soDigit);
        return 0;
    }
    batDau = 0;
    if (sdt[0] == '0' && soDigit == 10) batDau = 1;
    if (sdt[0] == '+' && p[0] == '8' && p[1] == '4') batDau = 1;
    if (sdt[0] == '8' && sdt[1] == '4' && soDigit == 11) batDau = 1;
    if (soDigit == 9 || soDigit == 12) batDau = 1;
    if (!batDau) {
        printf("  Loi:SDT khong dung dinh dang (VD: 0912345678 hoac +84912345678).\n");
        return 0;
    }
    return 1;
}

int isValidMaLop(const char *maLop)
{
    int i, len;
    if (!maLop || maLop[0] == '\0') {
        printf("  Loi:Ma lop khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(maLop);
    if (len > 19) {
        printf("  Loi:Ma lop qua dai (toi da 19 ky tu).\n");
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = maLop[i];
        int isAlpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        int isDigit = (c >= '0' && c <= '9');
        if (!isAlpha && !isDigit) {
            printf("  Loi:Ma lop chi duoc chua chu cai va chu so.\n");
            return 0;
        }
    }
    return 1;
}

int isValidMaMon(const char *maMon)
{
    int i, len;
    if (!maMon || maMon[0] == '\0') {
        printf("  Loi:Ma mon khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(maMon);
    if (len > 19) {
        printf("  Loi:Ma mon qua dai (toi da 19 ky tu).\n");
        return 0;
    }
    for (i = 0; i < len; i++) {
        char c = maMon[i];
        int isAlpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        int isDigit = (c >= '0' && c <= '9');
        if (!isAlpha && !isDigit) {
            printf("  Loi:Ma mon chi duoc chua chu cai va chu so.\n");
            return 0;
        }
    }
    return 1;
}

int isValidDiem(const char *input, float *out)
{
    float val;
    int i, len;
    if (!input || input[0] == '\0') {
        printf("  Loi: Diem khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(input);
    for (i = 0; i < len; i++) {
        char c = input[i];
        if (c == '-' && i == 0) continue;
        if (c == '.') continue;
        if (c < '0' || c > '9') {
            printf("  Loi: Diem khong hop le, chua ky tu '%c'.\n", c);
            return 0;
        }
    }
    val = atof(input);
    if (val < 0.0f || val > 10.0f) {
        printf("  Loi: Diem phai trong khoang 0.0 - 10.0 (nhap: %.2f).\n", val);
        return 0;
    }
    *out = val;
    return 1;
}

int isValidSoTinChi(const char *input, int *out)
{
    int val, i, len;
    if (!input || input[0] == '\0') {
        printf("  Loi:So tin chi khong duoc de trong.\n");
        return 0;
    }
    len = (int)strlen(input);
    for (i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("  Loi:So tin chi phai la so nguyen duong.\n");
            return 0;
        }
    }
    val = atoi(input);
    if (val < 1 || val > 10) {
        printf("  Loi:So tin chi phai tu 1 den 10 (nhap: %d).\n", val);
        return 0;
    }
    *out = val;
    return 1;
}
