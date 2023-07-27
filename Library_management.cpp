#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include<sstream>
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
    // Function to convert book data to a string for file I/O
    std::string toString() const {
        std::ostringstream oss;
        oss << book_name << "," << author << "," << isbn << "," << availablitity;
        return oss.str();
    }

    // Function to create a Book object from a string representation (file I/O)
    static Book fromString(const std::string& bookString) {
        std::istringstream iss(bookString);
        std::string title, author, isbn, available;
        if (std::getline(iss, title, ',') &&
            std::getline(iss, author, ',') &&
            std::getline(iss, isbn, ',') &&
            std::getline(iss, available)) {
            return Book(title, author, isbn, (available == "1"));
        }
        // Return a default Book if parsing fails (shouldn't happen with correct file format)
        return Book("", "", "", false);
    }
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
    void borrowBook(const std::string& isbn);
    void generateAvailableBooksReport();
private:
    Book* findBookByISBN(const std::string& isbn);
    void saveDataToFile();
    void loadDataFromFile();
};
void Library::return_book(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    if (book) {
        if (!book->isAvailable()) {
            book->setAvailable(true);
            std::cout << "Book successfully returned.\n";
        } else {
            std::cerr << "Error: The book is already available in the library.\n";
        }
    } else {
        std::cerr << "Error: Book not found.\n";
    }
}
void Library::saveDataToFile() {
    std::ofstream file("books.txt");
    if (file) {
        for (const Book& book : books) {
            file << book.toString() << '\n';
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to save book data to file.\n";
    }
}
void Library::loadDataFromFile() {
    std::ifstream file("books.txt");
    if (file) {
        std::string line;
        while (std::getline(file, line)) {
            books.push_back(Book::fromString(line));
        }
        file.close();
    } else {
        std::cerr << "Warning: Unable to load book data from file. Starting with an empty book collection.\n";
    }
}

void Library::add_books(const std::string& title, const std::string& author, const std::string& isbn) {
    books.push_back(Book(title, author, isbn, true));
    std::cout << "Book added successfully.\n";
}

// Function to search for a book by title or author and display its details
void Library::search_book(const std::string& searchTerm) {
    std::cout << "Search results:\n";
    bool found = false;
    for (const Book& book : books) {
        if (book.getBookName().find(searchTerm) != std::string::npos || book.getAuthor().find(searchTerm) != std::string::npos) {
            std::cout << "Title: " << book.getBookName() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN()
                      << ", Availability: " << (book.isAvailable() ? "Available" : "Not Available") << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No matching books found.\n";
    }
}
void Library::borrowBook(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    if (book) {
        if (book->isAvailable()) {
            book->setAvailable(false);
            std::cout << "Book successfully borrowed.\n";
        } else {
            std::cerr << "Error: Book is not available for borrowing.\n";
        }
    } else {
        std::cerr << "Error: Book not found.\n";
    }
}
Book* Library::findBookByISBN(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
        return book.getISBN() == isbn;
    });
    if (it != books.end()) {
        return &(*it);
    }
    return nullptr;
}

// Function to generate a report of all the books currently available in the library
void Library::generateAvailableBooksReport() {
    std::cout << "Available books in the library:\n";
    bool found = false;
    for (const Book& book : books) {
        if (book.isAvailable()) {
            std::cout << "Title: " << book.getBookName() << ", Author: " << book.getAuthor() << ", ISBN: " << book.getISBN() << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No available books in the library.\n";
    }
}
template <typename T>
T getValidInput() {
    T input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please try again: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

// main function
int main()
{
    Library library;
    cout << "\t\t Well Come to Library Management System" << endl;
    int choice;
    do
    {
        cout << "What do you want me to do?" << endl;
        cout << "Press 1 to add book\n";
        cout << "Press 2 to search for a book\n";
        cout << "Press 3 to borrow book\n";
        cout << "Press 4 to return a book\n";
        //cout << "Press 5 to add new user\n";
        cout << "Preass 6 to generate a report\n";
        cout << "Press 7 to exit\n";
        cin >> choice;
        choice = getValidInput<int>();

        switch (choice) {
            case 1: {
                std::cout << "Enter the title: ";
                std::string title = getValidInput<std::string>();
                std::cout << "Enter the author: ";
                std::string author = getValidInput<std::string>();
                std::cout << "Enter the ISBN: ";
                std::string isbn = getValidInput<std::string>();
                library.add_books(title, author, isbn);
                break;
            }
            case 2: {
                std::cout << "Enter the search term (title or author): ";
                std::string searchTerm = getValidInput<std::string>();
                library.search_book(searchTerm);
                break;
            }
            case 3: {
                std::cout << "Enter the ISBN of the book to borrow: ";
                std::string isbn = getValidInput<std::string>();
                library.borrowBook(isbn);
                break;
            }
            case 4: {
                std::cout << "Enter the ISBN of the book to return: ";
                std::string isbn = getValidInput<std::string>();
                library.return_book(isbn);
                break;
            }
            case 6: {
                library.generateAvailableBooksReport();
                break;
            }
            case 7: {
                std::cout << "Exiting the program. Saving data...\n";
                break;
            }
            default: {
                std::cerr << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice !=7);

    return 0;
}