# Chương Trình Quản Lý Thư Viện
- **Môn học**: Đồ án Tin học 
- **Giảng viên hướng dẫn**: Lương An Vinh
- **Sinh viên thực hiện:** 
  - Trần Đức Minh - MSSV: DH52400646
  - Phạm Đăng Lưu - MSSV: DH52400635

# Giới thiệu chung
- Đồ án xây dựng phần mềm quản lý thư viện bằng ngôn ngữ "C++". 
- Chương trình ứng dụng các Cấu trúc Dữ liệu & Giải thuật đã học, kết hợp với một CTDL tự tìm hiểu, lưu trữ dữ liệu trực tiếp trên file (nhị phân & văn bản) mà "không sử dụng hệ quản trị CSDL".

# Các chức năng chính
- **Quản lý Sách:** Thêm/Xóa/Sửa, tìm kiếm theo ISBN, tìm kiếm theo tiền tố tên, Import/Export file.
- **Quản lý Độc giả:** Thêm/Xóa/Sửa thông tin, quản lý theo CMND.
- **Mượn/Trả sách:** Lập phiếu mượn, xử lý trả sách, tính tiền phạt quá hạn, kiểm tra ràng buộc.
- **Thống kê - Báo cáo:** Thống kê lượt mượn theo tháng/thể loại, Top 10 sách/độc giả mượn nhiều nhất.
- **Tìm kiếm nâng cao & Gợi ý:** Gợi ý sách cùng thể loại (Đồ thị), tìm kiếm sách theo tiền tố (Trie - Autocomplete).
- **Lưu trữ:** Tự động đọc/ghi file nhị phân (.dat), xuất báo cáo (.txt), backup dữ liệu.

---

# Cấu trúc dữ liệu áp dụng
| STT | Cấu trúc dữ liệu / Giải thuật | Áp dụng cho chức năng |
|:---:|:---|:---|
| 1 | **Cây AVL** | Quản lý sách theo Mã ISBN |
| 2 | **Cây BST** | In danh mục sách theo tên (in-order) |
| 3 | **Hash Table** (Separate Chaining) | Quản lý độc giả theo CMND |
| 4 | **Danh sách liên kết đơn** | Danh sách phiếu mượn |
| 5 | **Danh sách đặc (Mảng động)** | Lịch sử giao dịch |
| 6 | **Đồ thị (Danh sách kề)** | Gợi ý sách cùng thể loại (BFS/DFS) |
| 7 | **CTDL tự tìm hiểu: Cây Trie** | Tìm sách theo tiền tố tên (Autocomplete) |
| 8 | **Đọc/Ghi file nhị phân** | Lưu trữ toàn bộ dữ liệu |

---

# Cấu trúc thư mục dự án

```text
LibraryManagement/
│
├── include/       # Chứa các file header (.h)
├── src/           # Chứa các file source code (.cpp)
├── data/          # Chứa file dữ liệu mẫu (.dat, .txt)
├── docs/          # Chứa báo cáo, hình ảnh, sơ đồ lớp
├── tests/         # Chứa các file test case
├── Makefile       # Hoặc file .sln (nếu dùng Visual Studio)
└── README.md      # File mô tả dự án (file này)
