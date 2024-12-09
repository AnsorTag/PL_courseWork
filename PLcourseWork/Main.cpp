#include "student.hpp"
#include "studentRegistry.hpp"
#include <iostream>

int main() {
    StudentRegistry registry;

    while (true) {
        std::cout << "\nActions: [print | add | highest-average | save | find | print-averages | exit]\n";
        std::cout << "Choose an action: ";
        std::string action;
        std::cin >> action;

        if (action == "print") {
            registry.printAllStudents();
        }
        else if (action == "add") {
            registry.addStudent(new StudentWithGrades());
        }
        else if (action == "highest-average") {
            int group = Student::getIntInput("Enter group number: ");
            registry.printHighestAverageInGroup(group);
        }
        else if (action == "save") {
            std::string filename;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            registry.saveToFile(filename);
        }
        else if (action == "find") {
            int facultyNumber = Student::getIntInput("Enter faculty number: ");
            StudentWithGrades* student = registry.GetStudentWithGivenFacultyNumber(facultyNumber);
            if (student) {
                student->printDetails();
            }
            else {
                std::cout << "Student with faculty number " << facultyNumber << " not found.\n";
            }
        }
        else if (action == "print-averages") {
            registry.PrintStudentsAverageGrade();
        }
        else if (action == "exit") {
            break;
        }
        else {
            std::cout << "Unknown action.\n";
        }
    }

    return 0;
}
