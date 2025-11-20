#include "AttachmentManager.h"
#include <random>
#include <fstream>

AttachmentManager::AttachmentManager(const std::string& storageDir) : storageDir(storageDir) {}

std::string AttachmentManager::uploadAttachment(const std::string& userId, const std::string& filename, const std::string& contentType, const std::vector<char>& data) {
    std::string attachmentId = generateAttachmentId();
    Attachment att;
    att.attachmentId = attachmentId;
    att.userId = userId;
    att.filename = filename;
    att.contentType = contentType;
    att.size = data.size();
    att.filePath = storageDir + "/" + attachmentId;
    
    std::ofstream file(att.filePath, std::ios::binary);
    file.write(data.data(), data.size());
    file.close();
    
    attachments[attachmentId] = att;
    return attachmentId;
}

Attachment AttachmentManager::getAttachment(const std::string& attachmentId) const {
    return attachments.at(attachmentId);
}

std::vector<Attachment> AttachmentManager::getUserAttachments(const std::string& userId) const {
    std::vector<Attachment> result;
    for (const auto& [id, att] : attachments) {
        if (att.userId == userId) result.push_back(att);
    }
    return result;
}

bool AttachmentManager::deleteAttachment(const std::string& attachmentId) {
    return attachments.erase(attachmentId) > 0;
}

std::string AttachmentManager::generateAttachmentId() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char* hex = "0123456789abcdef";
    std::string id;
    for (int i = 0; i < 32; i++) id += hex[dis(gen)];
    return id;
}
