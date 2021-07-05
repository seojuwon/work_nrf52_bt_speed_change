#include "user_fstorage.h"
#include "nrf_fstorage.h"
 #ifdef SOFTDEVICE_PRESENT
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_fstorage_sd.h"
#else
#include "nrf_drv_clock.h"
#include "nrf_fstorage_nvmc.h"
#endif
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
//#include "user_time.h"
//#include "user_ble.h"
#include "nrf_pwr_mgmt.h"
#include "pca10040.h"
uint32_t dumy_m_read_data[5]={0,};
/* Dummy data to write to flash. */
static uint32_t dumy_m_data          = 0xaADC0FF0;
//static char     m_hello_world[] = "hello world";

//extern user_time_type user_time;
//extern TOTAL_INFO_T total_info;

NRF_FSTORAGE_DEF(nrf_fstorage_t fstorage) =
{
    /* Set a handler for fstorage events. */
    .evt_handler = fstorage_evt_handler,

    /* These below are the boundaries of the flash space assigned to this instance of fstorage.
     * You must set these manually, even at runtime, before nrf_fstorage_init() is called.
     * The function nrf5_flash_end_addr_get() can be used to retrieve the last address on the
     * last page of flash available to write data. */
  //  .start_addr = 0x3e000,
	//  .end_addr   = 0x3ffff,
			.start_addr = 0x76000,  
			.end_addr   = 0x77fff,
};
static uint32_t nrf5_flash_end_addr_get()
{
    uint32_t const bootloader_addr = BOOTLOADER_ADDRESS;
    uint32_t const page_sz         = NRF_FICR->CODEPAGESIZE;
    uint32_t const code_sz         = NRF_FICR->CODESIZE;

    return (bootloader_addr != 0xFFFFFFFF ?
            bootloader_addr : (code_sz * page_sz));
}

static void fstorage_evt_handler(nrf_fstorage_evt_t * p_evt)
{
    if (p_evt->result != NRF_SUCCESS)
    {
        NRF_LOG_INFO("--> Event received: ERROR while executing an fstorage operation.");
        return;
    }

    switch (p_evt->id)
    {
        case NRF_FSTORAGE_EVT_WRITE_RESULT:
        {
            NRF_LOG_INFO("--> Event received: wrote %d bytes at address 0x%x.",
                         p_evt->len, p_evt->addr);
        } break;

        case NRF_FSTORAGE_EVT_ERASE_RESULT:
        {
            NRF_LOG_INFO("--> Event received: erased %d page from address 0x%x.",
                         p_evt->len, p_evt->addr);
        } break;

        default:
            break;
    }
}


static void print_flash_info(nrf_fstorage_t * p_fstorage)
{
    NRF_LOG_INFO("========| flash info |========");
    NRF_LOG_INFO("erase unit: \t%d bytes",      p_fstorage->p_flash_info->erase_unit);
    NRF_LOG_INFO("program unit: \t%d bytes",    p_fstorage->p_flash_info->program_unit);
    NRF_LOG_INFO("==============================");
}


void wait_for_flash_ready2(nrf_fstorage_t const * p_fstorage)
{
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage))
    {
       (void) sd_app_evt_wait();
		//if (NRF_LOG_PROCESS() == false)
		//{			nrf_pwr_mgmt_run();		}
//		idle_state_handle();
    }
}

void nvm_control(void)
{
		ret_code_t rc;
		NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
		nrf_fstorage_api_t * p_fs_api;
		p_fs_api = &nrf_fstorage_sd;
		rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(rc);

/////// Write
    print_flash_info(&fstorage);

		(void) nrf5_flash_end_addr_get();
		NRF_LOG_INFO("Writing \"%x\" to flash.", dumy_m_data);
#if 1
		rc = nrf_fstorage_write(&fstorage, 0x76000, &dumy_m_data, sizeof(dumy_m_data), NULL);
    APP_ERROR_CHECK(rc);
		wait_for_flash_ready2(&fstorage);
#endif
//		NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
	
//////// Read
		#if 0
//		    print_flash_info(&fstorage);
//	  (void) nrf5_flash_end_addr_get();
//NRF_LOG_INFO("Writing \"%x\" to flash.", dumy_m_data);
    //rc = nrf_fstorage_write(&fstorage, 0x76000, &dumy_m_data, sizeof(dumy_m_data), NULL);
		rc = nrf_fstorage_read(&fstorage, 0x76000, &dumy_m_read_data, sizeof(dumy_m_read_data));
    APP_ERROR_CHECK(rc);
		wait_for_flash_ready2(&fstorage);
		NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
		#endif
	
	
	
	// read ok
		uint8_t device_id[4];
		memcpy(device_id, (uint8_t *)0x3e010, 4);
		NRF_LOG_INFO("%x%x%x%x",device_id[0],device_id[1],device_id[2],device_id[3]);
		
		
	nrf_fstorage_uninit(&fstorage, NULL);
//----------------------------------------
}

void nvm_control_2(void)
{
		ret_code_t rc;
		NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
		nrf_fstorage_api_t * p_fs_api;
		p_fs_api = &nrf_fstorage_sd;
		rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
    APP_ERROR_CHECK(rc);

/////// Write
    print_flash_info(&fstorage);

		(void) nrf5_flash_end_addr_get();
		NRF_LOG_INFO("Writing \"%x\" to flash.", dumy_m_data);
#if 1
		//rc = nrf_fstorage_write(&fstorage, 0x76000, &dumy_m_data, sizeof(dumy_m_data), NULL);
		rc = nrf_fstorage_write(&fstorage, 0x77000, &dumy_m_data, sizeof(dumy_m_data), NULL);
    APP_ERROR_CHECK(rc);
		wait_for_flash_ready2(&fstorage);
#endif
//		NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
	
	// read ok
		uint8_t device_id[4];
		memcpy(device_id, (uint8_t *)0x3e010, 4);
		NRF_LOG_INFO("%x%x%x%x",device_id[0],device_id[1],device_id[2],device_id[3]);
		
		
	nrf_fstorage_uninit(&fstorage, NULL);
//----------------------------------------
}

void nvm_erase(uint8_t page_sel) //페이지 선택 1 또는 2 
{
		ret_code_t rc;
		nrf_fstorage_api_t * p_fs_api;
		p_fs_api = &nrf_fstorage_sd;
		rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
		APP_ERROR_CHECK(rc);
		//print_flash_info(&fstorage);
		(void) nrf5_flash_end_addr_get();
		rc = nrf_fstorage_erase(&fstorage, fstorage.start_addr+(4096*(page_sel-1)), 1, NULL);
		APP_ERROR_CHECK(rc);
		wait_for_flash_ready2(&fstorage);
		nrf_fstorage_uninit(&fstorage, NULL);
}

SAVE_INFO_T save_buf;

void nvm_total_save(void)
{
		SAVE_INFO_T move_buf;
		uint8_t move_buf2[4]={0x55,0xaa,0xbb,0xcc};
		uint8_t move_buf1[30]={0x55,0xaa,0xbb,0xcc};
		//0x76000 = BT ADDR
		//0x76100 = BT NAME
		//memcpy(&move_buf, &save_buf, sizeof(move_buf) ); // 데이터 복사
		
		//마지막 데이터가 오늘 날짜 인지 확인,
		//if( (move_buf[20].year == user_time.year) && (move_buf[20].month	== user_time.month) && (move_buf[20].day == user_time.day) ) // 같은날 저장 데이터가 있을때
		{
			printf("NVM started.\r\n");	
				/////// erase
				//nvm_erase(1);
			
			ret_code_t rc;
		nrf_fstorage_api_t * p_fs_api;
		p_fs_api = &nrf_fstorage_sd;
		rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
		APP_ERROR_CHECK(rc);
		//print_flash_info(&fstorage);
		(void) nrf5_flash_end_addr_get();
		rc = nrf_fstorage_erase(&fstorage, fstorage.start_addr, 1, NULL);
		APP_ERROR_CHECK(rc);
		wait_for_flash_ready2(&fstorage);
		//nrf_fstorage_uninit(&fstorage, NULL);
			
			
			
			printf("NVM erase.\r\n");
			#if 1
				/////// Write
//				ret_code_t rc;
				//NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
//				nrf_fstorage_api_t * p_fs_api;
				//p_fs_api = &nrf_fstorage_sd;
				//rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
				//APP_ERROR_CHECK(rc);

				(void) nrf5_flash_end_addr_get();
				
						//rc = nrf_fstorage_write(&fstorage, 0x76000, &dumy_m_data, sizeof(dumy_m_data), NULL);
						printf("NVM %x%x%x%x \r\n",save_buf.bd_save_name1[0],save_buf.bd_save_name1[1],save_buf.bd_save_name1[2],save_buf.bd_save_name1[3]);
						#if 1
						memcpy(&move_buf1, &save_buf.bd_save_name1, sizeof(move_buf2) ); // 데이터 복사
						memcpy(&move_buf1[4], &save_buf.bd_save_name2, sizeof(move_buf2) ); // 데이터 복사
						memcpy(&move_buf1[8], &save_buf.bd_save_name3, sizeof(move_buf2) ); // 데이터 복사
						memcpy(&move_buf1[12], &save_buf.bd_save_name_num, sizeof(move_buf2) ); // 데이터 복사
						//move_buf1
						//printf("NVM %x%x%x%x \r\n",move_buf2[0], move_buf2[1], move_buf2[2], move_buf2[3]);
						//rc = nrf_fstorage_write(&fstorage, 0x76000, &move_buf2 , sizeof(move_buf2)*2, NULL);
						rc = nrf_fstorage_write(&fstorage, 0x76000, &move_buf1, sizeof(move_buf2)*4, NULL);
						
						APP_ERROR_CHECK(rc);
						
						#if 0
						memcpy(&move_buf2, &save_buf.bd_save_name2, sizeof(move_buf2) ); // 데이터 복사
						rc = nrf_fstorage_write(&fstorage, 0x76000+4, &move_buf2 , sizeof(move_buf2), NULL);
						APP_ERROR_CHECK(rc);
						
						memcpy(&move_buf2, &save_buf.bd_save_name3, sizeof(move_buf2) ); // 데이터 복사
						rc = nrf_fstorage_write(&fstorage, 0x76000+8, &move_buf2 , sizeof(move_buf2), NULL);
						APP_ERROR_CHECK(rc);
						memcpy(&move_buf2, &save_buf.bd_save_name_num, sizeof(move_buf2) ); // 데이터 복사
						rc = nrf_fstorage_write(&fstorage, 0x76000+12, &move_buf2 , sizeof(move_buf2), NULL);
						APP_ERROR_CHECK(rc);
						#endif
						wait_for_flash_ready2(&fstorage);
				#endif
			#endif
			printf("NVM write\r\n");
			sd_nvic_SystemReset();
		}
		#if 0
		else            // 오래된 하루 데이터 삭제
		{
				move_buf[21].year 	= user_time.year;
				move_buf[21].month	= user_time.month;
				move_buf[21].day		= user_time.day;
				move_buf[21].cnt 		= 1; //user_time.tooth_cnt;
			
				/////// erase
				nvm_erase(1);
			
				/////// Write
				ret_code_t rc;
				//NRF_LOG_INFO("read %x",  dumy_m_read_data[0]);
				nrf_fstorage_api_t * p_fs_api;
				p_fs_api = &nrf_fstorage_sd;
				rc = nrf_fstorage_init(&fstorage, p_fs_api, NULL);
				APP_ERROR_CHECK(rc);

				(void) nrf5_flash_end_addr_get();
				#if 1
						rc = nrf_fstorage_write(&fstorage, 0x76000, &move_buf[1] , sizeof(move_buf)-sizeof(save_buf), NULL);
						APP_ERROR_CHECK(rc);
						wait_for_flash_ready2(&fstorage);
				#endif
		}
		#endif
		//NRF_LOG_INFO("%x %x %x %x",total_buf.uv_time ,total_buf.uv_auto_function_onoff, total_buf.now_uv_status, total_buf.now_music_status);
	
		printf("NVM uninit\r\n");
	

// read ok
		//memcpy(&total_buf, (uint8_t *)0x76000, sizeof(total_buf) ); //Write 이후 저장된 값 보여주기 위함
//		NRF_LOG_INFO("%x %x %x %x",total_buf.uv_time ,total_buf.uv_auto_function_onoff, total_buf.now_uv_status, total_buf.now_music_status);
		
		nrf_fstorage_uninit(&fstorage, NULL);
	
}

void nvm_time_read(void)
{
	#if 0
		user_time_type user_time_temp;  // 시간 구조체.
	
		memcpy(&user_time_temp, (uint8_t *)0x76000, sizeof(user_time_temp) );
	
		NRF_LOG_INFO("1 %d %d ", user_time_temp.am_pm, user_time_temp.hour_12_24);
		NRF_LOG_INFO("%d:%d %d:%d %d:%d", user_time_temp.alarm_1_hour, user_time_temp.alarm_1_min, 
								user_time_temp.alarm_2_hour, user_time_temp.alarm_2_min, 
								user_time_temp.alarm_3_hour, user_time_temp.alarm_3_min);
	
		if(user_time_temp.am_pm != 0xff && user_time_temp.hour != 0xff)
		{
			//memcpy(&user_time.am_pm, &user_time_temp.am_pm, sizeof(user_time_temp.am_pm) );
			memcpy(&user_time.hour_12_24 , &user_time_temp.hour_12_24, sizeof(user_time_temp.hour_12_24) );
			memcpy(&user_time.alarm_1_hour , &user_time_temp.alarm_1_hour , sizeof(user_time_temp.alarm_1_hour ) );
			memcpy(&user_time.alarm_1_min  , &user_time_temp.alarm_1_min  , sizeof(user_time_temp.alarm_1_min ) );
			memcpy(&user_time.alarm_2_hour , &user_time_temp.alarm_2_hour , sizeof(user_time_temp.alarm_2_hour ) );
			memcpy(&user_time.alarm_2_min  , &user_time_temp.alarm_2_min  , sizeof(user_time_temp.alarm_2_min ) );
			memcpy(&user_time.alarm_3_hour , &user_time_temp.alarm_3_hour , sizeof(user_time_temp.alarm_3_hour ) );
			memcpy(&user_time.alarm_3_min  , &user_time_temp.alarm_3_min  , sizeof(user_time_temp.alarm_3_min ) );
			
			NRF_LOG_INFO("2 %d %d ", user_time.am_pm, user_time.hour_12_24);
			NRF_LOG_INFO("%d:%d %d:%d %d:%d", user_time.alarm_1_hour, user_time.alarm_1_min, 
								user_time.alarm_2_hour, user_time.alarm_2_min, 
								user_time.alarm_3_hour, user_time.alarm_3_min);
		}
		 // 알람 시간 메모리에서 불러와야함. 만약에 데이터가 없어도 알람 값에 0xff 값을 넣어야됨.
		 #endif
}



