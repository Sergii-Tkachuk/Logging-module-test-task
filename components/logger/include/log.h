#ifndef LOG_H
#define LOG_H

#define MT_LOG_LEVEL_OFF    (0)
#define MT_LOG_LEVEL_FATAL  (1)
#define MT_LOG_LEVEL_ERROR  (2)
#define MT_LOG_LEVEL_WARN   (3)
#define MT_LOG_LEVEL_INFO   (4)
#define MT_LOG_LEVEL_DEBUG  (5)
#define MT_LOG_LEVEL_TRACE  (6)

#define MOD_CFG_LOG_LEVEL   MT_LOG_LEVEL_TRACE
#define MOD_CFG_LOG_STR_END "\r\n"

// void log_send_message(const int LOG_LEVEL, const char *TAG, const char *FILE_NAME, const char *FUNCTION_NAME, const int FILE_LINE_NUMBER, char *log_message, ...);
int log_send_message(const int LOG_LEVEL, const char *TAG, char *log_message, ...);

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_TRACE
#define LOG_T(tag, message, ...) log_send_message(MT_LOG_LEVEL_TRACE, tag, message, ##__VA_ARGS__) 

#else
#define LOG_T(tag, message, ...)
#endif

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_DEBUG
#define LOG_D(tag, message, ...) log_send_message(MT_LOG_LEVEL_DEBUG, tag, message, ##__VA_ARGS__) 

#else
#define LOG_D(tag, message, ...)
#endif

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_INFO
#define LOG_I(tag, message, ...) log_send_message(MT_LOG_LEVEL_INFO, tag, message, ##__VA_ARGS__) 

#else
#define LOG_I(tag, message, ...)
#endif

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_WARN
#define LOG_W(tag, message, ...) log_send_message(MT_LOG_LEVEL_WARN, tag, message, ##__VA_ARGS__) 

#else
#define LOG_W(tag, message, ...)
#endif

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_ERROR
#define LOG_E(tag, message, ...) log_send_message(MT_LOG_LEVEL_ERROR, tag, ("%s-%s()-L:%d-" message), __FILE__, __func__, __LINE__, ##__VA_ARGS__) 

#else
#define LOG_E(tag, message, ...)
#endif

#if MOD_CFG_LOG_LEVEL >= MT_LOG_LEVEL_FATAL
#define LOG_F(tag, message, ...) log_send_message(MT_LOG_LEVEL_FATAL, tag, ("%s-%s()-L:%d-" message), __FILE__, __func__, __LINE__, ##__VA_ARGS__) 

#else
#define LOG_F(tag, message, ...)
#endif

#endif //LOG_H