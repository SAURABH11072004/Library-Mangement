// Array
 #include <iostream>
 #include <string>
 using namespace std;
 // Class to represent a book with title, author, and ISBN
 class Book {
 private:
 string title;
 string author;
 string ISBN;
 public:
 // Method to input book details
 void getdata() {
 cout << "Enter book title: ";
 cin >> title;
 cout << "Enter author name: ";
 cin >> author;
 cout << "Enter ISBN: ";
 cin >> ISBN;
 cout << endl;
 }
 // Method to display book details
 void display() {
 cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << endl;
 }
 // Declaring LibraryManagementSystem as a friend class so it can access private members
 friend class LibraryManagementSystem;
 };
 // Class to represent a borrowed book and details about the borrower
 class BorrowedBook {
 private:
 string studentName;
 string bookTitle;
 string borrowDate;
 string returnDate;
 string studentPRN;
 string libraryCardNo;
 public:
// Method to input borrower's details
 void getdata() {
 cout << "Enter your name: ";
 cin >> studentName;
 cout << "Enter PRN: ";
 cin >> studentPRN;
 cout << "Enter library card number: ";
 cin >> libraryCardNo;
 cout << "Enter borrow date (dd-mm-yyyy): ";
 cin >> borrowDate;
 cout << "Return the book after exact 20days.";
 cout << endl;
 }
 // Method to display borrowed book and borrower details
 void display() {
 cout << "Borrowed Book: " << bookTitle << " by " << studentName
 << " (PRN: " <<studentPRN<< ", Library Card: " << libraryCardNo << ")"
 <<" (Borrowed on: " <<borrowDate<< ")"<<endl;
 }
 friend class LibraryManagementSystem;
 friend class BookQueue;
 };
 // Stack class to manage books in the library
 class BookStack {
 private:
 Book* stack[100]; // Array of pointers to Book objects
 int top; // Index of the top book in the stack
 public:
 // Constructor initializing the stack to be empty
 BookStack() { top =-1; }
 // Method to push a book onto the stack
 void push(Book* book) {
 if (top >= 99) {
 cout << "\nLibrary Stack full! Cannot add more books.\n\n";
 return;
 }
 stack[++top] = book;
 cout << "Book added to the library stack.\n\n";
 }
// Method to pop a book from the stack
 Book* pop() {
 if (top ==-1) {
 cout << "\nNo books to remove from the library stack!\n\n";
 return NULL;
 }
 cout << "\nBook removed from the library stack.\n\n";
 return stack[top--];
 }
 // Method to display all books in the stack
 void displayLibraryStack() {
 if (top ==-1) {
 cout << "\nNo books in the library stack!\n\n";
 return;
 }
 cout << "\nBooks in the Library Stack (Top first):\n";
 for (int i = top; i >= 0;--i) {
 stack[i]->display();
 }
 cout << endl;
 }
 };
 // Queue class to manage borrowed books
 class BookQueue {
 private:
 BorrowedBook* queue[100]; // Circular queue for borrowed books
 int front; // Front index of the queue
 int rear; // Rear index of the queue
 public:
 // Constructor initializing the queue to be empty
 BookQueue() { front =-1; rear =-1; }
 // Method to enqueue a borrowed book into the queue
 void enqueue(BorrowedBook* book) {
 if ((rear + 1) % 100 == front) {
 cout << "\nBorrowing queue full! Cannot borrow more books.\n\n";
 return;
 }
 if (front ==-1) {
 front = 0; // Set front to 0 if first book is added
 }
rear = (rear + 1) % 100;
 queue[rear] = book;
 cout << "\nBook borrowed and added to the borrowing queue.\n\n";
 }
 // Method to dequeue a book from the queue
 BorrowedBook* dequeue() {
 if (front ==-1) {
 cout << "\nNo borrowed books to return!\n\n";
 return NULL;
 }
 BorrowedBook* book = queue[front];
 if (front == rear) {
 front =-1; // Reset queue when last book is returned
 rear =-1;
 } else {
 front = (front + 1) % 100;
 }
 cout << "\nBook returned.\n\n";
 return book;
 }
 // Method to display all borrowed books
 void displayBorrowedBooks() {
 if (front ==-1) { //Checking whether queue is empty
 cout << "\nNo borrowed books!\n\n";
 return;
 }
 cout << "\nBorrowed Books in Queue:\n";
 int i = front;
 do {
 //loop diplaying borrowed books
 queue[i]->display();
 i = (i + 1) % 100;
 } while (i != (rear + 1) % 100);
 cout << endl;
 }
 };
 // Queue class to manage returned books
 class ReturnedBookQueue {
 private:
 BorrowedBook* queue[100]; // Circular queue for returned books
 int front;
 int rear;
public:
 // Constructor initializing the queue to be empty
 ReturnedBookQueue() { front =-1; rear =-1; }
 // Method to enqueue a returned book into the queue
 void enqueue(BorrowedBook* book) {
 if ((rear + 1) % 100 == front) {
 cout << "\nReturned book queue full! Cannot accept more returned books.\n\n";
 return;
 }
 if (front ==-1) {
 front = 0; // Set front to 0 if first book is added
 }
 rear = (rear + 1) % 100;
 queue[rear] = book;
 cout << "\nBook returned and added to the returned book queue.\n\n";
 }
 // Method to display all returned books
 void displayReturnedBooks() {
 if (front ==-1) { //Checking whether queue is empty or not
 cout << "\nNo returned books in the queue!\n";
 return;
 }
 cout << "\nReturned Books in Queue:\n";
 int i = front;
 do {
 //loop diplaying returned books
 queue[i]->display();
 i = (i + 1) % 100;
 } while (i != (rear + 1) % 100);
 cout << endl;
 }
 };
 // Main class to manage the library system, including adding, borrowing, and returning books
 class LibraryManagementSystem {
 private:
 BookStack libraryStack; // Stack for books in the library
 BookQueue borrowedBooksQueue; // Queue for borrowed books
 ReturnedBookQueue returnedBooksQueue; // Queue for returned books
 public:
 // Method to add a new book to the library
void addBookToLibrary() {
 Book* newBook = new Book; //Dynamically allocating memory
 newBook->getdata();
 libraryStack.push(newBook); //calling push function
 }
 // Method to arrange books in the library (pop from stack)
 void arrangeBooksInShellLibrary() {
 Book* removedBook = libraryStack.pop();
 if (removedBook != nullptr) {
 cout << "Arranged in Shell Library: ";
 removedBook->display();
 }
 }
 // Method to borrow a book (enqueue to borrowed books queue)
 void borrowBook() {
 BorrowedBook* newBorrow = new BorrowedBook; //Dyanamically allocating memory
 cout << "\nEnter book title to borrow: ";
 cin >> newBorrow->bookTitle;
 newBorrow->getdata();
 borrowedBooksQueue.enqueue(newBorrow); //calling enqueue() to add borrowed book
 }
 // Method to return a book (dequeue from borrowed queue and enqueue to returned queue)
 void returnBook() {
 BorrowedBook* returnedBook = borrowedBooksQueue.dequeue();
 if (returnedBook) {
 returnedBooksQueue.enqueue(returnedBook);
 }
 }
 // Method to display all borrowed books
 void displayBorrowedBooks() {
 borrowedBooksQueue.displayBorrowedBooks();
 }
 // Method to display all returned books
 void displayReturnedBooks() {
 returnedBooksQueue.displayReturnedBooks();
 }
 // Method to display all books in the library stack
 void displayLibraryBooks() {
libraryStack.displayLibraryStack();
 }
 };
 int main() {
 LibraryManagementSystem librarySystem; // Create a library management system object
 int choice;
 do {
 // Display the menu options to the user
 cout << "Library Management System\n";
 cout << "1. Add Book to Library\n";
 cout << "2. Arrange Books in Shelf\n";
 cout << "3. Display Books\n";
 cout << "4. Borrow Book\n";
 cout << "5. Return Book\n";
 cout << "6. Display Borrowed Books\n";
 cout << "7. Display Returned Books\n";
 cout << "0. Exit\n";
 cout << "Enter your choice: ";
 cin >> choice;
 switch (choice) {
 case 1:
 librarySystem.addBookToLibrary(); // Add a book
 break;
 case 2:
 librarySystem.arrangeBooksInShellLibrary(); // Arrange books
 break;
 case 3:
 librarySystem.displayLibraryBooks(); // Display library books
 break;
 case 4:
 librarySystem.borrowBook(); // Borrow a book
 break;
 case 5:
 librarySystem.returnBook(); // Return a book
 break;
 case 6:
 librarySystem.displayBorrowedBooks(); // Display borrowed books
 break;
 case 7:
 librarySystem.displayReturnedBooks(); // Display returned books
 break;
 case 0:
 cout << "Exiting system...\n";
break;
 default:
 cout << "Invalid choice! Please try again.\n";
 break;
 }
 } while (choice != 0); // Repeat the loop until the user chooses to exit
 return 0;
 }
