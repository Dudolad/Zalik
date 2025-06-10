#include <iostream>
#include <cstring>
#include "Hospital.h"

using namespace std;


void savePatients(const Patient* patients, int count, const char* filename);
int loadPatients(Patient*& patients, const char* filename);
void printPatient(const Patient& p);
void addPatient(Patient*& patients, int& count, const Patient& newPatient);
void deletePatient(Patient*& patients, int& count, int index);
int findPatientByLastName(Patient* patients, int count, const char* lastName);
void editPatient(Patient& patient, const Patient& updated);
void sortPatientsByBirthYear(Patient* patients, int count);


Patient inputPatient() {
    Patient p;
    cout << "Input patient last name: ";
    cin.getline(p.lastName, 50);

    cout << "Input patient first name: ";
    cin.getline(p.firstName, 50);

    cout << "Input patient middle name: ";
    cin.getline(p.middleName, 50);

    cout << "Input birth year: ";
    cin >> p.birthYear;
    cin.ignore();

    cout << "Input diagnosis: ";
    cin.getline(p.diagnosis, 100);

    cout << "Input admission date (dd.mm.yyyy): ";
    cin.getline(p.admissionDate, 20);

    cout << "Input discharge date (dd.mm.yyyy): ";
    cin.getline(p.dischargeDate, 20);

    cout << "Enter ward number: ";
    cin >> p.wardNumber;

    cout << "Enter room number: ";
    cin >> p.roomNumber;

    cout << "--- Doctor's info ---\n";
    cout << "Doctor last name: ";
    cin >> p.doctor.lastName;
    cin.ignore();

    cout << "Doctor first name: ";
    cin.getline(p.doctor.firstName, 50);

    cout << "Doctor middle name: ";
    cin.getline(p.doctor.middleName, 50);

    cout << "Doctor birth year: ";
    cin >> p.doctor.birthYear;
    cin.ignore();

    cout << "Doctor position: "; 
    cin.getline(p.doctor.position, 50);

    cout << "Doctor phone: ";
    cin.getline(p.doctor.phone, 20);

    return p;
}

int main() {
    Patient* patients = nullptr;
    int patientCount = 0;

    const char* filename = "patients.dat";

    patientCount = loadPatients(patients, filename);

    int choice = -1;
    while (choice != 0) {
        cout << "\n===== Hospital Management Menu =====\n";
        cout << "0 - Exit and save\n";
        cout << "1 - Show all patients\n";
        cout << "2 - Add new patient\n";
        cout << "3 - Delete patient by last name\n";
        cout << "4 - Edit patient by last name\n";
        cout << "5 - Find patient by last name\n";
        cout << "6 - Sort patients by birth year\n";
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            savePatients(patients, patientCount, filename);
            cout << "Data saved. Exiting...\n";
            break;
        }
        else if (choice == 1) {
            if (patientCount == 0) {
                cout << "No patients available.\n";
            }
            else {
                for (int i = 0; i < patientCount; i++) {
                    printPatient(patients[i]);
                }
            }
        }
        else if (choice == 2) {
            Patient newP = inputPatient();
            addPatient(patients, patientCount, newP);
            cout << "Patient added.\n";
        }
        else if (choice == 3) {
            char lname[50];
            cout << "Enter last name to delete: ";
            cin.getline(lname, 50);
            int idx = findPatientByLastName(patients, patientCount, lname);
            if (idx == -1) cout << "Patient not found.\n";
            else {
                deletePatient(patients, patientCount, idx);
                cout << "Patient deleted.\n";
            }
        }
        else if (choice == 4) {
            char lname[50];
            cout << "Enter last name to edit: ";
            cin.getline(lname, 50);
            int idx = findPatientByLastName(patients, patientCount, lname);
            if (idx == -1) {
                cout << "Patient not found.\n";
            }
            else {
                cout << "Enter new data:\n";
                Patient updated = inputPatient();
                editPatient(patients[idx], updated);
                cout << "Patient updated.\n";
            }
        }
        else if (choice == 5) {
            char lname[50];
            cout << "Enter last name to find: ";
            cin.getline(lname, 50);
            int idx = findPatientByLastName(patients, patientCount, lname);
            if (idx == -1) {
                cout << "Patient not found.\n";
            }
            else {
                printPatient(patients[idx]);
            }
        }
        else if (choice == 6) {
            sortPatientsByBirthYear(patients, patientCount);
            cout << "Patients sorted by birth year.\n";
        }
        else {
            cout << "Invalid option. Try again.\n";
        }
    }

    delete[] patients;
    return 0;
}