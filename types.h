#ifndef TYPES_H
#define TYPES_H

#define HASH_SIZE 10007 // so nguyen to, giup phan bo deu trong bang bam

// bang diem cua sinh vien (moi node la 1 mon)
typedef struct BangDiem {
    char maMon[20];
    float diemHe10;
    struct BangDiem *next;
    struct BangDiem *prev;
} BangDiem;

typedef struct SinhVien {
    char mssv[20];
    char hoVaTen[100];
    char ngaySinh[11]; // DD/MM/YYYY
    char email[100];
    char sdt[15];
    char maLop[20];
    BangDiem *danhSachDiem; // danh sach lien ket chua diem tung mon
    BangDiem *tailDiem;
    struct SinhVien *next;
    struct SinhVien *prev;
} SinhVien;

typedef struct MonHoc {
    char maMon[20];
    char tenMon[100];
    int soTinChi;
    struct MonHoc *next;
    struct MonHoc *prev;
} MonHoc;

typedef struct Lop {
    char maLop[20];
    char tenLop[100];
    char chuNhiemLop[100];
    int soLuongSinhVien;
    SinhVien *danhSachSV;
    SinhVien *tailSV;
    struct Lop *next;
    struct Lop *prev;
} Lop;

// moi o trong bang bam la 1 danh sach lien ket (xu ly xung dot bang chaining)
typedef struct EntryLop {
    char key[20];
    Lop *lop;
    struct EntryLop *next;
} EntryLop;

typedef struct EntrySV {
    char key[20];
    SinhVien *sv;
    struct EntrySV *next;
} EntrySV;

typedef struct EntryMonHoc {
    char key[20];
    MonHoc *monHoc;
    struct EntryMonHoc *next;
} EntryMonHoc;

typedef struct {
    EntryLop *buckets[HASH_SIZE];
} HashMapLop;

typedef struct {
    EntrySV *buckets[HASH_SIZE];
} HashMapSV;

typedef struct {
    EntryMonHoc *buckets[HASH_SIZE];
} HashMapMonHoc;

#endif
