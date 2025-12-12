#include "sorting_reporter.h"
#include "sorting_hill.h"

#include <iostream>

using namespace std::literals;

SortingReporterImpl::~SortingReporterImpl() {}

void SortingReporterImpl::StartShift(const SortingHill& sorting_hill) {
    std::cout << "Начало рабочей смены"s << std::endl;
    std::cout << "Очередь вагонов: "s << sorting_hill.GetNumberOfWagBuffer() << std::endl;
}

void SortingReporterImpl::EndShift(const SortingHill& sorting_hill) {
    std::cout << "Рабочая смена окончена"s << std::endl;
    std::cout << std::endl;
    std::cout << "===== ОТЧЁТ О СМЕНЕ ====="s << std::endl;
    std::cout << "Подготовлено путей:                    "s << sorting_hill.GetNumberOfPaths() << std::endl;
    std::cout << "Запланировано поездов:                 "s << sorting_hill.GetTrainsSent() << std::endl;
    std::cout << "Прибыло локомотивов:                   "s << sorting_hill.GetLocomotivesArrived() << std::endl;
    std::cout << "Обработано вагонов (с повторами):      "s << sorting_hill.GetTotalWagonsProcessed() << std::endl;
    std::cout << "Отправлено поездов:                    "s << sorting_hill.GetTrainsSent() << std::endl;
    std::cout << "Осталось вагонов в буфере:             "s << sorting_hill.GetNumberOfWagBuffer() << std::endl;
    std::cout << "Максимальное заполнение буфера:        "s << sorting_hill.GetMaxBufferUsage() << std::endl;
    std::cout << "=========================="s << std::endl;
}


void SortingReporterImpl::PreparePath(SortingHill& sorting_hill, OperationInfo& operation_info) {

}

void SortingReporterImpl::AllocatePathForTrain(SortingHill& sorting_hill, OperationInfo& operation_info) {

}

void SortingReporterImpl::HandleLocomotive(SortingHill& sorting_hill, const Locomotive& locomotive, OperationInfo& operation_info) {

}

void SortingReporterImpl::HandleWagon(SortingHill& sorting_hill, const Wagon& wagon, OperationInfo& operation_info) {

}

void SortingReporterImpl::SendTrain(SortingHill& sorting_hill, OperationInfo& operation_info) {

}
