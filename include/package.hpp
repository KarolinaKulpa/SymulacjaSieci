#ifndef SIEC_PACKAGE_HPP
#define SIEC_PACKAGE_HPP

#include <set>
#include "types.hpp"

class Package {
public:
    Package();

    explicit Package(ElementID id);

    Package(const Package& p) = default;
    Package(Package&&) noexcept;

    Package& operator=(Package&) = delete;
    Package& operator=(Package&&) noexcept;

    ~Package();

    ElementID get_id() const { return id_; }

private:
    static const ElementID BLANK_ID = -1;

    inline static std::set<ElementID> assigned_ids_{0};

    inline static std::set<ElementID> freed_ids_;

    ElementID id_ = BLANK_ID;
};



#endif //SIEC_PACKAGE_HPP
