#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>

using namespace std;

// User Class for Authentication
class User {
public:
    string username;
    string password;
    string role; // Roles: admin, doctor, nurse, receptionist

    User(string username, string password, string role) {
        this->username = username;
        this->password = password;
        this->role = role;
    }
};

// Authentication Class
class Authentication {
private:
    vector<User> users;

public:
    Authentication() {
        // Predefined users
        users.emplace_back("admin", "admin123", "admin");
        users.emplace_back("doctor", "doc123", "doctor");
        users.emplace_back("nurse", "nurse123", "nurse");
        users.emplace_back("receptionist", "rec123", "receptionist");
    }

    bool login(string username, string password, string &role) {
        for (auto &user : users) {
            if (user.username == username && user.password == password) {
                role = user.role;
                return true;
            }
        }
        return false;
    }
};

// Patient Class
class Patient {
public:
    int id;
    string name;
    int age;
    string disease;
    int priorityLevel; // 1 for High Priority, 2 for General
    string department;
    Patient *next;

    Patient(int id, string name, int age, string disease, int priorityLevel, string department) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->disease = disease;
        this->priorityLevel = priorityLevel;
        this->department = department;
        next = nullptr;
    }
};

// Linked List for Managing Patients
class PatientList {
private:
    Patient *head;

public:
    PatientList() {
        head = nullptr;
    }

    void addPatient(int id, string name, int age, string disease, int priorityLevel, string department) {
        Patient *newPatient = new Patient(id, name, age, disease, priorityLevel, department);
        if (!head) {
            head = newPatient;
        } else {
            Patient *temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "Patient added successfully!\n";
    }

    void editPatient(int id) {
        Patient *temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Editing details for Patient ID: " << id << endl;
                cout << "Enter new Name (current: " << temp->name << "): ";
                cin.ignore();
                getline(cin, temp->name);
                cout << "Enter new Age (current: " << temp->age << "): ";
                cin >> temp->age;
                cout << "Enter new Disease (current: " << temp->disease << "): ";
                cin.ignore();
                getline(cin, temp->disease);
                cout << "Enter new Priority Level (1 for High, 2 for General, current: " << temp->priorityLevel << "): ";
                cin >> temp->priorityLevel;
                cout << "Patient details updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    void deletePatient(int id) {
        if (!head) {
            cout << "No patients to delete.\n";
            return;
        }

        if (head->id == id) {
            Patient *temp = head;
            head = head->next;
            delete temp;
            cout << "Patient with ID " << id << " deleted successfully.\n";
            return;
        }

        Patient *temp = head;
        while (temp->next) {
            if (temp->next->id == id) {
                Patient *toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                cout << "Patient with ID " << id << " deleted successfully.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    void showPatient(int id) {
        Patient *temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Patient Found: ID: " << temp->id << ", Name: " << temp->name << ", Age: " << temp->age
                     << ", Disease: " << temp->disease << ", Priority: " << (temp->priorityLevel == 1 ? "High" : "General") << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Patient with ID " << id << " not found.\n";
    }

    void searchPatient(string keyword) {
        if (!head) {
            cout << "No patients found.\n";
            return;
        }

        Patient *temp = head;
        bool found = false;
        while (temp) {
            if (to_string(temp->id) == keyword || temp->name.find(keyword) != string::npos) {
                cout << "Patient Found: " << temp->id << ", " << temp->name << ", " << temp->age << " years, Disease: " << temp->disease << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No matching patient found.\n";
        }
    }

    void generateReport() {
        if (!head) {
            cout << "No patients to generate report.\n";
            return;
        }

        int totalPatients = 0;
        map<string, int> departmentCount;
        Patient *temp = head;

        while (temp) {
            totalPatients++;
            departmentCount[temp->department]++;
            temp = temp->next;
        }

        cout << "\nHospital Report:\n";
        cout << "Total Patients: " << totalPatients << endl;
        cout << "Patients by Department:\n";
        for (auto &entry : departmentCount) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    void saveBackup(const string &filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to create backup file.\n";
            return;
        }

        Patient *temp = head;
        while (temp) {
            file << temp->id << "," << temp->name << "," << temp->age << "," << temp->disease << "," << temp->priorityLevel << "," << temp->department << endl;
            temp = temp->next;
        }
        file.close();
        cout << "Backup saved successfully to " << filename << "\n";
    }

};
 // Function definitions for hospital management system menu
void displayDepartments() {
    cout << "\n========== Departments ==========" << endl;
    cout << "1. Medicine: General internal medicine cases." << endl;
    cout << "2. Surgery: Surgical procedures like operations, minor surgeries." << endl;
    cout << "3. Pediatrics: Health issues and treatments for children." << endl;
    cout << "4. Gynecology: Women's health issues, pregnancy, and related treatments." << endl;
    cout << "5. Orthopedics: Bone, joint, and musculoskeletal issues." << endl;
    cout << "6. Cardiology: Heart problems and their treatment." << endl;
    cout << "7. Dermatology: Skin diseases and treatments." << endl;
    cout << "8. Radiology: X-rays, CT scans, MRI, and other diagnostic imaging services." << endl;
    cout << "9. Anesthesiology: Anesthesia for surgeries and procedures." << endl;
    cout << "10. Emergency Medicine: Medical assistance for emergencies." << endl;
}

void displayFacilities() {
    cout << "\n========== Facilities ==========" << endl;
    cout << "1. OPD: Outpatient check-ups without admission." << endl;
    cout << "2. IPD: Rooms and services for admitted patients." << endl;
    cout << "3. Emergency Department: 24/7 critical care services." << endl;
    cout << "4. Diagnostic Center: Blood tests, imaging tests, etc." << endl;
    cout << "5. Pharmacy: Medicine supply for hospital patients." << endl;
    cout << "6. Laboratory: Various diagnostic tests." << endl;
    cout << "7. ICU: Specialized unit for critical care." << endl;
    cout << "8. Operating Theatres: Well-equipped theatres for surgeries." << endl;
    cout << "9. Rehabilitation Services: Physiotherapy and rehabilitation treatments." << endl;
}

void displaySpecializedServices() {
    cout << "\n========== Specialized Services ==========" << endl;
    cout << "1. Cancer Care: Oncology services and treatment options." << endl;
    cout << "2. Neurology: Brain and nervous system-related problems." << endl;
    cout << "3. Gastroenterology: Digestive system issues." << endl;
    cout << "4. Endocrinology: Hormonal and metabolic disorders." << endl;
}

void displaySupportServices() {
    cout << "\n========== Support Services ==========" << endl;
    cout << "1. Nursing Services: Skilled nursing care." << endl;
    cout << "2. Social Work Services: Addressing social needs of patients and families." << endl;
    cout << "3. Dietary Services: Specialized diets and nutrition support." << endl;
    cout << "4. Counseling Services: Mental health and emotional support." << endl;
}

void displayBillingAndInsurance() {
    cout << "\n========== Billing and Insurance ==========" << endl;
    cout << "1. Insurance Coordination: Assistance with claims and billing." << endl;
    cout << "2. Payment Options: Self-payment, insurance, and installment plans." << endl;
}

void displayPatientCareServices() {
    cout << "\n========== Patient Care Services ==========" << endl;
    cout << "1. Patient Education: Health-related information and awareness programs." << endl;
    cout << "2. Follow-up Services: Post-treatment follow-up appointments." << endl;
}

void displayVisitingHours() {
    cout << "\n========== Visiting Hours ==========" << endl;
    cout << "1. Visiting Policies: Timings and rules as per hospital policies." << endl;
}

void displayEmergencyContact() {
    cout << "\n========== Emergency Contact Information ==========" << endl;
    cout << "1. Helpline Numbers: Contact numbers for emergency services." << endl;
}

void displayOnlineServices() {
    cout << "\n========== Online Services ==========" << endl;
    cout << "1. Appointment Booking: Online booking for consultations." << endl;
    cout << "2. Telemedicine: Virtual consultations with doctors." << endl;
}

int main() {
    Authentication auth;
    string role;
    string username, password;

    cout << "Welcome to Hospital Management System\n";
    cout << "Select Role to Login:\n";
    cout << "1. Admin\n2. Doctor\n3. Receptionist\n";
    int roleChoice;
    cout << "Enter your choice: ";
    cin >> roleChoice;

    switch (roleChoice) {
        case 1:
            role = "admin";
            break;
        case 2:
            role = "doctor";
            break;
        case 3:
            role = "receptionist";
            break;
        default:
            cout << "Invalid role selected. Exiting...\n";
            return 1;
    }

    cout << "Login:\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!auth.login(username, password, role)) {
        cout << "Invalid credentials. Exiting...\n";
        return 1;
    }

    cout << "Login successful! Role: " << role << endl;

    PatientList patientList;
    int choice;
     do {
        cout << "\n========== Hospital Management System ==========" << endl;
        cout << "1. Departments" << endl;
        cout << "2. Facilities" << endl;
        cout << "3. Specialized Services" << endl;
        cout << "4. Support Services" << endl;
        cout << "5. Billing and Insurance" << endl;
        cout << "6. Patient Care Services" << endl;
        cout << "7. Visiting Hours" << endl;
        cout << "8. Emergency Contact Information" << endl;
        cout << "9. Online Services" << endl;
        cout << "10. Add Patient" << endl;
        cout << "11. Edit Patient" << endl;
        cout << "12. Delete Patient" << endl;
        cout << "13. Show Patient" << endl;
        cout << "14. Search Patient" << endl;
        cout << "15. Generate Report" << endl;
        cout << "16. Save Backup" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayDepartments();
                break;
            case 2:
                displayFacilities();
                break;
            case 3:
                displaySpecializedServices();
                break;
            case 4:
                displaySupportServices();
                break;
            case 5:
                displayBillingAndInsurance();
                break;
            case 6:
                displayPatientCareServices();
                break;
            case 7:
                displayVisitingHours();
                break;
            case 8:
                displayEmergencyContact();
                break;
            case 9:
                displayOnlineServices();
                break;
            case 10: {
                int id, age, priorityLevel;
                string name, disease, department;
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Disease: ";
                cin.ignore();
                getline(cin, disease);
                cout << "Enter Department: ";
                getline(cin, department);
                cout << "Enter Priority Level (1 for High, 2 for General): ";
                cin >> priorityLevel;
                patientList.addPatient(id, name, age, disease, priorityLevel, department);
                break;
            }
            case 11: {
                int id;
                cout << "Enter Patient ID to Edit: ";
                cin >> id;
                patientList.editPatient(id);
                break;
            }
            case 12: {
                int id;
                cout << "Enter Patient ID to Delete: ";
                cin >> id;
                patientList.deletePatient(id);
                break;
            }
            case 13: {
                int id;
                cout << "Enter Patient ID to Show: ";
                cin >> id;
                patientList.showPatient(id);
                break;
            }
            case 14: {
                string keyword;
                cout << "Enter Patient ID or Name to Search: ";
                cin.ignore();
                getline(cin, keyword);
                patientList.searchPatient(keyword);
                break;
            }
            case 15:
                patientList.generateReport();
                break;
            case 16:
                patientList.saveBackup("backup.txt");
                break;
            case 0:
                cout << "Exiting the system. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}