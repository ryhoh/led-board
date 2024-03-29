// #ifndef _STATUS_CLIENT_H_
// #define _STATUS_CLIENT_H_

// #if defined ESP8266 || defined ESP32

// #include <Arduino.h>
// #include <stdint.h>

// #ifdef ESP8266
// #include <ESP8266WiFi.h>
// #elif defined ESP32
// #include <WiFi.h>
// #endif

// const int32_t INTERVAL_S = 30;

// enum StatusClientResult {
//   SUCCESS,
//   SKIP,
//   FAILURE_CONNECTION,
//   FAILURE_NTP_NOT_SYNC
// };

// struct StatusClientOption {
//   String retval;  ///< A value what we want to obtain with the function.
//   StatusClientResult result;  ///< SUCCESS or FAILURE

//   bool ok() {
//     return (result == StatusClientResult::SUCCESS || result == StatusClientResult::SKIP);
//   }

//   bool skipped() {
//     return result == StatusClientResult::SKIP;
//   }
// };

// /**
//  * @brief 自身の生存を Status-Board に伝える
//  * @param name [in] 自身を表すデバイス名
//  * @retval STATUS_CLIENT_STATUS_CODE 成功したかどうか
//  * @note ある程度時刻合わせをしてから呼び出すこと（NTPなどで）
// */
// StatusClientOption postStatusToBoard(String name);

// #endif  /* ESP8266 */
// #endif  /* _STATUS_CLIENT_H_ */
