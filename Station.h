/*
 * Location.h
 *
 *  Created on: 29 Apr 2024
 *      Author: Dongmo
 */

#ifndef STATION_H_
#define STATION_H_

class Station {
public:
	int index;//Key
	string stationLocation;
	bool available;
	double chargingPrice;

	void printLocation() {
		cout << setw (6) << index << setw (20) << stationLocation << setw (15);
		if(available)
			cout << "yes";
		else
			cout << "no";

		if(available && chargingPrice == 0)
			cout << setw (28) << "free of charge" << endl;
		else if (!available )
			cout << setw (17) << "N/A" << endl;
		else
		   cout << setw(15) << "$" << setprecision(2) << chargingPrice << "/kWh" << endl;
	}

	bool operator<(const Station& l)  const {
		return chargingPrice <l.chargingPrice;
	}
};



#endif /* STATION_H_ */
