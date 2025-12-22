#include "sorting_operator.h"
#include <algorithm>
#include <iostream>

SortingOperatorImpl::~SortingOperatorImpl() {}

void SortingOperatorImpl::StartShift(const SortingHill&) {}

void SortingOperatorImpl::EndShift(const SortingHill&) {}

void SortingOperatorImpl::PreparePath(SortingHill& sorting_hill, OperationInfo& operation_info) {
    // Ничего не делаем, пути создаются при инициализации
}

void SortingOperatorImpl::AllocatePathForTrain(SortingHill& sorting_hill, OperationInfo& operation_info) {
    size_t free_path_index = sorting_hill.GetFreePath();
    if (free_path_index != static_cast<size_t>(-1)) {
        int train_number = sorting_hill.GetNextTrainNumber();
        // Тип поезда будет определен позже при добавлении первого вагона
        sorting_hill.GetPath(free_path_index).AssignTrain(train_number, TrainType::kFreight);
    }
}

void SortingOperatorImpl::HandleLocomotive(SortingHill& sorting_hill, const Locomotive& locomotive, OperationInfo& operation_info) {
    // Ищем путь с поездом, у которого еще нет локомотива
    for (size_t i = 0; i < sorting_hill.GetNumberOfPaths(); ++i) {
        Path& path = sorting_hill.GetPath(i);
        if (!path.IsFree() && path.GetTrain().has_value()) {
            const Train& train = path.GetTrain().value();
            if (train.GetLocomotive() == nullptr) {
                path.SetLocomotiveToTrain(locomotive);
                break;
            }
        }
    }
}

void SortingOperatorImpl::HandleWagon(SortingHill& sorting_hill, const Wagon& wagon, OperationInfo& operation_info) {
    // Определяем тип поезда по типу вагона
    TrainType train_type;
    switch (wagon.wagon_type) {
        case WagonType::kPass:
            train_type = TrainType::kPass;
            break;
        case WagonType::kDanger:
            train_type = TrainType::kDanger;
            break;
        case WagonType::kEmpty:
            train_type = TrainType::kFreight; // Пустые вагоны относим к грузовым
            break;
        case WagonType::kFreight:
        default:
            train_type = TrainType::kFreight;
            break;
    }

    // Ищем путь с поездом того же типа или свободный путь
    size_t target_path_index = static_cast<size_t>(-1);
    
    // Сначала ищем путь с поездом того же типа, у которого еще нет локомотива
    for (size_t i = 0; i < sorting_hill.GetNumberOfPaths(); ++i) {
        Path& path = sorting_hill.GetPath(i);
        if (!path.IsFree() && path.GetTrain().has_value()) {
            const Train& train = path.GetTrain().value();
            if (train.GetType() == train_type && train.GetLocomotive() == nullptr) {
                target_path_index = i;
                break;
            }
        }
    }
    
    // Если не нашли подходящий путь, ищем свободный путь
    if (target_path_index == static_cast<size_t>(-1)) {
        target_path_index = sorting_hill.GetFreePath();
        if (target_path_index != static_cast<size_t>(-1)) {
            // Назначаем новый поезд на свободный путь
            int train_number = sorting_hill.GetNextTrainNumber();
            sorting_hill.GetPath(target_path_index).AssignTrain(train_number, train_type);
        }
    }
    
    // Если нашли путь, добавляем вагон
    if (target_path_index != static_cast<size_t>(-1)) {
        sorting_hill.GetPath(target_path_index).AddWagonToTrain(wagon);
    }
}

void SortingOperatorImpl::SendTrain(SortingHill& sorting_hill, OperationInfo& operation_info) {
    // Отправляем все готовые поезда (с локомотивом и вагонами)
    for (size_t i = 0; i < sorting_hill.GetNumberOfPaths(); ++i) {
        Path& path = sorting_hill.GetPath(i);
        if (path.IsTrainComplete()) {
            path.Release();
        }
    }
}
