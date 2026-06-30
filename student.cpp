#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Students
{
    int rollno;
    string name;
    float cgpa;
    string branch;
    int semester;

public:
    Students()
    {
        rollno = 0;
        name = "";
        cgpa = 0.0;
        branch = "";
        semester = 0;
    }

    void addStudent();
    void displayStudents() const;
    void updateStudent();

    int getRollNo() const;
    void setRollNo(int r);

    string getName() const;
    void setName(string n);

    float getCgpa() const;
    void setCgpa(float c);

    string getBranch() const;
    void setBranch(string b);

    int getSemester() const;
    void setSemester(int s);
};

class StudentsList
{
    vector<Students> students;

public:
    void addStudent();
    void displayStudents();
    void searchStudent();
    void deleteStudent();
    void updateStudent();
    void saveToFile();
    void loadFromFile();
};

void Students::addStudent()
{
    cout << "Enter Roll Number: ";
    cin >> rollno;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter CGPA: ";
    cin >> cgpa;

    cout << "Enter Branch: ";
    cin >> branch;

    cout << "Enter Semester: ";
    cin >> semester;
}

void Students::displayStudents() const
{
    cout << "\n------------------------\n";
    cout << "Roll Number : " << rollno << endl;
    cout << "Name        : " << name << endl;
    cout << "CGPA        : " << cgpa << endl;
    cout << "Branch      : " << branch << endl;
    cout << "Semester    : " << semester << endl;
    cout << "------------------------\n";
}

void Students::updateStudent()
{
    int choice;

    cout << "\n1. Update Name";
    cout << "\n2. Update CGPA";
    cout << "\n3. Update Branch";
    cout << "\n4. Update Semester";
    cout << "\nEnter Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Enter New Name: ";
        cin >> name;
        break;

    case 2:
        cout << "Enter New CGPA: ";
        cin >> cgpa;
        break;

    case 3:
        cout << "Enter New Branch: ";
        cin >> branch;
        break;

    case 4:
        cout << "Enter New Semester: ";
        cin >> semester;
        break;

    default:
        cout << "Invalid Choice!" << endl;
        return;
    }

    cout << "Student Updated Successfully!" << endl;
}

int Students::getRollNo() const
{
    return rollno;
}

void Students::setRollNo(int r)
{
    rollno = r;
}

string Students::getName() const
{
    return name;
}

void Students::setName(string n)
{
    name = n;
}

float Students::getCgpa() const
{
    return cgpa;
}

void Students::setCgpa(float c)
{
    cgpa = c;
}

string Students::getBranch() const
{
    return branch;
}

void Students::setBranch(string b)
{
    branch = b;
}

int Students::getSemester() const
{
    return semester;
}

void Students::setSemester(int s)
{
    semester = s;
}

void StudentsList::addStudent()
{
    Students s;

    s.addStudent();

    for (const auto &student : students)
    {
        if (student.getRollNo() == s.getRollNo())
        {
            cout << "Roll Number Already Exists!" << endl;
            return;
        }
    }

    students.push_back(s);

    saveToFile();

    cout << "Student Added Successfully!" << endl;
}

void StudentsList::displayStudents()
{
    if (students.size() == 0)
    {
        cout << "No Students Found!" << endl;
        return;
    }

    for (const auto &student : students)
    {
        student.displayStudents();
    }
}

void StudentsList::searchStudent()
{
    int roll;

    cout << "Enter Roll Number To Search: ";
    cin >> roll;

    bool found = false;

    for (const auto &student : students)
    {
        if (student.getRollNo() == roll)
        {
            student.displayStudents();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student Not Found!" << endl;
    }
}

void StudentsList::deleteStudent()
{
    int roll;

    cout << "Enter Roll Number To Delete: ";
    cin >> roll;

    bool found = false;

    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->getRollNo() == roll) //-> is used to access the member function of the object pointed to by the iterator
        {
            students.erase(it);

            saveToFile();

            cout << "Student Deleted Successfully!" << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student Not Found!" << endl;
    }
}

void StudentsList::updateStudent()
{
    int roll;

    cout << "Enter Roll Number To Update: ";
    cin >> roll;

    bool found = false;

    for (auto &student : students) //& is used to get the reference of the object in the vector, so that we can modify the object directly
    {
        if (student.getRollNo() == roll)
        {
            student.updateStudent();

            saveToFile();

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student Not Found!" << endl;
    }
}

void StudentsList::saveToFile()
{
    ofstream outFile("students.txt");

    if (!outFile)
    {
        cout << "Unable To Open File!" << endl;
        return;
    }

    for (const auto &student : students)
    {
        outFile << student.getRollNo() << " "
                << student.getName() << " "
                << student.getCgpa() << " "
                << student.getBranch() << " "
                << student.getSemester()
                << endl;
    }

    outFile.close();
}

void StudentsList::loadFromFile()
{
    ifstream inFile("students.txt");

    if (!inFile)
    {
        return;
    }

    students.clear();

    int rollno;
    string name;
    float cgpa;
    string branch;
    int semester;

    while (inFile >> rollno >> name >> cgpa >> branch >> semester)
    {
        Students s;

        s.setRollNo(rollno);
        s.setName(name);
        s.setCgpa(cgpa);
        s.setBranch(branch);
        s.setSemester(semester);

        students.push_back(s);
    }

    inFile.close();
}

int main()
{
    StudentsList studentsList;

    studentsList.loadFromFile();

    int choice;

    do
    {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Update Student" << endl;
        cout << "6. Reload From File" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter Your Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            studentsList.addStudent();
            break;

        case 2:
            studentsList.displayStudents();
            break;

        case 3:
            studentsList.searchStudent();
            break;

        case 4:
            studentsList.deleteStudent();
            break;

        case 5:
            studentsList.updateStudent();
            break;

        case 6:
            studentsList.loadFromFile();
            cout << "Students Reloaded From File!" << endl;
            break;

        case 7:
            cout << "Exiting Program..." << endl;
            cout << "Thank You For Using The Student Management System!" << endl;
            cout << "Have A Great Day!" << endl;
            cout << "Goodbye!" << endl;
            cout << "Exited Successfully!" << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}
