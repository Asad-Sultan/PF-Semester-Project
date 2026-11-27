# University Management System v1 (Procedural)

A console-based university management system written in C++ with a role-based login for admins, teachers and students. This is the first version, built with structs, vectors and plain-text file storage as a **Programming Fundamentals** semester project. See [v2 (OOP)](https://github.com/Asad-Sultan/UMS-OOP) for the object-oriented rewrite.

## Features

- **Role-based access:** master admin, admin, teacher and student logins
- **Admin panel:** create and delete student records, create and edit logins, view all logins and students
- **Auto-generated roll numbers** per degree and semester (e.g. `BSSE-S2-1`)
- **Teacher panel:** mark attendance and grades per student
- **Student panel:** view personal details, attendance (with color-coded bars) and grades
- **Input validation** for usernames, passwords, degrees and semesters
- **Password change** for logged-in users
- **Persistent storage** in plain-text files, created automatically on first run
- Color-coded console interface

## Supported degrees

`BSSE` · `BSCS` · `BSAI` · `BSDS` · `BSGM`

## Getting started

**Requirements:** Windows, with MinGW-w64 (g++) or Visual Studio. The program uses `windows.h` and `conio.h`.

```bash
g++ ums.cpp -o ums.exe
ums.exe
```

On first run a `database/` folder is created with the data files.

**Default login:** username `MasterAdmin`, password `12345678`

## Project structure

```
ums.cpp          # entire program
database/        # created on first run
  ├─ logins.txt
  ├─ students.txt
  ├─ attendances.txt
  └─ gpas.txt
```

## Known limitations

- Passwords are stored in plain text (no hashing)
- Windows-only
- Each student has a fixed set of 5 subjects

## What I learned

Structs, vectors and file I/O in C++, designing role-based menus, validating input, and organizing a ~2,000-line program. These limits are what led to the OOP rewrite in v2.
