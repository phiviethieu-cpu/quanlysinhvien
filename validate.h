#ifndef VALIDATE_H
#define VALIDATE_H

int isValidMSSV(const char *mssv);
int isValidHoVaTen(const char *ten);
int isValidNgaySinh(const char *ngay);
int isValidEmail(const char *email);
int isValidSDT(const char *sdt);
int isValidMaLop(const char *maLop);
int isValidMaMon(const char *maMon);
int isValidDiem(const char *input, float *out);
int isValidSoTinChi(const char *input, int *out);

int laNamNhuan(int nam);
int soNgayHopLe(int ngay, int thang, int nam);

#endif
