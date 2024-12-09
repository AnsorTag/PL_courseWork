#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

class Student {
protected:
    std::string name;
    std::string course;
    int facultyNumber;
    int groupNumber;

public:
    Student() {
        std::cout << "Creating a new student\n";
        std::cout << "Enter name: ";
        std::cin >> name;

        std::cout << "Enter course: ";
        std::cin >> course;

        facultyNumber = getIntInput("Enter faculty number: ");
        groupNumber = getIntInput("Enter group number: ");
    }

    int getFacultyNumber() const { return facultyNumber; }
    int getGroupNumber() const { return groupNumber; }
    std::string getName() const { return name; }

    virtual void printDetails() const {
        std::cout << "Student {\n"
            << "  Name: " << name << "\n"
            << "  Course: " << course << "\n"
            << "  Faculty Number: " << facultyNumber << "\n"
            << "  Group Number: " << groupNumber << "\n"
            << "}\n";
    }

    static int getIntInput(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (!std::cin.fail()) break;
            std::cout << "Invalid input. Please enter an integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        student.printDetails();
        return os;
    }
};

class StudentWithGrades : public Student {
private:
    std::vector<std::vector<int>> grades;

public:
    StudentWithGrades() : Student() {
        int semesters = getIntInput("Enter number of semesters completed: ");
        for (int i = 0; i < semesters; ++i) {
            std::vector<int> semesterGrades;
            std::cout << "Entering grades for semester " << (i + 1) << "\n";
            for (int j = 0; j < 5; ++j) {
                semesterGrades.push_back(getIntInput("  Enter grade " + std::to_string(j + 1) + ": "));
            }
            grades.push_back(semesterGrades);
        }
    }

    float calculateAverageGrade() const {
        int totalSum = 0, count = 0;
        for (const auto& semester : grades) {
            for (int grade : semester) {
                totalSum += grade;
                ++count;
            }
        }
        return count ? static_cast<float>(totalSum) / count : 0.0f;
    }

    void printDetails() const override {
        Student::printDetails();
        std::cout << "  Grades:\n";
        for (size_t i = 0; i < grades.size(); ++i) {
            std::cout << "    Semester " << (i + 1) << ": ";
            for (int grade : grades[i]) {
                std::cout << grade << " ";
            }
            std::cout << "\n";
        }
        std::cout << "  Average Grade: " << calculateAverageGrade() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const StudentWithGrades& student) {
        student.printDetails();
        return os;
    }
};