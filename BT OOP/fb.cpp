#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct date
{
    int day;
    int month;
    int year;
};
typedef struct date DATE;

void ReadDate(ifstream &filein, DATE &date)
{
    filein >> date.day;
    filein.seekg(1, ios::cur);
    filein >> date.month;
    filein.seekg(1, ios::cur);
    filein >> date.year;
}

struct sinhvien
{
    string hoten;
    string mssv;
    DATE ngaysinh;
    float dtb;
};
typedef struct sinhvien SINHVIEN;

struct node
{
    SINHVIEN data;
    struct node *pNext = NULL;
};
typedef struct node NODE;

struct list
{
    NODE *pHead;
    NODE *pTail;
};
typedef struct list LIST;

void KhoiTaoDS(LIST &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}

NODE *KhoiTaoNode(SINHVIEN x)
{
    NODE *p = new NODE;
    if (p == NULL)
    {
        cout << "\nKhong du bo nho de cap phat!";
        return NULL;
    }
    p->data = x;
    p->pNext = NULL;
    return p;
}

void ThemVaoCuoi(LIST &l, NODE *p)
{
    if (l.pHead == NULL)
    {
        l.pHead = l.pTail = p;
    }
    l.pTail->pNext = p;
    l.pTail = p;
}

// void DocThongTin1ThangSinhVien(ifstream &filein, SINHVIEN &sv)
// {
//     getline(filein, sv.hoten, ',');
//     filein.seekg(1, ios::cur);
//     getline(filein, sv.mssv, ',');
//     filein.seekg(1, ios::cur);
//     ReadDate(filein, sv.ngaysinh);
//     filein.seekg(2, ios::cur);
//     filein >> sv.dtb;
//     string temp;
//     getline(filein, temp);
// }

void Doc_Danh_Sach_SinhVien(ifstream &filein, LIST &l)
{

    while (filein.eof() == false)
    {
        SINHVIEN sv;
        // DocThongTin1ThangSinhVien(filein, sv);
        getline(filein, sv.hoten, ',');
        filein.seekg(1, ios::cur);
        getline(filein, sv.mssv, ',');
        filein.seekg(1, ios::cur);
        ReadDate(filein, sv.ngaysinh);
        filein.seekg(2, ios::cur);
        filein >> sv.dtb;
        NODE *p = KhoiTaoNode(sv);
        ThemVaoCuoi(l, p);
    }
}

void Xuat(SINHVIEN sv)
{
    cout << "\nHo ten:" << sv.hoten;
    cout << "\nMa so sinh vien:" << sv.mssv;
    cout << "\nNgay sinh:" << sv.ngaysinh.day << "/" << sv.ngaysinh.month << "/" << sv.ngaysinh.year;
    cout << "\nDiem trung binh:" << sv.dtb;
}

void XuatDanhSachSinhVien(LIST l)
{
    int dem = 1;
    NODE *current = l.pHead; // Con trỏ current để duyệt danh sách
    while (current != NULL)
    {
        cout << "Sinh vien thu " << dem++ << "\n";
        Xuat(current->data);
        current = current->pNext;
    }
}

int main()
{
    SINHVIEN sv;
    LIST l;
    KhoiTaoDS(l);
    // mở file lên
    ifstream filein("SINHVIEN.txt");
    if (!filein.is_open())
    {
        cout << "fail\n";
        exit(1);
    }
    cout << "HNT\n";
    Doc_Danh_Sach_SinhVien(filein, l);
    XuatDanhSachSinhVien(l);

    // đóng file
    filein.close();
    system("pause");
    return 0;
}