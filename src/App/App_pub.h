/**
 * @file App_pub.h
 * @author ryhoh
 * @brief Public header for App.
 * 
 */

#ifndef _APP_PUB_H_
#define _APP_PUB_H_

// includes
#ifndef ARDUINO
#include <string>
typedef std::string String;
#endif  /* ARDUINO */

#include "App/led/AsciiMatrix.h"
#include "App/led/JISMatrix.h"
#include "App/led/Scroll.h"
#include "App/network/StatusClient.h"
#include "App/task/SystemControl.h"

// functions
void Main_Task(void);

#endif  /* _APP_PUB_H_ */
