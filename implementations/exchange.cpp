#include "/Users/arthur/Desktop/trade/trader.hpp"
#include "/Users/arthur/Desktop/trade/trade.hpp"
#include "/Users/arthur/Desktop/trade/owners.hpp"
#include "/Users/arthur/Desktop/trade/stock.hpp"
using namespace std;
void exchange(const Order& buyer_order, const Order& seller_order, double p) {
    
    Trader& seller = seller_order.get_trader();
    Trader& buyer = buyer_order.get_trader();
    Stock& stock = buyer_order.get_stock();
    int quantity = buyer_order.get_quantity();
    double price = p;
    
    seller.reduce_quantity(stock, quantity);
    buyer.add_to_portfolio(stock, quantity);
    
    if(0 == (Owners::getInstance().owners[seller.get_id()][stock] -= quantity)) {
        Owners::getInstance().owners[seller.get_id()].erase(stock);
    }
    Owners::getInstance().owners[buyer.get_id()][stock] += quantity;
    
    seller.top_up(price);
    buyer.pay(price);
    
    seller.delete_buy_order(seller_order.get_id());
    buyer.delete_buy_order(buyer_order.get_id());
    
    stock.add_trade(buyer.get_id(),seller.get_id(),price,quantity);
    
}


