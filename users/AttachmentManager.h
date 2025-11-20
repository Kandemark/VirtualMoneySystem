#ifndef ATTACHMENT_MANAGER_H
#define ATTACHMENT_MANAGER_H
#include <string>
#include <vector>
#include <map>

struct Attachment {
    std::string attachmentId;
    std::string userId;
    std::string filename;
    std::string contentType;
    size_t size;
    std::string filePath;
};

class AttachmentManager {
public:
    AttachmentManager(const std::string& storageDir);
    std::string uploadAttachment(const std::string& userId, const std::string& filename, const std::string& contentType, const std::vector<char>& data);
    Attachment getAttachment(const std::string& attachmentId) const;
    std::vector<Attachment> getUserAttachments(const std::string& userId) const;
    bool deleteAttachment(const std::string& attachmentId);

private:
    std::string storageDir;
    std::map<std::string, Attachment> attachments;
    std::string generateAttachmentId() const;
};

#endif
