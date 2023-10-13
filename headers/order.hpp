// Order.hpp
#ifndef ORDER_H_
#define ORDER_H_
#include <mutex>
typedef int Type;
enum OrderType : Type {
    LIMIT_BUY_ORDER = 1,
    LIMIT_SELL_ORDER = 2,
    MARKET_BUY_ORDER = 3,
    MARKET_SELL_ORDER = 4
};
class Stock;
class Trader;
class Order {
public:
    Order(Trader&,Stock&, unsigned int, double);
    Order(const Order&);
    Order& operator=(const Order&);
    bool operator<(const Order&) const;
public:
    Trader& get_trader() const;
    Stock& get_stock() const;
    size_t get_id() const;
    unsigned int get_quantity() const;
    
    virtual Type get_type() const;
    virtual double get_price() const;
private:
    static size_t unique_id;
    size_t order_id;
    Stock& stock;
    Trader& trader;
    unsigned int quantity;
    std::mutex idMutex;
protected:
    double price;
};


class MarketBuyOrder : public Order {
public:
    MarketBuyOrder(Trader&, Stock&, unsigned int, double);
    MarketBuyOrder(const MarketBuyOrder&);
    Type get_type()  const override;
    double get_price() const override;
private:
    Type ordertype = MARKET_BUY_ORDER;
};


class MarketSellOrder : public Order {
public:
    MarketSellOrder(Trader&, Stock&, unsigned int, double);
    MarketSellOrder(const MarketBuyOrder&);
    Type get_type() const override;
    double get_price() const override;
private:
    Type ordertype = MARKET_SELL_ORDER;
};





class LimitBuyOrder : public Order {
public:
    LimitBuyOrder(Trader&, Stock&, unsigned int, double);
    LimitBuyOrder(const LimitBuyOrder&);
    Type get_type() const override;
    double get_price() const override;
private:
    Type ordertype = LIMIT_BUY_ORDER;
};

class LimitSellOrder : public Order {
public:
    LimitSellOrder(Trader&, Stock&, unsigned int, double);
    LimitSellOrder(const LimitSellOrder&);
    Type get_type() const override;
    double get_price() const override;
private:
    Type ordertype = LIMIT_SELL_ORDER;
};
#endif

