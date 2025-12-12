#include "sorting_hill.h"
#include "random.h"

#include <stdexcept>
#include <algorithm>

SortingHill::SortingHill(size_t number_of_paths, std::vector<std::unique_ptr<SortingHandler>> handlers)
    : handlers_(std::move(handlers)),
      number_of_paths_(number_of_paths),
      paths_(number_of_paths, Path(0)) {
    for (size_t i = 0; i < number_of_paths_; ++i) {
        paths_[i] = Path(static_cast<int>(i));
    }
}

size_t SortingHill::GetNumberOfPaths() const {
    return number_of_paths_;
}

size_t SortingHill::GetNumberOfWagBuffer() const {
    return wagon_buffer_.size();
}

Path& SortingHill::GetPath(size_t index) {
    return paths_[index];
}

const Path& SortingHill::GetPath(size_t index) const {
    return paths_[index];
}

size_t SortingHill::GetFreePath() const {
    for (size_t i = 0; i < paths_.size(); ++i) {
        if (paths_[i].IsFree()) {
            return i;
        }
    }
    return static_cast<size_t>(-1); // Нет свободных путей
}

bool SortingHill::HasFreePath() const {
    return GetFreePath() != static_cast<size_t>(-1);
}

int SortingHill::GetNextTrainNumber() {
    return train_index_++;
}

size_t SortingHill::GetTotalWagonsProcessed() const {
    return total_wagons_processed_;
}

size_t SortingHill::GetTrainsSent() const {
    return trains_sent_;
}

size_t SortingHill::GetMaxBufferUsage() const {
    return max_buffer_usage_;
}

size_t SortingHill::GetLocomotivesArrived() const {
    return locomotives_arrived_;
}

void SortingHill::AddWagon(Wagon wagon) {
    wagon_buffer_.push(wagon);
    // Обновляем максимальное использование буфера для отчетности
    max_buffer_usage_ = std::max(max_buffer_usage_, wagon_buffer_.size());
}

/* Проверка возможности события. */
bool SortingHill::CheckEvent(EventType event) const {
    switch (event) {
        case EventType::kPreparePath: {
            /* Проверить, что есть свободные пути. */
            return HasFreePath();
        }
        case EventType::kTrainPlanned: {
            /* Проверить, что на назначенных путях нет поездов. */
            return HasFreePath();
        }
        case EventType::kLocoArrived: {
            /* Проверить, что у поезда нет локомотива. */
            return true;
        }
        case EventType::kTrainReady: {
            /* Проверить, что количество вагонов соответствует локомотиву или буфер вагонов пустой. */
            return true;
        }
        default:
            return true;
    }
}

void SortingHill::PopWagon() {
    wagon_buffer_.pop();
}

bool SortingHill::IsWagonBuffer() const {
    return !wagon_buffer_.empty();
}

void SortingHill::HandleEvent(EventType event) {
    switch (event) {
        case EventType::kShiftStarted: {
            for (const auto& handler : handlers_) {
                handler->StartShift(*this);
            }
            break;
        }
        case EventType::kShiftEnded: {
            /* Здесь нужно освободить все пути. Можно отправлять локомотивы, даже без вагонов. */
            for (const auto& handler : handlers_) {
                handler->EndShift(*this);
            }
            break;
        }
        case EventType::kWagonArrived: {
            if (!IsWagonBuffer()) {
                break;
            }
            const auto& wagon = wagon_buffer_.front();
            OperationInfo operation_info;
            for (const auto& handler : handlers_) {
                handler->HandleWagon(*this, wagon, operation_info);
            }
            PopWagon();
            total_wagons_processed_++; // Увеличиваем счетчик обработанных вагонов
            break;
        }
        case EventType::kLocoArrived: {
            auto loco_type = RandomGen::GetRandomElem<LocoType>(kLocoType);
            Locomotive locomotive{loco_type};
            OperationInfo operation_info;
            for (const auto& handler : handlers_) {
                handler->HandleLocomotive(*this, locomotive, operation_info);
            }
            locomotives_arrived_++; // Увеличиваем счетчик прибывших локомотивов
            break;
        }
        case EventType::kTrainPlanned: {
            OperationInfo operation_info;
            for (const auto& handler : handlers_) {
                handler->AllocatePathForTrain(*this, operation_info);
            }
            break;
        }
        case EventType::kTrainReady: {
            OperationInfo operation_info;
            for (const auto& handler : handlers_) {
                handler->SendTrain(*this, operation_info);
            }
            trains_sent_++; // Увеличиваем счетчик отправленных поездов
            break;
        }
        case EventType::kPreparePath: {
            OperationInfo operation_info;
            for (const auto& handler : handlers_) {
                handler->PreparePath(*this, operation_info);
            }
            break;
        }
        default: {
            using namespace std::literals;
            throw std::out_of_range("Неожиданное событие"s);
        }
    }
}
