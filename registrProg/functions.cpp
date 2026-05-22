#pragma region files
#include "includes.h"
#include "struct.h"
#include "prototypes.h"
#pragma endregion files

#pragma region HelperFunctions
size_t findResidentIndexById(const Resident* const array, size_t count, size_t targetId) {
    for (size_t i = 0; i < count; i++) {
        if (array[i].id == targetId) {
            return i;
        }
    }
    return size_t(-1);
}

static size_t findApartmentIndex(const ApartmentList& aptList, size_t targetNumber) {
    for (size_t i = 0; i < aptList.count; i++) {
        if (aptList.data[i].number == targetNumber) {
            return i;
        }
    }
    return size_t(-1);
}

void growResidents(Resident*& arr, size_t* const capacity) {
    size_t newCap = (*capacity) * 2;
    Resident* newArr = new Resident[newCap];
    for (size_t i = 0; i < *capacity; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    *capacity = newCap;
}

void growApartments(Apartment*& arr, size_t* const capacity) {
    size_t newCap = (*capacity) * 2;
    Apartment* newArr = new Apartment[newCap];
    for (size_t i = 0; i < *capacity; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    *capacity = newCap;
}
#pragma endregion HelperFunctions

#pragma region stringFunct
int strCmp(const char* str1, const char* str2) {
    size_t i = 0;
    while (str1[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }
    if (str1[i] == str2[i]) {
        return 0;
    }
    return (str1[i] > str2[i]) ? 1 : -1;
}

void copyString(char* const dest, const char* src, size_t bufferSize) {
    size_t i = 0;
    while (src[i] != '\0' && i < bufferSize - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void clearString(char* const str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        str[i] = '\0';
    }
}

size_t stringLength(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
#pragma endregion stringFunct

#pragma region resManagement
void addResident(ResidentList& resList) {
    if (resList.count >= resList.capacity) {
        growResidents(resList.data, &resList.capacity);
        printf("Массив жильцов расширен до %llu.\n", resList.capacity);
    }
    Resident newRes;
    printf("Введите ID нового жильца: ");
    if (scanf_s("%llu", &newRes.id) != 1) {
        printf("Ошибка ввода ID!\n");
        return;
    }
    printf("Введите ФИО жильца: ");
    if (scanf_s(" %[^\n]", newRes.fullName, (unsigned int)sizeof(newRes.fullName)) != 1) {
        printf("Ошибка ввода ФИО!\n");
        return;
    }
    if (findResidentIndexById(resList.data, resList.count, newRes.id) != size_t(-1)) {
        printf("Ошибка: Жилец с ID %llu уже существует.\n", newRes.id);
        return;
    }
    resList.data[resList.count] = newRes;
    resList.count++;
    printf("Успех: Жилец добавлен!\n");
}

void deleteResident(ResidentList& resList, size_t rId) {
    size_t indexToDelete = findResidentIndexById(resList.data, resList.count, rId);
    if (indexToDelete == size_t(-1)) {
        printf("Ошибка: Жилец с ID %llu не найден.\n", rId);
        return;
    }
    for (size_t i = indexToDelete; i < resList.count - 1; i++) {
        resList.data[i] = resList.data[i + 1];
    }
    resList.count--;
    printf("Жилец с ID %llu успешно удален.\n", rId);
}

void printAllResidents(const ResidentList& resList) {
    if (resList.count == 0) {
        printf("База жильцов пуста.\n");
        return;
    }
    printf("\n--- СПИСОК ВСЕХ ЖИЛЬЦОВ ---\n");
    for (size_t i = 0; i < resList.count; i++) {
        printf("ID: %-5llu | ФИО: %s\n", resList.data[i].id, resList.data[i].fullName);
    }
}
#pragma endregion resManagement

#pragma region aparManagement
void addApartment(ApartmentList& aptList) {
    if (aptList.count >= aptList.capacity) {
        growApartments(aptList.data, &aptList.capacity);
        printf("[i] Массив квартир расширен до %llu.\n", aptList.capacity);
    }
    Apartment newApt;
    printf("Введите номер квартиры: ");
    if (scanf_s("%llu", &newApt.number) != 1) {
        printf("Ошибка ввода номера!\n");
        return;
    }
    if (findApartmentIndex(aptList, newApt.number) != size_t(-1)) {
        printf("Ошибка: Квартира №%llu уже существует.\n", newApt.number);
        return;
    }
    printf("Введите этаж: ");
    if (scanf_s("%llu", &newApt.floor) != 1) {
        printf("Ошибка ввода этажа!\n");
        return;
    }
    printf("Введите количество комнат: ");
    if (scanf_s("%llu", &newApt.roomsCount) != 1) {
        printf("Ошибка ввода комнат!\n");
        return;
    }
    newApt.residentCount = 0;
    aptList.data[aptList.count] = newApt;
    aptList.count++;
    printf("Успех: Квартира №%llu добавлена.\n", newApt.number);
}

void deleteApartment(ApartmentList& aptList, size_t aptNumber) {
    size_t indexToDelete = findApartmentIndex(aptList, aptNumber);
    if (indexToDelete == size_t(-1)) {
        printf("Ошибка: Квартира №%llu не найдена.\n", aptNumber);
        return;
    }
    for (size_t i = indexToDelete; i < aptList.count - 1; i++) {
        aptList.data[i] = aptList.data[i + 1];
    }
    aptList.count--;
    printf("Квартира №%llu успешно удалена.\n", aptNumber);
}

void linkResidentToApartment(ApartmentList& aptList, size_t aptNumber, size_t resId) {
    int idx = findApartmentIndex(aptList, aptNumber);
    if (idx == -1) {
        printf("Ошибка: Квартира №%llu не найдена.\n", aptNumber);
        return;
    }
    for (int j = 0; j < aptList.data[idx].residentCount; j++) {
        if (aptList.data[idx].residentIds[j] == resId) {
            printf("Ошибка: Жилец с ID %llu уже заселен в квартиру №%llu.\n", resId, aptNumber);
            return;
        }
    }
    if (aptList.data[idx].residentCount < maxPerApt) {
        aptList.data[idx].residentIds[aptList.data[idx].residentCount] = resId;
        aptList.data[idx].residentCount++;
        printf("Успех: Жилец с ID %llu заселен в квартиру №%llu.\n", resId, aptNumber);
    }
    else {
        printf("Ошибка: В квартире №%llu нет мест! Максимум: %llu.\n", aptNumber, maxPerApt);
    }
}

void unlinkResidentFromApartment(ApartmentList& aptList, size_t aptNumber, size_t resId) {
    size_t aptIdx = findApartmentIndex(aptList, aptNumber);
    if (aptIdx == size_t(-1)) {
        printf("Ошибка: Квартира №%llu не найдена.\n", aptNumber);
        return;
    }
    size_t indexToDelete = size_t(-1);
    for (size_t j = 0; j < aptList.data[aptIdx].residentCount; j++) {
        if (aptList.data[aptIdx].residentIds[j] == resId) {
            indexToDelete = j;
            break;
        }
    }
    if (indexToDelete == size_t(-1)) {
        printf("Ошибка: Жилец с ID %llu не найден в квартире №%llu.\n", resId, aptNumber);
        return;
    }
    for (size_t j = indexToDelete; j < aptList.data[aptIdx].residentCount - 1; j++) {
        aptList.data[aptIdx].residentIds[j] = aptList.data[aptIdx].residentIds[j + 1];
    }
    aptList.data[aptIdx].residentCount--;
    printf("Успех: Жилец с ID %llu откреплен от квартиры №%llu.\n", resId, aptNumber);
}

void printAllApartments(const ApartmentList& aptList) {
    if (aptList.count == 0) {
        printf("База квартир пуста.\n");
        return;
    }
    printf("\n--- СПИСОК ВСЕХ КВАРТИР ---\n");
    for (size_t i = 0; i < aptList.count; i++) {
        printf("Квартира №%-4llu | Этаж: %-2llu | Комнат: %-2llu | Жильцов: %llu/%d\n",
            aptList.data[i].number, aptList.data[i].floor, aptList.data[i].roomsCount,
            aptList.data[i].residentCount, maxPerApt);
    }
}

void printResidentsInApartment(size_t aptNumber, const ApartmentList& aptList, const ResidentList& resList) {
    size_t idx = findApartmentIndex(aptList, aptNumber);
    if (idx == size_t(-1)) {
        printf("Ошибка: Квартира №%llu не найдена.\n", aptNumber);
        return;
    }
    printf("\nЖильцы квартиры №%llu (Этаж %llu, Комнат: %llu):\n",
        aptList.data[idx].number, aptList.data[idx].floor, aptList.data[idx].roomsCount);
    if (aptList.data[idx].residentCount == 0) {
        printf("  -- В этой квартире никто не зарегистрирован --\n");
    }
    else {
        for (size_t j = 0; j < aptList.data[idx].residentCount; j++) {
            size_t currentId = aptList.data[idx].residentIds[j];
            size_t resIdx = findResidentIndexById(resList.data, resList.count, currentId);
            if (resIdx != size_t(-1)) {
                printf("  -> ID: %llu | %s\n", resList.data[resIdx].id, resList.data[resIdx].fullName);
            }
            else {
                printf("  -> ID: %llu | <Данные жильца удалены>\n", currentId);
            }
        }
    }
}

void printApartmentsByFloor(const ApartmentList& aptList, size_t floor) {
    printf("\n--- Квартиры на %llu этаже ---\n", floor);
    size_t foundCount = 0;
    for (size_t i = 0; i < aptList.count; i++) {
        if (aptList.data[i].floor == floor) {
            printf("Квартира №%llu (%llu-комнатная, Жильцов: %llu/%d)\n",
                aptList.data[i].number, aptList.data[i].roomsCount,
                aptList.data[i].residentCount, maxPerApt);
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("На %llu этаже квартир нет.\n", floor);
    }
}

void printApartmentsByType(const ApartmentList& aptList, size_t rooms) {
    printf("\n--- Список квартир: %llu-комнатные ---\n", rooms);
    size_t foundCount = 0;
    for (size_t i = 0; i < aptList.count; i++) {
        if (aptList.data[i].roomsCount == rooms) {
            printf("Квартира №%llu | Этаж: %llu | Жильцов: %llu/%d\n",
                aptList.data[i].number, aptList.data[i].floor,
                aptList.data[i].residentCount, maxPerApt);
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("Квартир с таким количеством комнат (%llu) не найдено.\n", rooms);
    }
}
#pragma endregion aparManagement

#pragma region SystemFunctions
void cleanMemory(ResidentList& resList, ApartmentList& aptList) {
    if (resList.data != nullptr) {
        delete[] resList.data;
        resList.data = nullptr;
    }
    if (aptList.data != nullptr) {
        delete[] aptList.data;
        aptList.data = nullptr;
    }
    resList.count = 0;
    resList.capacity = 0;
    aptList.count = 0;
    aptList.capacity = 0;
}
#pragma endregion SystemFunctions