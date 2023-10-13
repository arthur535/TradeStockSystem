#include "/Users/arthur/Desktop/trade/owners.hpp"
#include "/Users/arthur/Desktop/trade/stock.hpp"
#include "/Users/arthur/Desktop/trade/trader.hpp"
void Owners::add_record(Trader& trader,Stock stock, unsigned int quantity) {
    owners[trader.get_id()][stock] = quantity;
    trader.add_to_portfolio(stock, quantity);
}
int Owners::get_stock_quantity(Trader& trader,Stock& stock) {
    if(trader.get_id() >= owners.size())
        throw std::invalid_argument("trader argument is not valid");
    
    return owners[trader.get_id()][stock];
}
std::size_t Owners::StockHash::operator()(const Stock& stock) const {
    return std::hash<std::string>()(stock.get_symbol());
}
