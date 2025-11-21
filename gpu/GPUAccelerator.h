/**
 * @file GPUAccelerator.h
 * @brief GPU acceleration for crypto operations
 */

#ifndef GPU_ACCELERATOR_H
#define GPU_ACCELERATOR_H

#include <vector>
#include <cstdint>

namespace VirtualMoney {

class GPUAccelerator {
public:
    GPUAccelerator();
    
    bool isAvailable() const;
    std::vector<uint8_t> hashBatch(const std::vector<std::vector<uint8_t>>& data);
    std::vector<uint8_t> encryptBatch(const std::vector<std::vector<uint8_t>>& data);
    bool validateBatch(const std::vector<double>& amounts);
    
    struct GPUStats {
        std::string deviceName;
        int computeUnits;
        size_t memoryMB;
        double utilizationPercent;
    };
    GPUStats getStats() const;
    
private:
    bool gpuAvailable;
};

} // namespace VirtualMoney

#endif
