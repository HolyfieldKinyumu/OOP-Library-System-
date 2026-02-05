#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class 1: The Book (Encapsulation of data)
class Book {
private:
    string title, author, isbn;
    bool isAvailable;

public:
    Book(string t, string a, string i) : title(t), author(a), isbn(i), isAvailable(true) {}

    string getIsbn() const { return isbn; }
    string getTitle() const { return title; }
    bool getStatus() const { return isAvailable; }

    void setStatus(bool status) { isAvailable = status; }

    void display() const {
        cout << "ISBN: " << isbn << " | Title: " << title << " | Author: " << author 
             << " | " << (isAvailable ? "Available" : "Borrowed") << endl;
    }
};

// Class 2: The User
class User {
private:
    string name;
    int id;
    vector<string> borrowedBooks; // Stores ISBNs of borrowed books

public:
    User(string n, int d) : name(n), id(d) {}
    int getId() const { return id; }
    string getName() const { return name; }
    
    void addBorrowedBook(string isbn) { borrowedBooks.push_back(isbn); }
};

// Class 3: The Library (The Manager)
class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    void addBook(Book b) { books.push_back(b); }
    void registerUser(User u) { users.push_back(u); }

    // Search Logic
    void searchBook(string query) {
        cout << "\nSearch Results for '" << query << "':" << endl;
        for (const auto& b : books) {
            if (b.getTitle().find(query) != string::npos || b.getIsbn() == query) {
                b.display();
            }
        }
    }

    // Borrow Logic (The core "Transaction")
    void borrowBook(int userID, string isbn) {
        for (auto& b : books) {
            if (b.getIsbn() == isbn) {
                if (b.getStatus()) {
                    b.setStatus(false);
                    cout << "Success: Book borrowed by User ID " << userID << endl;
                    return;
                } else {
                    cout << "Error: Book is already borrowed." << endl;
                    return;
                }
            }
        }
        cout << "Error: Book not found." << endl;
    }
};

int main() {
    Library myLib;

    // --- TEST DATA (To satisfy the "Robust Test Suite" requirement) ---
    myLib.addBook(Book("Intro to C++", "Bjarne Stroustrup", "101"));
    myLib.addBook(Book("Data Structures", "Robert Lafore", "102"));
    myLib.registerUser(User("Calculative Fellow", 1));

    // Test 1: Successful Search
    myLib.searchBook("Intro");

    // Test 2: Successful Borrow (Positive Scenario)
    myLib.borrowBook(1, "101");

    // Test 3: Attempt to borrow already borrowed book (Negative Scenario)
    myLib.borrowBook(1, "101");

    return 0;
}
