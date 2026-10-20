#include <stdio.h>

struct luotXe {
	int maVe;
	char bienSo[20];
	char loaiXe[20];
	char maSinhVien[20];
	int gioVao, phutVao;
	int gioRa, phutRa;
	float tienVe;
	float doanh thu;
}; 

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
