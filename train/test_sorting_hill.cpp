#include "sorting_hill.h"
#include "sorting_operator.h"
#include "enums.h"
#include "common.h"

#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

void TestBasicFunctionality() {
    std::cout << "Тест базовой функциональности..." << std::endl;
    
    // Создаем сортировочную станцию с 3 путями
    std::vector<std::unique_ptr<SortingHandler>> handlers;
    handlers.push_back(std::make_unique<SortingOperatorImpl>());
    SortingHill sorting_hill(3, std::move(handlers));
    
    // Добавляем несколько вагонов
    sorting_hill.AddWagon({12345678, WagonType::kFreight});
    sorting_hill.AddWagon({87654321, WagonType::kPass});
    sorting_hill.AddWagon({11111111, WagonType::kDanger});
    
    // Проверяем, что вагоны добавились
    assert(sorting_hill.GetNumberOfWagBuffer() == 3);
    
    std::cout << "Тест базовой функциональности пройден." << std::endl;
}

void TestTrainFormation() {
    std::cout << "Тест формирования поезда..." << std::endl;
    
    // Создаем сортировочную станцию с 3 путями
    std::vector<std::unique_ptr<SortingHandler>> handlers;
    handlers.push_back(std::make_unique<SortingOperatorImpl>());
    SortingHill sorting_hill(3, std::move(handlers));
    
    // Добавляем вагон грузового типа
    sorting_hill.AddWagon({12345678, WagonType::kFreight});
    
    // Планируем поезд
    sorting_hill.HandleEvent(EventType::kTrainPlanned);
    
    // Добавляем локомотив
    // В текущей реализации локомотивы генерируются случайным образом, поэтому мы не можем напрямую проверить их тип.
    // В реальных тестах может потребоваться mock для RandomGen.
    
    std::cout << "Тест формирования поезда завершен." << std::endl;
}

void TestPathManagement() {
    std::cout << "Тест управления путями..." << std::endl;
    
    // Создаем сортировочную станцию с 2 путями
    std::vector<std::unique_ptr<SortingHandler>> handlers;
    handlers.push_back(std::make_unique<SortingOperatorImpl>());
    SortingHill sorting_hill(2, std::move(handlers));
    
    // Проверяем начальное состояние
    assert(sorting_hill.HasFreePath() == true);
    assert(sorting_hill.GetFreePath() < sorting_hill.GetNumberOfPaths());
    
    std::cout << "Тест управления путями пройден." << std::endl;
}

int main() {
    try {
        TestBasicFunctionality();
        TestTrainFormation();
        TestPathManagement();
        
        std::cout << "Все тесты пройдены успешно!" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Ошибка во время тестирования: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}