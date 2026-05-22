#pragma once
#include "struct.h"

#pragma region utilityFunctions
size_t findResidentIndexById(const Resident* const array, size_t count, size_t targetId);
void growResidents(Resident*& arr, size_t* const capacity);
void growApartments(Apartment*& arr, size_t* const capacity);
#pragma endregion utilityFunctions

#pragma region stringFunct
int strCmp(const char* s1, const char* s2);
void copyString(char* const dest, const char* src, size_t bufferSize);
void clearString(char* const str, size_t size);
size_t stringLength(const char* str);
#pragma endregion stringFunct

#pragma region resManagement
void addResident(ResidentList& resList);
void deleteResident(ResidentList& resList, size_t rId);
void printAllResidents(const ResidentList& resList);
#pragma endregion resManagement

#pragma region aparManagement
void addApartment(ApartmentList& aptList);
void deleteApartment(ApartmentList& aptList, size_t aptNumber);
void linkResidentToApartment(ApartmentList& aptList, size_t aptNumber, size_t resId);
void unlinkResidentFromApartment(ApartmentList& aptList, size_t aptNumber, size_t resId);
void printAllApartments(const ApartmentList& aptList);
void printResidentsInApartment(size_t aptNumber, const ApartmentList& aptList, const ResidentList& resList);
void printApartmentsByFloor(const ApartmentList& aptList, size_t floor);
void printApartmentsByType(const ApartmentList& aptList, size_t rooms);
#pragma endregion aparManagement

#pragma region SystemFunctions
void cleanMemory(ResidentList& resList, ApartmentList& aptList);
#pragma endregion SystemFunctions