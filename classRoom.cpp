#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <limits>
using namespace std;

class User {
private:
    string name;
    string email;
    string password;

public:
    User() {}
    User(string n, string e, string p) : name(n), email(e), password(p) {}

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPass() const { return password; }

    void view_my_account() const {
        cout << "Name : " << name << "\nEmail: " << email << "\n";
    }
};

class Teach : public User {
private:
    vector<int> myCourseIds;

public:
    Teach() {}
    Teach(string n, string e, string p) : User(n, e, p) {}

    void addCourseId(int cid) { myCourseIds.push_back(cid); }
    vector<int> getCourseIds() const { return myCourseIds; }
};

class Stud : public User {
private:
    string stId;
    vector<int> enrolledCourseIds;

public:
    Stud() {}
    Stud(string n, string e, string p, string id) : User(n, e, p), stId(id) {}

    string getId() const { return stId; }

    void enroll(int cid) { enrolledCourseIds.push_back(cid); }
    vector<int> getEnrolled() const { return enrolledCourseIds; }

    void view_my_account() const {
        User::view_my_account();
        cout << "Student ID: " << stId << "\n";
    }
};

class Course {
public:
    string courseName;
    int courseId;
    string teacherName;

    Course(string n = "", int i = 0, string t = "") : courseName(n), courseId(i), teacherName(t) {}
};

class Assignment {
public:
    int assignmentId;
    string title;
    string description;
    string dueDate;
    int courseId;
    string teacherName;

    Assignment() {}
    Assignment(int aid, string t, string d, string due, int c, string teach)
        : assignmentId(aid), title(t), description(d), dueDate(due), courseId(c), teacherName(teach) {}

    void viewAssignmentDetails() const {
        cout << "Assignment ID: " << assignmentId << "\nTitle: " << title << "\nDesc: " << description
             << "\nDue: " << dueDate << "\nCourse ID: " << courseId << "\nBy: " << teacherName << "\n";
    }
};

class Announcement {
public:
    int announcementId;
    string title;
    string message;
    int courseId;

    Announcement() {}
    Announcement(int aid, string t, string m, int c)
        : announcementId(aid), title(t), message(m), courseId(c) {}

    void displayAnnouncement() const {
        cout << "Announcement ID: " << announcementId << "\nTitle: " << title << "\nMessage: " << message
             << "\nCourse ID: " << courseId << "\n";
    }
};

class Submission {
public:
    int submissionId;
    int assignmentId;
    string studentId;
    int grade;
    string feedback;
    string filePath;

    Submission() : submissionId(0), assignmentId(0), studentId(""), grade(-1), feedback(""), filePath("") {}
    Submission(int sid, int aid, string stuId, string path)
        : submissionId(sid), assignmentId(aid), studentId(stuId), grade(-1), feedback(""), filePath(path) {}

    void addSubmission() const {
        cout << "Submission ID: " << submissionId << " added for assignment " << assignmentId << " by student " << studentId << "\n";
    }

    void viewSubmission() const {
        cout << "Submission ID: " << submissionId << "\nAssignment ID: " << assignmentId << "\nStudent ID: " << studentId
             << "\nFile: " << filePath << "\n";
        if (grade >= 0)
            cout << "Grade: " << grade << "\nFeedback: " << feedback << "\n";
        else
            cout << "Not graded yet." << "\n";
    }
};

class ClassRoom {
private:
    vector<Course> courses;
    vector<Assignment> assignments;
    vector<Announcement> announcements;
    vector<Submission> submissions;
    vector<Teach> teachers;
    vector<Stud> students;

    int nextAssignmentId = 1;
    int nextAnnouncementId = 1;
    int nextSubmissionId = 1;

public:
    void registerTech() {
        string name, email, password;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter password: ";
        getline(cin, password);
        teachers.push_back(Teach(name, email, password));
        cout << "Teacher registered." << "\n";
    }

    void registerStud() {
        string name, email, password, id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter ID: ";
        getline(cin, id);
        students.push_back(Stud(name, email, password, id));
        cout << "Student registered." << "\n";
    }

    // bool loginTech() { // <-- OLD
    int loginTech() { // <-- NEW: returns index or -1
        string email, password;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;

    // Loop with an index
        for (int i = 0; i < teachers.size(); ++i) { 
            if (email == teachers[i].getEmail() && password == teachers[i].getPass()) {
                cout << "Login Successful!" << "\n";
            // teachers.push_back(t); // <-- REMOVED THIS
                return i; // <-- NEW: Return the index of the logged-in teacher
            }
        }
        cout << "Login Failed" << "\n";
        return -1; // <-- NEW: Return -1 (or any invalid index) on failure
    }

    int loginStud() { // Return index instead of bool
    string email, password;
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < students.size(); ++i) {
        if (email == students[i].getEmail() && password == students[i].getPass()) {
            cout << "Login Successful!\n";
            return i; // Return index of the logged-in student
        }
    }

    cout << "Login Failed\n";
    return -1; // invalid
}

    void workTech(int teacherIndex) {
        Teach &t = teachers[teacherIndex]; // Reference to the last logged-in teacher
        while(true){
        cout << "\nTeacher Menu:\n1.Create_Course\n2.Create_Assignment\n3.Share_Announcement\n4.Grade_Submission\n5.View_Submissions\n6.View_My_Account\n7.View_Courses\n0.Logout\n";
        int input;
        cin >> input;
        cin.ignore();

        if (input == 1) {
            string name;
            int id;
            cout << "Enter Course name: ";
            getline(cin, name);
            cout << "Enter Course ID (number): ";
            cin >> id;
            cin.ignore();
            courses.push_back(Course(name, id, t.getName()));
            t.addCourseId(id);
            cout << "Course created: " << name << " (ID: " << id << ")" << "\n";
        }
        else if (input == 2) {
            if (courses.empty()) {
                cout << "No courses available. Create a course first." << "\n";
                continue;
            }
            int cid;
            cout << "Enter Course ID to add assignment to: ";
            cin >> cid;
            cin.ignore();
            bool found = false;
            for (auto &c : courses) if (c.courseId == cid) { found = true; break; }
            if (!found) {
                cout << "Course ID not found." << "\n";
                continue;
            }
            string title, desc, due;
            cout << "Enter Assignment Title: ";
            getline(cin, title);
            cout << "Enter Description: ";
            getline(cin, desc);
            cout << "Enter Due Date (string): ";
            getline(cin, due);
            Assignment a(nextAssignmentId++, title, desc, due, cid, t.getName());
            assignments.push_back(a);
            cout << "Assignment created with ID " << a.assignmentId << "\n";
        }
        else if (input == 3) {
            if (courses.empty()) {
                cout << "No courses available. Create a course first." << "\n";
                continue;
            }
            int cid;
            cout << "Enter Course ID to announce for: ";
            cin >> cid;
            cin.ignore();
            bool found = false;
            for (auto &c : courses) if (c.courseId == cid) { found = true; break; }
            if (!found) {
                cout << "Course ID not found." << "\n";
                continue;
            }
            string title, message;
            cout << "Enter Announcement Title: ";
            getline(cin, title);
            cout << "Enter Message: ";
            getline(cin, message);
            Announcement an(nextAnnouncementId++, title, message, cid);
            announcements.push_back(an);
            cout << "Announcement posted (ID " << an.announcementId << ")." << "\n";
        }
        else if (input == 4) {
            if (submissions.empty()) {
                cout << "No submissions present." << "\n";
                continue;
            }
            cout << "All submissions:\n";
            for (const auto &sub : submissions) sub.viewSubmission();
            int sid;
            cout << "Enter Submission ID to grade: ";
            cin >> sid;
            cin.ignore();
            bool found = false;
            for (auto &sub : submissions) {
                if (sub.submissionId == sid) {
                    found = true;
                    int grade;
                    string feedback;
                    cout << "Enter grade (integer): ";
                    cin >> grade;
                    cin.ignore();
                    cout << "Enter feedback: ";
                    getline(cin, feedback);
                    sub.grade = grade;
                    sub.feedback = feedback;
                    cout << "Graded submission " << sid << "\n";
                    break;
                }
            }
            if (!found) cout << "Submission ID not found." << "\n";
        }
        else if (input == 5) {
            if (submissions.empty()) {
                cout << "No submissions present." << "\n";
                continue;
            }
            cout << "Submissions for your courses:\n";
            for (const auto &sub : submissions) {
                for (const auto &a : assignments) {
                    if (a.assignmentId == sub.assignmentId) {
                        if (a.teacherName == t.getName()) {
                            sub.viewSubmission();
                        }
                        break;
                    }
                }
            }
        }
        else if (input == 6) {
            t.view_my_account();
        }
        else if (input == 7) {
            cout << "Your courses:\n";
            for (const auto &c : courses) {
                if (c.teacherName == t.getName()) {
                    cout << "Name: " << c.courseName << " ID: " << c.courseId << "\n";
                }
            }
        }
        else if (input == 0) {
            cout << "Logging out teacher." << "\n";
            return;
        }
        else {
            cout << "Invalid Response\n";
        }}
    }

    void workStud(int studentIndex) {
    Stud &s = students[studentIndex]; // Directly reference the logged-in student

    while (true) { // allow continuous interaction until logout
        cout << "\nStudent Menu:\n"
             << "1.Join_Course\n2.View_Assignments\n3.Submit_Assignment\n"
             << "4.View_Announcements\n5.View_Grades\n6.View_My_Account\n0.Logout\n";

        int input;
        cin >> input;
        cin.ignore();

        if (input == 1) {
            if (courses.empty()) {
                cout << "No courses available.\n";
                continue;
            }
            int cid;
            cout << "Available courses:\n";
            for (const auto &c : courses)
                cout << "Course: " << c.courseName << " (ID: " << c.courseId << ")\n";

            cout << "Enter Course ID to join: ";
            cin >> cid;
            cin.ignore();

            bool found = false;
            for (auto &c : courses)
                if (c.courseId == cid) { found = true; break; }

            if (!found) {
                cout << "Course ID not found.\n";
                continue;
            }

            s.enroll(cid);
            cout << "Enrolled in course " << cid << "\n";
        }

        else if (input == 2) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course.\n";
                continue;
            }

            cout << "Assignments for your courses:\n";
            for (const auto &a : assignments)
                for (int cid : enrolled)
                    if (a.courseId == cid)
                        a.viewAssignmentDetails();
        }

        else if (input == 3) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course.\n";
                continue;
            }

            cout << "Your enrolled course IDs: ";
            for (int c : enrolled) cout << c << " ";
            cout << "\nAvailable assignments:\n";

            for (const auto &a : assignments)
                for (int cid : enrolled)
                    if (a.courseId == cid)
                        a.viewAssignmentDetails();

            int aid;
            cout << "Enter Assignment ID to submit: ";
            cin >> aid;
            cin.ignore();

            bool found = false;
            for (const auto &a : assignments) {
                if (a.assignmentId == aid) {
                    found = true;
                    string path;
                    cout << "Enter file path / description of submission: ";
                    getline(cin, path);
                    Submission sub(nextSubmissionId++, aid, s.getId(), path);
                    submissions.push_back(sub);
                    cout << "Submission added with ID " << sub.submissionId << "\n";
                    break;
                }
            }
            if (!found)
                cout << "Assignment ID not found or not accessible.\n";
        }

        else if (input == 4) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course.\n";
                continue;
            }

            cout << "Announcements for your courses:\n";
            for (const auto &an : announcements)
                for (int cid : enrolled)
                    if (an.courseId == cid)
                        an.displayAnnouncement();
        }

        else if (input == 5) {
            bool any = false;
            for (const auto &sub : submissions)
                if (sub.studentId == s.getId()) {
                    any = true;
                    sub.viewSubmission();
                }

            if (!any)
                cout << "No submissions found for you.\n";
        }

        else if (input == 6) {
            s.view_my_account();
        }

        else if (input == 0) {
            cout << "Logging out student.\n";
            break; // stop loop instead of popping from vector
        }

        else {
            cout << "Invalid Response\n";
        }
    }
}
    void loadData() {
    namespace fs = std::filesystem;
    string basePath = "./";
    cout << "\n Loading data from: " << fs::absolute(basePath) << "\n";

    ifstream fin;
    string line;

    // Load Teachers 
    fin.open(basePath + "teachers.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string n, e, p;
            stringstream ss(line);
            getline(ss, n, ',');
            getline(ss, e, ',');
            getline(ss, p, ',');
            teachers.push_back(Teach(n, e, p));
        }
        fin.close();
    }

    // Load Students
    fin.open(basePath + "students.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string n, e, p, id;
            stringstream ss(line);
            getline(ss, n, ',');
            getline(ss, e, ',');
            getline(ss, p, ',');
            getline(ss, id, ',');
            students.push_back(Stud(n, e, p, id));
        }
        fin.close();
    }

    // Load Courses
    fin.open(basePath + "courses.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string n, t, tmp;
            int id;
            stringstream ss(line);
            getline(ss, n, ',');
            getline(ss, tmp, ',');
            id = stoi(tmp);
            getline(ss, t, ',');
            courses.push_back(Course(n, id, t));
        }
        fin.close();
    }

    // Load Assignments
    fin.open(basePath + "assignments.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string t, d, du, te, tmp;
            int aid, cid;
            stringstream ss(line);
            getline(ss, tmp, ',');
            aid = stoi(tmp);
            getline(ss, t, ',');
            getline(ss, d, ',');
            getline(ss, du, ',');
            getline(ss, tmp, ',');
            cid = stoi(tmp);
            getline(ss, te, ',');
            assignments.push_back(Assignment(aid, t, d, du, cid, te));
            nextAssignmentId = max(nextAssignmentId, aid + 1);
        }
        fin.close();
    }

    // Load Announcements
    fin.open(basePath + "announcements.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string t, m, tmp;
            int aid, cid;
            stringstream ss(line);
            getline(ss, tmp, ',');
            aid = stoi(tmp);
            getline(ss, t, ',');
            getline(ss, m, ',');
            getline(ss, tmp, ',');
            cid = stoi(tmp);
            announcements.push_back(Announcement(aid, t, m, cid));
            nextAnnouncementId = max(nextAnnouncementId, aid + 1);
        }
        fin.close();
    }

    // Load Submissions
    fin.open(basePath + "submissions.txt");
    if (fin.is_open()) {
        while (getline(fin, line)) {
            string stu, fb, fp, tmp;
            int sid, aid, gr;
            stringstream ss(line);
            getline(ss, tmp, ',');
            sid = stoi(tmp);
            getline(ss, tmp, ',');
            aid = stoi(tmp);
            getline(ss, stu, ',');
            getline(ss, tmp, ',');
            gr = stoi(tmp);
            getline(ss, fb, ',');
            getline(ss, fp, ',');
            submissions.push_back(Submission(sid, aid, stu, fp));
            submissions.back().grade = gr;
            submissions.back().feedback = fb;
            nextSubmissionId = max(nextSubmissionId, sid + 1);
        }
        fin.close();
    }

    cout << "Data loaded successfully!\n";
    }
    void saveData() {
    namespace fs = std::filesystem;
    string basePath = "./";

    cout << "\n Saving data to: " << fs::absolute(basePath) << "\n";

    ofstream fout;

    // Save Teachers
    fout.open(basePath + "teachers.txt");
    if (!fout) {
        cerr << "Error: Could not open teachers.txt\n";
    } else {
        for (auto &t : teachers)
            fout << t.getName() << " " << t.getEmail() << " " << t.getPass() << "\n";
        fout.close();
    }

    // Save Students
    fout.open(basePath + "students.txt");
    if (!fout) {
        cerr << " Error: Could not open students.txt\n";
    } else {
        for (auto &s : students)
            fout << s.getName() << " " << s.getEmail() << " " << s.getPass() << " " << s.getId() << "\n";
        fout.close();
    }

    // Save Courses
    fout.open(basePath + "courses.txt");
    if (!fout) {
        cerr << "Error: Could not open courses.txt\n";
    } else {
        for (auto &c : courses)
            fout << c.courseName << " " << c.courseId << " " << c.teacherName << "\n";
        fout.close();
    }

    // Save Assignments
    fout.open(basePath + "assignments.txt");
    if (!fout) {
        cerr << "Error: Could not open assignments.txt\n";
    } else {
        for (auto &a : assignments)
            fout << a.assignmentId << " " << a.title <<  " " << a.description << " "
                 << a.dueDate << " " << a.courseId << " " << a.teacherName << "\n";
        fout.close();
    }

    // Save Announcements
    fout.open(basePath + "announcements.txt");
    if (!fout) {
        cerr << "Error: Could not open announcements.txt\n";
    } else {
        for (auto &an : announcements)
            fout << an.announcementId << " " << an.title << " " << an.message << " " << an.courseId << "\n";
        fout.close();
    }

    // Save Submissions
    fout.open(basePath + "submissions.txt");
    if (!fout) {
        cerr << "Error: Could not open submissions.txt\n";
    } else {
        for (auto &sub : submissions)
            fout << sub.submissionId << " " << sub.assignmentId << " " << sub.studentId << " "
                 << sub.grade << " " << sub.feedback << " " << sub.filePath << "\n";
        fout.close();
    }

    cout << "Data saved successfully in " << fs::absolute(basePath) << "\n";
}
};

int main() {
    cout << "Current Working Directory: " << std::filesystem::current_path() << "\n";
    cout << "Welcome to E-ClassRoom\n";

    ClassRoom c;
    c.loadData();

    int run = 1;
    while (run == 1) {
        cout << "\nYou are: 1.Teacher 2.Student 3.Exit\n";
        char option;
        cin >> option;

        if (option == '1') {
            cout << "Teacher Menu: 1.Register 2.Login 3.Back\n";
            char ch;
            cin >> ch;
            if (ch == '1') {
                c.registerTech();
            } else if (ch == '2') {
                int loggedInIndex = c.loginTech();
                if (loggedInIndex != -1) {
                    c.workTech(loggedInIndex);
                }
            } else if (ch == '3') {
                continue;
            } else {
                cout << "Invalid choice.\n";
            }
        } 
        else if (option == '2') {
            cout << "Student Menu: 1.Register 2.Login 3.Back\n";
            char ch;
            cin >> ch;
            if (ch == '1') {
                c.registerStud();
            } else if (ch == '2') {
                int loggedInIndex = c.loginStud();
                if (loggedInIndex != -1) {
                    c.workStud(loggedInIndex);
                }
            } else if (ch == '3') {
                continue;
            } else {
                cout << "Invalid choice.\n";
            }
        } 
        else if (option == '3') {
            run = 0; // exit main loop
        } 
        else {
            cout << "Invalid choice.\n";
        }
    }

    c.saveData();
    cout << "Exiting E-ClassRoom. Bye!\n";
    return 0;
}
