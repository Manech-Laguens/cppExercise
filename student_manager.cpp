#include <iostream>
#include <string>

struct Student {
    int student_id;
    std::string name;
    std::string generation;

    // Constructor for Student
    Student(int id = 0, std::string name = "", std::string generation = "")
        : student_id(id), name(name), generation(generation) {}
};

// Data structure to store and manage students
class StudentManager {
    Student students[100]; // Fixed-size array for simplicity
    int count;

public:
    StudentManager() : count(0) {}

    // Add a new student
    void addStudent() {
        if (count >= 100) {
            std::cout << "Cannot add more students. List is full.\n";
            return;
        }
        int id;
        std::string name, generation;
        std::cout << "Enter Student ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Generation: ";
        std::cin >> generation;
        students[count++] = Student(id, name, generation);
        std::cout << "Student added successfully.\n";
    }

    // Retrieve a student by ID using Binary Search
    void retrieveStudent() {
        int id;
        std::cout << "Enter Student ID to retrieve: ";
        std::cin >> id;
        int index = binarySearch(id);
        if (index != -1) {
            displayStudent(students[index]);
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Update a student's details
    void updateStudent() {
        int id;
        std::cout << "Enter Student ID to update: ";
        std::cin >> id;
        int index = binarySearch(id);
        if (index != -1) {
            std::string name, generation;
            std::cout << "Enter new Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new Generation: ";
            std::cin >> generation;
            students[index].name = name;
            students[index].generation = generation;
            std::cout << "Student updated successfully.\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Remove a student by ID
    void removeStudent() {
        int id;
        std::cout << "Enter Student ID to remove: ";
        std::cin >> id;
        int index = binarySearch(id);
        if (index != -1) {
            for (int i = index; i < count - 1; ++i) {
                students[i] = students[i + 1];
            }
            --count;
            std::cout << "Student removed successfully.\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Sort students by name using Merge Sort
    void sortStudents() {
        mergeSort(0, count - 1);
        std::cout << "Students sorted by name.\n";
    }

    // Display all students
    void displayAll() {
        if (count == 0) {
            std::cout << "No students to display.\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            displayStudent(students[i]);
        }
    }

private:
    // Display a single student
    void displayStudent(const Student& student) {
        std::cout << "ID: " << student.student_id
                  << ", Name: " << student.name
                  << ", Generation: " << student.generation << std::endl;
    }

    // Binary Search to find a student by ID
    int binarySearch(int id) {
        int left = 0, right = count - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (students[mid].student_id == id) {
                return mid;
            } else if (students[mid].student_id < id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    // Merge Sort implementation
    void mergeSort(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(left, mid);
            mergeSort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    void merge(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Student leftArray[100], rightArray[100];
        for (int i = 0; i < n1; ++i)
            leftArray[i] = students[left + i];
        for (int j = 0; j < n2; ++j)
            rightArray[j] = students[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i].name <= rightArray[j].name) {
                students[k++] = leftArray[i++];
            } else {
                students[k++] = rightArray[j++];
            }
        }
        while (i < n1) {
            students[k++] = leftArray[i++];
        }
        while (j < n2) {
            students[k++] = rightArray[j++];
        }
    }
};

// Console Menu
void menu() {
    StudentManager manager;
    int choice;
    do {
        std::cout << "\nMenu:\n"
                  << "1. Add Student\n"
                  << "2. Retrieve Student\n"
                  << "3. Update Student\n"
                  << "4. Remove Student\n"
                  << "5. Sort Students\n"
                  << "6. Display All Students\n"
                  << "7. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.retrieveStudent(); break;
            case 3: manager.updateStudent(); break;
            case 4: manager.removeStudent(); break;
            case 5: manager.sortStudents(); break;
            case 6: manager.displayAll(); break;
            case 7: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}

int main() {
    menu();
    return 0;
}