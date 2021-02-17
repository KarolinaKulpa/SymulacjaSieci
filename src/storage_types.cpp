#include "storage_types.hpp"

// IPackageStockpile

using ElementID = int;
using set = std::set<ElementID>;
using iter = std::deque<Package>::const_iterator;

Package PackageQueue::pop(){
    Package pack;
    switch(_typesOfQueue){
        case PackageQueueType::LIFO:
            pack = std::move(_deque.back());
            _deque.pop_back();
            break;
        case PackageQueueType::FIFO:
            pack = std::move(_deque.front());
            _deque.pop_front();
            break;
    }
    return pack;
}



