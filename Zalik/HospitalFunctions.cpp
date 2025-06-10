#include "Hospital.h"
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

void savePatients(const Patient* patients, int count, const char* filename) {
    FILE* file = nullptr;
    if (fopen_s(&file, filename, "wb") != 0 || !file) {
        cout << "Cannot open file for writing.\n";
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(patients, sizeof(Patient), count, file);
    fclose(file);
}

int loadPatients(Patient*& patients, const char* filename) {
    FILE* file = nullptr;
    if (fopen_s(&file, filename, "rb") != 0 || !file) {
        cout << "Cannot open file for reading.\n";
        patients = nullptr;
        return 0;
    }
    int count = 0;
    fread(&count, sizeof(int), 1, file);
    patients = new Patient[count];
    fread(patients, sizeof(Patient), count, file);
    fclose(file);
    return count;
}

void printPatient(const Patient& p) {
    cout << "----------------------------------------\n";
    cout << "Patient: " << p.lastName << " " << p.firstName << " " << p.middleName << "\n";
    cout << "Birth Year: " << p.birthYear << "\n";
    cout << "Diagnosis: " << p.diagnosis << "\n";
    cout << "Admission Date: " << p.admissionDate << "\n";
    cout << "Discharge Date: " << p.dischargeDate << "\n";
    cout << "Doctor: " << p.doctor.lastName << " " << p.doctor.firstName << p.doctor.middleName << "\n";
    cout << "Ward: " << p.wardNumber << ", Room: " << p.roomNumber << "\n";
    cout << "----------------------------------------\n";
}

void addPatient(Patient*& patients, int& count, const Patient& newPatient) {
    Patient* temp = new Patient[count + 1];
    for (int i = 0; i < count; i++)
        temp[i] = patients[i];
    temp[count] = newPatient;
    delete[] patients;
    patients = temp;
    count++;
}

void deletePatient(Patient*& patients, int& count, int index) {
    if (index < 0 || index >= count) return;
    Patient* temp = new Patient[count - 1];
    for (int i = 0, j = 0; i < count; i++) {
        if (i != index) temp[j++] = patients[i];
    }
    delete[] patients;
    patients = temp;
    count--;
}

int findPatientByLastName(Patient* patients, int count, const char* lastName) {
    for (int i = 0; i < count; i++) {
        if (strcmp(patients[i].lastName, lastName) == 0)
            return i;
    }
    return -1;
}

void editPatient(Patient& patient, const Patient& updated) {
    patient = updated;
}

void sortPatientsByBirthYear(Patient* patients, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (patients[j].birthYear > patients[j + 1].birthYear) {
                Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
}