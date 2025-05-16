#include "card.h"

// Assuming a basic implementation where "Ace" = 1, "Two" = 2, etc.
int Card::getRank() const {
    if (rank == "Ace") return 1;
    else if (rank == "Two") return 2;
    else if (rank == "Three") return 3;
    else if (rank == "Four") return 4;
    else if (rank == "Five") return 5;
    else if (rank == "Six") return 6;
    else if (rank == "Seven") return 7;
    else if (rank == "Eight") return 8;
    else if (rank == "Nine") return 9;
    else if (rank == "Ten") return 10;
    else if (rank == "Jack") return 11;
    else if (rank == "Queen") return 12;
    else if (rank == "King") return 13;
    return 0;  // Default return value if rank is unknown
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << c.suit << " " << c.rank;
    return os;
}
