

#include <iostream>
#include<array>
#include<assert.h>
#include<vector>
#include<algorithm>

using namespace std;
struct Product
{
    unsigned int quantity;
    double price;
};

class ProductInfo {

public:
    double price;
    unsigned int quantity;

    ProductInfo(double x, unsigned int y)
    {
        this->price = x;
        this->quantity = y;
    }
};

class VendingMachineBalance {

public:
    int remainingDimes = 0;
    int remainingDollars = 0;
    int remainingQuaters = 0;
    int remainingNickels = 0;
    int remainingPennies = 0;
};

class VendingMachine
{
public:
    //VendingMachine(std::array<Product, 3> const& products, std::array<int, 5> const& coins);
    //implement the constructor
   //Product pdts[3];
    double noDimes = 0;
    double noDollar = 0;
    double noQuater = 0;
    double noNickel = 0;
    double noPenny = 0;

    std::vector<ProductInfo> pdts;

    VendingMachineBalance vmb;

    VendingMachine(std::array<Product, 3> const& products, std::array<int, 5> const& coins)
    {

        for (int i = 0; i < 3; i++)
        {
            double price = products[i].price;
            if (products[i].quantity > 10)
            {
                if (price > 0)
                {
                    pdts.push_back(ProductInfo(price, 10));
                }
                else
                {
                    pdts.push_back(ProductInfo(1, 0));
                }
            }
            else
            {
                unsigned int quantity = products[i].quantity;
                if (price > 0)
                {
                    pdts.push_back(ProductInfo(price, quantity));
                }
            }
        }
        vmb.remainingDollars = coins[0];
        vmb.remainingQuaters = coins[1];
        vmb.remainingDimes = coins[2];
        vmb.remainingNickels = coins[3];
        vmb.remainingPennies = coins[4];
    }
    // user actions
    void insertDollar();
    void insertQuarter();
    void insertDime();
    void insertNickel();
    void insertPenny();
    void clearCurrencyUpdates();
    void restoreBalancesVM(); // function used to update balances of each coins on the Vending Machine
    //std::array<int, 6> changetoDispense(std::array<int, 6> coins);
    // returns the dispensed quantity of each in the following order:
    // products, dollars, quarters, dimes, nickels, pennies
    std::array<int, 6> makeSelection(int product);
    std::array<int, 6> calculateChange(double valueofCoins, double actualPrice);
};
//function to restore the balances in the vending machine
void VendingMachine::restoreBalancesVM()
{
    vmb.remainingDollars -= noDollar;
    vmb.remainingQuaters -= noQuater;
    vmb.remainingDimes -= noDimes;
    vmb.remainingNickels -= noNickel;
    vmb.remainingPennies -= noPenny;
}
//function to clear the currency
void VendingMachine::clearCurrencyUpdates()
{
    noDollar = 0;
    noQuater = 0;
    noPenny = 0;
    noNickel = 0;
    noDimes = 0;
}
//fucntion to calculate how much change to return to user
std::array<int, 6> VendingMachine::calculateChange(double valueofCoins, double actualPrice)
{
    int diff = 0;
    int actualPriceCents = actualPrice * 1;
    diff = ((int)valueofCoins - actualPriceCents);
    std::array<int, 6> returnChange;
    returnChange[0] = 0;

    //products, dollars, quarters, dimes, nickels, pennies
    returnChange[1] = diff / 100;
    diff = diff % 100;
    returnChange[2] = diff / 25;
    diff = diff % 25;
    returnChange[3] = diff / 10;
    diff = diff % 10;
    returnChange[4] = diff / 5;
    diff = diff % 5;
    returnChange[5] = diff / 1;
    return returnChange;
}
std::array<int, 6> VendingMachine::makeSelection(int product)
{
    std::array<int, 6> change_ar;
    double valueofCoins = (noDollar * 100) + (noQuater * 25) + (noDimes * 10) + (noNickel * 5) + (noPenny);
    double actualPrice;
    actualPrice = pdts[product].price;
    actualPrice = actualPrice * 100;
    if (valueofCoins == 0)
    {
        change_ar[0] = 0;
        change_ar[1] = noDollar;
        change_ar[2] = noQuater;
        change_ar[3] = noDimes;
        change_ar[4] = noNickel;
        change_ar[5] = noPenny;
    }
    else if (valueofCoins >= actualPrice)
    {
        if (pdts[product].quantity > 0 && pdts[product].quantity <= 10)
        {
            pdts[product].quantity = pdts[product].quantity - 1;
            change_ar = calculateChange(valueofCoins, actualPrice);
            change_ar[0] = 1;
            restoreBalancesVM();
        }
        else
        {
            change_ar[0] = 0;
            change_ar[1] = noDollar;
            change_ar[2] = noQuater;
            change_ar[3] = noDimes;
            change_ar[4] = noNickel;
            change_ar[5] = noPenny;
            restoreBalancesVM();
        }
    }
    else
    {
        //change_ar = calculateChange(valueofCoins, actualPrice);
        change_ar[0] = 0;
        change_ar[1] = noDollar;
        change_ar[2] = noQuater;
        change_ar[3] = noDimes;
        change_ar[4] = noNickel;
        change_ar[5] = noPenny;
        restoreBalancesVM();
    }
    clearCurrencyUpdates();
    return change_ar;
}
//functions for user actions

void VendingMachine::insertDollar()
{
    vmb.remainingDollars += 1;
    noDollar++;
}
void VendingMachine::insertQuarter()
{
    vmb.remainingQuaters += 1;
    noQuater++;
}
void VendingMachine::insertDime()
{
    vmb.remainingDimes += 1;
    noDimes++;
}
void VendingMachine::insertNickel()
{
    vmb.remainingNickels += 1;
    noNickel++;
}
void VendingMachine::insertPenny()
{
    vmb.remainingPennies += 1;
    noPenny++;
}int main()
{

    VendingMachine machine(std::array<Product, 3>{Product{ 1,1.50 }, Product{ 2, 1.00 }, Product{ 0, -1.25 }}, std::array<int, 5>{20, 80, 200, 0, 2000});
    machine.insertDollar();
    machine.insertDime();
    machine.insertDime();
    machine.insertDime();
    std::array<int, 6> pdt = machine.makeSelection(2);
    
    for (int i = 0;i < 6;i++)
    {
        cout << pdt[i] << "\t";
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
