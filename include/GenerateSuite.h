#ifndef __GENERATESUITE_SELF_DEF_H__
#define __GENERATESUITE_SELF_DEF_H__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <set>

#include "Order.h"
class GenerateSuite {
    public:
        static void generateRandomData(std::ofstream& file, int size) {
            std::set<int> ids = {};
            random_device rd;
            mt19937 gen(rd());
            // Generate random data
            // Follow class Order
            // Order(int oid, float price, int spicyLevel, Soup soup, vector<string> ingredients, bool takeaway)
            uniform_int_distribution<int> id_dist(0, 99999999);
            uniform_real_distribution<float> price_dist(0, 100);
            uniform_int_distribution<int> spicy_dist(0, 10);
            uniform_int_distribution<int> soup_dist(-1, 6);
            uniform_int_distribution<int> takeaway_dist(0, 1);
            // ingredient random from a list
            vector<string> ingredients = {"beef", "pork", "chicken", "mushroom", "tofu", "egg", "noodle", "rice", "vegetable", "onion", "garlic", "ginger", "chili", "pepper", "salt", "sugar", "soy sauce", "vinegar", "sesame oil", "peanut oil", "corn oil", "olive oil", "butter", "cheese", "milk", "yogurt", "bread", "cake", "cookie", "chocolate", "candy", "ice cream", "coffee", "tea", "juice", "soda", "beer", "wine", "whiskey", "vodka", "rum", "gin", "brandy", "tequila", "liqueur", "cocktail", "mocktail", "water"};
            // random size between 1 - 4
            uniform_int_distribution<int> size_dist(1, 4);
            // random ingredient
            uniform_int_distribution<int> ingredient_dist(0, ingredients.size() - 1);

            for (int i = 0; i < size; i++) {
                int oid = id_dist(gen);
                while (ids.find(oid) != ids.end()) {
                    oid = id_dist(gen);
                }
                float price = price_dist(gen);
                int spicyLevel = spicy_dist(gen);
                Soup soup = Soup {static_cast<Soup::Value>(soup_dist(gen))};
                vector<string> ing;
                int size = size_dist(gen);
                for (int j = 0; j < size; j++) {
                    ing.push_back(ingredients[ingredient_dist(gen)]);
                }
                bool takeaway = takeaway_dist(gen);
                // Output format: oid price spicyLevel soup ingredients takeaway
                file << oid << "," << price << "," << spicyLevel << "," << soup << "," << size;
                for (int j = 0; j < size; j++) {
                    file << "," << ing[j];
                }
                file << "," << takeaway << std::endl;
            }
        }
};

#endif // __GENERATESUITE_SELF_DEF_H__
