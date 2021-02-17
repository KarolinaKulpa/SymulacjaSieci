#ifndef SIEC_STORAGE_TYPES_HPP
#define SIEC_STORAGE_TYPES_HPP

#include<iostream>
#include<set>
#include<list>
#include<deque>
#include<functional>
#include "package.hpp"

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push( Package &&pack) = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockpile() {};
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
};


class IPackageQueue: public IPackageStockpile{
public:
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop()=0;
    virtual ~IPackageQueue(){};
};

class PackageQueue :public IPackageQueue{
public:
    explicit PackageQueue(PackageQueueType typesOfQueue = PackageQueueType::LIFO) : _typesOfQueue(typesOfQueue){}
    ~PackageQueue(){};
    PackageQueueType get_queue_type() const override { return _typesOfQueue;}
    Package pop() override;
    void push(Package &&pack) override{ _deque.emplace_back(std::move(pack)); }
    size_t size()const override{ return _deque.size();}
    bool empty() const override { return _deque.empty(); }
    const_iterator cbegin() const override {return _deque.cbegin();};
    const_iterator cend() const override {return _deque.cend();};
    const_iterator begin() const override { return _deque.begin();};
    const_iterator end() const override {return _deque.end();};
private:
    PackageQueueType _typesOfQueue;
    std::list<Package> _deque;
};

#endif //SIEC_STORAGE_TYPES_HPP
