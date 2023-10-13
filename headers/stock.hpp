// Stock.hpp
#ifndef STOCK_H_
#define STOCK_H_

#include <vector>
#include <string>
#include <set>
#include <mutex>
#include "trade.hpp"
class Order;
class Stock {
public:
    Stock(const std::string symbol, const std::string name);
    Stock(const Stock&);
    Stock& operator=(const Stock&);
    bool operator==(const Stock&) const;
    bool operator<(const Stock&) const;
    
    std::string get_symbol() const;
    std::string get_name() const;
    
    void add_trade(size_t, size_t, double, unsigned int);
    void rename(const std::string);
    void add_order(const Order&);
private:
    class OrderBook {
    public:
        OrderBook();
        OrderBook& operator=(const OrderBook&);
        void matching(const Order&);
    private:
        class SellCompare {
        public:
            bool operator()(const Order&, const Order&) const ;
        };
        class BuyCompare {
        public:
            bool operator()(const Order&, const Order&) const;
        };
    private:
        std::set<Order,BuyCompare> buy_orders;
        std::set<Order,SellCompare> sell_orders;
        std::mutex mutex;
    };
    
private:
    std::string symbol;
    std::string name;
    std::vector<Trade> trade_history;
    OrderBook ob;
};

#endif


