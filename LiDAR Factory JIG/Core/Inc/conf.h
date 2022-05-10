#include "main.h"

#define PROTOCOL_HEADER 0xFAU
#define PRODUCT_LINE 0x00U
#define PRODUCT_ID 0xD0U
#define LIDAR_MODE 0x0FU
#define GUI_MODE 0xF0U
#define LIDAR_COMMAND_INFO 0x00U
#define LIDAR_COMMAND_START 0x01U
#define LIDAR_COMMAND_DETECT1 0x02U
#define LIDAR_COMMAND_DETECT2 0x03U
#define LIDAR_COMMAND_DETECT3 0x04U
#define GUI_COMMAND_CONNECT 0x00U
#define GUI_COMMAND_MODE 0x01U
#define GUI_COMMAND_ETHERNET 0x02U
#define GUI_COMMAND_APD_BIAS 0x03U
#define GUI_COMMAND_MOT_SPEED 0x04U
#define GUI_COMMAND_ENC_CHECK 0x05U
#define GUI_COMMAND_TDC_INIT 0x06U
#define GUI_COMMAND_TDC_CAL 0x07U
#define RX_BUFFER_SIZE 0x09U
