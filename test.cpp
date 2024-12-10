#include <deepstate/DeepState.hpp>
#include "LibraryManagementSystem.cpp"

using namespace deepstate;

TEST(LibraryManagementSystem, ComprehensiveTest) {
    cout << "################################################" << endl;
    LibraryManagementSystem lms;

    // Generate random IDs and details for books and students
    int bookId = DeepState_IntInRange(1, 1000);
    int studentId = DeepState_IntInRange(1, 1000);

    std::string bookTitle = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string bookAuthor = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string bookPublisher = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string updatedBookTitle = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string updatedBookAuthor = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string updatedBookPublisher = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));

    std::string studentName = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string studentDepartment = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string updatedStudentName = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));
    std::string updatedStudentDepartment = std::string(DeepState_CStr_C(20, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "));

    int roomNumber = DeepState_IntInRange(1, 100);
    int capacity = DeepState_IntInRange(1, 10);
    bool isGroup = DeepState_Bool();

    // Add a book and a student
    std::cout << "Adding book with ID " << bookId << "\n";
    lms.addBook(bookId, bookTitle, bookAuthor, bookPublisher);
    std::cout << "Adding student with ID " << studentId << "\n";
    lms.addStudent(studentId, studentName, studentDepartment);

    // Update book details and verify
    ASSERT_TRUE(lms.updateBookDetails(bookId, updatedBookTitle, updatedBookAuthor, updatedBookPublisher))
        << "Error: Updating book failed for Book ID: " << bookId;

    // Update student details and verify
    ASSERT_TRUE(lms.updateStudentDetails(studentId, updatedStudentName, updatedStudentDepartment))
        << "Error: Updating student failed for Student ID: " << studentId;

    // Issue the book to the student
    std::cout << "Issuing book to student...\n";
    std::string issueResult = lms.issueBook(bookId, studentId);
    ASSERT_TRUE(issueResult.find("issued to") != std::string::npos)
        << "Error: Issue book failed. Result: " << issueResult;

    // Return the book
    std::cout << "Returning book...\n";
    std::string returnResult = lms.returnBook(bookId);
    ASSERT_TRUE(returnResult.find("returned") != std::string::npos)
        << "Error: Return book failed. Result: " << returnResult;

    // Delete the book and verify it cannot be found
    std::cout << "Deleting book with ID " << bookId << "\n";
    ASSERT_TRUE(lms.deleteBook(bookId))
        << "Error: Deleting book failed for Book ID: " << bookId;

    std::cout << "Verifying book deletion...\n";
    ASSERT_TRUE(lms.searchBooksByTitle(updatedBookTitle).find("No books found.") != std::string::npos)
        << "Error: Book still found after deletion.";

    // Add and book a study room
    std::cout << "Adding and booking a study room...\n";
    lms.addStudyRoom(roomNumber, capacity, isGroup);
    std::string bookingResult = lms.bookStudyRoom(roomNumber, studentName, isGroup);
    ASSERT_TRUE(bookingResult.find("booked successfully") != std::string::npos)
        << "Error: Booking study room failed. Result: " << bookingResult;

    // Release the study room and rebook it
    std::cout << "Releasing study room...\n";
    ASSERT_TRUE(lms.releaseStudyRoom(roomNumber))
        << "Error: Releasing study room failed for Room Number: " << roomNumber;

    std::cout << "Rebooking study room...\n";
    ASSERT_TRUE(lms.bookStudyRoom(roomNumber, studentName, isGroup).find("booked successfully") != std::string::npos)
        << "Error: Rebooking study room failed for Room Number: " << roomNumber;
}
