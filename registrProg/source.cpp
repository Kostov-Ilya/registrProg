#define _CRT_SECURE_NO_WARNINGS
#pragma region files
#include "includes.h"
#include "struct.h"
#include "prototypes.h"
#include "fileManager.h"
#pragma endregion files

int main() {
    system("chcp 65001 > nul");
    ResidentList resList = { new Resident[startCap], 0, startCap };
    ApartmentList aptList = { new Apartment[startCap], 0, startCap };
    size_t rId = 0;
    size_t choice = 0;
    size_t aNum = 0;
    size_t floor = 0;
    size_t rooms = 0;
    loadFromFiles(resList, aptList);
    while (true) {
        printf("\n--- СИСТЕМА УЧЁТА ---\n");
        printf("1. Добавить жильца         | 7. Список жильцов\n");
        printf("2. Удалить жильца          | 8. Список квартир\n");
        printf("3. Добавить квартиру       | 9. Жильцы в кв.\n");
        printf("4. Удалить квартиру        | 10. По этажам\n");
        printf("5. Связать                 | 11. По числу комнат\n");
        printf("6. Отвязать                | 12. Сохранить\n");
        printf("0. Выход\n");
        printf(">> ");
        if (scanf_s("%llu", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice > 12) {
            printf("Введите число от 0 до 12!\n");
            continue;
        }
        if (choice == 0) {
            break;
        }
        switch (choice) {
            case 1:
                addResident(resList);
                break;
            case 2:
                printf("ID жильца: ");
                if (scanf_s("%llu", &rId) == 1)
                    deleteResident(resList, rId);
                break;
            case 3:
                addApartment(aptList);
                break;
            case 4:
                printf("Номер квартиры: ");
                if (scanf_s("%llu", &aNum) == 1) {
                    deleteApartment(aptList, aNum);
                }
                break;
            case 5:
                printf("ID жильца: ");
                scanf_s("%llu", &rId);
                printf("Номер квартиры: ");
                scanf_s("%llu", &aNum);
                linkResidentToApartment(aptList, resList, aNum, rId);
                break;
            case 6:
                printf("Номер квартиры: ");
                scanf_s("%llu", &aNum);
                printf("ID жильца: ");
                scanf_s("%llu", &rId);
                unlinkResidentFromApartment(aptList, aNum, rId);
                break;
            case 7:
                printAllResidents(resList);
                break;
            case 8:
                printAllApartments(aptList);
                break;
            case 9:
                printf("Номер квартиры: ");
                if (scanf_s("%llu", &aNum) == 1)
                    printResidentsInApartment(aNum, aptList, resList);
                break;
            case 10:
                printf("Этаж: ");
                if (scanf_s("%llu", &floor) == 1)
                    printApartmentsByFloor(aptList, floor);
                break;
            case 11:
                printf("Комнат: ");
                if (scanf_s("%llu", &rooms) == 1)
                    printApartmentsByType(aptList, rooms);
                break;
            case 12:
                saveToFiles(resList, aptList);
                printf("Данные сохранены\n");
                break;
            default:
                printf("Ошибка выбора\n");
                break;
        }
    }
    saveToFiles(resList, aptList);
    cleanMemory(resList, aptList);
    printf("Программа завершена\n");
    return 0;
}