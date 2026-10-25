
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct {
    char maSinhVien[30];
    char tenSinhVien[100];
    char bienSoXe[30];
    char loaiXe[20];
    int dangHoatDong;
} VeThang;

typedef struct {
    char bienSoXe[30];
    char loaiXe[20];
    char maVeThang[30];
    int daRaKhoiBai;
    double tienPhi;
} LuotXe;

LuotXe danhSachLuotXe[MAX];
VeThang danhSachVeThang[MAX];

int soLuongLuotXe = 0;
int soLuongVeThang = 0;

double giaXeMay = 4000;
double giaOTo = 20000;
double giaVeThangXeMay = 100000;
double giaVeThangOTo = 500000;

void xoaDong() {
    int kyTu;
    while ((kyTu = getchar()) != '\n' && kyTu != EOF);
}

int main() {
    int luaChon;

    do {
        printf("\n=== QUAN LY BAI GIU XE ===\n");
        printf("1. Hien thi danh sach luot gui xe\n");
        printf("2. Tiep nhan xe vao bai\n");
        printf("3. Ghi nhan xe ra khoi bai\n");
        printf("4. Tim kiem theo bien so xe\n");
        printf("5. Quan ly thong tin ve thang\n");
        printf("6. Thiet lap gia ve gui xe\n");
        printf("7. Dang ky ve thang cho sinh vien\n");
        printf("8. Khoa ve thang\n");
        printf("9. Thong ke so luot xe vao va ra\n");
        printf("10. Thong ke doanh thu\n");
        printf("0. Thoat chuong trinh\n");
        printf("Nhap lua chon: ");

        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le!\n");
            xoaDong();
            continue;
        }

        xoaDong();

        if (luaChon == 1) {
            printf("\n--- DANH SACH LUOT GUI XE ---\n");

            for (int i = 0; i < soLuongLuotXe; i++) {
                printf("Bien so xe: %s | Loai xe: %s | Trang thai: %s\n",
                    danhSachLuotXe[i].bienSoXe,
                    danhSachLuotXe[i].loaiXe,
                    danhSachLuotXe[i].daRaKhoiBai
                        ? "Da ra khoi bai"
                        : "Dang trong bai");
            }

            if (soLuongLuotXe == 0) {
                printf("Chua co luot gui xe nao!\n");
            }
        }

        else if (luaChon == 2) {
            if (soLuongLuotXe >= MAX) {
                printf("Danh sach luot gui xe da day!\n");
                continue;
            }

            LuotXe xe;
            int xeDaTrongBai = 0;

            printf("Nhap bien so xe: ");
            scanf("%29s", xe.bienSoXe);

            for (int i = 0; i < soLuongLuotXe; i++) {
                if (strcmp(danhSachLuotXe[i].bienSoXe,
                           xe.bienSoXe) == 0
                    && !danhSachLuotXe[i].daRaKhoiBai) {
                    xeDaTrongBai = 1;
                    break;
                }
            }

            if (xeDaTrongBai) {
                printf("Xe nay dang o trong bai!\n");
                xoaDong();
                continue;
            }

            printf("Nhap loai xe (XeMay/Oto): ");
            scanf("%19s", xe.loaiXe);
            xoaDong();

            if (strcmp(xe.loaiXe, "XeMay") != 0
                && strcmp(xe.loaiXe, "Oto") != 0) {
                printf("Loai xe khong hop le!\n");
                continue;
            }

            xe.maVeThang[0] = '\0';
            xe.daRaKhoiBai = 0;
            xe.tienPhi = 0;

            for (int i = 0; i < soLuongVeThang; i++) {
                if (strcmp(danhSachVeThang[i].bienSoXe,
                           xe.bienSoXe) == 0
                    && danhSachVeThang[i].dangHoatDong
                    && strcmp(danhSachVeThang[i].loaiXe,
                              xe.loaiXe) == 0) {
                    strcpy(xe.maVeThang,
                           danhSachVeThang[i].maSinhVien);
                    break;
                }
            }

            danhSachLuotXe[soLuongLuotXe++] = xe;

            printf("Tiep nhan xe vao bai thanh cong!\n");
        }

        else if (luaChon == 3) {
            char bienSoCanTim[30];
            int timThay = 0;

            printf("Nhap bien so xe can ra khoi bai: ");
            scanf("%29s", bienSoCanTim);
            xoaDong();

            for (int i = soLuongLuotXe - 1; i >= 0; i--) {
                if (strcmp(danhSachLuotXe[i].bienSoXe,
                           bienSoCanTim) == 0
                    && !danhSachLuotXe[i].daRaKhoiBai) {

                    danhSachLuotXe[i].daRaKhoiBai = 1;

                    if (danhSachLuotXe[i].maVeThang[0] != '\0') {
                        danhSachLuotXe[i].tienPhi = 0;
                    }
                    else if (strcmp(danhSachLuotXe[i].loaiXe,
                                    "Oto") == 0) {
                        danhSachLuotXe[i].tienPhi = giaOTo;
                    }
                    else {
                        danhSachLuotXe[i].tienPhi = giaXeMay;
                    }

                    printf("Xe da ra khoi bai thanh cong!\n");
                    printf("Tien phi gui xe: %.0f VND\n",
                           danhSachLuotXe[i].tienPhi);

                    timThay = 1;
                    break;
                }
            }

            if (!timThay) {
                printf("Khong tim thay xe dang trong bai!\n");
            }
        }

        else if (luaChon == 4) {
            char bienSoCanTim[30];
            int timThay = 0;

            printf("Nhap bien so xe can tim: ");
            scanf("%29s", bienSoCanTim);
            xoaDong();

            for (int i = 0; i < soLuongLuotXe; i++) {
                if (strcmp(danhSachLuotXe[i].bienSoXe,
                           bienSoCanTim) == 0) {
                    printf("Bien so xe: %s | Loai xe: %s | Trang thai: %s\n",
                        danhSachLuotXe[i].bienSoXe,
                        danhSachLuotXe[i].loaiXe,
                        danhSachLuotXe[i].daRaKhoiBai
                            ? "Da ra khoi bai"
                            : "Dang trong bai");

                    timThay = 1;
                }
            }

            if (!timThay) {
                printf("Khong tim thay thong tin xe!\n");
            }
        }

        else if (luaChon == 5) {
            printf("\n--- DANH SACH VE THANG ---\n");

            for (int i = 0; i < soLuongVeThang; i++) {
                printf("Mssv: %s | Ten sinh vien: %s | Bien so xe: %s | Loai xe: %s | Trang thai ve: %s\n",
                    danhSachVeThang[i].maSinhVien,
                    danhSachVeThang[i].tenSinhVien,
                    danhSachVeThang[i].bienSoXe,
                    danhSachVeThang[i].loaiXe,
                    danhSachVeThang[i].dangHoatDong
                        ? "Dang hoat dong"
                        : "Da khoa");
            }

            if (soLuongVeThang == 0) {
                printf("Chua co ve thang nao!\n");
            }
        }

        else if (luaChon == 6) {
            double giaMoiXeMay, giaMoiOTo;

            printf("Nhap gia gui xe may moi: ");
            if (scanf("%lf", &giaMoiXeMay) != 1
                || giaMoiXeMay < 0) {
                printf("Gia ve khong hop le!\n");
                xoaDong();
                continue;
            }

            printf("Nhap gia gui o to moi: ");
            if (scanf("%lf", &giaMoiOTo) != 1
                || giaMoiOTo < 0) {
                printf("Gia ve khong hop le!\n");
                xoaDong();
                continue;
            }

            giaXeMay = giaMoiXeMay;
            giaOTo = giaMoiOTo;
            xoaDong();

            printf("Cap nhat gia ve thanh cong!\n");
        }

        else if (luaChon == 7) {
            if (soLuongVeThang >= MAX) {
                printf("Danh sach ve thang da day!\n");
                continue;
            }

            VeThang ve;
            int daDangKy = 0;

            printf("Mssv: ");
            scanf("%29s", ve.maSinhVien);
            xoaDong();

            for (int i = 0; i < soLuongVeThang; i++) {
                if (strcmp(danhSachVeThang[i].maSinhVien,
                           ve.maSinhVien) == 0
                    && danhSachVeThang[i].dangHoatDong) {
                    daDangKy = 1;
                    break;
                }
            }

            if (daDangKy) {
                printf("Sinh vien da co ve thang dang hoat dong!\n");
                continue;
            }

            printf("Nhap ten sinh vien: ");
            fgets(ve.tenSinhVien, sizeof(ve.tenSinhVien), stdin);
            ve.tenSinhVien[strcspn(ve.tenSinhVien, "\n")] = '\0';

            printf("Nhap bien so xe: ");
            scanf("%29s", ve.bienSoXe);

            printf("Nhap loai xe (XeMay/Oto): ");
            scanf("%19s", ve.loaiXe);
            xoaDong();

            if (strcmp(ve.loaiXe, "XeMay") != 0
                && strcmp(ve.loaiXe, "Oto") != 0) {
                printf("Loai xe khong hop le!\n");
                continue;
            }

            ve.dangHoatDong = 1;
            danhSachVeThang[soLuongVeThang++] = ve;

            printf("Dang ky ve thang thanh cong!\n");
            printf("Tien ve thang: %.0f VND\n",
                strcmp(ve.loaiXe, "Oto") == 0
                    ? giaVeThangOTo
                    : giaVeThangXeMay);
        }

        else if (luaChon == 8) {
            char maSinhVien[30];
            int timThay = 0;

            printf("Mssv can khoa ve thang: ");
            scanf("%29s", maSinhVien);
            xoaDong();

            for (int i = 0; i < soLuongVeThang; i++) {
                if (strcmp(danhSachVeThang[i].maSinhVien,
                           maSinhVien) == 0
                    && danhSachVeThang[i].dangHoatDong) {

                    danhSachVeThang[i].dangHoatDong = 0;
                    printf("Khoa ve thang thanh cong!\n");
                    timThay = 1;
                    break;
                }
            }

            if (!timThay) {
                printf("Khong tim thay ve thang dang hoat dong!\n");
            }
        }

        else if (luaChon == 9) {
            int soXeTrongBai = 0;
            int soLuotXeDaRa = 0;

            for (int i = 0; i < soLuongLuotXe; i++) {
                if (danhSachLuotXe[i].daRaKhoiBai) {
                    soLuotXeDaRa++;
                }
                else {
                    soXeTrongBai++;
                }
            }

            printf("So xe dang trong bai: %d\n", soXeTrongBai);
            printf("So luot xe da ra khoi bai: %d\n", soLuotXeDaRa);
            printf("Tong so luot gui xe: %d\n", soLuongLuotXe);
        }

        else if (luaChon == 10) {
            double tongDoanhThu = 0;

            for (int i = 0; i < soLuongLuotXe; i++) {
                tongDoanhThu += danhSachLuotXe[i].tienPhi;
            }

            printf("Tong tien phi gui xe da thu: %.0f VND\n",
                   tongDoanhThu);

            printf("Luu y: Doanh thu ve thang chua duoc ghi nhan tu giao dich thanh toan.\n");
        }

        else if (luaChon != 0) {
            printf("Lua chon khong hop le!\n");
        }

    } while (luaChon != 0);

    printf("Da thoat chuong trinh!\n");

    return 0;
}

