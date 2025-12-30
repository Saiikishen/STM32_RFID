/*
 * rfid_handler.h
 *
 *  Created on: Dec 30, 2025
 *      Author: saiik
 */

#ifndef INC_RFID_HANDLER_H_
#define INC_RFID_HANDLER_H_


#include "main.h"
#include <stdint.h>
#include <string.h>


void indicate_master_stored(void);
void indicate_card_match(void);
void indicate_card_mismatch(void);
void set_master_card(uint8_t* card_uid);
uint8_t compare_cards(uint8_t* master, uint8_t* current);
void validate_card(uint8_t* card_uid);
void process_rfid_card(uint8_t* card_uid);

#endif /* INC_RFID_HANDLER_H_ */
