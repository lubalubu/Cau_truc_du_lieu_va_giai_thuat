#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
    string title;
    int pages;
    vector<Node*> children;

    Node(string t, int p) : title(t), pages(p) {}
};

class Book {
private:
    Node* root;

    void deleteNode(Node* node) {
        for (int i = 0; i < node->children.size(); ++i) {
            deleteNode(node->children[i]);
        }
        delete node;
    }

    int countChapters(Node* node) {
        if (node == nullptr) return 0;
        int count = 0;
        for (int i = 0; i < node->children.size(); ++i) {
            count += countChapters(node->children[i]);
        }
        return count + 1;
    }

    Node* findLongestChapter(Node* node, Node*& longest) {
        if (node == nullptr) return longest;
        if (node->pages > longest->pages) {
            longest = node;
        }
        for (int i = 0; i < node->children.size(); ++i) {
            findLongestChapter(node->children[i], longest);
        }
        return longest;
    }

    Node* findAndRemove(Node* node, const string& title) {
        if (node == nullptr) return nullptr;
        for (int i = 0; i < node->children.size(); ++i) {
            if (node->children[i]->title == title) {
                Node* toDelete = node->children[i];
                node->children.erase(node->children.begin() + i);
                deleteNode(toDelete);
                return node;
            }
            Node* found = findAndRemove(node->children[i], title);
            if (found) return found;
        }
        return nullptr;
    }

public:
    Book() : root(nullptr) {}

    ~Book() {
        deleteNode(root);
    }

    void setRoot(Node* node) {
        root = node;
    }

    int getChapterCount() {
        return countChapters(root);
    }

    Node* getLongestChapter() {
        Node* longest = root;
        return findLongestChapter(root, longest);
    }

    void removeNode(const string& title) {
        if (root->title == title) {
            Node* oldRoot = root;
            root = nullptr;
            deleteNode(oldRoot);
        } else {
            findAndRemove(root, title);
        }
    }
};

int main() {
    Book book;
    Node* root = new Node("Book Title", 0);
    Node* chapter1 = new Node("Chapter 1", 10);
    Node* chapter2 = new Node("Chapter 2", 20);
    Node* section1 = new Node("Section 1.1", 5);
    Node* section2 = new Node("Section 1.2", 15);

    chapter1->children.push_back(section1);
    chapter1->children.push_back(section2);
    root->children.push_back(chapter1);
    root->children.push_back(chapter2);
    book.setRoot(root);

    cout << "Total chapters: " << book.getChapterCount() << endl;
    Node* longest = book.getLongestChapter();
    if (longest) {
        cout << "Longest chapter: " << longest->title << " with " << longest->pages << " pages" << endl;
    }

    book.removeNode("Section 1.1");
    cout << "Total chapters after removal: " << book.getChapterCount() << endl;

    return 0;
}