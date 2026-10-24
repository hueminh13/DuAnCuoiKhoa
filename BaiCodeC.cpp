#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct VeThang {
    string maSV, tenSV, bienSo, loai;
    bool active;
};

struct LuotXe {
    string maLuot, bienSo, loai, maVeThang;
    bool daRa;
    double tien;
};

vector<LuotXe> dsLuotXe;
vector<VeThang> dsVeThang;
double giaMay = 5000, giaOto = 20000;
double giaVTMay = 100000, giaVTOto = 500000;

int main() {
    int chon;
    do {
        cout << "\n=== QUAN LY BAI GIU XE ===\n"
             << "1. Hien thi danh sach luot xe\n"
             << "2. Tiep nhan xe vao bai\n"
             << "3. Ghi nhan xe ra\n"
             << "4. Tim kiem theo bien so hoac ma\n"
             << "5. Quan ly thong tin ve thang\n"
             << "6. Thiet lap gia ve\n"
             << "7. Dang ky ve thang cho sinh vien\n"
             << "8. Khoa ve thang\n"
             << "9. Thong ke so xe vao/ra\n"
             << "10. Thong ke doanh thu\n"
             << "0. Thoat\n"
             << "Chon chuc nang: ";
        cin >> chon;

        if (chon == 1) {
            cout << "\n--- DANH SACH LUOT XE ---\n";
            for (size_t i = 0; i < dsLuotXe.size(); i++) {
                cout << "Ma: " << dsLuotXe[i].maLuot
                     << " | BS: " << dsLuotXe[i].bienSo
                     << " | Loai: " << dsLuotXe[i].loai
                     << " | Trang thai: "
                     << (dsLuotXe[i].daRa ? "Da ra" : "Trong bai")
                     << endl;
            }
        }
        else if (chon == 2) {
            LuotXe x;
            cout << "Ma luot xe: "; cin >> x.maLuot;
            cout << "Bien so xe: "; cin >> x.bienSo;
            cout << "Loai xe (XeMay/Oto): "; cin >> x.loai;

            x.maVeThang = "";
            x.daRa = false;
            x.tien = 0;

            for (size_t i = 0; i < dsVeThang.size(); i++) {
                if (dsVeThang[i].bienSo == x.bienSo && dsVeThang[i].active) {
                    x.maVeThang = dsVeThang[i].maSV;
                }
            }

            dsLuotXe.push_back(x);
            
            cout << "-> Tiep nhan xe vao thanh cong!\n";
        }
        else if (chon == 3) {
            string id;
            cout << "Nhap ma luot hoac bien so xe ra: ";
            cin >> id;

            for (size_t i = 0; i < dsLuotXe.size(); i++) {
                if ((dsLuotXe[i].maLuot == id || dsLuotXe[i].bienSo == id)
                    && !dsLuotXe[i].daRa) {
                    dsLuotXe[i].daRa = true;
                    dsLuotXe[i].tien = dsLuotXe[i].maVeThang.empty()
                        ? (dsLuotXe[i].loai == "Oto" ? giaOto : giaMay)
                        : 0;

                    cout << "-> Xe ra thanh cong. Tien phi: "
                         << dsLuotXe[i].tien << " VND\n";
                }
            }
        }
        else if (chon == 4) {
            string k;
            cout << "Nhap bien so hoac ma: ";
            cin >> k;

            for (size_t i = 0; i < dsLuotXe.size(); i++) {
                if (dsLuotXe[i].bienSo == k || dsLuotXe[i].maLuot == k) {
                    cout << "Tim thay -> Ma: " << dsLuotXe[i].maLuot
                         << ", BS: " << dsLuotXe[i].bienSo
                         << ", Trang thai: "
                         << (dsLuotXe[i].daRa ? "Da ra" : "Trong bai")
                         << endl;
                }
            }
        }
        else if (chon == 5) {
            cout << "\n--- DANH SACH VE THANG ---\n";
            for (size_t i = 0; i < dsVeThang.size(); i++) {
                cout << "SV: " << dsVeThang[i].maSV
                     << " - " << dsVeThang[i].tenSV
                     << " | BS: " << dsVeThang[i].bienSo
                     << " | Trang thai: "
                     << (dsVeThang[i].active ? "Hoat dong" : "Khoa")
                     << endl;
            }
        }
        else if (chon == 6) {
            cout << "Gia xe may moi: "; cin >> giaMay;
            cout << "Gia o to moi: "; cin >> giaOto;
            cout << "-> Da cap nhat gia ve!\n";
        }
        else if (chon == 7) {
            VeThang vt;
            cout << "Ma sinh vien: "; cin >> vt.maSV;
            cin.ignore();
            cout << "Ten sinh vien: "; getline(cin, vt.tenSV);
            cout << "Bien so xe: "; cin >> vt.bienSo;
            cout << "Loai xe (XeMay/Oto): "; cin >> vt.loai;

            vt.active = true;
            dsVeThang.push_back(vt);
            cout << "-> Dang ky ve thang thanh cong!\n";
        }
        else if (chon == 8) {
            string ma;
            cout << "Nhap ma SV can khoa: ";
            cin >> ma;

            bool found = false;
            for (size_t i = 0; i < dsVeThang.size(); i++) {
                if (dsVeThang[i].maSV == ma) {
                    dsVeThang[i].active = false;
                    cout << "-> Da khoa ve thang!\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "-> Khong tim thay ma sinh vien nay!\n";
            }
        }
        else if (chon == 9) {
            int trongBai = 0, daRa = 0;
            for (size_t i = 0; i < dsLuotXe.size(); i++) {
                if (dsLuotXe[i].daRa) {
                    daRa++;
                } else {
                    trongBai++;
                }
            }

            cout << "Dang trong bai: " << trongBai
                 << " | Da ra: " << daRa << endl;
        }
        else if (chon == 10) {
            double tong = 0;
            for (size_t i = 0; i < dsLuotXe.size(); i++) {
                tong += dsLuotXe[i].tien;
            }

            for (size_t i = 0; i < dsVeThang.size(); i++) {
                if (dsVeThang[i].active) {
                    tong += dsVeThang[i].loai == "Oto"
                        ? giaVTOto
                        : giaVTMay;
                }
            }

            cout << "Tong doanh thu: " << tong << " VND\n";
        }
    } while (chon != 0);

    return 0;
}
