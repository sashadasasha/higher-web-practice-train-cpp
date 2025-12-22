#pragma once

#include "handler_interface.h"
#include "enums.h"
#include "common.h"
#include "path.h"
#include "train.h"

#include <memory>
#include <optional>
#include <queue>
#include <vector>

class SortingHill {
public:
    explicit SortingHill(size_t number_of_paths,
                         std::vector<std::unique_ptr<SortingHandler>> handlers);

    void AddWagon(Wagon wagon);
    bool IsWagonBuffer() const;
    size_t GetNumberOfPaths() const;
    size_t GetNumberOfWagBuffer() const;
    bool CheckEvent(EventType event) const;
    void HandleEvent(EventType event);
    
    // Методы для работы с путями
    Path& GetPath(size_t index);
    const Path& GetPath(size_t index) const;
    size_t GetFreePath() const;
    bool HasFreePath() const;
    
    // Методы для работы с поездами
    int GetNextTrainNumber();
    
    // Методы для отчетности
    size_t GetTotalWagonsProcessed() const;
    size_t GetTrainsSent() const;
    size_t GetMaxBufferUsage() const;
    size_t GetLocomotivesArrived() const;

private:
    std::vector<std::unique_ptr<SortingHandler>> handlers_;
    const size_t number_of_paths_;
    std::queue<Wagon> wagon_buffer_;
    std::vector<Path> paths_;
    int train_index_ = 1;
    
    // Статистика для отчетности
    size_t total_wagons_processed_ = 0;
    size_t trains_sent_ = 0;
    size_t locomotives_arrived_ = 0;
    size_t max_buffer_usage_ = 0;

private:
    void PopWagon();
};
