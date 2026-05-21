#pragma once
#include "struct.h"

#pragma region templatesFunc
template <typename T>
int findPerById(const T* const array, int count, int targetId) {
    for (int i = 0; i < count; i++) {
        if (array[i].id == targetId) {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool growArray(T*& arr, int* const capacity) {
    int newCap = (*capacity) * 2;
    T* newArr = new (std::nothrow) T[newCap];
    if (newArr == nullptr) {
        printf("Ошибка: Не удалось выделить память!\n");
        return false;
    }
    for (int i = 0; i < *capacity; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    *capacity = newCap;
    return true;
}
#pragma endregion templatesFunc

#pragma region stringFunct
int strCmp(const char* s1, const char* s2);
void copyString(char* const dest, const char* src, int bufferSize);
void clearString(char* const str, int size);
int stringLength(const char* str);
#pragma endregion stringFunct

#pragma region resManagement
void addResident(ResidentList& resList);
void deleteResident(ResidentList& resList, int rId);
void printAllResidents(const ResidentList& resList);
#pragma endregion resManagement

#pragma region aparManagement
void addApartment(ApartmentList& aptList);
void deleteApartment(ApartmentList& aptList, int aptNumber);
void linkResidentToApartment(ApartmentList& aptList, int aptNumber, int resId);
void unlinkResidentFromApartment(ApartmentList& aptList, int aptNumber, int resId);
void printAllApartments(const ApartmentList& aptList);
void printResidentsInApartment(int aptNumber, const ApartmentList& aptList, const ResidentList& resList);
void printApartmentsByFloor(const ApartmentList& aptList, int floor);
void printApartmentsByType(const ApartmentList& aptList, int rooms);
#pragma endregion aparManagement

#pragma region SystemFunctions
void cleanMemory(ResidentList& resList, ApartmentList& aptList);
#pragma endregion SystemFunctions