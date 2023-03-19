/**
 * @file NetworkTask.c
 * @author ryhoh
 * @brief Network task source file.
 * 
 */

// インクルード
#include "NetworkTask.h"

// 変数宣言
static uint8_t u8_network_setupstate = true;
static const char gscc_weekday[m_NETWORK_TASK_WEEKDAY_STR_SIZE] = "日月火水木金土";
static String gsstr_wifi_ssid = "";
// static String gsstr_time = "";
// static String gsstr_date = "";
// static String gsstr_lastMessage = "";

// 関数定義

/**
 * @brief ネットワークタスク初期化関数
 * @note 起動時に1回だけ実行される
 * 
 */
void Network_Task_Init(void) {
  // wip
  // ssid はNVMから読み込む
}

/**
 * @brief ネットワークタスクメイン関数
 * @note 320ms周期で実行される
 * 
 */
void Network_Task_Main(void) {
  static time_t t;
  static struct tm *tm;
  static int32_t last_mday = -1;
  uint8_t *pu8_is_network_setup_state = Get_SYSCTL_NetworkSetupState();

  if (u8_network_setupstate == 0) {
    /* Check Date,Time */
    if (last_mday == -1 || last_mday == tm->tm_mday) {  // Date changed
      // Routines which run only one time each day
      configTzTime("JST-9", "time.cloudflare.com", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
    }

    t = time(NULL);
    tm = localtime(&t);

    /* Clock */
    Network_Task_Clock(tm);

    /* Date */
    Network_Task_Date(tm);
    
    /* Message From StatusBoard */
    Network_Task_Message();

    *pu8_is_network_setup_state = m_OFF;  // ネットワークセットアップ完了
  }
}

/**
 * @brief 時刻設定関数
 * @note 320ms周期で実行される
 * 
 * @param tm 時刻構造体
 */
void Network_Task_Clock(const tm *tm) {
  char now_s[m_NETWORK_TASK_TIME_STR_SIZE] = "12:34:56";
  const uint8_t cu8_matrix_num = (uint8_t)(Get_VARIANT_MatrixNum() && 0x000000FF);
  DisplayInfo_t *pst_matrixLEDs_clock = GET_LED_Task_DisplayInfoClock();

  now_s[0] = '0' + tm->tm_hour / 10;
  now_s[1] = '0' + tm->tm_hour % 10;
  // now_s[2] = (tm->tm_sec % 2 != 0) ? ':' : ' ';  // 1秒おきにコロンを点滅
  now_s[3] = '0' + tm->tm_min / 10;
  now_s[4] = '0' + tm->tm_min % 10;
  now_s[6] = '0' + tm->tm_sec / 10;
  now_s[7] = '0' + tm->tm_sec % 10;

  pst_matrixLEDs_clock->str_to_display = String(now_s);
  pst_matrixLEDs_clock->u32_offset_from_left = m_NETWORK_TASK_TIME_LEFT_OFFSET;
}

/**
 * @brief 日付設定関数
 * @note 320ms周期で実行される
 * 
 * @param tm 時刻構造体
 */
void Network_Task_Date(const tm *tm) {
  static char date_s[m_NETWORK_TASK_DATE_STR_SIZE] = "11月11日(火)";
  const uint8_t cu8_matrix_num = (uint8_t)(Get_VARIANT_MatrixNum() && 0x000000FF);
  DisplayInfo_t *pst_matrixLEDs_date = GET_LED_Task_DisplayInfoDate();

  date_s[0] = ((tm->tm_mon+1) / 10 == 0) ? ' ' : '1';
  date_s[1] = '0' + ((tm->tm_mon+1) % 10);
  date_s[5] = (tm->tm_mday / 10 == 0) ? ' ' : '0' + (tm->tm_mday / 10);
  date_s[6] = '0' + (tm->tm_mday % 10);
  date_s[11] = gscc_weekday[tm->tm_wday * 3];  // utf-8 1文字分を3byteで
  date_s[12] = gscc_weekday[tm->tm_wday * 3 + 1];
  date_s[13] = gscc_weekday[tm->tm_wday * 3 + 2];

  pst_matrixLEDs_date->str_to_display = String(date_s);
  pst_matrixLEDs_date->u32_offset_from_left = m_NETWORK_TASK_DATE_LEFT_OFFSET;
}

/**
 * @brief メッセージ設定関数
 * @note 320ms周期で実行される
 * 
 */
void Network_Task_Message(void) {
  DisplayInfo_t *pst_matrixLEDs_msg = GET_LED_Task_DisplayInfoMsg();
  // statusClientOption = postStatusToBoard(myName);
  // if (!statusClientOption.skipped()) {
  //   lastMessage = statusClientOption.retval;
  //   lastMessage.replace("\n", " ");
  //   lastMessage.replace("\t", " ");
  //   lastMessage.replace("\r", " ");
  //   lastMessage.trim();
  // }
  pst_matrixLEDs_msg->str_to_display = "Hello world!";  // @@暫定
}

uint8_t GET_NetWork_Task_NetworkSetupState(void) {
  return u8_network_setupstate;
}

String GET_Network_WiFi_SSID(void) {
  return gsstr_wifi_ssid;
}

// String GET_Network_Task_Time(void) {
//   return gsstr_time;
// }

// String GET_Network_Task_Date(void) {
//   return gsstr_date;
// }

// String GET_Network_Task_LastMessage(void) {
//   return gsstr_lastMessage;
// }