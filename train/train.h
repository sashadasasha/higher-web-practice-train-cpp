#pragma once

#include "enums.h"
#include "common.h"

#include <vector>
#include <string>

class Train {
public:
    Train(int train_number, TrainType type);
    
    void AddWagon(const Wagon& wagon);
    void SetLocomotive(const Locomotive& locomotive);
    
    int GetTrainNumber() const;
    TrainType GetType() const;
    const std::vector<Wagon>& GetWagons() const;
    const Locomotive* GetLocomotive() const;
    
    bool IsComplete() const;
    int GetMaxWagons() const;
    
private:
    int train_number_;
    TrainType type_;
    std::vector<Wagon> wagons_;
    std::optional<Locomotive> locomotive_;
};