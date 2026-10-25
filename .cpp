#include <stdio.h>
#include <string.h> 
#define MAX 1000
struct luotXe {
	int maVe;
	char bienSo[20];
	char loaiXe[20];
	char maSinhVien[20];
	int gioVao, phutVao;
	int gioRa, phutRa;
	float tienVe;
}; 

struct theXe {
	char maThe[20];
	char maSinhVien[20];
	char bienSo[20];
	char loaiXe[20];
	int dangHoatDong;
}; 

struct luotXe ds[MAX];
struct theXe dsThe[MAX];
int soLuong = 0, soLuongThe = 0;
float giaXeMay = 4000, giaOTo = 10000;

void xoaDongNhap(void){
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

void nhapChuoi(const char *thongBao, char *s, int kichThuoc) {
	printf("%s", thongBao);
	if (fgets(s, kichThuoc, stdin) != NULL){
		size_t n = strlen(s);
		if (n > 0 && s[n - 1] == '\n'){
			s[n - 1] = '\0';
		}
		else{
			xoaDongNhap ();
		}
	}
}

int timViTriMaVe (int maVe) {
	int i; 
	for(i = 0; i < soLuong; i++) {
		if (ds[i].maVe == maVe){
			return i;
		}
	}
	return -1;		
}

int timViTriBienSoDangGui(const char *bienSo) {
	int i;
	for (i = 0; i < soLuong; i++){
		if (strcmp(ds[i].bienSo, bienSo) == 0 && ds[i].gioRa == -1) {
			return i;
		}
	}
	return -1;
}

int gioPhutHopLe(int gio, int phut){
	return gio >= 0 && gio <=23 && phut >=0 && phut <=59;
}

void hienThiMotLuotXe (struct luotXe x) {
	printf("%-8d %-14s %-10s %-14s %02d:%02d  ", x.maVe, x.bienSo, x.loaiXe,
			x.maSinhVien[0] ? x.maSinhVien : "-", x.gioVao, x.phutVao);
	if (x.gioRa == -1) {
		printf("%-8s", "Dang gui");
	} 
	else {
		printf("%02d:%02d  ", x.gioRa, x.phutRa);
	}
	printf("%-10.0f", x.tienVe);
}

void hienThiDanhSachXe (void) {
	int i;
	if (soLuong == 0) {
		printf("Danh sach luot xe dang trong");
		return;
		printf("%-8s %-14s %-10s %-14s %-7s %-8s %-10s %-10s",
				"Ma ve", "Bien so", "Loai xe", "MSSV", "Gio vao", "Gio ra", "Tien ve");
		for (int i = 0; i < soLuong; i++){
			hienThiMotLuotXe (ds[i]);
		}
	}
}

void ghiNhanXeVao(void){
	struct luotXe x;
	int ma;
	if (soLuong >= MAX) {
		printf("Danh sach da day");
		return;
	}
	printf("Nhap ma ve: ");
	if (scanf("%d", &ma) != 1){
		printf("Ma ve khong hop le");
		xoaDongNhap ();
		return;
	}
	xoaDongNhap();
	if (ma <= 0 || timViTriMaVe(ma) != -1) {
		printf("Ma ve phai duong va khong duoc trung");
		return;
	}
	x.maVe = ma;
	nhapChuoi("Nhap bien so xe: ", x.bienSo, sizeof(x.bienSo));
	if (strlen(x.bienSo) == 0){
		printf("Bien so khong hop le");
		return;
	}
	if(timViTriBienSoDangGui(x.bienSo) != -1){
		printf("Xe dang gui trong bai");
		return;
	}
	nhapChuoi("Nhap loai xe: ", x.loaiXe, sizeof(x.loaiXe));
	if (strcmp(x.loaiXe, "Xe may") != 0 && strcmp(x.loaiXe, "Oto") != 0 ){
		printf("Loai xe chi nhan Xe may hoac Oto");
		return;
	}
	nhapChuoi("Nhap ma sinh vien (bo trong neu khong co): ", x.maSinhVien, sizeof(x.maSinhVien));
	printf("Nhap gio vao va phut vao: ");
	if(scanf("%d%d", &x.gioVao, &x.phutVao) != 2){
		printf("Thoi gian khong hop le");
		xoaDongNhap();
		return;
	}
	xoaDongNhap();
	if(!gioPhutHopLe(x.gioVao, x.phutVao)) {
		printf("Thoi gian khong hop le");
		return;
	}	
	x.gioRa = -1; x.phutRa = -1; x.tienVe;
	ds[soLuong++] = x;
	printf("Da ghi nhan xe vao");
}

void ghiNhanXeRa(void){
	int ma, gio, phut, viTri;
	printf("Nhap ma ve: ");
	if(scanf("%d", &ma) != 1){
		printf("Ma ve khong hop le");
		xoaDongNhap();
		return;
	}
	printf("Nhap gio ra va phut ra: ");
	if(scanf("%d%d", &gio, &phut) != 2){
		printf("Thoi gian khong hop le");
		xoaDongNhap ();
		return;
	}
	xoaDongNhap();
	viTri = timViTriMaVe(ma);
	if (viTri == -1){
		printf("Khong tim thay ma ve");
		return;
	}
	if(ds[viTri].gioRa != -1){
		printf("Luot xe nay da ket thuc");
		return;
	}
	if(!gioPhutHopLe(gio, phut)) {
		printf("Khong hop le");
		return;
	}
	if(gio * 60 + phut < ds[viTri].gioVao * 60 + ds[viTri].phutVao){
		printf("Gio ra khong duoc truoc gio vao cung ngay");
		return;
	}
	ds[viTri].gioVao = gio; ds[viTri].phutRa = phut;
	ds[viTri].tienVe = strcmp(ds[viTri].loaiXe, "xe may") == 0 ? giaXeMay : giaOTo;
	printf("Da ghi nhan xe ra. Phi gui xe: %.0f VND", ds[viTri].tienVe);
	}
	
	
void menu () {
	printf(" =====QUAN LY BAI GIU XE=====\n");
	printf("1. Hien thi danh sach xe\n");
	printf("2.Ghi nhan xe vao\n");
	printf("3. Ghi nhan xe ra\n");
	printf("4. Tim kiem theo bien so xe hoac ma the xe\n");
	printf("5. Quan ly thong tin the xe\n");
	printf("6. Thiet lap gia ve\n");
	printf("7. Cap nhap sinh vien mua ve thang\n");
	printf("8. Cap nhap du lieu xe ve thang\n");
	printf("9. Thong ke so xe vao / ra hang ngay\n");
	printf("10. Thong ke doanh thu theo ngay/ thang\n");
	printf("0. Thoat");
}
int main (){
		int luaChon;
		
		do {
			menu ();
			
			printf("Nhap lua chon: ");
			scanf("%d", &luaChon);
				
			switch (luaChon) {
				case 1: 
					hienThiDanhSachXe ();
					break;
				case 2:
					ghiNhanXeVao ();
					break;
				case 3:
					ghiNhanXeRa ();
					break;
				case 4: 
					timKiemXe ();
					break;
				case 5:
					quanLyThongTinThe ();
					break;
				case 6:
					thietLapGiaVe ();
					break;
				case 7:
					capNhapSinhVienVeThang ();
					break;
				case 8:
					capNhapXeVeThang ();
					break;
				case 9:
					thongKeSoXe ();
					break;
				case 10:
					thongKeDoanhThu ();
					break;
				case 0:
					printf("Ket thuc chuong trinh!");
					break;
				default:
					printf("Lua chon khong hop le!");
			}
			
		}
		while (luaChon != 0);
		return 0;
}
