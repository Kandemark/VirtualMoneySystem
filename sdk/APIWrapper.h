/**
 * @file APIWrapper.h
 * @brief High-level API wrapper for SDK
 */

#ifndef API_WRAPPER_H
#define API_WRAPPER_H

#include <string>
#include <map>

/**
 * @brief Simplified API wrapper
 */
class APIWrapper {
public:
    /**
     * @brief Make GET request
     * @param endpoint API endpoint
     * @param params Query parameters
     * @return Response string
     */
    std::string get(const std::string& endpoint, const std::map<std::string, std::string>& params = {});
    
    /**
     * @brief Make POST request
     * @param endpoint API endpoint
     * @param data Request body
     * @return Response string
     */
    std::string post(const std::string& endpoint, const std::string& data);
    
    /**
     * @brief Set authentication header
     * @param token Auth token
     */
    void setAuthToken(const std::string& token);

private:
    std::string authToken;
};

#endif
