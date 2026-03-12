#include "log.h"

const char *TAG = "APP_TASK";

void init_hardware(int conf)
{
    if (!conf)
    {
        LOG_E(TAG, "Config is enpty.");
        LOG_T(TAG, "Config = %d", conf);
    }
    
    LOG_I(TAG, "Start initialization");
    int val = -1;
    if (val == -1)
    {
        LOG_E("ERROR", "Something went wrong. Error code:%d", -1);
    }
}


void send_data(int i, char ch, const char *desc)
{
    LOG_D(TAG, "Integer = %d, Char = %c, Description: %s", i, ch, desc);
}


void app_main(void)
{
    LOG_I(0, 0);
    init_hardware(-1);

    send_data(8, 'f', "Send data.");
    int dsf;
    int err_code = -10;
    const char* err_desc_p = "Timeout error";
    LOG_E(TAG, "No response: %s(%d)", err_desc_p, err_code );

    LOG_T("TAG_TRACE", "Building C object");
    LOG_D("TAG_DEBUG", "Debug");
    LOG_I("TAG_INFO", "Message :%s", "message");
    LOG_W("TAG_WARNING", "unused variable 'dsf'");
    LOG_E("TAG_ERROR", "expected '%c' before '%c' token", ';', '}');
    LOG_F("FATAL_ERROR", "Core %d panic'ed (%s). Exception was unhandled.", 0, "LoadProhibited");
}