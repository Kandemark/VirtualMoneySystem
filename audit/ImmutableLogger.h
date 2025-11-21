/**
 * @file ImmutableLogger.h
 * @brief Immutable append-only logging
 */

#ifndef IMMUTABLE_LOGGER_H
#define IMMUTABLE_LOGGER_H

#include <string>

/**
 * @brief Provides immutable append-only logging
 */
class ImmutableLogger {
public:
    /**
     * @brief Log entry (append-only)
     * @param level Log level
     * @param message Log message
     * @param metadata Additional metadata
     * @return Entry ID
     */
    std::string log(const std::string& level, const std::string& message, const std::string& metadata = "");
    
    /**
     * @brief Get log entry
     * @param entryId Entry identifier
     * @return Log entry content
     */
    std::string getEntry(const std::string& entryId);
    
    /**
     * @brief Seal log (make immutable)
     * @param logId Log identifier
     */
    void sealLog(const std::string& logId);

private:
    bool isSealed = false;
};

#endif
