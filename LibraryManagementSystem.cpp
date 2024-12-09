#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

// Utility to get the current date
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
}

// Book structure
struct Book {
    int id;
    string title;
    string author;
    bool isIssued = false;
    string issuedTo;
    string issueDate;
    string dueDate;
};

// Student structure
struct Student {
    int id;
    string name;
};

// Study room booking structure
struct StudyRoom {
    int roomNumber;
    bool isGroup;
    int capacity;
    bool isBooked = false;
    string bookedBy;
};

// Library Management System Class
class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Student> students;
    vector<StudyRoom> studyRooms;

public:
    void addBook(int id, const string &title, const string &author) {
        books.push_back({id, title, author});
        cout << "Book \"" << title << "\" added successfully!\n";
    }

    void addStudent(int id, const string &name) {
        students.push_back({id, name});
        cout << "Student \"" << name << "\" added successfully!\n";
    }

    void issueBook(int bookId, int studentId) {
        Book *book = findBook(bookId);
        if (!book) {
            cout << "Book with ID " << bookId << " not found.\n";
            return;
        }

        if (book->isIssued) {
            cout << "Book \"" << book->title << "\" is already issued to another student.\n";
            return;
        }

        Student *student = findStudent(studentId);
        if (!student) {
            cout << "Student with ID " << studentId << " not found.\n";
            return;
        }

        book->isIssued = true;
        book->issuedTo = student->name;
        book->issueDate = getCurrentDate();
        book->dueDate = "2024-12-20"; // Example due date
        cout << "Book \"" << book->title << "\" issued to " << student->name << ".\n";
    }

    void returnBook(int bookId) {
        Book *book = findBook(bookId);
        if (!book || !book->isIssued) {
            cout << "Book with ID " << bookId << " is not issued.\n";
            return;
        }

        string returnDate = getCurrentDate();
        int penalty = calculatePenalty(book->dueDate, returnDate);
        if (penalty > 0) {
            cout << "Book returned late. Penalty: $" << penalty << ".\n";
        } else {
            cout << "Book returned on time.\n";
        }

        book->isIssued = false;
        book->issuedTo = "";
        book->issueDate = "";
        book->dueDate = "";
    }

    void bookStudyRoom(int roomNumber, const string &studentName, bool isGroup) {
        for (auto &room : studyRooms) {
            if (room.roomNumber == roomNumber) {
                if (room.isBooked) {
                    cout << "Room " << roomNumber << " is already booked.\n";
                } else {
                    room.isBooked = true;
                    room.bookedBy = studentName;
                    cout << "Room " << roomNumber << " booked successfully by " << studentName << ".\n";
                }
                return;
            }
        }
        cout << "Room " << roomNumber << " not found.\n";
    }

    void addStudyRoom(int roomNumber, int capacity, bool isGroup) {
        studyRooms.push_back({roomNumber, isGroup, capacity});
        cout << "Study Room " << roomNumber << " added successfully!\n";
    }

private:
    Book *findBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;
    }

    Student *findStudent(int id) {
        for (auto &student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    int calculatePenalty(const string &dueDate, const string &returnDate) {
        // Simplistic penalty calculation based on string comparison
        if (returnDate > dueDate) {
            return 5; // Flat rate for demonstration
        }
        return 0;
    }
};

// Main function
int main() {
    LibraryManagementSystem lms;

    // Adding books
    lms.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald");
    lms.addBook(2, "1984", "George Orwell");

    // Adding students
    lms.addStudent(1, "Alice");
    lms.addStudent(2, "Bob");

    // Issuing books
    lms.issueBook(1, 1); // Issue to Alice
    lms.issueBook(2, 2); // Issue to Bob

    // Returning books
    lms.returnBook(1);

    // Adding and booking study rooms
    lms.addStudyRoom(101, 1, false); // Individual room
    lms.addStudyRoom(201, 5, true);  // Group room
    lms.bookStudyRoom(101, "Alice", false); // Alice books room 101

    return 0;
}
