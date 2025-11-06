# 🎓 E-Classroom Management System (Eva)

**EVA** is a C++ console-based application that simulates a classroom management platform for teachers and students. Built using object-oriented programming principles, this academic project supports core classroom functionalities through a menu-driven interface. It ensures offline persistence using plain text files.

---

## ✨ Key Features

- 👨‍🏫 **Teacher & Student Accounts**: Separate registration and login.  
- 🏫 **Course Management**: Teachers can create and manage courses.  
- 📝 **Assignments**: Teachers create assignments; students can submit them.  
- 📢 **Announcements**: Teachers can post updates to their courses.  
- 🧾 **Grading & Feedback**: Teachers evaluate and give feedback.  
- 🎓 **Enrollment**: Students can join available courses.  
- 💾 **Persistent Storage**: File-based text storage system.  
- 🔘 **Console UI**: Menu-driven navigation.

---

## 🛠 Technologies Used

- **C++ (C++17)**
- **OOP Principles**
- **Standard Template Library (STL)**
- **File I/O (Text-based persistence)**
- **`<filesystem>` for file management**

---

## 🚀 Getting Started

### 🧩 Prerequisites
- A C++17-compatible compiler (G++, Clang++, or MSVC)

### ⚙️ Setup Instructions
```bash
git clone https://github.com/sutikshanupman/eva-classroom.git
cd eva-classroom
g++ -std=c++17 Eva.cpp -o Eva
./Eva   # For Windows: Eva.exe
```

---

## 📁 Project Structure

| File              | Description                             |
|-------------------|-----------------------------------------|
| `Eva.cpp`         | Main code file with all class logic     |
| `*.txt` files     | Persistent storage for users/data       |

### 🧱 Core Classes
- `User` → Base class for shared user data
- `Teach`, `Stud` → Derived classes for teachers & students
- `Course`, `Assignment`, `Announcement`, `Submission` → Entities for interaction
- `ClassRoom` → Central controller for the entire system

---

## 👥 Contributors

| Name              | Role                                             |
|-------------------|--------------------------------------------------|
| Arpit Thorat      | Data handling & file I/O                         |
| **Sutikshan Upman** | OOP architecture, system flow, interface design |
| Akshat Pareek     | Debugging, testing, and refinement               |

---

## 🔮 Future Enhancements

- 🖥 GUI/Web interface with modern frameworks
- 🗃 Migration to database (e.g., SQLite/MySQL)
- 🔐 Password hashing and authentication security
- 📊 Analytics for progress and usage tracking
- 👨‍🏫 Multi-teacher and admin role management

---

## 📄 License

This project is licensed under the **MIT License**.

---

## 🙏 Acknowledgments

Inspired by tools like **Google Classroom** and **Moodle**, this educational tool was developed for academic demonstration purposes. Special thanks to peers and faculty for support during development.
