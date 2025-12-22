#include "path.h"

Path::Path(int path_number) : path_number_(path_number) {}

bool Path::IsFree() const {
    return !train_.has_value();
}

bool Path::AssignTrain(int train_number, TrainType type) {
    if (IsFree()) {
        train_.emplace(train_number, type);
        return true;
    }
    return false;
}

bool Path::IsTrainComplete() const {
    if (!train_.has_value()) {
        return false;
    }
    return train_.value().IsComplete();
}

void Path::Release() {
    train_.reset();
}

int Path::GetPathNumber() const {
    return path_number_;
}

const std::optional<Train>& Path::GetTrain() const {
    return train_;
}

void Path::AddWagonToTrain(const Wagon& wagon) {
    if (train_.has_value()) {
        train_.value().AddWagon(wagon);
    }
}

void Path::SetLocomotiveToTrain(const Locomotive& locomotive) {
    if (train_.has_value()) {
        train_.value().SetLocomotive(locomotive);
    }
}