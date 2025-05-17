// card.cpp
#include "card.h"
#include <string>

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << c.suit << " " << c.rank;
    return os;
}