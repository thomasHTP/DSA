//
// Created by Thomas Htay on 22/5/2024.
//

#ifndef BASECODE_PRICES_H
#define BASECODE_PRICES_H

struct Prices {
    double price;
    int locationId;

    Prices(double pri = -1, int ID = -1) : price(pri), locationId(ID) {};



};

#endif //BASECODE_PRICES_H
