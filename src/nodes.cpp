#include "nodes.hpp"
#include <stdexcept>
#include <optional>

// ****************** RAMP *******************************************************

void Ramp::deliver_goods(Time t){
    if(send_buffer != std::nullopt){
            throw std::logic_error("There is a different product (on the ramp)");
    }
    if((t-1)%DI==0){
        Package pack=Package();
        push_package(std::move(pack));
    }
}

void Worker::do_work(Time time){
   if(workerbuffer)
   {
       bool raport= (get_processing_duration() == (time - get_package_processing_start_time() + 1));
       if(raport){
       push_package(std::move(workerbuffer.value()));
       workerbuffer.reset();
       }
   }
   else{
       if(ptrWorker){
           workerbuffer=std::optional<Package>(ptrWorker->pop());
           timeWorker=time;
       }
   }
   }




// ******************************** PACKAGESENDER ****************************************
void PackageSender::send_package()
{
    if(send_buffer)
    {
        auto var = receiver_preferences_.choose_receiver();
        var->receive_package(std::move(send_buffer.value()));
        send_buffer.reset();

    }
}

//*********************************RECEIVEFERENCE*********************************
void ReceiverPreferences::make_new_preferences()
{
    double sum_of_pref = 0;
    for(auto& elem : my_pref)
    {
        sum_of_pref += elem.second;
    }
    for(auto& item : my_pref)
    {
        item.second = item.second/sum_of_pref;
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver* rec)
{
    my_pref[rec]=0;
    double NewProbability=(double) 1/my_pref.size();
    for(auto & i : my_pref){
        i.second = NewProbability;
    }
    make_new_preferences();
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* rec)
{
    auto RemoveProbability = my_pref.find(rec);
    bool IsProbability = RemoveProbability!=my_pref.end();
    if(IsProbability)
    {
        auto ProbabilityValue = RemoveProbability->second;
        my_pref.erase(RemoveProbability);
        for(auto &e: my_pref){
            e.second = (double) e.second/(1 - ProbabilityValue);
        }
    }

    make_new_preferences();
}

IPackageReceiver* ReceiverPreferences::choose_receiver()
    {
        double pr = probability_generator();
        double sum = 0;
        for(auto &e : my_pref){
            sum+=e.second;
            if(sum>=pr){
                return e.first;
            }
        }
        throw std::logic_error("Can't choose a receiver");
    }
    
