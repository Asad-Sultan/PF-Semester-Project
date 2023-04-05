#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <direct.h>
#include <conio.h>
#include <vector>
#include <fstream>

using namespace std;

bool is_loggedIn = false;
string currentUser = "Guest", mode = "Guest";

struct user
{
  string type;
  string username;
  string password;
};

struct studentData
{
  string username;
  string semester;
  string degree;
  string rollnumber;
  string fullname;
  string gender;
};

struct attendance
{
  string rollnumber;
  int s1;
  int s2;
  int s3;
  int s4;
  int s5;
};

struct gpa
{
  string rollnumber;
  float s1;
  float s2;
  float s3;
  float s4;
  float s5;
};

vector<user> logins;
vector<studentData> students;
vector<attendance> attendances;
vector<gpa> gpas;

//-------------------- AESTHETIC FUNCTIONS --------------------//

void setColor(int desiredColor)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}

void headerLeft()
{
  setColor(9);
  cout << "#---[ ";
  setColor(7);
}

void headerRight()
{
  setColor(9);
  cout << " ]---#\n\n";
  setColor(7);
}

//-------------------- DATA FETCH, LOGIN, SORT & GENERAL REUSABLE FUNCTIONS --------------------//

void initializeFiles()
{
  mkdir("database");

  ifstream loginsExist("database/logins.txt");
  if (!loginsExist)
  {
    ofstream initializeUsers("database/logins.txt");
    initializeUsers << "#Admin" << endl;
    initializeUsers << "MasterAdmin" << endl;
    initializeUsers << "12345678" << endl;
    initializeUsers << endl;
    initializeUsers << EOF;
    initializeUsers.close();
  }

  ifstream studentsExist("database/students.txt");
  if (!studentsExist)
  {
    ofstream initializeStudents("database/students.txt");
    initializeStudents << EOF;
    initializeStudents.close();
  }

  ifstream attendancesExist("database/attendances.txt");
  if (!attendancesExist)
  {
    ofstream initializeAttendances("database/attendances.txt");
    initializeAttendances << EOF;
    initializeAttendances.close();
  }

  ifstream gpasExist("database/gpas.txt");
  if (!gpasExist)
  {
    ofstream initializeGPAs("database/gpas.txt");
    initializeGPAs << EOF;
    initializeGPAs.close();
  }
}

void loadData()
{
  initializeFiles();
  string lineBreak;

  // *** Load Users *** //
  user tempUser;
  ifstream loginsReader("database/logins.txt");

  if (loginsReader.is_open())
  {
    while (!loginsReader.eof())
    {
      getline(loginsReader, tempUser.type);

      if (tempUser.type != "-1")
      {
        getline(loginsReader, tempUser.username);
        getline(loginsReader, tempUser.password);

        getline(loginsReader, lineBreak);

        logins.push_back(tempUser);
      }
    }
    loginsReader.close();
  }

  // *** Load Students *** //
  studentData tempStudent;
  ifstream studentsReader("database/students.txt");

  if (studentsReader.is_open())
  {
    while (!studentsReader.eof())
    {
      getline(studentsReader, tempStudent.username);

      if (tempStudent.username != "-1")
      {
        getline(studentsReader, tempStudent.semester);
        getline(studentsReader, tempStudent.degree);
        getline(studentsReader, tempStudent.rollnumber);
        getline(studentsReader, tempStudent.fullname);
        getline(studentsReader, tempStudent.gender);

        getline(studentsReader, lineBreak);

        students.push_back(tempStudent);
      }
    }

    studentsReader.close();
  }

  // *** Load Attendances *** //
  attendance tempAttendance;
  string attendanceArr[5];
  ifstream attendanceReader("database/attendances.txt");

  if (attendanceReader.is_open())
  {
    while (!attendanceReader.eof())
    {
      getline(attendanceReader, tempAttendance.rollnumber);

      if (tempAttendance.rollnumber != "-1")
      {
        getline(attendanceReader, attendanceArr[0]);
        tempAttendance.s1 = stoi(attendanceArr[0]);
        getline(attendanceReader, attendanceArr[1]);
        tempAttendance.s2 = stoi(attendanceArr[1]);
        getline(attendanceReader, attendanceArr[2]);
        tempAttendance.s3 = stoi(attendanceArr[2]);
        getline(attendanceReader, attendanceArr[3]);
        tempAttendance.s4 = stoi(attendanceArr[3]);
        getline(attendanceReader, attendanceArr[4]);
        tempAttendance.s5 = stoi(attendanceArr[4]);

        getline(attendanceReader, lineBreak);

        attendances.push_back(tempAttendance);
      }
    }
    attendanceReader.close();
  }

  // *** Load GPAs *** //
  gpa tempGPA;
  string gpaArr[5];
  ifstream gpaReader("database/gpas.txt");

  if (gpaReader.is_open())
  {
    while (!gpaReader.eof())
    {
      getline(gpaReader, tempGPA.rollnumber);

      if (tempGPA.rollnumber != "-1")
      {
        getline(gpaReader, gpaArr[0]);
        tempGPA.s1 = stof(gpaArr[0]);
        getline(gpaReader, gpaArr[1]);
        tempGPA.s2 = stof(gpaArr[1]);
        getline(gpaReader, gpaArr[2]);
        tempGPA.s3 = stof(gpaArr[2]);
        getline(gpaReader, gpaArr[3]);
        tempGPA.s4 = stof(gpaArr[3]);
        getline(gpaReader, gpaArr[4]);
        tempGPA.s5 = stof(gpaArr[4]);

        getline(gpaReader, lineBreak);

        gpas.push_back(tempGPA);
      }
    }
    gpaReader.close();
  }
}

void saveData()
{
  // *** Save Users *** //

  ofstream loginsWriter("database/logins.txt");

  if (loginsWriter.is_open())
  {
    loginsWriter.clear();

    for (int i = 0; i < logins.size(); i++)
    {
      loginsWriter << logins[i].type << endl;
      loginsWriter << logins[i].username << endl;
      loginsWriter << logins[i].password << endl;
      loginsWriter << endl;
    }

    loginsWriter << EOF;
    loginsWriter.close();
  }

  // *** Save Students *** //

  ofstream studentsWriter("database/students.txt");

  if (studentsWriter.is_open())
  {
    studentsWriter.clear();

    for (int i = 0; i < students.size(); i++)
    {
      studentsWriter << students[i].username << endl;
      studentsWriter << students[i].semester << endl;
      studentsWriter << students[i].degree << endl;
      studentsWriter << students[i].rollnumber << endl;
      studentsWriter << students[i].fullname << endl;
      studentsWriter << students[i].gender << endl;
      studentsWriter << endl;
    }

    studentsWriter << EOF;
    studentsWriter.close();
  }

  // *** Save Attendances *** //

  ofstream attendanceWriter("database/attendances.txt");

  if (attendanceWriter.is_open())
  {
    attendanceWriter.clear();

    for (int i = 0; i < attendances.size(); i++)
    {
      attendanceWriter << attendances[i].rollnumber << endl;
      attendanceWriter << attendances[i].s1 << endl;
      attendanceWriter << attendances[i].s2 << endl;
      attendanceWriter << attendances[i].s3 << endl;
      attendanceWriter << attendances[i].s4 << endl;
      attendanceWriter << attendances[i].s5 << endl;
      attendanceWriter << endl;
    }

    attendanceWriter << EOF;
    attendanceWriter.close();
  }

  // *** Save GPAs *** //

  ofstream gpaWriter("database/gpas.txt");

  if (gpaWriter.is_open())
  {
    gpaWriter.clear();

    for (int i = 0; i < gpas.size(); i++)
    {
      gpaWriter << gpas[i].rollnumber << endl;
      gpaWriter << gpas[i].s1 << endl;
      gpaWriter << gpas[i].s2 << endl;
      gpaWriter << gpas[i].s3 << endl;
      gpaWriter << gpas[i].s4 << endl;
      gpaWriter << gpas[i].s5 << endl;
      gpaWriter << endl;
    }

    gpaWriter << EOF;
    gpaWriter.close();
  }
}

void login()
{
  system("CLS");
  string username, password;

  headerLeft();
  cout << "University Management System";
  headerRight();

  cout << "Username: ";
  getline(cin, username);
  cout << "Password: ";
  getline(cin, password);

  for (int i = 0; i < logins.size(); i++)
  {
    if (logins[i].username == username && logins[i].password == password)
    {
      is_loggedIn = true;
      currentUser = username;
      mode = logins[i].type;
      break;
    }
  }

  if (is_loggedIn)
  {
    setColor(10);
    cout << "\nSuccessfully Logged In As ";
    setColor(7);
    cout << currentUser;
    setColor(10);
    cout << " (" << mode << ")";
    setColor(7);
    Sleep(1000);
  }
  else
  {
    setColor(12);
    cout << "\nLog In Failed! Please Try Again";
    setColor(7);
    Sleep(1000);
  }
}

bool username_LengthCheck(string username)
{
  if (username.length() > 20 || username.length() < 8)
  {
    setColor(12);
    cout << "\nUsername must be between 8 and 20 characters!\n";
    setColor(7);

    return false;
  }
  else
    return true;
}

bool password_LengthCheck(string password)
{
  if (password.length() > 20 || password.length() < 8)
  {
    setColor(12);
    cout << "\nPassword must be between 8 and 20 characters!\n";
    setColor(7);

    return false;
  }
  else
    return true;
}

int return_UserIndex(string username)
{
  int index = -1;

  for (int i = 0; i < logins.size(); i++)
  {
    if (logins[i].username == username)
      index = i;
  }

  return index;
}

int return_StudentIndex(string username)
{
  int index = -1;

  for (int i = 0; i < students.size(); i++)
  {
    if (students[i].username == username)
      index = i;
  }

  return index;
}

int return_StudentIndex_RN(string rollnumber)
{
  int index = -1;

  for (int i = 0; i < students.size(); i++)
  {
    if (students[i].rollnumber == rollnumber)
      index = i;
  }

  return index;
}

void change_Password(string username, bool skipPasswordCheck)
{
  int index = return_UserIndex(username);
  string oldPassword, newPassword, confirmNewPassword;

  if (skipPasswordCheck == false)
  {
    do
    {
      cout << "Enter current password: ";
      cin >> oldPassword;

      if (logins[index].password != oldPassword)
      {
        setColor(12);
        cout << "\nIncorrect password! try again\n\n";
        setColor(7);
      }
    } while (logins[index].password != oldPassword);
  }

  do
  {
    cout << "\nEnter new password: ";
    cin >> newPassword;
  } while (!password_LengthCheck(newPassword));

  do
  {
    cout << "\nConfirm new password: ";
    cin >> confirmNewPassword;

    if (confirmNewPassword != newPassword)
    {
      setColor(12);
      cout << "\nPasswords do not match!\n";
      setColor(7);
    }
  } while (confirmNewPassword != newPassword);

  logins[index].password = confirmNewPassword;
  saveData();

  setColor(10);
  cout << "\nPassword changed successfully\n";
  setColor(7);

  cout << "\nPress any key to continue...";
  getch();
}

// *** Student Managing Validations *** //

bool checkStudentUsernameInLogins(string username)
{
  if (return_UserIndex(username) == -1)
  {
    setColor(12);
    cout << "\nNo such username found in logins database\n";
    setColor(6);
    cout << "Please create this user first or enter an existing username\n\n";
    setColor(7);
    return false;
  }
  else
    return true;
}

bool checkIfUserTypeIsStudent(string username)
{
  if (logins[return_UserIndex(username)].type != "Student")
  {
    setColor(12);
    cout << "\nThis username is not a student\n";
    setColor(6);
    cout << "Please change user's type or enter a different username\n\n";
    setColor(7);
    return false;
  }
  else
    return true;
}

bool checkIfAStudentAlreadyExists(string username)
{
  bool available = true;

  for (int i = 0; i < students.size(); i++)
    if (students[i].username == username)
      available = false;

  if (!available)
  {
    setColor(12);
    cout << "\nA student already exists with this username\n\n";
    setColor(7);
  }

  return available;
}

bool validateSemester(string semseter)
{
  int semesterNumber = int(semseter[0]) - 48;

  if (semesterNumber < 1 || semesterNumber > 8)
  {
    setColor(12);
    cout << "\nSemester must be between 1 & 8\n\n";
    setColor(7);
    return false;
  }
  else
    return true;
}

//-------------------- ADMIN FUNCTIONS --------------------//

// *** Manage Students *** //

string Student_AssignRollNo(string semester, string degree)
{
  string rollno;

  rollno = degree + "-S" + semester + "-";

  int count = 1;

  for (int i = 0; i < students.size(); i++)
  {
    if (students[i].semester == semester && students[i].degree == degree)
      count++;
  }

  rollno = rollno + to_string(count);
  return rollno;
}

void admin_ManageStudents_Create()
{
  studentData newStudent;

  system("CLS");

  headerLeft();
  cout << "Admin Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > Manage Students > Create";
  headerRight();

  bool validStudentUsername;
  do
  {
    cout << "Enter student's username: ";
    cin >> newStudent.username;

    validStudentUsername = (checkStudentUsernameInLogins(newStudent.username) && checkIfUserTypeIsStudent(newStudent.username) && checkIfAStudentAlreadyExists(newStudent.username));
  } while (!validStudentUsername);

  do
  {
    cout << "Enter student's semester: ";
    cin >> newStudent.semester;
  } while (!validateSemester(newStudent.semester));

  do
  {
    cout << "Enter student's degree: ";
    cin >> newStudent.degree;

    if (newStudent.degree != "BSSE" && newStudent.degree != "BSCS" && newStudent.degree != "BSAI" && newStudent.degree != "BSDS" && newStudent.degree != "BSGM")
    {
      setColor(12);
      cout << "\nInvalid degree!\n";
      setColor(6);
      cout << "You must choose one of the following options: BSSE, BSCS, BSAI, BSDS, BSGM\n\n";
      setColor(7);
    }
  } while (newStudent.degree != "BSSE" && newStudent.degree != "BSCS" && newStudent.degree != "BSAI" && newStudent.degree != "BSDS" && newStudent.degree != "BSGM");

  newStudent.rollnumber = Student_AssignRollNo(newStudent.semester, newStudent.degree);

  string fName, lName;
  cout << "Enter student's first name: ";
  cin >> fName;
  cout << "Enter student's last name: ";
  cin >> lName;
  newStudent.fullname = fName + " " + lName;

  do
  {
    cout << "Enter student's gender (Male/Female): ";
    cin >> newStudent.gender;

    if (newStudent.gender != "Male" && newStudent.gender != "Female")
    {
      setColor(12);
      cout << "\nInvalid input!\n\n";
      setColor(7);
    }
  } while (newStudent.gender != "Male" && newStudent.gender != "Female");

  students.push_back(newStudent);
  saveData();

  setColor(10);
  cout << "\nStudent created successfully!\n\n";
  setColor(7);

  setColor(14);
  cout << left << setw(12) << "Username: ";
  setColor(7);
  cout << newStudent.username;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Semester: ";
  setColor(7);
  cout << newStudent.semester;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Degree: ";
  setColor(7);
  cout << newStudent.degree;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Roll No: ";
  setColor(7);
  cout << newStudent.rollnumber;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Full Name: ";
  setColor(7);
  cout << newStudent.fullname;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Gender: ";
  setColor(7);
  cout << newStudent.gender;
  cout << "\n\n";

  cout << "Press any key to continue...";
  getch();
}

void admin_ManageStudents_Delete()
{
  string studentToDelete;
  int index;
  bool student_exits;

  system("CLS");

  headerLeft();
  cout << "Admin Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > Manage Students > Delete";
  headerRight();

  do
  {
    cout << "Enter username of the student you want to delete: ";
    cin >> studentToDelete;

    if (studentToDelete == "!CANCEL")
    {
      student_exits = false;
      break;
    }

    for (int i = 0; i < students.size(); i++)
    {
      if (students[i].username == studentToDelete)
      {
        student_exits = true;
        index = i;
      }
    }

    if (!student_exits)
    {
      setColor(12);
      cout << "\nStudent does not exist! Try again or type !CANCEL to return to menu\n\n";
      setColor(7);
    }
  } while (!student_exits);

  if (student_exits)
  {
    int option;

    string confirmAction;

    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Manage Students > Delete '" << studentToDelete << "'";
    headerRight();

    setColor(6);
    cout << "Warning! This action cannot be undone\n\n";
    setColor(7);

    do
    {
      cout << "Enter !DELETE to confirm student deletion\n";
      cout << "Enter !CANCEL to cancel the action\n\n";

      cout << "Input: ";
      cin >> confirmAction;

      if (confirmAction != "!DELETE" && confirmAction != "!CANCEL")
      {
        setColor(12);
        cout << "\nInvalid Input!\n\n";
        setColor(7);
      }
    } while (confirmAction != "!DELETE" && confirmAction != "!CANCEL");

    if (confirmAction == "!DELETE")
    {
      students.erase(students.begin() + index);
      saveData();

      setColor(10);
      cout << "\nStudent deleted successfully!\n";
      setColor(7);

      cout << "\nPress any key to continue...";
      getch();
    }
  }
}

void admin_ManageStudents()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Manage Students";
    headerRight();

    cout << "1 - Create New Student\n";
    cout << "2 - Delete a Student\n";

    cout << "\n0 - Back\n";

    cout << "\nChoose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      admin_ManageStudents_Create();
      break;

    case 2:
      admin_ManageStudents_Delete();
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

// *** Manage Logins *** //

void admin_ManageLogins_Create()
{
  user newUser;
  int type;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Manage Logins > Create";
    headerRight();

    cout << "1 - Admin\n";
    cout << "2 - Student\n";
    cout << "3 - Teacher\n\n";

    cout << "0 - Cancel\n\n";

    cout << "Choose user type: ";
    cin >> type;

    if (type == 1 && mode != "#Admin")
    {
      setColor(6);
      cout << "\nWarning! Only Head Admin can create new Admins";
      setColor(7);
      Sleep(1500);

      type = -1;
    }

    switch (type)
    {
    case 1:
      newUser.type = "Admin";
      break;

    case 2:
      newUser.type = "Student";
      break;

    case 3:
      newUser.type = "Teacher";
      break;

    case 0:
    case -1:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }
  } while (type != 1 && type != 2 && type != 3 && type != 0);

  if (type != 0)
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Manage Logins > Create New " << newUser.type;
    headerRight();

    bool usernameAvailable, username_RightLength;
    do
    {
      do
      {
        cout << "Create username: ";
        cin >> newUser.username;

        username_RightLength = username_LengthCheck(newUser.username);

        if (return_UserIndex(newUser.username) == -1)
          usernameAvailable = true;
        else
        {
          usernameAvailable = false;
          setColor(12);
          cout << "\nUsername already exists! Try another username\n";
          setColor(7);
        }

        if (!username_RightLength || !usernameAvailable)
          cout << endl;
      } while (!username_RightLength);
    } while (!usernameAvailable);

    do
    {
      cout << "\nCreate password: ";
      cin >> newUser.password;
    } while (!password_LengthCheck(newUser.password));

    logins.push_back(newUser);
    saveData();

    setColor(10);
    cout << "\nUser created successfully\n";
    setColor(7);

    cout << "\nPress any key to continue...";
    getch();
  }
}

void admin_ManageLogins_Edit()
{
  string userToEdit;
  int index;
  bool user_exists;

  system("CLS");

  headerLeft();
  cout << "Admin Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > Manage Logins > Edit";
  headerRight();

  do
  {
    cout << "Enter username of the user you want to edit: ";
    cin >> userToEdit;

    if (userToEdit == "!CANCEL")
    {
      user_exists = false;
      break;
    }

    for (int i = 0; i < logins.size(); i++)
    {
      if (logins[i].username == userToEdit)
      {
        user_exists = true;
        index = i;
      }
    }

    if (!user_exists)
    {
      setColor(12);
      cout << "\nUser does not exist! Try again or type !CANCEL to return to menu\n\n";
      setColor(7);

      user_exists = false;
    }
    else
    {
      if (logins[index].type == "Admin" && mode != "#Admin")
      {
        setColor(6);
        cout << "\nWarning! Only Head Admin can edit other Admins\n\n";
        setColor(7);

        user_exists = false;
      }

      if (logins[index].type == "#Admin")
      {
        setColor(6);
        cout << "\nWarning! Head Admin cannot be edited\n\n";
        setColor(7);

        user_exists = false;
      }
    }
  } while (!user_exists);

  int studentIndex;

  if (logins[index].type == "Student")
  {
    studentIndex = return_StudentIndex(userToEdit);
  }

  if (user_exists)
  {
    int option;

    do
    {
      system("CLS");

      headerLeft();
      cout << "Admin Panel (";
      setColor(14);
      cout << currentUser;
      setColor(7);
      cout << ") > Manage Logins > Editing '" << userToEdit << "'";
      headerRight();

      cout << "1 - Change User Type\n";
      cout << "2 - Edit Username\n";
      cout << "3 - Change Password\n";
      cout << "4 - Delete User\n\n";

      cout << "0 - Cancel\n\n";

      cout << "Choose an option: ";
      cin >> option;

      int type;
      string newUsername, confirmAction;

      switch (option)
      {
      case 1:
        do
        {
          cout << "\n1 - Admin\n";
          cout << "2 - Student\n";
          cout << "3 - Teacher\n\n";

          cout << "Choose user type: ";
          cin >> type;

          switch (type)
          {
          case 1:
            logins[index].type = "Admin";
            break;

          case 2:
            logins[index].type = "Student";
            break;

          case 3:
            logins[index].type = "Teacher";
            break;

          default:
            setColor(12);
            cout << "\nInvalid Input!\n";
            setColor(7);
            break;
          }
        } while (type != 1 && type != 2 && type != 3);

        // *** Update Student. Warning: Changing a Student to another user type will delete data from students vector *** //
        if (studentIndex != -1 && logins[index].type != "Student")
          students.erase(students.begin() + studentIndex);

        saveData();

        setColor(10);
        cout << "\nUser type changed successfully";
        setColor(7);

        Sleep(1000);
        break;

      case 2:
        bool usernameAvailable;

        do
        {
          do
          {
            cout << "\nChoose new username: ";
            cin >> newUsername;

            if (return_UserIndex(newUsername) == -1)
              usernameAvailable = true;
            else
            {
              usernameAvailable = false;
              setColor(12);
              cout << "\nUsername already exists! Try another username\n";
              setColor(7);
            }
          } while (!username_LengthCheck(newUsername));
        } while (!usernameAvailable);

        logins[index].username = newUsername;
        userToEdit = newUsername;

        // *** Update Student Username As Well *** //
        if (studentIndex != -1)
          students[studentIndex].username = newUsername;

        saveData();

        setColor(10);
        cout << "\nUsername changed successfully";
        setColor(7);

        Sleep(1000);
        break;

      case 3:
        change_Password(userToEdit, true);
        break;

      case 4:
        system("CLS");

        headerLeft();
        cout << "Admin Panel (";
        setColor(14);
        cout << currentUser;
        setColor(7);
        cout << ") > Manage Logins > Delete '" << userToEdit << "'";
        headerRight();

        setColor(6);
        cout << "Warning! This action cannot be undone\n\n";
        setColor(7);

        do
        {
          cout << "Enter !DELETE to confirm user deletion\n";
          cout << "Enter !CANCEL to cancel the action\n\n";

          cout << "Input: ";
          cin >> confirmAction;

          if (confirmAction != "!DELETE" && confirmAction != "!CANCEL")
          {
            setColor(12);
            cout << "\nInvalid Input!\n\n";
            setColor(7);
          }
        } while (confirmAction != "!DELETE" && confirmAction != "!CANCEL");

        if (confirmAction == "!DELETE")
        {
          logins.erase(logins.begin() + index);

          // *** Update Student. Warning: Deleting a Student user will delete data from students vector *** //
          if (studentIndex != -1)
            students.erase(students.begin() + studentIndex);

          saveData();
          option = 0;

          setColor(10);
          cout << "\nUser deleted successfully!\n";
          setColor(7);

          cout << "\nPress any key to continue...";
          getch();
        }
        break;

      case 0:
        break;

      default:
        setColor(12);
        cout << "\nInvalid Input!";
        setColor(7);
        Sleep(1000);
        break;
      }

    } while (option != 0);
  }
}

void admin_ManageLogins()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Manage Logins";
    headerRight();

    cout << "1 - Create New Login\n";
    cout << "2 - Edit Existing Login\n";

    cout << "\n0 - Back\n";

    cout << "\nChoose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      admin_ManageLogins_Create();
      break;

    case 2:
      admin_ManageLogins_Edit();
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

// *** View Databases *** //

void admin_View_Logins()
{
  system("CLS");

  headerLeft();
  cout << "Admin Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > View Databases > Logins";
  headerRight();

  setColor(14);
  cout << left << setw(21) << "User Type";
  cout << left << setw(21) << "Username";
  cout << left << setw(21) << "Password";
  setColor(7);
  cout << "\n\n";

  for (int i = 0; i < logins.size(); i++)
  {
    cout << left << setw(21) << logins[i].type;
    cout << left << setw(21) << logins[i].username;

    if (mode != "#Admin" && (logins[i].type == "#Admin" || logins[i].type == "Admin"))
      cout << left << setw(21) << "**********";
    else
      cout << left << setw(21) << logins[i].password;

    cout << endl;
  }

  cout << "\nPress any key to continue...";
  getch();
}

void admin_View_Students()
{
  system("CLS");

  headerLeft();
  cout << "Admin Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > View Databases > Students";
  headerRight();

  if (students.empty())
  {
    setColor(14);
    cout << "Students database is empty!\n\n";
    setColor(7);

    cout << "Press any key to continue...";
    getch();
  }
  else
  {
    setColor(14);
    cout << left << setw(25) << "Full Name";
    cout << left << setw(21) << "Username";
    cout << left << setw(15) << "Semester";
    cout << left << setw(15) << "Degree";
    cout << left << setw(15) << "Roll No";
    cout << left << setw(15) << "Gender";
    setColor(7);
    cout << "\n\n";

    for (int i = 0; i < students.size(); i++)
    {

      cout << left << setw(25) << students[i].fullname;
      cout << left << setw(21) << students[i].username;
      cout << left << setw(15) << students[i].semester;
      cout << left << setw(15) << students[i].degree;
      cout << left << setw(15) << students[i].rollnumber;
      cout << left << setw(15) << students[i].gender;
      cout << endl;
    }

    cout << "\nPress any key to continue...";
    getch();
  }
}

void admin_View()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > View Databases";
    headerRight();

    cout << "1 - View All Logins\n";
    cout << "2 - View All Students\n\n";

    cout << "0 - Back\n\n";

    cout << "Choose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      admin_View_Logins();
      break;

    case 2:
      admin_View_Students();
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

// *** Main Admin Function *** //

void admin()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Admin Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ")";
    headerRight();

    cout << "1 - View Databases\n";
    cout << "2 - Manage Logins\n";
    cout << "3 - Manage Students\n\n";
    cout << "5 - Change Account Password\n";

    cout << "\n0 - Logout\n";

    cout << "\nChoose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      admin_View();
      break;

    case 2:
      admin_ManageLogins();
      break;

    case 3:
      admin_ManageStudents();
      break;

    case 5:
      system("CLS");

      headerLeft();
      cout << "Admin Panel (";
      setColor(14);
      cout << currentUser;
      setColor(7);
      cout << ") > Change Account Password";
      headerRight();

      change_Password(currentUser, false);
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

//-------------------- STUDENT FUNCTIONS --------------------//

void student_View_Details()
{
  system("CLS");

  headerLeft();
  cout << "Student Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > View Details";
  headerRight();

  int index = return_StudentIndex(currentUser);

  setColor(14);
  cout << left << setw(12) << "Username: ";
  setColor(7);
  cout << students[index].username;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Semester: ";
  setColor(7);
  cout << students[index].semester;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Degree: ";
  setColor(7);
  cout << students[index].degree;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Roll No: ";
  setColor(7);
  cout << students[index].rollnumber;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Full Name: ";
  setColor(7);
  cout << students[index].fullname;
  cout << "\n";

  setColor(14);
  cout << left << setw(12) << "Gender: ";
  setColor(7);
  cout << students[index].gender;
  cout << "\n";

  cout << "\nPress any key to continue...";
  getch();
}

void cout_NotMarked()
{
  setColor(3);
  cout << "Not Marked\n";
  setColor(7);
}

void renderAttendanceBar(int percentage)
{
  setColor(15);
  cout << "[";

  if (percentage >= 80)
    setColor(2);
  else if (percentage >= 75)
    setColor(6);
  else
    setColor(4);

  for (int i = 1; i <= percentage / 2; i++)
    cout << "#";

  setColor(15);
  cout << right << setw((50 - percentage / 2) + 1) << "]";
  cout << " - (";

  if (percentage >= 80)
    setColor(2);
  else if (percentage >= 75)
    setColor(6);
  else
    setColor(4);

  cout << percentage << "%";

  setColor(15);
  cout << ")\n";
  setColor(7);
}

void student_View_Attendance()
{
  system("CLS");

  headerLeft();
  cout << "Student Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > View Attendance";
  headerRight();

  string rollno = students[return_StudentIndex(currentUser)].rollnumber;
  int index = -1;

  for (int i = 0; i < attendances.size(); i++)
    if (attendances[i].rollnumber == rollno)
      index = i;

  cout << "Subject 1: ";
  if (index != -1)
    renderAttendanceBar(attendances[index].s1);
  else
    cout_NotMarked();

  cout << "Subject 2: ";
  if (index != -1)
    renderAttendanceBar(attendances[index].s2);
  else
    cout_NotMarked();

  cout << "Subject 3: ";
  if (index != -1)
    renderAttendanceBar(attendances[index].s3);
  else
    cout_NotMarked();

  cout << "Subject 4: ";
  if (index != -1)
    renderAttendanceBar(attendances[index].s4);
  else
    cout_NotMarked();

  cout << "Subject 5: ";
  if (index != -1)
    renderAttendanceBar(attendances[index].s5);
  else
    cout_NotMarked();

  cout << "\nPress any key to continue...";
  getch();
}

void renderGPA(float gpa)
{
  if (gpa <= 4.00 && gpa >= 3.00)
    setColor(2);
  else if (gpa >= 2.00)
    setColor(6);
  else
    setColor(4);

  cout << gpa << endl;

  setColor(7);
}

void student_View_Grades()
{
  system("CLS");

  headerLeft();
  cout << "Student Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > View Grades";
  headerRight();

  string rollno = students[return_StudentIndex(currentUser)].rollnumber;
  int index = -1;

  for (int i = 0; i < gpas.size(); i++)
    if (gpas[i].rollnumber == rollno)
      index = i;

  cout << "Subject 1: ";
  if (index != -1)
    renderGPA(gpas[index].s1);
  else
    cout_NotMarked();

  cout << "Subject 2: ";
  if (index != -1)
    renderGPA(gpas[index].s2);
  else
    cout_NotMarked();

  cout << "Subject 3: ";
  if (index != -1)
    renderGPA(gpas[index].s3);
  else
    cout_NotMarked();

  cout << "Subject 4: ";
  if (index != -1)
    renderGPA(gpas[index].s4);
  else
    cout_NotMarked();

  cout << "Subject 5: ";
  if (index != -1)
    renderGPA(gpas[index].s5);
  else
    cout_NotMarked();

  cout << "\nPress any key to continue...";
  getch();
}

void student()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Student Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ")";
    headerRight();

    cout << "1 - View Details\n";
    cout << "2 - View Attendance\n";
    cout << "3 - View Grades\n\n";
    cout << "4 - Change Account Password\n";

    cout << "\n0 - Logout\n";

    cout << "\nChoose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      student_View_Details();
      break;

    case 2:
      student_View_Attendance();
      break;

    case 3:
      student_View_Grades();
      break;

    case 4:
      system("CLS");

      headerLeft();
      cout << "Student Panel (";
      setColor(14);
      cout << currentUser;
      setColor(7);
      cout << ") > Change Account Password";
      headerRight();

      change_Password(currentUser, false);
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

//-------------------- TEACHER FUNCTIONS --------------------//

bool verifyAttendance(int percentage)
{
  if (percentage >= 0 && percentage <= 100)
    return true;
  else
  {
    setColor(12);
    cout << "\nPercentage must be in the range 1-100\n\n";
    setColor(7);
    return false;
  }
}

void teacher_MarkAttendance()
{
  string rollnumber;
  attendance temp;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Teacher Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Mark Attendance";
    headerRight();

    cout << "Enter student's roll number to start marking attendance: ";
    cin >> rollnumber;

    if (return_StudentIndex_RN(rollnumber) == -1)
    {
      setColor(12);
      cout << "\nStudent " << rollnumber << " does not exist!";
      setColor(7);
      Sleep(1000);
    }
  } while (return_StudentIndex_RN(rollnumber) == -1);

  char choice;

  for (int i = 0; i < attendances.size(); i++)
  {
    if (attendances[i].rollnumber == rollnumber)
    {
      setColor(9);
      cout << "\nThis student's attendance was marked already. Do you wish to overwrite? (Y/N): ";
      cin >> choice;
      setColor(7);
      choice = toupper(choice);

      if (choice == 'Y')
      {
        attendances.erase(attendances.begin() + i);
      }
      else
        return;
    }
  }

  system("CLS");

  headerLeft();
  cout << "Teacher Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > Marking ";
  setColor(14);
  cout << rollnumber;
  setColor(7);
  cout << "'s Attendance";
  headerRight();

  temp.rollnumber = rollnumber;

  do
  {
    cout << "Enter subject 1's attendance %: ";
    cin >> temp.s1;
  } while (!verifyAttendance(temp.s1));

  do
  {
    cout << "Enter subject 2's attendance %: ";
    cin >> temp.s2;
  } while (!verifyAttendance(temp.s2));

  do
  {
    cout << "Enter subject 3's attendance %: ";
    cin >> temp.s3;
  } while (!verifyAttendance(temp.s3));

  do
  {
    cout << "Enter subject 4's attendance %: ";
    cin >> temp.s4;
  } while (!verifyAttendance(temp.s4));

  do
  {
    cout << "Enter subject 5's attendance %: ";
    cin >> temp.s5;
  } while (!verifyAttendance(temp.s5));

  attendances.push_back(temp);
  saveData();

  setColor(10);
  cout << "\nAttendance marked successfully\n";
  setColor(7);

  cout << "\nPress any key to continue...";
  getch();
}

bool verifyGrade(float grade)
{
  if (grade >= 0 && grade <= 4.00)
    return true;
  else
  {
    setColor(12);
    cout << "\nGPA must be between 0 & 4.00\n\n";
    setColor(7);
    return false;
  }
}

void teacher_MarkGrades()
{
  string rollnumber;
  gpa temp;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Teacher Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ") > Mark Grades";
    headerRight();

    cout << "Enter student's roll number to start marking grades: ";
    cin >> rollnumber;

    if (return_StudentIndex_RN(rollnumber) == -1)
    {
      setColor(12);
      cout << "\nStudent " << rollnumber << " does not exist!";
      setColor(7);
      Sleep(1000);
    }
  } while (return_StudentIndex_RN(rollnumber) == -1);

  char choice;

  for (int i = 0; i < gpas.size(); i++)
  {
    if (gpas[i].rollnumber == rollnumber)
    {
      setColor(9);
      cout << "\nThis student's GPA was marked already. Do you wish to overwrite? (Y/N): ";
      cin >> choice;
      setColor(7);
      choice = toupper(choice);

      if (choice == 'Y')
      {
        gpas.erase(gpas.begin() + i);
      }
      else
        return;
    }
  }

  system("CLS");

  headerLeft();
  cout << "Teacher Panel (";
  setColor(14);
  cout << currentUser;
  setColor(7);
  cout << ") > Marking ";
  setColor(14);
  cout << rollnumber;
  setColor(7);
  cout << "'s Grades";
  headerRight();

  temp.rollnumber = rollnumber;

  do
  {
    cout << "Enter subject 1's GPA: ";
    cin >> temp.s1;
  } while (!verifyGrade(temp.s1));

  do
  {
    cout << "Enter subject 2's GPA: ";
    cin >> temp.s2;
  } while (!verifyGrade(temp.s2));

  do
  {
    cout << "Enter subject 3's GPA: ";
    cin >> temp.s3;
  } while (!verifyGrade(temp.s3));

  do
  {
    cout << "Enter subject 4's GPA: ";
    cin >> temp.s4;
  } while (!verifyGrade(temp.s4));

  do
  {
    cout << "Enter subject 5's GPA: ";
    cin >> temp.s5;
  } while (!verifyGrade(temp.s5));

  gpas.push_back(temp);
  saveData();

  setColor(10);
  cout << "\nGrades marked successfully\n";
  setColor(7);

  cout << "\nPress any key to continue...";
  getch();
}

void teacher()
{
  int option;

  do
  {
    system("CLS");

    headerLeft();
    cout << "Teacher Panel (";
    setColor(14);
    cout << currentUser;
    setColor(7);
    cout << ")";
    headerRight();

    cout << "1 - Mark Attendance\n";
    cout << "2 - Mark Grades\n\n";
    cout << "3 - Change Account Password\n";

    cout << "\n0 - Logout\n";

    cout << "\nChoose an option: ";
    cin >> option;

    switch (option)
    {
    case 1:
      teacher_MarkAttendance();
      break;

    case 2:
      teacher_MarkGrades();
      break;

    case 3:
      system("CLS");

      headerLeft();
      cout << "Teacher Panel (";
      setColor(14);
      cout << currentUser;
      setColor(7);
      cout << ") > Change Account Password";
      headerRight();

      change_Password(currentUser, false);
      break;

    case 0:
      break;

    default:
      setColor(12);
      cout << "\nInvalid Input!";
      setColor(7);
      Sleep(1000);
      break;
    }

  } while (option != 0);
}

//-------------------- MAIN FUNCTION --------------------//

int main()
{
  loadData();

  do
    login();
  while (!is_loggedIn);

  if (mode == "Admin" || mode == "#Admin")
    admin();
  if (mode == "Teacher")
    teacher();
  if (mode == "Student")
    student();
}