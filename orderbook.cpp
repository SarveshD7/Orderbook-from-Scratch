#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<memory>
#include<variant>
#include<optional>
#include<tuple>
#include<format>

enum class OrderType
{
    GoodTillCancel,
    FillAndKill
};

enum class Side{
    Buy, 
    Sell
};

using Price  = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo
{
    Price price_;
    Quantity quantity_;
};

using levelInfos = std::vector<LevelInfo>;

class OrderbookLevelInfos{

    public:
    OrderbookLevelInfos(const levelInfos& bids, const levelInfos& asks)
    : bids_{bids},
    asks_{asks}
    {}
    const levelInfos&bids_, asks_;
    private:
    LevelInfo bids_;
    LevelInfo asks_;
};

class Order{
    public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
    :orderType_ {orderType},
    orderId_{orderId},
    side_ {side},
    price_ {price},
    intialQuantity_{quantity},
    remainingQuantity(quantity)
    {}

    OrderId GetOrderId() const {return orderId_;}
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    OrderType GetOrderType() const {return orderType_;}
    Quantity GetIntialQuantity() const {return intialQuantity_;}
    Quantity GetRemainingQuantity() const {return remainingQuantity;}
    Quantity GetFilledQuantity() const {return GetIntialQuantity()-GetRemainingQuantity();}
    void Fill(Quantity quantity){
        if (quantity > GetRemainingQuantity())
        throw std::logic_error("Order cannot be filled for more than its remaining quantity");
        remainingQuantity -= quantity;
    }
    private:
        OrderType orderType_;
        OrderId orderId_;
        Side side_;
        Price price_;
        Quantity intialQuantity_;
        Quantity remainingQuantity;

};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

class OrderModify{
    public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
    :orderId_{orderId},
    price_{price},
    side_{side},
    quantity_{quantity} 
    {}
    OrderId GetOrderId() const {return orderId_;}
    Price GetPrice() const {return price_;}
    Side GetSide() const {return side_;}
    Quantity GetQuantity() const {return quantity_;}

    OrderPointer ToOrderPointer(OrderType type) const{
        return std::make_shared<Order>(type, GetOrderId(), GetSide(), GetPrice(), GetQuantity());
    }

    private:
        OrderId orderId_;
        Price price_;
        Side side_;
        Quantity quantity_;

}

int main(){

    return 0;
}