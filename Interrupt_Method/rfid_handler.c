#include "rfid_handler.h"
#include "RC522.h"

extern uint8_t MasterCardID[5];
extern uint8_t CurrentCardID[5];
extern uint8_t hasMasterCard;
extern uint8_t matchflag;

void indicate_master_stored(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}

void indicate_card_match(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}

void indicate_card_mismatch(void) {
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
}

void set_master_card(uint8_t* card_uid) {
    memcpy(MasterCardID, card_uid, 5);
    hasMasterCard = 1;
    indicate_master_stored();
}

uint8_t compare_cards(uint8_t* master, uint8_t* current) {
    return (memcmp(master, current, 5) == 0) ? 1 : 0;
}

void validate_card(uint8_t* card_uid) {
    memcpy(CurrentCardID, card_uid, 5);

    if(compare_cards(MasterCardID, CurrentCardID)) {
        matchflag = 1;
        indicate_card_match();
        matchflag = 0;
    } else {
        matchflag = 0;
        indicate_card_mismatch();
    }

    memset(CurrentCardID, 0, 5);
}

void process_rfid_card(uint8_t* card_uid) {
    if(hasMasterCard == 0) {
        set_master_card(card_uid);
    } else {
        validate_card(card_uid);
    }
    MFRC522_Halt();
}
