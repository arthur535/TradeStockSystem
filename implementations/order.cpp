#include "/Users/arthur/Desktop/trade/order.hpp"
#include "/Users/arthur/Desktop/trade/stock.hpp"
#include "/Users/arthur/Desktop/trade/trader.hpp"
Order::Order(Trader& trader, Stock& stock, unsigned int quantity, double price)
: trader(trader), stock(stock), quantity(quantity), price(price) {
    idMutex.lock();
    unique_id++;
    idMutex.unlock();
    order_id = unique_id;
}

Order::Order(const Order& oth) : trader(oth.trader), stock(oth.stock) {
    order_id = oth.order_id;
    quantity = oth.quantity;
    price = oth.price;
}

size_t Order::unique_id = 0;

Order& Order::operator=(const Order& oth) {
    if (this == &oth) {
        return *this;
    }
    trader = oth.get_trader();
    stock = oth.get_stock();
    order_id = oth.order_id;
    quantity = oth.quantity;
    price = oth.price;
    return *this;
}

Type Order::get_type() const { return -1; }
size_t Order::get_id() const { return order_id; }
Trader& Order::get_trader() const { return trader; }
Stock& Order::get_stock() const { return stock; }

bool Order::operator<(const Order& other) const { return quantity < other.quantity; }

unsigned int Order::get_quantity() const { return quantity; }


MarketBuyOrder::MarketBuyOrder(Trader& trader, Stock& stock, unsigned int quantity, double price)
: Order(trader, stock, quantity, price) {}
MarketBuyOrder::MarketBuyOrder(const MarketBuyOrder& oth) : Order(oth) {}
Type MarketBuyOrder::get_type() const {
    return ordertype;
}

MarketSellOrder::MarketSellOrder(Trader& trader, Stock& stock, unsigned int quantity, double price)
: Order(trader, stock, quantity, price) {}
MarketSellOrder::MarketSellOrder(const MarketBuyOrder& oth) : Order(oth) {}
Type MarketSellOrder::get_type() const {
    return ordertype;
}


LimitBuyOrder::LimitBuyOrder(Trader& trader,Stock& stock, unsigned int quantity, double max_price)
: Order(trader, stock, quantity, max_price) {}

LimitBuyOrder::LimitBuyOrder(const LimitBuyOrder& oth) : Order(oth) {}
Type LimitBuyOrder::get_type() const {
    return ordertype;
}



LimitSellOrder::LimitSellOrder(Trader& trader, Stock& stock, unsigned int quantity, double min_price)
: Order(trader, stock, quantity, min_price) {}

LimitSellOrder::LimitSellOrder(const LimitSellOrder& oth) : Order(oth) {}
Type LimitSellOrder::get_type() const {
    return ordertype;
}

double Order::get_price() const { return price; }
