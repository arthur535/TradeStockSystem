#include "/Users/arthur/Desktop/trade/trader.hpp"
#include "/Users/arthur/Desktop/trade/stock.hpp"
#include "/Users/arthur/Desktop/trade/owners.h"
#include <iostream>
Trader::Trader(const std::string name, const std::string email)
: trader_name(name), trader_email(email) {
    idMutex.lock();
    unique_id++;
    idMutex.unlock();
    trader_id = unique_id;
    fund = 0;
    portfolio = std::map<Stock,int>();
}
Trader::Trader(const std::string name, const std::string email, Strategy strategy)
: trader_name(name), trader_email(email), trader_strategy(strategy) {
    idMutex.lock();
    unique_id++;
    idMutex.unlock();
    trader_id = unique_id;
    fund = 0;
    portfolio = std::map<Stock,int>();
}

Trader& Trader::operator=(const Trader& oth) {
    if (this == &oth) {
        return *this;
    }
    trader_name = oth.trader_name;
    trader_email = oth.trader_email;
    trader_strategy = oth.trader_strategy;
    portfolio = oth.portfolio;
    fund = oth.fund;
    current_sell_orders = oth.current_sell_orders;
    current_buy_orders = oth.current_buy_orders;
    return *this;
}
Trader::Trader(const Trader& other) {
    if (this == &other) {
        return;
    }
    trader_name = other.trader_name;
    trader_email = other.trader_email;
    trader_strategy = other.trader_strategy;
    portfolio = other.portfolio;
    fund = other.fund;
    current_sell_orders = other.current_sell_orders;
    current_buy_orders = other.current_buy_orders;

}

int Trader::unique_id = 0;
std::mutex Trader::idMutex;

bool Trader::operator==(const Trader& oth) const {
    return trader_id == oth.get_id();
}
void Trader::set_name(const std::string name) { trader_name = name; }
void Trader::set_email(const std::string email) { trader_email = email; }
void Trader::set_strategy(Strategy strategy) {trader_strategy = strategy;}

std::string Trader::get_name() const { return trader_name; }
std::string Trader::get_email() const { return trader_email; }
int Trader::get_id() const { return trader_id; }
double Trader::get_fund() const { return fund; }

void Trader::place_sell_order(Stock& stock, int quantity, double min_price) {
    int q = portfolio[stock];
    if(q == -1 or q < quantity){
        throw std::invalid_argument("invalid order");
    }
    Order* order;
    if (trader_strategy == Strategy::LIMIT_ORDER)
        order = new LimitSellOrder(*this, stock, quantity,min_price);
    else if (trader_strategy == Strategy::MARKET_ORDER)
        order = new MarketSellOrder(*this, stock,quantity,this->get_fund());
    else
        throw std::runtime_error("no strategy chosen");
    
    sellOrdersMutex.lock();
    stock.add_order(*order);
    current_sell_orders.push_back(*order);
    sellOrdersMutex.unlock();
}

void Trader::place_buy_order(Stock& stock, int quantity, double max_price) {
    Order* order;
    if (trader_strategy == Strategy::LIMIT_ORDER)
        order = new LimitBuyOrder(*this,stock,quantity,max_price);
    else if (trader_strategy == Strategy::MARKET_ORDER)
        order = new MarketBuyOrder(*this,stock,quantity,this->get_fund());
    else
        throw std::runtime_error("no strategy chosen");
    
    buyOrdersMutex.lock();
    stock.add_order(*order);
    current_buy_orders.push_back(*order);
    buyOrdersMutex.unlock();
}

void Trader::top_up(double deposit) {
    std::lock_guard<std::mutex> lock(top_upMutex);
    fund += deposit;
}

void Trader::pay(double price) {
    std::lock_guard<std::mutex> lock(payMutex);
    fund -= price;
}

void Trader::add_to_portfolio(const Stock& stock,int quantity) {
    std::lock_guard<std::mutex> lock(portfolioMutex);
    portfolio[stock] += quantity;
}

void Trader::reduce_quantity(const Stock& stock, int part) {
    if((portfolio[stock] -= part) == 0){
        portfolio.erase(stock);
    }
}

void Trader::delete_buy_order(int order_id) {
    for(auto it = current_buy_orders.begin(); it != current_buy_orders.end(); ++it) {
        if(it->get_id() == order_id)
            current_buy_orders.erase(it, it);
    }
}
void Trader::delete_sell_order(int order_id) {
    for(auto it = current_sell_orders.begin(); it != current_sell_orders.end(); ++it) {
        if(it->get_id() == order_id)
            current_sell_orders.erase(it, it);
    }
}

