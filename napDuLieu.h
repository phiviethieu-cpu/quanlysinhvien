#ifndef DATA_H
#define DATA_H

#include "types.h"
#include "hashmap.h"

void napDuLieu(const char *fileLopPath, const char *fileSVPath,
               const char *fileMHPath, const char *fileDiemPath,
               Lop **headLop, Lop **tailLop,
               MonHoc **headMH, MonHoc **tailMH,
               HashMapLop *hmLop, HashMapSV *hmSV,
               HashMapMonHoc *hmMH);

#endif
