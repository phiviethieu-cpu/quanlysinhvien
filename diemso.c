#include "diemso.h"
#include "hashmap.h"
#include "types.h"

// quy doi diem he 10 sang he 4 theo bang quy dinh
float chuyenDiemHe10SangHe4(float diemHe10)
{
    if (diemHe10 >= 9.5f)  return 4.0f;  // A+
    if (diemHe10 >= 8.5f)  return 4.0f;  // A
    if (diemHe10 >= 8.0f)  return 3.5f;  // B+
    if (diemHe10 >= 7.0f)  return 3.0f;  // B
    if (diemHe10 >= 6.5f)  return 2.5f;  // C+
    if (diemHe10 >= 5.5f)  return 2.0f;  // C
    if (diemHe10 >= 5.0f)  return 1.5f;  // D+
    if (diemHe10 >= 4.0f)  return 1.0f;  // D
    return 0.0f;                         // F
}

// xep loai hoc luc dua tren GPA he 4
const char* xepLoaiHocLuc(float gpaHe4)
{
    if (gpaHe4 >= 3.6f) return "Xuat sac";
    if (gpaHe4 >= 3.2f) return "Gioi";
    if (gpaHe4 >= 2.5f) return "Kha";
    if (gpaHe4 >= 2.0f) return "Trung binh";
    if (gpaHe4 >= 1.0f) return "Yeu";
    return "Kem";
}

// tinh GPA tich luy he 4 (co trong so tin chi)
// cong thuc: tong(diem_he4 * tin_chi) / tong(tin_chi)
float tinhGPA(SinhVien *sv, HashMapMonHoc *hmMH)
{
    float tong = 0;
    int tongTC = 0;
    BangDiem *bd = sv->danhSachDiem;
    while (bd) {
        MonHoc *mh = hmMonHocTimKiem(hmMH, bd->maMon);
        if (mh) {
            tong += chuyenDiemHe10SangHe4(bd->diemHe10) * mh->soTinChi;
            tongTC += mh->soTinChi;
        }
        bd = bd->next;
    }
    if (tongTC == 0) return 0.0f;
    return tong / tongTC;
}
