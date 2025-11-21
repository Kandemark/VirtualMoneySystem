/**
 * @file PluginSandbox.h
 * @brief Secure sandbox for plugin execution
 */

#ifndef PLUGIN_SANDBOX_H
#define PLUGIN_SANDBOX_H

#include <string>

/**
 * @brief Provides isolated execution environment for plugins
 */
class PluginSandbox {
public:
    /**
     * @brief Execute plugin code in sandbox
     * @param pluginId Plugin to execute
     * @param code Code to execute
     * @return Execution result
     */
    std::string executeInSandbox(const std::string& pluginId, const std::string& code);
    
    /**
     * @brief Set resource limits for plugin
     * @param pluginId Plugin identifier
     * @param maxMemoryMB Maximum memory in MB
     * @param maxCPUPercent Maximum CPU percentage
     */
    void setResourceLimits(const std::string& pluginId, int maxMemoryMB, int maxCPUPercent);
    
    /**
     * @brief Terminate plugin execution
     * @param pluginId Plugin to terminate
     */
    void terminatePlugin(const std::string& pluginId);
};

#endif
