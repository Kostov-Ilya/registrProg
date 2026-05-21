#pragma region files
#include "includes.h"
#include "struct.h"
#include "prototypes.h"
#pragma endregion files

typedef unsigned int unInt;

#pragma region HelperFunctions
static const Resident* findResidentById(const ResidentList& resList, int id) {
    for (int i = 0; i < resList.count; i++) {
        if (resList.data[i].id == id) {
            return &resList.data[i];
        }
    }
    return nullptr;
}

static int findApartmentIndex(const ApartmentList& aptList, int targetNumber) {
    for (int i = 0; i < aptList.count; i++) {
        if (aptList.data[i].number == targetNumber) {
            return i;
        }
    }
    return -1;
}
#pragma endregion HelperFunctions

#pragma region stringFunct
int strCmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }
    if (str1[i] == str2[i]) return 0;
    return (str1[i] > str2[i]) ? 1 : -1;
}

void copyString(char* const dest, const char* src, int bufferSize) {
    int i = 0;
    while (src[i] != '\0' && i < bufferSize - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void clearString(char* const str, int size) {
    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
}

int stringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
#pragma endregion stringFunct

#pragma region resManagement
void addResident(ResidentList& resList) {
    if (resList.count >= resList.capacity) {
        if (!growArray(resList.data, &resList.capacity)) {
            return;
        }
        printf("Массив жильцов расширен до %d.\n", resList.capacity);
    }
    Resident newRes;
    printf("Введите ID нового жильца: ");
    if (scanf_s("%d", &newRes.id) != 1) {
        printf("Ошибка ввода ID!\n");
        return;
    }
    printf("Введите ФИО жильца: ");
    if (scanf_s(" %[^\n]", newRes.fullName, (unInt)sizeof(newRes.fullName)) != 1) {
        printf("Ошибка ввода ФИО!\n");
        return;
    }
    if (findPerById(resList.data, resList.count, newRes.id) != -1) {
        printf("Ошибка: Жилец с ID %d уже существует.\n", newRes.id);
        return;
    }
    resList.data[resList.count] = newRes;
    resList.count++;
    printf("Успех: Жилец добавлен!\n");
}

void deleteResident(ResidentList& resList, int rId) {
    int indexToDelete = findPerById(resList.data, resList.count, rId);
    if (indexToDelete == -1) {
        printf("Ошибка: Жилец с ID %d не найден.\n", rId);
        return;
    }
    for (int i = indexToDelete; i < resList.count - 1; i++) {
        resList.data[i] = resList.data[i + 1];
    }
    resList.count--;
    printf("Жилец с ID %d успешно удален.\n", rId);
}

void printAllResidents(const ResidentList& resList) {
    if (resList.count == 0) {
        printf("База жильцов пуста.\n");
        return;
    }
    printf("\n--- СПИСОК ВСЕХ ЖИЛЬЦОВ ---\n");
    for (int i = 0; i < resList.count; i++) {
        printf("ID: %-5d | ФИО: %s\n", resList.data[i].id, resList.data[i].fullName);
    }
}
#pragma endregion resManagement

#pragma region aparManagement
void addApartment(ApartmentList& aptList) {
    if (aptList.count >= aptList.capacity) {
        if (!growArray(aptList.data, &aptList.capacity)) {
            return;
        }
        printf("[i] Массив квартир расширен до %d.\n", aptList.capacity);
    }
    Apartment newApt;
    printf("Введите номер квартиры: ");
    if (scanf_s("%d", &newApt.number) != 1) {
        printf("Ошибка ввода номера!\n");
        return;
    }
    if (findApartmentIndex(aptList, newApt.number) != -1) {
        printf("Ошибка: Квартира №%d уже существует.\n", newApt.number);
        return;
    }
    printf("Введите этаж: ");
    if (scanf_s("%d", &newApt.floor) != 1) {
        printf("Ошибка ввода этажа!\n");
        return;
    }
    printf("Введите количество комнат: ");
    if (scanf_s("%d", &newApt.roomsCount) != 1) {
        printf("Ошибка ввода комнат!\n");
        return;
    }
    newApt.residentCount = 0;
    aptList.data[aptList.count] = newApt;
    aptList.count++;
    printf("Успех: Квартира №%d добавлена.\n", newApt.number);
}

void deleteApartment(ApartmentList& aptList, int aptNumber) {
    int indexToDelete = findApartmentIndex(aptList, aptNumber);
    if (indexToDelete == -1) {
        printf("Ошибка: Квартира №%d не найдена.\n", aptNumber);
        return;
    }
    for (int i = indexToDelete; i < aptList.count - 1; i++) {
        aptList.data[i] = aptList.data[i + 1];
    }
    aptList.count--;
    printf("Квартира №%d успешно удалена.\n", aptNumber);
}

void linkResidentToApartment(ApartmentList& aptList, int aptNumber, int resId) {
    int idx = findApartmentIndex(aptList, aptNumber);
    if (idx == -1) {
        printf("Ошибка: Квартира №%d не найдена.\n", aptNumber);
        return;
    }
    if (aptList.data[idx].residentCount < maxPerApt) {
        aptList.data[idx].residentIds[aptList.data[idx].residentCount] = resId;
        aptList.data[idx].residentCount++;
        printf("Успех: Жилец с ID %d заселен в квартиру №%d.\n", resId, aptNumber);
    }
    else {
        printf("Ошибка: В квартире №%d нет мест! Максимум: %d.\n", aptNumber, maxPerApt);
    }
}

void unlinkResidentFromApartment(ApartmentList& aptList, int aptNumber, int resId) {
    int aptIdx = findApartmentIndex(aptList, aptNumber);
    if (aptIdx == -1) {
        printf("Ошибка: Квартира №%d не найдена.\n", aptNumber);
        return;
    }
    int indexToDelete = -1;
    for (int j = 0; j < aptList.data[aptIdx].residentCount; j++) {
        if (aptList.data[aptIdx].residentIds[j] == resId) {
            indexToDelete = j;
            break;
        }
    }
    if (indexToDelete == -1) {
        printf("Ошибка: Жилец с ID %d не найден в квартире №%d.\n", resId, aptNumber);
        return;
    }
    for (int j = indexToDelete; j < aptList.data[aptIdx].residentCount - 1; j++) {
        aptList.data[aptIdx].residentIds[j] = aptList.data[aptIdx].residentIds[j + 1];
    }
    aptList.data[aptIdx].residentCount--;
    printf("Успех: Жилец с ID %d откреплен от квартиры №%d.\n", resId, aptNumber);
}

void printAllApartments(const ApartmentList& aptList) {
    if (aptList.count == 0) {
        printf("База квартир пуста.\n");
        return;
    }
    printf("\n--- СПИСОК ВСЕХ КВАРТИР ---\n");
    for (int i = 0; i < aptList.count; i++) {
        printf("Квартира №%-4d | Этаж: %-2d | Комнат: %-2d | Жильцов: %d/%d\n",
            aptList.data[i].number, aptList.data[i].floor, aptList.data[i].roomsCount,
            aptList.data[i].residentCount, maxPerApt);
    }
}

void printResidentsInApartment(int aptNumber, const ApartmentList& aptList, const ResidentList& resList) {
    int idx = findApartmentIndex(aptList, aptNumber);
    if (idx == -1) {
        printf("Ошибка: Квартира №%d не найдена.\n", aptNumber);
        return;
    }
    printf("\nЖильцы квартиры №%d (Этаж %d, Комнат: %d):\n",
        aptList.data[idx].number, aptList.data[idx].floor, aptList.data[idx].roomsCount);
    if (aptList.data[idx].residentCount == 0) {
        printf("  -- В этой квартире никто не зарегистрирован --\n");
    }
    else {
        for (int j = 0; j < aptList.data[idx].residentCount; j++) {
            int currentId = aptList.data[idx].residentIds[j];
            const Resident* r = findResidentById(resList, currentId);
            if (r != nullptr) {
                printf("  -> ID: %d | %s\n", r->id, r->fullName);
            }
            else {
                printf("  -> ID: %d | <Данные жильца удалены>\n", currentId);
            }
        }
    }
}

void printApartmentsByFloor(const ApartmentList& aptList, int floor) {
    printf("\n--- Квартиры на %d этаже ---\n", floor);
    int foundCount = 0;
    for (int i = 0; i < aptList.count; i++) {
        if (aptList.data[i].floor == floor) {
            printf("Квартира №%d (%d-комнатная, Жильцов: %d/%d)\n",
                aptList.data[i].number, aptList.data[i].roomsCount,
                aptList.data[i].residentCount, maxPerApt);
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("На %d этаже квартир нет.\n", floor);
    }
}

void printApartmentsByType(const ApartmentList& aptList, int rooms) {
    printf("\n--- Список квартир: %d-комнатные ---\n", rooms);
    int foundCount = 0;
    for (int i = 0; i < aptList.count; i++) {
        if (aptList.data[i].roomsCount == rooms) {
            printf("Квартира №%d | Этаж: %d | Жильцов: %d/%d\n",
                aptList.data[i].number, aptList.data[i].floor,
                aptList.data[i].residentCount, maxPerApt);
            foundCount++;
        }
    }
    if (foundCount == 0) {
        printf("Квартир с таким количеством комнат (%d) не найдено.\n", rooms);
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