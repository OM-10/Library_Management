#include <deepstate/DeepState.hpp>
#include "LibraryManagementSystem.cpp" // Include the Library Management System implementation

using namespace deepstate;

TEST(LibraryManagementSystem, ComprehensiveTests) {
    LibraryManagementSystem lms;

    // Generate random IDs and names for books, students, and study rooms
    int bookId = DeepState_IntInRange(1, 1000);
    int studentId = DeepState_IntInRange(1, 1000);
    string bookTitle = DeepState_CStr_C("");
    string bookAuthor = DeepState_CStr_C("");
    string studentName = DeepState_CStr_C("");

    int roomNumber = DeepState_IntInRange(1, 100);
    int capacity = DeepState_IntInRange(1, 10);
    bool isGroup = DeepState_Bool();

    // Add a book to the library
    lms.addBook(bookId, bookTitle, bookAuthor);

    // Add a student to the library
    lms.addStudent(studentId, studentName);

    // Try issuing the book to the student
    string issueResult = lms.issueBook(bookId, studentId);
    if (issueResult == "Book with ID " + to_string(bookId) + " not found.") {
        ASSERT_TRUE(false) << "Failed to add or find book with ID: " << bookId;
    } else if (issueResult == "Student with ID " + to_string(studentId) + " not found.") {
        ASSERT_TRUE(false) << "Failed to add or find student with ID: " << studentId;
    } else if (issueResult == "Book is already issued.") {
        ASSERT_TRUE(false) << "Book is already marked as issued.";
    } else {
        ASSERT_TRUE(issueResult.find("issued to") != string::npos)
            << "Book issuing did not work as expected.";
    }

    // Return the book and check penalties
    string returnResult = lms.returnBook(bookId);
    if (returnResult.find("Penalty: $") != string::npos) {
        ASSERT_TRUE(true) << "Penalty applied correctly.";
    } else {
        ASSERT_TRUE(returnResult == "Book returned on time.") << "Unexpected return result.";
    }

    // Attempt to issue a non-existent book
    int invalidBookId = bookId + 1;
    string invalidIssueResult = lms.issueBook(invalidBookId, studentId);
    ASSERT_TRUE(invalidIssueResult == "Book with ID " + to_string(invalidBookId) + " not found.")
        << "Failed to catch non-existent book issue.";

    // Attempt to issue a book to a non-existent student
    int invalidStudentId = studentId + 1;
    string invalidStudentIssueResult = lms.issueBook(bookId, invalidStudentId);
    ASSERT_TRUE(invalidStudentIssueResult == "Student with ID " + to_string(invalidStudentId) + " not found.")
        << "Failed to catch non-existent student issue.";

    // Add a study room
    lms.addStudyRoom(roomNumber, capacity, isGroup);

    // Try booking the room
    string bookingResult = lms.bookStudyRoom(roomNumber, studentName, isGroup);
    ASSERT_TRUE(bookingResult.find("booked successfully") != string::npos)
        << "Room booking failed for room number: " << roomNumber;

    // Attempt to book the same room again
    string doubleBookingResult = lms.bookStudyRoom(roomNumber, studentName, isGroup);
    ASSERT_TRUE(doubleBookingResult == "Room " + to_string(roomNumber) + " is already booked.")
        << "Failed to detect double booking for room number: " << roomNumber;

    // Attempt to book a non-existent room
    int invalidRoomNumber = roomNumber + 1;
    string invalidRoomBookingResult = lms.bookStudyRoom(invalidRoomNumber, studentName, isGroup);
    ASSERT_TRUE(invalidRoomBookingResult == "Room " + to_string(invalidRoomNumber) + " not found.")
        << "Failed to detect non-existent room booking.";
}
