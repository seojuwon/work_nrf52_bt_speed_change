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

#define MAX_REC_COUNT      3     /**< Maximum records count. */

#if 0
/* Text message in English with its language code. */
/** @snippet [NFC text usage_1] */
uint8_t en_payload[] =
{
    'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'
};
uint8_t en_code[] = {'e', 'n'};
/** @snippet [NFC text usage_1] */

/* Text message in Norwegian with its language code. */
uint8_t no_payload[] =
{
    'H', 'a', 'l', 'l', 'o', ' ', 'V', 'e', 'r', 'd', 'e', 'n', '!'
};
uint8_t no_code[] = {'N', 'O'};

/* Text message in Polish with its language code. */
uint8_t pl_payload[] =
{
    'W', 'i', 't', 'a', 'j', ' ', 0xc5, 0x9a, 'w', 'i', 'e', 'c', 'i', 'e', '!'
};
uint8_t pl_code[] = {'P', 'L'};

/* Buffer used to hold an NFC NDEF message. */
uint8_t m_ndef_msg_buf[256];

#endif
/**
 * @brief Callback function for handling NFC events.
 */
void nfc_callback(void * p_context, nfc_t2t_event_t event, const uint8_t * p_data, size_t data_length);

/**
 * @brief Function for encoding the NDEF text message.
 */
ret_code_t welcome_msg_encode(uint8_t * p_buffer, uint32_t * p_len);


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


