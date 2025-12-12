#pragma once

#include "train.h"
#include <optional>

class Path {
public:
    Path(int path_number);
    
    bool IsFree() const;
    bool AssignTrain(int train_number, TrainType type);
    void Release();
    
    int GetPathNumber() const;
    const std::optional<Train>& GetTrain() const;
    void AddWagonToTrain(const Wagon& wagon);
    void SetLocomotiveToTrain(const Locomotive& locomotive);
    
    // Проверяет, готов ли поезд к отправке
    bool IsTrainComplete() const;
    
private:
    int path_number_;
    std::optional<Train> train_;
};