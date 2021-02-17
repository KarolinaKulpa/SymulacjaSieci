//
// Created by Asus on 04.01.2020.
//

#ifndef SYMULACJA_SIECI_NODES_HPP
#define SYMULACJA_SIECI_NODES_HPP

#include "storage_types.hpp"
#include "package.hpp"
#include "types.hpp"
#include <memory>
#include <optional>
#include <map>
#include "helpers.hpp"


enum class ReceiverType {
    WORKER, STOREHOUSE
};

//************************************I_PACKAGE_RECEIVER*****************************
class IPackageReceiver
{
public:
    using const_iterator = IPackageStockpile::const_iterator;
//    virtual ~IPackageReceiver(){};
    virtual void receive_package(Package&& pck) = 0;
    virtual ElementID get_id() const = 0;

    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

};

// ****************************************************RECEIVERPREFERENCES*******************************8
class ReceiverPreferences
{
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;
private:
    void make_new_preferences(); // funkcja slużaca do poprawiania preferencji po każdej zmianie aby suma prawdopodobienstwa byla 1
    preferences_t my_pref;
    ProbabilityGenerator my_prg;
public:
    explicit ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : my_prg(pg){};
    void add_receiver(IPackageReceiver* rec);
    void remove_receiver(IPackageReceiver* rec);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const {return my_pref;}

    iterator begin() {return my_pref.begin();};
    iterator end() {return my_pref.end();};
    const_iterator cbegin() const {return my_pref.cbegin();};
    const_iterator cend() const {return my_pref.cend();};

};


//***************************STOREHOUSE*********************************
class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d= std::make_unique<PackageQueue>()): ID(id), depot(std::move(d)){}
    void receive_package(Package&& p) override {depot->push(std::move(p));};
    ElementID get_id() const override {return ID;}
    const_iterator begin() const override {return depot->begin();};
    const_iterator end()  const override {return depot->end();};
    const_iterator cbegin() const override {return depot->cbegin();};
    const_iterator cend() const override {return depot->cend();};

private:
    ElementID ID;
    std::unique_ptr<IPackageStockpile> depot;
};

//***************************PackageSender*********************************
class PackageSender
{
public:
    ReceiverPreferences receiver_preferences_;
    std::optional<Package> send_buffer = std::nullopt;
    void send_package();
    const inline std::optional<Package>& get_sending_buffer() const {return send_buffer;};
protected:
    void push_package(Package&& p){send_buffer = std::optional<Package>(std::move(p));}


};



// **************************************RAMP**********************************
class Ramp: public PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : ID(id), DI(di) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const{ return DI;}
    ElementID get_id(){ return ID;}
private:
    ElementID ID;
    TimeOffset DI;
};

// **************************************Worker******************************
class Worker: public PackageSender,public IPackageReceiver{
private:
    ElementID idWorker;
    TimeOffset processing_durationWorker;
    std::unique_ptr<IPackageQueue> ptrWorker;
    std::optional<Package> workerbuffer = std::nullopt;
    Time timeWorker = 0;
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> ptr): idWorker(id), processing_durationWorker(pd), ptrWorker(std::move(ptr)){}
    void receive_package(Package&& p) override {ptrWorker->push(std::move(p));}
    ~Worker(){};
    ElementID get_id() const override{return idWorker;}
    void do_work(Time time);
    auto size() {return ptrWorker->size();}
    TimeOffset get_processing_duration() const{return processing_durationWorker;}
    Time get_package_processing_start_time() const{return timeWorker;}
    const_iterator cbegin() const override {return ptrWorker->cbegin();}
    const_iterator cend() const override { return ptrWorker->cend();}
    const_iterator begin() const override {return ptrWorker->begin();}
    const_iterator end()  const override {return ptrWorker->end();}

};

#endif //SYMULACJA_SIECI_NODES_HPP
