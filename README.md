# 📚 E-ClassRoom (C++ OOP Project)

## 📖 Overview
E-ClassRoom is a **console-based classroom management system** implemented in **C++ using Object-Oriented Programming (OOP) principles**.  
It allows **teachers and students** to interact in a virtual classroom with functionalities like **registration, login, course management, assignments, submissions, announcements, and grading**.

---

## Frontend Development Notice

The frontend of this project was initially generated with the assistance of AI (ChatGPT/GPT-5 by OpenAI).  
I have reviewed, modified, and adapted the code as necessary for this project.  

## ✨ Features

### 👩‍🏫 Teacher Features
- **Register/Login** into the system.  
- **Create Courses** with unique course IDs.  
- **Create Assignments** linked to specific courses.  
- **Post Announcements** for enrolled students.  
- **View Submissions** made by students.  
- **Grade Submissions** and provide feedback.  
- **View My Account** details.  
- **List Created Courses**.  

### 👨‍🎓 Student Features
- **Register/Login** into the system with a unique student ID.  
- **Join Courses** using course IDs.  
- **View Assignments** from enrolled courses.  
- **Submit Assignments** with file path/description.  
- **View Announcements** from enrolled courses.  
- **Check Grades & Feedback** for their submissions.  
- **View My Account** details.  

---

## 🏗️ System Design

### Classes & Responsibilities
- **User (Base Class)**  
  - Stores common user details: `name`, `email`, `password`.  
  - Functions: `view_my_account()`.  

- **Teach (Derived from User)**  
  - Manages `myCourseIds`.  
  - Functions: `addCourseId()`, `getCourseIds()`.  

- **Stud (Derived from User)**  
  - Has `studentId` and `enrolledCourseIds`.  
  - Functions: `enroll()`, `getEnrolled()`, `view_my_account()`.  

- **Course**  
  - Holds `courseName`, `courseId`, `teacherName`.  

- **Assignment**  
  - Contains assignment details (`title`, `desc`, `dueDate`).  
  - Function: `viewAssignmentDetails()`.  

- **Announcement**  
  - Contains announcements (`title`, `message`).  
  - Function: `displayAnnouncement()`.  

- **Submission**  
  - Tracks student submissions (`filePath`, `grade`, `feedback`).  
  - Functions: `addSubmission()`, `viewSubmission()`.  

- **ClassRoom (Controller Class)**  
  - Manages collections of **courses, assignments, announcements, submissions, teachers, students**.  
  - Handles registration, login, and workflows for teachers & students.  

---

## ▶️ How to Run

### 1. Compile
```bash
g++ -o classroom main.cpp
```

### 2. Run
```bash
./classroom
```

---

## 🖥️ User Flow

### Main Menu
```
Welcome to E-ClassRoom
You are: 
1. Teacher 
2. Student 
3. Exit
```

#### Teacher Flow
```
Teacher Menu: 
1. Register 
2. Login 
3. Back
```
- After login → Teacher actions menu (Course/Assignment/Announcements/Grading).

#### Student Flow
```
Student Menu: 
1. Register 
2. Login 
3. Back
```
- After login → Student actions menu (Join Course, Submit Assignment, View Announcements, View Grades).

---

## 📌 Example Usage

**Teacher registers & creates a course:**
```
Enter Name: Alice
Enter Email: alice@school.com
Enter password: ****
Teacher registered.

Login → Create Course
Enter Course name: Data Structures
Enter Course ID: 101
Course created: Data Structures (ID: 101)
```

**Student joins the course & views assignment:**
```
Enter Name: Bob
Enter Email: bob@student.com
Enter password: ****
Enter ID: S01
Student registered.

Login → Join Course
Available courses:
Course: Data Structures (ID: 101)
Enter Course ID to join: 101
Enrolled in course 101
```

---

## 🔑 Key OOP Concepts Used
- **Encapsulation** → Private attributes with getters/setters.  
- **Inheritance** → `Teach` & `Stud` inherit from `User`.  
- **Polymorphism** → `view_my_account()` overridden in `Stud`.  
- **Abstraction** → Separate classes for `Course`, `Assignment`, `Announcement`, `Submission`.  
- **Composition** → `ClassRoom` manages vectors of multiple objects.  

---

## 🚀 Future Improvements
- Add persistent storage (file or database) instead of in-memory vectors.  
- Add authentication with hashed passwords.  
- Improve UI with menus looping until logout.  
- Allow multiple actions in one login session (currently limited to one).  
- Add course codes instead of numeric IDs.  
