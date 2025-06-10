#pragma once
#include <cstdio>

struct Doctor {
    char lastName[50];
    char firstName[50];
    char middleName[50];
    int birthYear;
    char phone[20];
    char position[50];
};

struct Patient {
    char lastName[50];
    char firstName[50];
    char middleName[50];
    int birthYear;
    char diagnosis[100];
    char admissionDate[20];
    char dischargeDate[20];
    int roomNumber;
    int wardNumber;
    Doctor doctor;               
};
