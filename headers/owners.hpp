#ifndef OWNERS_H_
#define OWNERS_H_
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
class Stock;
class Trader;

class Owners {
public:
    static Owners& getInstance() {
        static Owners instance;
        return instance;
    }
    
    struct StockHash {
        std::size_t operator()(const Stock& stock) const;
    };
    
    void add_record(Trader&, Stock, unsigned int);
    int get_stock_quantity(Trader&, Stock&);
    
    std::unordered_map<size_t,std::unordered_map<Stock,int, StockHash>> owners;
private:
    Owners(){}
    Owners(const Owners&) = delete;
    Owners& operator=(const Owners&) = delete;
};
#endif

