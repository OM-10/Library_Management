#include "LibraryUtils.h" // Include utility functions
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    string publication;
    bool isIssued = false;
    string issuedTo;
    string issueDate;
    string dueDate;
};

// Student structure
struct Student {
    int id;
    string name;
    string department;
};

// Study room structure
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
    // List of all books in the library
    vector<Book> books;
    // List of all students in the library system
    vector<Student> students;
    // List of all study rooms in the library
    vector<StudyRoom> studyRooms;

public:
    // Function to add a new book to the library
    void addBook(int id, const string &title, const string &author, const string &publication) {
        books.push_back({id, title, author, publication});
        cout << "Book \"" << title << "\" added successfully!" << endl;
    }

    // Function to delete a book from the library
    bool deleteBook(int id) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                std::cout << "Deleting book with ID " << id << " and Title " << it->title << "\n";
                books.erase(it);
                std::cout << "Book successfully deleted\n";
                return true;
            }
        }
        std::cout << "Book with ID " << id << " not found\n";
        return false;
    }


    // Function to update book details
    bool updateBookDetails(int id, const string &newTitle, const string &newAuthor, const string &newPublisher) {
        for (auto &book : books) {
            if (book.id == id) {
                book.title = newTitle;
                book.author = newAuthor;
                book.publication = newPublisher;
                cout << "Book with ID " << id << " updated successfully!\n";
                return true;
            }
        }
        cout << "Book with ID " << id << " not found!\n";
        return false;
    }

    // Function to add a new student to the library system
    void addStudent(int id, const string &name, const string &department) {
        students.push_back({id, name, department});
        cout << "Student \"" << name << "\" added successfully!" << endl;
    }

    // Function to delete a student from the library system
    bool deleteStudent(int id) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                students.erase(it); // Remove the student from the vector
                cout << "Student with ID " << id << " deleted successfully!" << endl;
                return true;
            }
        }
        cout << "Student with ID " << id << " not found!" << endl;
        return false;
    }

    // Function to update student details
    bool updateStudentDetails(int id, const string &newName, const string &newDepartment) {
        for (auto &student : students) {
            if (student.id == id) {
                student.name = newName;
                student.department = newDepartment;
                cout << "Student with ID " << id << " updated successfully!\n";
                return true;
            }
        }
        cout << "Student with ID " << id << " not found!\n";
        return false;
    }

    // Function to issue a book to a student
    std::string issueBook(int bookId, int studentId) {
        Book *book = findBook(bookId);
        if (!book) {
            return "Book with ID " + to_string(bookId) + " not found.";
        }
        if (book->isIssued) {
            return "Book is already issued.";
        }
        Student *student = findStudent(studentId);
        if (!student) {
            return "Student with ID " + to_string(studentId) + " not found.";
        }
        // Update book details to mark it as issued
        book->isIssued = true;
        book->issuedTo = student->name;
        book->issueDate = getCurrentDate();
        book->dueDate = calculateDueDate(book->issueDate);
        return "Book issued to " + student->name + ".";
    }

    // Function to return a book
    std::string returnBook(int bookId) {
        Book *book = findBook(bookId);
        if (!book || !book->isIssued) {
            return "Book with ID " + to_string(bookId) + " is not issued.";
        }
        // Calculate overdue days and reset book details
        int overdueDays = calculateOverdueDays(book->dueDate);
        book->isIssued = false;
        book->issuedTo = "";
        book->issueDate = "";
        book->dueDate = "";
        if (overdueDays > 0) {
            return "Book returned with a penalty of $" + to_string(overdueDays * 1) + ".";
        }
        return "Book returned on time.";
    }

    // Function to list overdue books
    void listOverdueBooks() {
        string currentDate = getCurrentDate();
        cout << "Overdue Books:\n";
        bool found = false;
        for (const auto &book : books) {
            if (book.isIssued && daysBetween(book.dueDate, currentDate) > 0) {
                int overdueDays = daysBetween(book.dueDate, currentDate);
                cout << "Book ID: " << book.id << ", Title: " << book.title
                     << ", Issued To: " << book.issuedTo << ", Overdue Days: " << overdueDays << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No overdue books.\n";
        }
    }

    // Function to add a new study room
    void addStudyRoom(int roomNumber, int capacity, bool isGroup) {
        studyRooms.push_back({roomNumber, isGroup, capacity});
        cout << "Study Room " << roomNumber << " added successfully!" << endl;
    }

    // Function to book a study room
    std::string bookStudyRoom(int roomNumber, const string &studentName, bool isGroup) {
        for (auto &room : studyRooms) {
            if (room.roomNumber == roomNumber) {
                if (room.isBooked) {
                    return "Room " + to_string(roomNumber) + " is already booked.";
                } else {
                    room.isBooked = true;
                    room.bookedBy = studentName;
                    return "Room " + to_string(roomNumber) + " booked successfully by " + studentName + ".";
                }
            }
        }
        return "Room " + to_string(roomNumber) + " not found.";
    }

    // Function to release a study room after use
    bool releaseStudyRoom(int roomNumber) {
        for (auto &room : studyRooms) {
            if (room.roomNumber == roomNumber) {
                if (!room.isBooked) {
                    cout << "Room " << roomNumber << " is not currently booked." << endl;
                    return false;
                }
                room.isBooked = false;
                room.bookedBy = "";
                cout << "Room " << roomNumber << " has been released successfully!" << endl;
                return true;
            }
        }
        cout << "Room " << roomNumber << " not found!" << endl;
        return false;
    }

    // Function to search for books by title
    std::string searchBooksByTitle(const string &title) {
        string result = "Search results for \"" + title + "\":\n";
        for (const auto &book : books) {
            if (book.title.find(title) != string::npos) {
                result += "Book ID: " + to_string(book.id) + ", Title: " + book.title + ", Author: " + book.author + "\n";
            }
        }
        return result == "Search results for \"" + title + "\":\n" ? "No books found." : result;
    }


    // Function to list all issued books
    std::string listIssuedBooks() {
        string result = "Currently Issued Books:\n";
        for (const auto &book : books) {
            if (book.isIssued) {
                result += "Book ID: " + to_string(book.id) + ", Title: " + book.title + ", Issued To: " + book.issuedTo + ", Due Date: " + book.dueDate + "\n";
            }
        }
        return result.empty() ? "No books are currently issued." : result;
    }

    // Function to list all available books
    std::string listAvailableBooks() {
        string result = "Available Books:\n";
        for (const auto &book : books) {
            if (!book.isIssued) {
                result += "Book ID: " + to_string(book.id) + ", Title: " + book.title + ", Author: " + book.author + "\n";
            }
        }
        return result == "Available Books:\n" ? "No books are currently available." : result;
    }

    // Function to display all books in the library
    void listAllBooks() {
        if (books.empty()) {
            cout << "No books available in the library." << endl;
            return;
        }
        cout << "All Books in the Library:\n";
        for (const auto &book : books) {
            cout << "Book ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                 << ", Issued: " << (book.isIssued ? "Yes" : "No") << endl;
        }
    }

    // Function to display all students in the library system
    void listAllStudents() {
        if (students.empty()) {
            cout << "No students registered in the library system." << endl;
            return;
        }
        cout << "All Registered Students:\n";
        for (const auto &student : students) {
            cout << "Student ID: " << student.id << ", Name: " << student.name << ", Department: " << student.department << endl;
        }
    }


private:
    // Helper function to find a book by ID
    Book *findBook(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr;
    }

    // Helper function to find a student by ID
    Student *findStudent(int id) {
        for (auto &student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    // Helper function to calculate the due date for a book
    std::string calculateDueDate(const std::string &issueDate) {
        struct tm tm = {};
        strptime(issueDate.c_str(), "%Y-%m-%d", &tm);
        tm.tm_mday += 14; // Add 14 days
        mktime(&tm);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
        return string(buffer);
    }

    // Helper function to calculate overdue days for a book
    int calculateOverdueDays(const string &dueDate) {
        string currentDate = getCurrentDate();
        return max(0, daysBetween(dueDate, currentDate));
    }
};
