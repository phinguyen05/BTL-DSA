#include <bits/stdc++.h>

using namespace std;

const int MAX = 10; // Kích thước tối đa của danh sách.

struct SinhVien {
    string maSV;   // Mã sinh viên.
    string hoTen;  // Họ tên sinh viên.
    int namSinh;   // Năm sinh.
    float diemTB;  // Điểm trung bình.
};

SinhVien danhSach[MAX]; // Mảng lưu thông tin sinh viên.
int nextNode[MAX];      // Mảng lưu chỉ số tiếp theo trong danh sách liên kết.
int head = -1;          // Chỉ số đầu danh sách, -1 nghĩa là danh sách rỗng.
int freeIndex = 0;      // Vị trí trống tiếp theo trong mảng.

/// Hàm khởi tạo danh sách liên kết tĩnh.
void khoiTao() {
    for (int i = 0; i < MAX; i++) {
        nextNode[i] = -1; // Gán tất cả phần tử trong mảng liên kết bằng -1 (chưa có nút tiếp theo).
    }
}

// Hàm thêm sinh viên mới vào danh sách.
void themSinhVien(const SinhVien& sv) {
    if (freeIndex >= MAX) { // Kiểm tra nếu mảng đầy.
        cout << "Danh sach day, khong the them moi!\n";
        return;
    }

    danhSach[freeIndex] = sv; // Lưu sinh viên tại vị trí freeIndex.

    if (head == -1) { // Nếu danh sách rỗng, gán nút đầu tiên.
        head = freeIndex;
    } else { // Tìm vị trí cuối cùng trong danh sách và liên kết nó với nút mới.
        int temp = head;
        while (nextNode[temp] != -1) temp = nextNode[temp]; // Duyệt tới nút cuối.
        nextNode[temp] = freeIndex; // Gán nút tiếp theo của nút cuối là nút mới.
    }

    freeIndex++; // Tăng vị trí trống lên.
}

// Hàm đọc dữ liệu sinh viên từ file.
void docFile(const string& fileName) {
    ifstream file(fileName); // Mở file.
    if (!file.is_open()) { // Kiểm tra nếu không thể mở file.
        cout << "Khong the mo file " << fileName << "!\n";
        return;
    }

    while (!file.eof()) { // Đọc dữ liệu từ file cho đến cuối.
        SinhVien sv;
        file >> sv.maSV;           // Đọc mã sinh viên.
        file.ignore();             // Bỏ qua ký tự xuống dòng.
        getline(file, sv.hoTen);   // Đọc họ tên.
        file >> sv.namSinh >> sv.diemTB; // Đọc năm sinh và điểm trung bình.

        themSinhVien(sv); // Thêm sinh viên vào danh sách.
    }

    file.close(); // Đóng file.
    cout << "Da doc du lieu tu file " << fileName << " thanh cong!\n";
}

// Hàm hiển thị danh sách sinh viên.
void hienThiDanhSach() {
    if (head == -1) { // Kiểm tra nếu danh sách rỗng.
        cout << "Danh sach rong!\n";
        return;
    }

    // In tiêu đề bảng.
    cout << setw(10) << "Ma SV" << setw(20) << "Ho Ten" 
         << setw(10) << "Nam Sinh" << setw(10) << "Diem TB" << endl;

    int temp = head;
    while (temp != -1) { // Duyệt danh sách và in thông tin sinh viên.
        cout << setw(10) << danhSach[temp].maSV 
             << setw(20) << danhSach[temp].hoTen 
             << setw(10) << danhSach[temp].namSinh 
             << setw(10) << danhSach[temp].diemTB << endl;
        temp = nextNode[temp]; // Di chuyển tới nút tiếp theo.
    }
}

// Hàm tìm kiếm sinh viên theo mã.
int timKiem(const string& maSV) {
    int temp = head;
    while (temp != -1) { // Duyệt danh sách để tìm sinh viên có mã tương ứng.
        if (danhSach[temp].maSV == maSV) return temp; // Trả về chỉ số nếu tìm thấy.
        temp = nextNode[temp]; // Di chuyển tới nút tiếp theo.
    }
    return -1; // Trả về -1 nếu không tìm thấy.
}

// Hàm xóa sinh viên theo mã.
void xoaSinhVien(const string& maSV) {
    if (head == -1) { // Kiểm tra nếu danh sách rỗng.
        cout << "Danh sach rong!\n";
        return;
    }

    int temp = head, prev = -1;
    while (temp != -1 && danhSach[temp].maSV != maSV) { // Tìm vị trí sinh viên cần xóa.
        prev = temp;
        temp = nextNode[temp];
    }

    if (temp == -1) { // Kiểm tra nếu không tìm thấy sinh viên.
        cout << "Khong tim thay sinh vien co ma: " << maSV << endl;
        return;
    }

    if (prev == -1) { // Nếu sinh viên cần xóa là đầu danh sách.
        head = nextNode[temp];
    } else { // Liên kết nút trước và nút sau của nút cần xóa.
        nextNode[prev] = nextNode[temp];
    }

    cout << "Da xoa sinh vien co ma: " << maSV << endl;
}

// Hàm cập nhật thông tin sinh viên.
void capNhatThongTin(const string& maSV) {
    int idx = timKiem(maSV); // Tìm chỉ số sinh viên.
    if (idx == -1) { // Kiểm tra nếu không tìm thấy.
        cout << "Khong tim thay sinh vien co ma: " << maSV << endl;
        return;
    }

    // Nhập thông tin mới.
    cout << "Nhap thong tin moi:\n";
    cout << "Ho ten: ";
    cin.ignore();
    getline(cin, danhSach[idx].hoTen);
    cout << "Nam sinh: ";
    cin >> danhSach[idx].namSinh;
    cout << "Diem trung binh: ";
    cin >> danhSach[idx].diemTB;
}

// Hàm sắp xếp danh sách theo điểm trung bình giảm dần.
void sapXepDanhSach() {
    int tempHead = head;
    int size = 0;

    int idx[MAX];
    while (tempHead != -1) { // Tạo mảng các chỉ số trong danh sách liên kết.
        idx[size++] = tempHead;
        tempHead = nextNode[tempHead];
    }

    sort(idx, idx + size, [](int a, int b) { // Sắp xếp theo điểm trung bình.
        return danhSach[a].diemTB > danhSach[b].diemTB;
    });

    // Cập nhật danh sách liên kết theo thứ tự đã sắp xếp.
    head = idx[0];
    for (int i = 0; i < size - 1; i++) {
        nextNode[idx[i]] = idx[i + 1];
    }
    nextNode[idx[size - 1]] = -1;
}

// Hàm xuất danh sách sinh viên có điểm trung bình >= 5.
void xuatSinhVienDiemTB() {
    int temp = head;

    cout << "Danh sach sinh vien co diem trung binh >= 5:\n";
    cout << setw(10) << "Ma SV" << setw(20) << "Ho Ten" 
         << setw(10) << "Nam Sinh" << setw(10) << "Diem TB" << endl;

    while (temp != -1) { // Duyệt danh sách và in thông tin sinh viên thỏa mãn.
        if (danhSach[temp].diemTB >= 5) {
            cout << setw(10) << danhSach[temp].maSV 
                 << setw(20) << danhSach[temp].hoTen 
                 << setw(10) << danhSach[temp].namSinh 
                 << setw(10) << danhSach[temp].diemTB << endl;
        }
        temp = nextNode[temp];
    }
}

int main() {
    khoiTao(); // Khởi tạo danh sách liên kết tĩnh.

    docFile("sinhvien.txt"); // Đọc dữ liệu từ file.

    int choice;
    do {
        // Hiển thị menu và cho phép người dùng chọn chức năng.
        cout << "\nMenu:\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Xoa sinh vien\n";
        cout << "4. Tim sinh vien\n";
        cout << "5. Cap nhat thong tin sinh vien\n";
        cout << "6. Sap xep danh sach theo diem TB giam dan\n";
        cout << "7. Xuat danh sach sinh vien co diem TB >= 5\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: { // Thêm sinh viên mới.
                SinhVien sv;
                cout << "Ma SV: ";
                cin >> sv.maSV;
                cin.ignore();
                cout << "Ho ten: ";
                getline(cin, sv.hoTen);
                cout << "Nam sinh: ";
                cin >> sv.namSinh;
                cout << "Diem trung binh: ";
                cin >> sv.diemTB;
                themSinhVien(sv);
                break;
            }
            case 2: // Hiển thị danh sách sinh viên.
                hienThiDanhSach();
                break;
            case 3: { // Xóa sinh viên.
                string maSV;
                cout << "Nhap ma SV can xoa: ";
                cin >> maSV;
                xoaSinhVien(maSV);
                break;
            }
            case 4: { // Tìm kiếm sinh viên.
                string maSV;
                cout << "Nhap ma SV can tim: ";
                cin >> maSV;
                int idx = timKiem(maSV);
                if (idx != -1) {
                    cout << "Tim thay sinh vien: " << danhSach[idx].hoTen << endl;
                } else {
                    cout << "Khong tim thay!\n";
                }
                break;
            }
            case 5: { // Cập nhật thông tin sinh viên.
                string maSV;
                cout << "Nhap ma SV can cap nhat: ";
                cin >> maSV;
                capNhatThongTin(maSV);
                break;
            }
            case 6: // Sắp xếp danh sách.
                sapXepDanhSach();
                cout << "Da sap xep danh sach!\n";
                break;
            case 7: // Xuất danh sách sinh viên có điểm trung bình >= 5.
                xuatSinhVienDiemTB();
                break;
            case 0: // Thoát chương trình.
                cout << "Thoat chuong trinh.\n";
                break;
            default: // Xử lý lựa chọn không hợp lệ.
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0); // Thực hiện cho đến khi người dùng chọn thoát.

    return 0;
}
