#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <filesystem>

struct Node {
    std::string name;
    size_t size;
    std::time_t modifiedTime;
    Node* next;

    Node(const std::string& fileName, size_t fileSize, std::time_t modTime)
        : name(fileName), size(fileSize), modifiedTime(modTime), next(nullptr) {}
};

class FileCollection {
private:
    Node* start;

public:
    FileCollection() : start(nullptr) {}

    void addFileToList(const std::string& fileName, size_t fileSize, std::time_t modTime) {
        Node* newNode = new Node(fileName, fileSize, modTime);

        if (!start || difftime(start->modifiedTime, modTime) > 0) {
            newNode->next = start;
            start = newNode;
        } else {
            Node* current = start;
            while (current->next && difftime(current->next->modifiedTime, modTime) < 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    size_t totalFileSize() const {
        size_t total = 0;
        Node* current = start;
        while (current) {
            total += current->size;
            current = current->next;
        }
        return total;
    }

    void limitTotalSize(size_t maxSize) {
        while (totalFileSize() > maxSize) {
            Node* smallest = start;
            Node* prevSmallest = nullptr;
            Node* current = start;
            Node* previous = nullptr;

            while (current) {
                if (current->size < smallest->size) {
                    smallest = current;
                    prevSmallest = previous;
                }
                previous = current;
                current = current->next;
            }

            if (prevSmallest) {
                prevSmallest->next = smallest->next;
            } else {
                start = smallest->next;
            }
            delete smallest;
        }
    }

    void showFiles() const {
        Node* current = start;
        while (current) {
            std::cout << "File: " << current->name
                      << ", Size: " << current->size << " bytes"
                      << ", Last Modified: " << std::ctime(&current->modifiedTime);
            current = current->next;
        }
    }
};

void copyAndAddToCollection(FileCollection& collection, const std::string& src, const std::string& dest, size_t fileSize, std::time_t modTime) {
    #ifdef _WIN32
        std::system(("copy " + src + " " + dest).c_str());
    #else
        std::system(("cp " + src + " " + dest).c_str());
    #endif
    collection.addFileToList(dest, fileSize, modTime);
}

int main() {
    FileCollection files;

    files.addFileToList("file1.txt", 1000, std::time(nullptr) - 100);
    files.addFileToList("file2.txt", 2000, std::time(nullptr) - 200);
    files.addFileToList("file3.txt", 500, std::time(nullptr) - 50);

    std::cout << "Files in collection:\n";
    files.showFiles();

    copyAndAddToCollection(files, "source_file.txt", "destination_file.txt", 1500, std::time(nullptr) - 150);

    std::cout << "\nFiles after copy:\n";
    files.showFiles();

    files.limitTotalSize(static_cast<size_t>(32) * 1024 * 1024 * 1024);

    std::cout << "\nFiles after limiting to 32GB:\n";
    files.showFiles();

    return 0;
}