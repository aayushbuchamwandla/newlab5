#include "card.h"


Card::Card() {
   suit = CLUBS;
   rank = ACE;
}


Card::Card(char s, string r) {
   ConvertSuit(s);
   ConvertRank(r);
}


void Card::ConvertSuit(char s) {
   if (s == 'c') suit = CLUBS;
   else if (s == 'd') suit = DIAMONDS;
   else if (s == 's') suit = SPADES;
   else if (s == 'h') suit = HEARTS;
}


void Card::ConvertRank(string r) {
   if (r == "a") rank = ACE;
   else if (r == "2") rank = TWO;
   else if (r == "3") rank = THREE;
   else if (r == "4") rank = FOUR;
   else if (r == "5") rank = FIVE;
   else if (r == "6") rank = SIX;
   else if (r == "7") rank = SEVEN;
   else if (r == "8") rank = EIGHT;
   else if (r == "9") rank = NINE;
   else if (r == "10") rank = TEN;
   else if (r == "j") rank = JACK;
   else if (r == "q") rank = QUEEN;
   else if (r == "k") rank = KING;
}


bool Card::operator==(const Card& c) const {
   return (suit == c.suit) && (rank == c.rank);
}


bool Card::operator>(const Card& c) const {
   if (suit > c.suit) return true;
   if (suit == c.suit) return rank > c.rank;
   return false;
}


bool Card::operator<(const Card& c) const {
   if (suit < c.suit) return true;
   if (suit == c.suit) return rank < c.rank;
   return false;
}


ostream& operator<<(ostream &out, const Card& c) {
   string s;
   string r;


   if (c.suit == Card::CLUBS) s = "c";
   else if (c.suit == Card::DIAMONDS) s = "d";
   else if (c.suit == Card::SPADES) s = "s";
   else if (c.suit == Card::HEARTS) s = "h";


   if (c.rank == Card::ACE) r = "a";
   else if (c.rank == Card::TWO) r = "2";
   else if (c.rank == Card::THREE) r = "3";
   else if (c.rank == Card::FOUR) r = "4";
   else if (c.rank == Card::FIVE) r = "5";
   else if (c.rank == Card::SIX) r = "6";
   else if (c.rank == Card::SEVEN) r = "7";
   else if (c.rank == Card::EIGHT) r = "8";
   else if (c.rank == Card::NINE) r = "9";
   else if (c.rank == Card::TEN) r = "10";
   else if (c.rank == Card::JACK) r = "j";
   else if (c.rank == Card::QUEEN) r = "q";
   else if (c.rank == Card::KING) r = "k";


   out << s << " " << r;
   return out;
}


int Card::getRank() const {
   return static_cast<int>(rank);
}
