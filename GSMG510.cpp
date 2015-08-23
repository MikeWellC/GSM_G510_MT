/*
 * GSMG510.cpp
 *
 *  Created on: 1 sty 2015
 *      Author: Wojtek
 */

#include "GSMG510.h"

void GSM_G510::init() {
	Serial0.init(19200);

	sbi(DDRD,PD2);
	cbi(PORTD,PD2);


}

/*
 * 0 - wyslano
 * 1 -  blad
 */
uint8_t GSM_G510::sendSMSR(const char *phoneNumber, const char *message) {
	for (uint8_t i = 0; i < 10; i++) {
		if (GSM_G510::sendSMS(phoneNumber, message) == 0) {
			return 0;
		}
		_delay_ms(500);
	}

	return 1;
}

/*
 * 0 - wyslano
 * 1 -  blad
 */

uint8_t GSM_G510::sendSMS(const char * phoneNumber, const char * message) {
	uint8_t result = 1;

	Serial0.flushRead();

	Serial0.write("AT+CMGF=1\r\n");

	if (GSM_G510::check("OK")) {

		Serial0.write("AT+CMGS=\"");
		Serial0.write(phoneNumber);
		Serial0.write("\"\r");
		if (GSM_G510::check(">")) {

			Serial0.write(message);
			Serial0.write("\x1A\r\n");
			if (GSM_G510::check("+CMGS: ")) {
				result = 0;
			} else {
				result = 1;
			}

		} else {
			result = 1;
		}
	}

	return result;

}

bool GSM_G510::check(const char * command) {
	Serial0.findReset();

	for (uint8_t i = 0; i < 200; i++) {
		if (Serial0.find(command) != NULL) {
			return true;
		}

		if (Serial0.find("ERROR\r\n") != NULL) {
			return false;
		}

		_delay_ms(50);
	}
	return false;
}

bool GSM_G510::getOperator(char * name) {

	Serial0.findReset();
	Serial0.write("AT+COPS?\r\n");
	_delay_ms(2000);
char temp[100];


	if (GSM_G510::check("+COPS:")) {
		strcpy(temp, strstr(Serial0.findBuffor, "\"") + 1);
		size_t end = (size_t) strstr(temp, "\"");
		strncpy(name, temp, 6);


	} else {
		return false;
	}

	return true;;

}
