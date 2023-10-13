// Trade.hpp
#ifndef TRADE_H_
#define TRADE_H_

class Trade {
public:
    Trade (size_t t1_id, size_t t2_id, double price, int quantity)
    : buyer_id(t1_id), seller_id(t2_id), price(price), quantity(quantity) {}
private:
    size_t buyer_id;
    size_t seller_id;
    double price;
    unsigned int quantity;
};
#endif

