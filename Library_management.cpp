#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

// Book Class
class Book
{
private:
    string book_name;
    string author;
    string isbn;
    bool availablitity;

public:
    Book(const string &book_name, const string &author, const string isbn, bool availablitity)
    : book_name(book_name), author(author), isbn(isbn), availablitity(availablitity) {}
    string getBookName() const { return book_name; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }
    bool isAvailable() const { return availablitity; }

    void setAvailable(bool availablitity) { this->availablitity = availablitity; }
};

class User
{
private:
    string name;
    string id;
    string contactInfo;

public:
    User(const std::string &name, const std::string &id, const std::string &contactInfo)
        : name(name), id(id), contactInfo(contactInfo) {}

    string getName() const { return name; }
    string getID() const { return id; }
    string getContactInfo() const { return contactInfo; }
};

class Library
{
private:
    vector<Book> books;
    vector<User> users;

public:
    void add_books(const string &book_name, const string &author, const string &isbn);
    void search_book(const string &book_name);
    void return_book(const string &isbn);
    void add_user(const string &name, const string &id, const string &contactInfo);
    void generate_report();
private:
    Book* find_book_by_ISBN(const string& isbn);
    User* find_user_by_id(const string userId);
};
// main function
int main()
{
    cout << "\t\t Well Come to Library Management System" << endl;
    int choice;
    do
    {
        cout << "What do you want me to do?" << endl;
        cout << "Press 1 to add book\n";
        cout << "Press 2 to search for a book\n";
        cout << "Press 3 to borrow book\n";
        cout << "Press 4 to return a book\n";
        cout << "Press 5 to add new user\n";
        cout << "Preass 6 to generate a report\n";
        cout << "Press 7 to exit\n";
        cin >> choice;
    } while (choice = !7);

    return 0;
}