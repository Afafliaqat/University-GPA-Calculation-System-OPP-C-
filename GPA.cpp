#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

class Course {
private:
    string name;
    int creditHours;
    char grade;

public:
    Course(string name, int creditHours, char grade)
        : name(name), creditHours(creditHours), grade(grade) {}

    double getGradePoint() const {
        switch (grade) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default: return 0.0;
        }
    }

    int getCreditHours() const { return creditHours; }

    double getWeightedPoints() const {
        return getGradePoint() * creditHours;
    }

    void show() const {
        cout << "- " << name << " (" << creditHours << " cr): Grade " << grade << "\n";
    }
};

class Student {
private:
    string name, id;
    vector<Course> courses;

public:
    Student(string name, string id) : name(name), id(id) {}

    void addCourse(const Course& c) {
        courses.push_back(c);
    }

    double calculateGPA() const {
        double totalPoints = 0;
        int totalCredits = 0;
        for (const auto& c : courses) {
            totalPoints += c.getWeightedPoints();
            totalCredits += c.getCreditHours();
        }
        return (totalCredits == 0) ? 0 : totalPoints / totalCredits;
    }

    void showTranscript() const {
        cout << "\n📄 Transcript for " << name << " (ID: " << id << ")\n";
        cout << "-----------------------------------------\n";
        for (const auto& c : courses)
            c.show();
        cout << "GPA: " << fixed << setprecision(2) << calculateGPA() << "\n\n";
    }

    string getId() const {
        return id;
    }
};

// Global student database
vector<Student> students;

Student* findStudentById(const string& id) {
    for (auto& s : students) {
        if (s.getId() == id)
            return &s;
    }
    return nullptr;
}

void menu() {
    cout << "\n========== University GPA System ==========\n";
    cout << "1. Add Student\n";
    cout << "2. Add Course to Student\n";
    cout << "3. Show Transcript\n";
    cout << "4. Exit\n";
    cout << "===========================================\n";
    cout << "Choose an option: ";
}

int main() {
    int choice;
    do {
        menu();
        cin >> choice;

        if (choice == 1) {
            string name, id;
            cout << "Enter student name (no spaces): ";
            cin >> name;
            cout << "Enter student ID: ";
            cin >> id;
            students.emplace_back(name, id);
            cout << "✅ Student added.\n";

        }
        else if (choice == 2) {
            string id;
            cout << "Enter student ID: ";
            cin >> id;
            Student* s = findStudentById(id);
            if (s) {
                string cname;
                int credits;
                char grade;
                cout << "Enter course name (no spaces): ";
                cin >> cname;
                cout << "Enter credit hours: ";
                cin >> credits;
                cout << "Enter grade (A-F): ";
                cin >> grade;
                s->addCourse(Course(cname, credits, toupper(grade)));
                cout << "📚 Course added.\n";
            }
            else {
                cout << "⚠️ Student not found.\n";
            }

        }
        else if (choice == 3) {
            string id;
            cout << "Enter student ID: ";
            cin >> id;
            Student* s = findStudentById(id);
            if (s) {
                s->showTranscript();
            }
            else {
                cout << "⚠️ Student not found.\n";
            }

        }
        else if (choice == 4) {
            cout << " Exiting system. Goodbye!\n";
        }
        else {
            cout << " Invalid option. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

