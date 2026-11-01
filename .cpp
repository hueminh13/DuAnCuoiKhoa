#include <stdio.h>
#include <string.h>

typedef struct{
	char maSinhVien[20];
	char tenSinhVien[50];
	char bienSoXe[30];
	char loaiXe[20];
	int dangHoatDong;
} VeThang;

typedef struct{
	char bienSoXe[30];
	char loaiXe[20];
	char maVeThang[30];
	int daRaKhoiBai;
	float tienPhi;
}LuotXe;

LuotXe dsLuotXe[1000];
VeThang dsVeThang[1000];

int soLuongLuotXe = 0;
int soLuongVeThang = 0;

float giaXeMay = 4000;
float giaOTo = 20000;
float giaVeThangXeMay = 100000;
float giaVeThangOTo = 500000;
float doanhThuVeThang = 0;

void xoaDong(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
} 

int nhapChuoi(const char *loiNhac, char s[], int kichThuoc) {
	size_t len;
	int c;
	printf("%s", loiNhac);
	if (fgets(s, kichThuoc, stdin) == NULL) {
		return 0;
	}
	len = strlen(s);
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
	}
	else {
		c = getchar ();
		if (c != '\n' && c != EOF) {
			while ((c = getchar ()) != '\n' && c != EOF) {}
			s[0] = '\0';
			printf("Du lieu qua dai, vui long nhap lai.");
			return 0;
		}
	}
	
	{
		size_t dau = 0, cuoi = strlen(s), i;
		while (dau < cuoi && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r')) dau++;
		while (cuoi > dau && (s[cuoi - 1] == ' ' || s[cuoi - 1] == '\t' || s[cuoi - 1] == '\r')) cuoi--;
		if (dau > 0) {
			for (i = 0; dau < cuoi; dau++, i++) s[i] = s[dau];
			s[i] = '\0';
		}
		else {
			s[cuoi] = '\0';
		}
	}
	return 1;
} 

int chuoiRong (const char s[]) {
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r' && s[i] != '\n')
			return 0;
	}
	return 1;
}

int nhapChuoiBatBuoc (const char *loiNhac, char s[], int kichThuoc) {
	while (1) {
		if (!nhapChuoi(loiNhac, s, kichThuoc)) continue;
		if (chuoiRong(s)) {
			printf("Khong duoc de trong. Vui long nhap lai.");
			continue;
		}
		return 1;
	}
}

int nhapSoNguyen(const char *loiNhac, int *giaTri) {
	char dong[100], du;
	int n;
	while (1) {
		if (!nhapChuoiBatBuoc(loiNhac, dong, sizeof(dong))) continue;
		if (sscanf(dong, "%d %c", &n, &du) == 1){
			*giaTri = n;
			return 1;
		}
		printf("Vui long nhap mot so nguyen hop le.");
	}
}

int nhapSoThucKhongAm(const char *loiNhac, float *giaTri) {
	char dong[100], du;
	float n;
	while (1) {
		if (!nhapChuoiBatBuoc(loiNhac, dong, sizeof(dong))) continue;
		if (sscanf(dong, "%f %c", &n, &du) == 1 && n >= 0) {
			*giaTri = n;
			return 1;
		}
		printf("Gia tri khong hop le. Hay nhap so lon hon khong");
	}
}

int loaiXeHopLe(const char loai[]) {
	return strcmp(loai, "Xe May") == 0 || strcmp(loai, " Oto") == 0;
}

int timVeTheoMaSV(const char maSV[]) {
	int i;
	for(i = 0; i < soLuongVeThang; i++) {
		if (strcmp(dsVeThang[i].maSinhVien, maSV) == 0) return i;
	}
	return -1;
}

int timVeHoatDongTheoBienSo(const char bienSo[]) {
	int i;
	for (i = 0; i < soLuongVeThang ; i++) {
		if (dsVeThang[i].dangHoatDong &&
			strcmp(dsVeThang[i].bienSoXe, bienSo) == 0) return i;
	}
	return -1;
}

int xeDangTrongBai(const char bienSo[], int boQua) {
	int i;
	for(i = 0; i < soLuongLuotXe; i++)
		if(i != boQua && !dsLuotXe[i].daRaKhoiBai &&
			strcmp(dsLuotXe[i].bienSoXe, bienSo) == 0) return 1;
	return 0;
}

int bienSoCoVeThangHoatDong(const char bienSo[], int boQua) {
	int i;
	for (i = 0; i < soLuongVeThang; i++)
		if (i != boQua && dsVeThang[i].dangHoatDong &&
			strcmp(dsVeThang[i].bienSoXe, bienSo) == 0) return 1;
	return 0;
}

void khoiTaoDuLieuMau(void) {
    strcpy(dsLuotXe[0].bienSoXe, "59A1-12345");
    strcpy(dsLuotXe[0].loaiXe, "Xe May");
    dsLuotXe[0].maVeThang[0] = '\0';
    dsLuotXe[0].daRaKhoiBai = 0;
    dsLuotXe[0].tienPhi = 0;

    strcpy(dsLuotXe[1].bienSoXe, "59B2-67890");
    strcpy(dsLuotXe[1].loaiXe, "Xe May");
    strcpy(dsLuotXe[1].maVeThang, "SV001");
    dsLuotXe[1].daRaKhoiBai = 0;
    dsLuotXe[1].tienPhi = 0;

    strcpy(dsLuotXe[2].bienSoXe, "51A-24680");
    strcpy(dsLuotXe[2].loaiXe, "Oto");
    dsLuotXe[2].maVeThang[0] = '\0';
    dsLuotXe[2].daRaKhoiBai = 0;
    dsLuotXe[2].tienPhi = 0;

    strcpy(dsLuotXe[3].bienSoXe, "50F-13579");
    strcpy(dsLuotXe[3].loaiXe, "Oto");
    strcpy(dsLuotXe[3].maVeThang, "SV002");
    dsLuotXe[3].daRaKhoiBai = 0;
    dsLuotXe[3].tienPhi = 0;

    soLuongLuotXe = 4;
}

void hienThiDanhSach(void) {
	int i, stt = 0;
	printf("================ DANH SACH LUOT GUI XE ================\n");
	if (stt == 0) {
		printf("Danh sach rong. Chua co luot gui xe nao.");
		return;
	}
	printf("| STT  | Bien so        | Loai xe  | Ma ve thang    | Trang thai       | Tien phi     |\n");
	for (i = 0; i < soLuongLuotXe; i++) {
		if (!dsLuotXe[i].daRaKhoiBai) {
            stt++;
		printf("| %-4d | %-14s | %-8s | %-14s | %-16s | %10.0f   |\n",
				stt,
				dsLuotXe[i].bienSoXe,
				dsLuotXe[i].loaiXe,
				dsLuotXe[i].maVeThang[0] ? dsLuotXe[i].maVeThang : "-",
				dsLuotXe[i].daRaKhoiBai ? "Da ra khoi bai" : "Trong bai",
				dsLuotXe[i].tienPhi);
	}
	printf("Tong so xe hien dang trong bai: %d", stt);
}

void tiepNhanXe(void) {
	LuotXe xe;
	int viTriVe;
	if (soLuongLuotXe >= 1000) {
		printf("Danh sach luot gui xe da day!");
		return;
	}
	nhapChuoiBatBuoc("Nhap bien so xe: ", xe.bienSoXe, sizeof(xe.bienSoXe));
	if (xeDangTrongBai(xe.bienSoXe, -1)) {
		printf("Xe nay dang o trong bai!");
		return;
	}
	while (1) {
		nhapChuoiBatBuoc("Nhap loai xe: ", xe.loaiXe, sizeof(xe.loaiXe));
		if (loaiXeHopLe(xe.loaiXe)) break;
		printf("Loai xe khong hop le. Chi nhap Xe may hoac Oto.");
	}
	xe.maVeThang[0] = '\0';
	viTriVe = timVeHoatDongTheoBienSo(xe.bienSoXe);
	if (viTriVe >= 0) {
		if (strcmp(dsVeThang[viTriVe].loaiXe, xe.loaiXe) != 0) {
            printf("Loai xe khong khop voi thong tin ve thang!");
            return;
        }
        strcpy(xe.maVeThang, dsVeThang[viTriVe].maSinhVien);
	}
	xe.daRaKhoiBai = 0;
    xe.tienPhi = 0;
    dsLuotXe[soLuongLuotXe++] = xe;
    printf("Tiep nhan xe vao bai thanh cong!");
}

void ghiNhanXeRa(void) {
    char bienSo[30];
    int i, timThay = 0;
    nhapChuoiBatBuoc("Nhap bien so xe can ra khoi bai: ", bienSo, sizeof(bienSo));
    for (i = soLuongLuotXe - 1; i >= 0; i--) {
        if (strcmp(dsLuotXe[i].bienSoXe, bienSo) == 0 &&
            !dsLuotXe[i].daRaKhoiBai) {
            dsLuotXe[i].daRaKhoiBai = 1;
            if (dsLuotXe[i].maVeThang[0] != '\0') {
                dsLuotXe[i].tienPhi = 0;
            } else if (strcmp(dsLuotXe[i].loaiXe, "Oto") == 0) {
                dsLuotXe[i].tienPhi = giaOTo;
            } else {
                dsLuotXe[i].tienPhi = giaXeMay;
            }
            printf("Xe da ra khoi bai thanh cong!\nTien phi gui xe: %.0f VND",
                   dsLuotXe[i].tienPhi);
            timThay = 1;
            break;
        }
    }
    if (!timThay) printf("Khong tim thay xe dang trong bai!");
}

void timKiemBienSo(void) {
    char bienSo[30];
    int i, timThay = 0;
    nhapChuoiBatBuoc("Nhap bien so xe can tim: ", bienSo, sizeof(bienSo));
    for (i = 0; i < soLuongLuotXe; i++) {
        if (strcmp(dsLuotXe[i].bienSoXe, bienSo) == 0) {
            printf("Bien so: %s | Loai: %s | Trang thai: %s | Phi: %.0f VND",
                   dsLuotXe[i].bienSoXe, dsLuotXe[i].loaiXe,
                   dsLuotXe[i].daRaKhoiBai ? "Da ra khoi bai" : "Dang trong bai",
                   dsLuotXe[i].tienPhi);
            timThay = 1;
        }
    }
    if (!timThay) printf("Khong tim thay thong tin xe!");
}

void quanLyVeThang(void) {
    int i;
    printf("================ DANH SACH VE THANG ================\n");
    if (soLuongVeThang == 0) {
        printf("Danh sach rong. Chua co ve thang nao.");
        return;
    }
    printf("| STT  | Ma sinh vien   | Ten sinh vien        | Bien so        | Loai xe  | Trang thai   |\n");
    for (i = 0; i < soLuongVeThang; i++) {
        printf("| %-4d | %-14s | %-20.20s | %-14s | %-8s | %-12s |\n",
               i + 1,
               dsVeThang[i].maSinhVien,
               dsVeThang[i].tenSinhVien,
               dsVeThang[i].bienSoXe,
               dsVeThang[i].loaiXe,
               dsVeThang[i].dangHoatDong ? "Hoat dong" : "Da khoa");
    }
}

void thietLapGiaVe(void) {
    float gm, go, gvm, gvo;
    nhapSoThucKhongAm("Nhap gia gui xe may moi: ", &gm);
    nhapSoThucKhongAm("Nhap gia gui o to moi: ", &go);
    nhapSoThucKhongAm("Nhap gia ve thang xe may: ", &gvm);
    nhapSoThucKhongAm("Nhap gia ve thang o to: ", &gvo);
    giaXeMay = gm;
    giaOTo = go;
    giaVeThangXeMay = gvm;
    giaVeThangOTo = gvo;
    printf("Cap nhat gia ve thanh cong!");
}

void dangKyVeThang(void) {
    VeThang ve;
    int viTri;
    float phi;
    if (soLuongVeThang >= 1000) {
        printf("Danh sach ve thang da day!\n");
        return;
    }
    nhapChuoiBatBuoc("MSSV: ", ve.maSinhVien, sizeof(ve.maSinhVien));
    if (timVeTheoMaSV(ve.maSinhVien) >= 0) {
        printf("MSSV da ton tai trong danh sach, ke ca ve da khoa!");
        return;
    }
    nhapChuoiBatBuoc("Nhap ten sinh vien: ", ve.tenSinhVien, sizeof(ve.tenSinhVien));
    nhapChuoiBatBuoc("Nhap bien so xe: ", ve.bienSoXe, sizeof(ve.bienSoXe));
    if (bienSoCoVeThangHoatDong(ve.bienSoXe, -1)) {
        printf("Bien so nay da co ve thang hoat dong!");
        return;
    }
    while (1) {
        nhapChuoiBatBuoc("Nhap loai xe: ", ve.loaiXe, sizeof(ve.loaiXe));
        if (loaiXeHopLe(ve.loaiXe)) break;
        printf("Loai xe khong hop le. Chi nhap XeMay hoac Oto.");
    }
    viTri = -1;
    {
        int i;
        for (i = 0; i < soLuongLuotXe; i++) {
            if (!dsLuotXe[i].daRaKhoiBai &&
                strcmp(dsLuotXe[i].bienSoXe, ve.bienSoXe) == 0) {
                viTri = i;
                break;
            }
        }
    }
    if (viTri >= 0 && strcmp(dsLuotXe[viTri].loaiXe, ve.loaiXe) != 0) {
        printf("Loai xe khong khop voi xe dang trong bai!");
        return;
    }
    ve.dangHoatDong = 1;
    dsVeThang[soLuongVeThang++] = ve;
    phi = strcmp(ve.loaiXe, "Oto") == 0 ? giaVeThangOTo : giaVeThangXeMay;
    doanhThuVeThang += phi;
    printf("Dang ky ve thang thanh cong! Phi: %.0f VND", phi);
}

void khoaVeThang(void) {
    char maSV[30];
    int i;
    nhapChuoiBatBuoc("MSSV can khoa ve thang: ", maSV, sizeof(maSV));
    i = timVeTheoMaSV(maSV);
    if (i < 0 || !dsVeThang[i].dangHoatDong) {
        printf("Khong tim thay ve thang dang hoat dong!");
        return;
    }
    dsVeThang[i].dangHoatDong = 0;
    printf("Khoa ve thang thanh cong!");
}

void thongKeLuotXe(void) {
    int i, trongBai = 0, daRa = 0;
    for (i = 0; i < soLuongLuotXe; i++) {
        if (dsLuotXe[i].daRaKhoiBai) daRa++;
        else trongBai++;
    }
    printf("So xe dang trong bai: %d\n", trongBai);
    printf("So luot xe da ra khoi bai: %d\n", daRa);
    printf("Tong so luot gui xe: %d", soLuongLuotXe);
}

void thongKeDoanhThu(void) {
    int i;
    float tong = doanhThuVeThang;
    for (i = 0; i < soLuongLuotXe; i++) tong += dsLuotXe[i].tienPhi;
    printf("Doanh thu ve thang da ghi nhan: %.0f VND\n", doanhThuVeThang);
    printf("Tong tien phi gui xe da thu: %.0f VND\n", tong - doanhThuVeThang);
    printf("Tong doanh thu: %.0f VND\n", tong);
}

void menu () {
	printf(" =====QUAN LY BAI GIU XE=====\n");
	printf("1. Hien thi danh sach xe\n");
	printf("2. Tiep nhan xe vao bai\n");
	printf("3. Ghi nhan xe ra\n");
	printf("4. Tim kiem theo bien so xe\n");
	printf("5. Quan ly thong tin ve thang\n");
	printf("6. Thiet lap gia ve\n");
	printf("7. Dang ky ve thang cho sinh vien\n");
	printf("8. Khoa ve thang\n");
	printf("9. Thong ke so luot xe va vao\n");
	printf("10. Thong ke doanh thu\n");
	printf("0. Thoat chuong trinh\n");
}

void xuLyLuaChon(int luaChon) {
    switch (luaChon) {
        case 1: 
			hienThiDanhSach(); 
			break;
        case 2: 
			tiepNhanXe(); 
			break;
        case 3: 
			ghiNhanXeRa(); 
			break;
        case 4: 
			timKiemBienSo(); 
			break;
        case 5: 
			quanLyVeThang(); 
			break;
        case 6: 
			thietLapGiaVe(); 
			break;
        case 7: 
			dangKyVeThang(); 
			break;
        case 8: 
			khoaVeThang(); 
			break;
        case 9: 
			thongKeLuotXe(); 
			break;
        case 10: 
			thongKeDoanhThu(); 
			break;
        case 0: 
			printf("Da thoat chuong trinh!\\n"); 
			break;
        default: 
			printf("Lua chon khong hop le!\\n");
    }
}

int main(void) {
    int luaChon;
    khoiTaoDuLieuMau();
    do {
        menu();
        if (!nhapSoNguyen("Nhap lua chon: ", &luaChon)) {
            continue;
        }
        xuLyLuaChon(luaChon);
    } 
	while (luaChon != 0);
    return 0;
}
