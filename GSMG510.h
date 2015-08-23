/*
 * GSMG510.h
 *
 *  Created on: 1 sty 2015
 *      Author: Wojtek
 */

#ifndef GSMG510_H_
#define GSMG510_H_

#include "GLOBAL.h"
#include "Serial0.h"



class GSM_G510 {
public:

	void static init();
	uint8_t static sendSMS(const char *phoneNumber, const char *message);
	uint8_t static sendSMSR(const char *phoneNumber, const char *message);
	bool static check(const char * command);
	bool static getOperator(char * name);
};

#endif /* GSMG510_H_ */
