#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

// Cấu trúc lưu thông tin file
struct File {
    string name;
    int size;         // Dung lượng (đơn vị KB)
    time_t createdAt; // Thời gian lưu (timestamp)


    void display() const {  //Hàm hiển thị thông tin file
        cout << "Tên file: " << name << ", Dung lượng: " << size << " KB, Thời gian lưu: " 
             << ctime(&createdAt);
    }
};

// Hàm sắp xếp file theo dung lượng tăng dần
bool compareFiles(const File& a, const File& b) {
    if (a.size != b.size)
        return a.size < b.size;       // Sắp xếp theo dung lượng
    return a.createdAt < b.createdAt; // Nếu cùng dung lượng, sắp xếp theo thời gian lưu
}

// Hàm xóa các file có dung lượng nhỏ nhất và thời gian lưu lâu nhất
void deleteSmallestFiles(vector<File>& files) {
    if (files.empty()) {
        cout << "Thư mục rỗng, không có file để xóa." << endl;
        return;
    }

    // Tìm dung lượng nhỏ nhất
    int minSize = files[0].size;

    // Lọc các file có dung lượng nhỏ nhất
    vector<File>::iterator it = files.begin();
    while (it != files.end() && it->size == minSize) {
        it = files.erase(it); // Xóa file có dung lượng nhỏ nhất
    }
}

int main() {
    vector<File> folder;

    // Tạo một vài file trong thư mục
    folder.push_back({"File1.txt", 100, time(0) - 5000}); // 50003 giây    
    folder.push_back({"File2.txt", 200, time(0) - 3000}); // 3000 giây trước
    folder.push_back({"File3.txt", 100, time(0) - 10000}); // 10000 giây trước
    folder.push_back({"File4.txt", 300, time(0) - 2000}); // 2000 giây trước
    folder.push_back({"File5.txt", 100, time(0) - 7000}); // 7000 giây trước

    cout << "Thư mục ban đầu:" << endl;
    for (const auto& file : folder) {
        file.display();
    }

    // Sắp xếp file theo dung lượng tăng dần, nếu dung lượng bằng nhau thì ưu tiên thời gian lưu
    sort(folder.begin(), folder.end(), compareFiles);

    cout << "\nThư mục sau khi sắp xếp:" << endl;
    for (const auto& file : folder) {
        file.display();
    }

    deleteSmallestFiles(folder);

    cout << "\nThư mục sau khi xóa file có dung lượng nhỏ nhất:" << endl;
    if (folder.empty()) {
        cout << "Thư mục trống." << endl;
    } else {
        for (const auto& file : folder) {
            file.display();
        }
    }

    return 0;
}
