#include <iostream>
#include <vector>
#include <string>
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

    bool loginTech() {
        string email, password;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;
        for (const auto &t : teachers) {
            if (email == t.getEmail() && password == t.getPass()) {
                cout << "Login Successful!" << "\n";
                teachers.push_back(t); // Temporarily store current teacher for workTech
                return true;
            }
        }
        cout << "Login Failed" << "\n";
        return false;
    }

    bool loginStud() {
        string email, password;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter password: ";
        cin >> password;
        for (const auto &s : students) {
            if (email == s.getEmail() && password == s.getPass()) {
                cout << "Login Successful!" << "\n";
                students.push_back(s); // Temporarily store current student for workStud
                return true;
            }
        }
        cout << "Login Failed" << "\n";
        return false;
    }

    void workTech() {
        Teach &t = teachers.back(); // Reference to the last logged-in teacher
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
                return;
            }
            int cid;
            cout << "Enter Course ID to add assignment to: ";
            cin >> cid;
            cin.ignore();
            bool found = false;
            for (auto &c : courses) if (c.courseId == cid) { found = true; break; }
            if (!found) {
                cout << "Course ID not found." << "\n";
                return;
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
                return;
            }
            int cid;
            cout << "Enter Course ID to announce for: ";
            cin >> cid;
            cin.ignore();
            bool found = false;
            for (auto &c : courses) if (c.courseId == cid) { found = true; break; }
            if (!found) {
                cout << "Course ID not found." << "\n";
                return;
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
                return;
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
                return;
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
            teachers.pop_back(); // Remove temporary teacher
            return;
        }
        else {
            cout << "Invalid Response\n";
        }
    }

    void workStud() {
        Stud &s = students.back(); // Reference to the last logged-in student
        cout << "\nStudent Menu:\n1.Join_Course\n2.View_Assignments\n3.Submit_Assignment\n4.View_Announcements\n5.View_Grades\n6.View_My_Account\n0.Logout\n";
        int input;
        cin >> input;
        cin.ignore();

        if (input == 1) {
            if (courses.empty()) {
                cout << "No courses available." << "\n";
                return;
            }
            int cid;
            cout << "Available courses:\n";
            for (const auto &c : courses) cout << "Course: " << c.courseName << " (ID: " << c.courseId << ")\n";
            cout << "Enter Course ID to join: ";
            cin >> cid;
            cin.ignore();
            bool found = false;
            for (auto &c : courses) if (c.courseId == cid) { found = true; break; }
            if (!found) {
                cout << "Course ID not found." << "\n";
                return;
            }
            s.enroll(cid);
            cout << "Enrolled in course " << cid << "\n";
        }
        else if (input == 2) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course." << "\n";
                return;
            }
            cout << "Assignments for your courses:\n";
            for (const auto &a : assignments) {
                for (int cid : enrolled) {
                    if (a.courseId == cid) {
                        a.viewAssignmentDetails();
                    }
                }
            }
        }
        else if (input == 3) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course." << "\n";
                return;
            }
            cout << "Your enrolled course IDs: ";
            for (int c : enrolled) cout << c << " ";
            cout << "\nAvailable assignments:\n";
            for (const auto &a : assignments) {
                for (int cid : enrolled) {
                    if (a.courseId == cid) {
                        a.viewAssignmentDetails();
                    }
                }
            }
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
            if (!found) cout << "Assignment ID not found or not accessible." << "\n";
        }
        else if (input == 4) {
            auto enrolled = s.getEnrolled();
            if (enrolled.empty()) {
                cout << "You are not enrolled in any course." << "\n";
                return;
            }
            cout << "Announcements for your courses:\n";
            for (const auto &an : announcements) {
                for (int cid : enrolled) {
                    if (an.courseId == cid) {
                        an.displayAnnouncement();
                    }
                }
            }
        }
        else if (input == 5) {
            bool any = false;
            for (const auto &sub : submissions) {
                if (sub.studentId == s.getId()) {
                    any = true;
                    sub.viewSubmission();
                }
            }
            if (!any) cout << "No submissions found for you." << "\n";
        }
        else if (input == 6) {
            s.view_my_account();
        }
        else if (input == 0) {
            cout << "Logging out student." << "\n";
            students.pop_back(); // Remove temporary student
            return;
        }
        else {
            cout << "Invalid Response\n";
        }
    }
};

int main() {
    cout << "Welcome to E-ClassRoom\n";
    ClassRoom c;
    int run = 1;

    while (run == 1) {
        cout << "\nYou are: 1.Teacher 2.Student 3.Exit\n";
        int option;
        cin >> option;

        if (option == 1) {
            cout << "Teacher Menu: 1.Register 2.Login 3.Back\n";
            int ch;
            cin >> ch;
            if (ch == 1) {
                c.registerTech();
            } 
            else if (ch == 2) {
                if (c.loginTech()) {
                    c.workTech();
                }
            } 
            else if (ch == 3) {
                continue;
            } 
            else {
                cout << "Invalid choice.\n";
            }
        } 
        else if (option == 2) {
            cout << "Student Menu: 1.Register 2.Login 3.Back\n";
            int ch;
            cin >> ch;
            if (ch == 1) {
                c.registerStud();
            } 
            else if (ch == 2) {
                if (c.loginStud()) {
                    c.workStud();
                }
            } 
            else if (ch == 3) {
                continue;
            } 
            else {
                cout << "Invalid choice.\n";
            }
        } 
        else if (option == 3) {
            run = 0;
        } 
        else {
            cout << "Invalid choice.\n";
        }
    }

    cout << "Exiting E-ClassRoom. Bye!\n";
    return 0;
}