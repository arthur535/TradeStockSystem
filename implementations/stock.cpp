#include "/Users/arthur/Desktop/trade/stock.hpp"
#include "/Users/arthur/Desktop/trade/order.hpp"
#include "/Users/arthur/Desktop/trade/trader.hpp"
#include <thread>
void exchange(const Order&, const Order&,double);
Stock::Stock(const std::string symbol, const std::string name) : symbol(symbol), name(name) {}

Stock::Stock(const Stock& oth) {
    symbol = oth.symbol;
    name = oth.name;
    trade_history = oth.trade_history;
    ob = oth.ob;
}

Stock& Stock::operator=(const Stock& oth) {
    symbol = oth.symbol;
    name = oth.name;
    trade_history = oth.trade_history;
    ob = oth.ob;
    return *this;
}

std::string Stock::get_symbol() const { return symbol; }
std::string Stock::get_name() const { return name; }

void Stock::add_trade(size_t t1_id, size_t t2_id, double price, unsigned int quantity) {
    Trade trade(t1_id, t2_id, price, quantity);
    trade_history.push_back(trade);
}

void Stock::rename(const std::string new_name) {
    name = new_name;
}


bool Stock::operator==(const Stock& oth) const {
    return symbol == oth.get_symbol();
}

bool Stock::operator<(const Stock& other) const {
    return symbol < other.get_symbol();
}

void Stock::add_order(const Order& order) {
    ob.matching(order);
}

Stock::OrderBook::OrderBook() {
    buy_orders = std::set<Order,BuyCompare>();
    sell_orders = std::set<Order,SellCompare>();
}


Stock::OrderBook& Stock::OrderBook::operator=(const OrderBook& oth) {
    buy_orders = oth.buy_orders;
    sell_orders = oth.sell_orders;
    return *this;
}
void Stock::OrderBook::matching(const Order& order) {
    
    if(order.get_type() == LIMIT_BUY_ORDER) {
        buy_orders.insert(order);
        //for(auto& buys : buy_orders){
        //    for(auto& sells : sell_orders){
        //        if(sells.get_quantity() >= buys.get_quantity() and
        //           buys.get_trader().get_fund() >= sells.get_price()){
        //            exchange(buys, sells, sells.get_price());
        //        }
        //    }
        //}

    }
    
    else if(order.get_type() == LIMIT_SELL_ORDER) {
        sell_orders.insert(order);
    }
    else if (order.get_type() == MARKET_BUY_ORDER) {
        if(!sell_orders.empty()) {
            bool status = false;
            for(auto & ref : sell_orders) {
                if(ref.get_quantity() >= order.get_quantity() and
                   order.get_trader().get_fund() >= ref.get_price())
                {
                    exchange(order,ref,ref.get_price());
                    status = true;
                }
                if(status) break;
            }
        }
    }
    else if(order.get_type() == MARKET_SELL_ORDER){
        if(!buy_orders.empty()) {
            bool status = false;
            for(auto & ref : buy_orders) {
                if(order.get_quantity() >= ref.get_quantity() and
                   ref.get_trader().get_fund() >= order.get_price())
                {
                    exchange(ref,order,ref.get_price());
                    status = true;
                }
                if(status) break;
            }
        }
    }
}

bool Stock::OrderBook::SellCompare::operator()(const Order& below, const Order& above) const {
    //ascending order
    if (below.get_price() > above.get_price()) {
        return true;
    }
    return false;
}

bool Stock::OrderBook::BuyCompare::operator()(const Order& below, const Order& above) const {
    //descending order
    if (below.get_price() <= above.get_price()) {
        return true;
    }
    return false;
}


