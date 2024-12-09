#pragma once
#include "student.hpp"
#include <vector>
#include <fstream>

class StudentRegistry {
private:
    std::vector<StudentWithGrades*> students;

public:
    StudentRegistry() {
        int numberOfStudents = Student::getIntInput("Enter number of students to create: ");
        for (int i = 0; i < numberOfStudents; ++i) {
            std::cout << "Adding student " << (i + 1) << "\n";
            students.push_back(new StudentWithGrades());
        }
    }

    ~StudentRegistry() {
        for (auto* student : students) delete student;
    }

    void printAllStudents() const {
        for (const auto* student : students) student->printDetails();
    }

    void printHighestAverageInGroup(int groupNumber) const {
        const StudentWithGrades* topStudent = nullptr;
        float highestAverage = 0.0f;

        for (const auto* student : students) {
            if (student->getGroupNumber() == groupNumber) {
                float avg = student->calculateAverageGrade();
                if (!topStudent || avg > highestAverage) {
                    highestAverage = avg;
                    topStudent = student;
                }
            }
        }

        if (topStudent) {
            std::cout << "Top student in group " << groupNumber << ":\n";
            topStudent->printDetails();
        }
        else {
            std::cout << "No students found in group " << groupNumber << "\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filename << "\n";
            return;
        }
        for (const auto* student : students) file << *student << "\n";
        std::cout << "Data saved to " << filename << "\n";
    }

    void addStudent(StudentWithGrades* newStudent) {
        if (newStudent) {
            students.push_back(newStudent);
            std::cout << "Student added successfully.\n";
        }
        else {
            std::cout << "Failed to add student. Pointer is null.\n";
        }
    }

    StudentWithGrades* GetStudentWithGivenFacultyNumber(int facultyNumber) const {
        for (const auto* student : students) {
            if (student->getFacultyNumber() == facultyNumber) {
                return const_cast<StudentWithGrades*>(student); // Safe as we return a non-const pointer
            }
        }
        return nullptr;
    }

    void PrintStudentsAverageGrade() const {
        for (const auto* student : students) {
            std::cout << "Student: " << student->getName() << "\n";
            std::cout << "  Average Grade: " << student->calculateAverageGrade() << "\n";
        }
    }
};
