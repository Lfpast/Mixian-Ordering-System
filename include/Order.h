#ifndef __ORDER_SELF_DEF_H__
#define __ORDER_SELF_DEF_H__

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Simulate a real mixian order
// It includes
// 1. Order ID
// 2. Soup
// 3. Price
// 4. Spicy Level
// 5. Ingredients
class Soup {
    public:
        enum Value {
            DEFAULT = -1,
            HOT_AND_SOUR_SOUP = 0,
            TOMATO_SOUP,
            HOT_AND_NUMBING_SOUP,
            PEPPER_AND_SPICY_SOUP,
            SHASHA_SOUP,
            CLEAR_SOUP,
            VEGGIE_SOUP
        };
        Soup() = default;
        Soup(Value soup) : soup(soup) {}
        string toString() const {
            switch (soup) {
                case HOT_AND_SOUR_SOUP:
                    return "Hot and Sour Soup";
                case TOMATO_SOUP:
                    return "Tomato Soup";
                case HOT_AND_NUMBING_SOUP:
                    return "Hot and Numbing Soup";
                case PEPPER_AND_SPICY_SOUP:
                    return "Pepper and Spicy Soup";
                case SHASHA_SOUP:
                    return "Shasha Soup";
                case CLEAR_SOUP:
                    return "Clear Soup";
                case VEGGIE_SOUP:
                    return "Veggie Soup";
                default:
                    return "Unknown";
            }
        }
        friend ostream& operator<<(ostream& os, const Soup& soup) {
            os << soup.toString();
            return os;
        }
        // FROM string to Value
        static Value fromString(string soup) {
            if (soup == "Hot and Sour Soup") {
                return HOT_AND_SOUR_SOUP;
            } else if (soup == "Tomato Soup") {
                return TOMATO_SOUP;
            } else if (soup == "Hot and Numbing Soup") {
                return HOT_AND_NUMBING_SOUP;
            } else if (soup == "Pepper and Spicy Soup") {
                return PEPPER_AND_SPICY_SOUP;
            } else if (soup == "Shasha Soup") {
                return SHASHA_SOUP;
            } else if (soup == "Clear Soup") {
                return CLEAR_SOUP;
            } else if (soup == "Veggie Soup") {
                return VEGGIE_SOUP;
            } else {
                return HOT_AND_SOUR_SOUP;
            }
        }

        bool operator==(const Soup& other) const {
            return this->soup == other.soup;
        }

        bool operator!=(const Soup& other) const {
            return this->soup != other.soup;
        }

        bool operator<(const Soup& other) const {
            return this->soup < other.soup;
        }

        bool operator>(const Soup& other) const {
            return this->soup > other.soup;
        }

        bool operator<=(const Soup& other) const {
            return this->soup <= other.soup;
        }

        bool operator>=(const Soup& other) const {
            return this->soup >= other.soup;
        }
    private:
        Value soup;
    

};




class Order {
    public:
        Order(int oid, float price, int spicyLevel, Soup soup, vector<string> ingredients, bool takeaway) : oid(oid), price(price), spicyLevel(spicyLevel), soup(soup), ingredients(ingredients), takeaway(takeaway) {}
        Order(const Order& order) = delete;
        ~Order() = default;
        int getOid() const {
            return this->oid;
        }
        float getPrice() const {
            return this->price;
        }
        int getSpicyLevel() const {
            return this->spicyLevel;
        }
        Soup getSoup() const {
            return this->soup;
        }
        vector<string> getIngredients() const {
            return this->ingredients;
        }
        bool isTakeaway() const {
            return this->takeaway;
        }
    private:
        int oid;
        float price;
        int spicyLevel;
        Soup soup;
        vector<string> ingredients;
        bool takeaway;
        friend ostream& operator<<(ostream& os, const Order& order);
};



#endif // __ORDER_SELF_DEF_H__
