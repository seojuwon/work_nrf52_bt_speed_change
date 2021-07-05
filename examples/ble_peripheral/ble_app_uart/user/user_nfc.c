/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
  by seo. 2020 06 25
 */
#include <stdint.h>
#include "nfc_t2t_lib.h"
#include "nfc_ndef_msg.h"
#include "nfc_text_rec.h"
#include "boards.h"
#include "app_error.h"
#include "hardfault.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "user_nfc.h"

#if 1

/* Text message in English with its language code. */
/** @snippet [NFC text usage_1] */
static const uint8_t en_payload[] =
{
    'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'
};
static const uint8_t en_code[] = {'e', 'n'};
/** @snippet [NFC text usage_1] */

/* Text message in Norwegian with its language code. */
static const uint8_t no_payload[] =
{
    'H', 'a', 'l', 'l', 'o', ' ', 'V', 'e', 'r', 'd', 'e', 'n', '!'
};
static const uint8_t no_code[] = {'N', 'O'};

/* Text message in Polish with its language code. */
static const uint8_t pl_payload[] =
{
    'W', 'i', 't', 'a', 'j', ' ', 0xc5, 0x9a, 'w', 'i', 'e', 'c', 'i', 'e', '!'
};
static const uint8_t pl_code[] = {'P', 'L'};

/* Buffer used to hold an NFC NDEF message. */
uint8_t m_ndef_msg_buf[256];
#endif
/**
 * @brief Callback function for handling NFC events.
 */
void nfc_callback(void * p_context, nfc_t2t_event_t event, const uint8_t * p_data, size_t data_length)
{
    (void)p_context;

    switch (event)
    {
        case NFC_T2T_EVENT_FIELD_ON:
            bsp_board_led_on(BSP_BOARD_LED_3);
						printf("NFC FIELD on");
            break;
        case NFC_T2T_EVENT_FIELD_OFF:
            bsp_board_led_off(BSP_BOARD_LED_3);
						printf("NFC FIELD off");
            break;
        default:
            break;
    }
}


/**
 * @brief Function for encoding the NDEF text message.
 */
ret_code_t welcome_msg_encode(uint8_t * p_buffer, uint32_t * p_len)
{
    /** @snippet [NFC text usage_2] */
    ret_code_t err_code;

    /* Create NFC NDEF text record description in English */
    NFC_NDEF_TEXT_RECORD_DESC_DEF(nfc_en_text_rec,
                                  UTF_8,
                                  en_code,
                                  sizeof(en_code),
                                  en_payload,
                                  sizeof(en_payload));
    /** @snippet [NFC text usage_2] */

    /* Create NFC NDEF text record description in Norwegian */
    NFC_NDEF_TEXT_RECORD_DESC_DEF(nfc_no_text_rec,
                                  UTF_8,
                                  no_code,
                                  sizeof(no_code),
                                  no_payload,
                                  sizeof(no_payload));

    /* Create NFC NDEF text record description in Polish */
    NFC_NDEF_TEXT_RECORD_DESC_DEF(nfc_pl_text_rec,
                                  UTF_8,
                                  pl_code,
                                  sizeof(pl_code),
                                  pl_payload,
                                  sizeof(pl_payload));

    /* Create NFC NDEF message description, capacity - MAX_REC_COUNT records */
    /** @snippet [NFC text usage_3] */
    NFC_NDEF_MSG_DEF(nfc_text_msg, MAX_REC_COUNT);
    /** @snippet [NFC text usage_3] */

    /* Add text records to NDEF text message */
    /** @snippet [NFC text usage_4] */
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_text_msg),
                                       &NFC_NDEF_TEXT_RECORD_DESC(nfc_en_text_rec));
    VERIFY_SUCCESS(err_code);
    /** @snippet [NFC text usage_4] */
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_text_msg),
                                       &NFC_NDEF_TEXT_RECORD_DESC(nfc_no_text_rec));
    VERIFY_SUCCESS(err_code);
    err_code = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(nfc_text_msg),
                                       &NFC_NDEF_TEXT_RECORD_DESC(nfc_pl_text_rec));
    VERIFY_SUCCESS(err_code);

    /** @snippet [NFC text usage_5] */
    err_code = nfc_ndef_msg_encode(&NFC_NDEF_MSG(nfc_text_msg),
                                   p_buffer,
                                   p_len);
    return err_code;
    /** @snippet [NFC text usage_5] */
}

/**
 *@brief Function for initializing logging.
 */
#if 0
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}
#endif

/**
 * @brief Function for application main entry.
 */
#if 0
int main(void)
{
    uint32_t  len = sizeof(m_ndef_msg_buf);
    uint32_t  err_code;

    log_init();

    /* Configure LED-pins as outputs */
    bsp_board_init(BSP_INIT_LEDS);

    /* Set up NFC */
    err_code = nfc_t2t_setup(nfc_callback, NULL);
    APP_ERROR_CHECK(err_code);

    /* Encode welcome message */
    err_code = welcome_msg_encode(m_ndef_msg_buf, &len);
    APP_ERROR_CHECK(err_code);

    /* Set created message as the NFC payload */
    err_code = nfc_t2t_payload_set(m_ndef_msg_buf, len);
    APP_ERROR_CHECK(err_code);

    /* Start sensing NFC field */
    err_code = nfc_t2t_emulation_start();
    APP_ERROR_CHECK(err_code);

    while (1)
    {
        NRF_LOG_FLUSH();
        __WFE();
    }
}
#endif

