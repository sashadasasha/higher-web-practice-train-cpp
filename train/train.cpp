#include "train.h"

Train::Train(int train_number, TrainType type) 
    : train_number_(train_number), type_(type) {}

void Train::AddWagon(const Wagon& wagon) {
    wagons_.push_back(wagon);
}

void Train::SetLocomotive(const Locomotive& locomotive) {
    locomotive_ = locomotive;
}

int Train::GetTrainNumber() const {
    return train_number_;
}

TrainType Train::GetType() const {
    return type_;
}

const std::vector<Wagon>& Train::GetWagons() const {
    return wagons_;
}

const Locomotive* Train::GetLocomotive() const {
    if (locomotive_.has_value()) {
        return &locomotive_.value();
    }
    return nullptr;
}

bool Train::IsComplete() const {
    if (!locomotive_.has_value()) {
        return false;
    }
    
    // Поезд считается завершенным, если у него есть локомотив и хотя бы один вагон
    return !wagons_.empty() && static_cast<int>(wagons_.size()) <= GetMaxWagons();
}

int Train::GetMaxWagons() const {
    if (!locomotive_.has_value()) {
        return 0;
    }
    
    switch (locomotive_.value().loco_type) {
        case LocoType::kElectro16:
        case LocoType::kDiesel24:
            return 16;
        case LocoType::kElectro32:
        case LocoType::kDiesel64:
            return 32;
        default:
            return 0;
    }
}