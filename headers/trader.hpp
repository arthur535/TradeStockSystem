// Trader.hpp
#ifndef TRADER_H_
#define TRADER_H_
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <queue>
#include "order.hpp"
enum Strategy {
    MARKET_ORDER,
    LIMIT_ORDER,
    NO_STRATEGY
};
class Stock;
class Trader {
public:
    Trader(const std::string, const std::string);
    Trader(const std::string, const std::string, Strategy);
    Trader(const Trader&);
    Trader& operator=(const Trader&);
    bool operator==(const Trader&) const;
public:
    void set_name(const std::string);
    void set_email(const std::string);
    void set_strategy(Strategy);
    
    std::string get_name() const;
    std::string get_email() const;
    size_t get_id() const;
    double get_fund() const;
    
    void place_sell_order(Stock&, unsigned int, double);
    void place_buy_order(Stock&, unsigned int, double);
    
    void delete_sell_order(int);
    void delete_buy_order(int);
    
    void top_up(double);
    void pay(double);
    
    void add_to_portfolio(const Stock&,int);
    void reduce_quantity(const Stock& stock, int part);
    
private:
    std::string trader_name;
    std::string trader_email;
    static size_t unique_id;
    size_t trader_id;
    Strategy trader_strategy = Strategy::NO_STRATEGY;
    std::vector<Order> current_sell_orders;
    std::vector<Order> current_buy_orders;
    std::map<Stock,int> portfolio;
    double fund;
    
    std::mutex sellOrdersMutex;
    std::mutex buyOrdersMutex;
    std::mutex top_upMutex;
    std::mutex payMutex;
    std::mutex portfolioMutex;
    static std::mutex idMutex;
};
#endif
