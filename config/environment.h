#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

// ================== Environment Selection ==================
// Uncomment the active environment
//#define ENVIRONMENT_DEVELOPMENT
//#define ENVIRONMENT_STAGING
#define ENVIRONMENT_PRODUCTION

// ================== Environment Check Macros ==================
#if defined(ENVIRONMENT_DEVELOPMENT)
    #define IS_DEVELOPMENT 1
#else
    #define IS_DEVELOPMENT 0
#endif

#if defined(ENVIRONMENT_STAGING)
    #define IS_STAGING 1
#else
    #define IS_STAGING 0
#endif

#if defined(ENVIRONMENT_PRODUCTION)
    #define IS_PRODUCTION 1
#else
    #define IS_PRODUCTION 0
#endif

// ================== Database Configuration ==================
#if IS_DEVELOPMENT
    #define DATABASE_HOST "localhost"
    #define DATABASE_PORT 5432
    #define DATABASE_USER "dev_user"
    #define DATABASE_PASSWORD "dev_password"
    #define DATABASE_NAME "evms_dev"
#elif IS_STAGING
    #define DATABASE_HOST "staging.db.server"
    #define DATABASE_PORT 5432
    #define DATABASE_USER "staging_user"
    #define DATABASE_PASSWORD "staging_password"
    #define DATABASE_NAME "evms_staging"
#elif IS_PRODUCTION
    #define DATABASE_HOST "prod.db.server"
    #define DATABASE_PORT 5432
    #define DATABASE_USER "prod_user"
    #define DATABASE_PASSWORD "prod_password"
    #define DATABASE_NAME "evms_prod"
#endif
#define DATABASE_POOL_SIZE 20
#define DATABASE_SSL_ENABLED 1
#define DATABASE_CONNECTION_TIMEOUT_MS 5000

// ================== API Endpoint Configuration ==================
#if IS_DEVELOPMENT
    #define API_BASE_URL "http://localhost:8080/api"
#elif IS_STAGING
    #define API_BASE_URL "https://staging.api.evms.com/api"
#elif IS_PRODUCTION
    #define API_BASE_URL "https://api.evms.com/api"
#endif
#define API_VERSION "v1"
#define API_HEALTHCHECK_ENDPOINT "/health"
#define API_STATUS_ENDPOINT "/status"

// ================== Cache Configuration ==================
#define CACHE_ENABLED 1
#define CACHE_TYPE_REDIS 1
#define CACHE_TYPE_MEMCACHED 2
#if IS_PRODUCTION
    #define CACHE_TYPE CACHE_TYPE_REDIS
    #define CACHE_HOST "prod.redis.evms.com"
    #define CACHE_PORT 6379
#elif IS_STAGING
    #define CACHE_TYPE CACHE_TYPE_REDIS
    #define CACHE_HOST "staging.redis.evms.com"
    #define CACHE_PORT 6379
#else
    #define CACHE_TYPE CACHE_TYPE_MEMCACHED
    #define CACHE_HOST "localhost"
    #define CACHE_PORT 11211
#endif
#define CACHE_DEFAULT_TTL_SECONDS 3600
#define CACHE_MAX_SIZE_MB 256

// ================== Email Server Configuration ==================
#if IS_PRODUCTION
    #define EMAIL_SMTP_SERVER "smtp.evms.com"
    #define EMAIL_SMTP_PORT 465
    #define EMAIL_USE_TLS 1
#elif IS_STAGING
    #define EMAIL_SMTP_SERVER "smtp.staging.evms.com"
    #define EMAIL_SMTP_PORT 465
    #define EMAIL_USE_TLS 1
#else
    #define EMAIL_SMTP_SERVER "localhost"
    #define EMAIL_SMTP_PORT 1025
    #define EMAIL_USE_TLS 0
#endif
#define EMAIL_FROM_ADDRESS "noreply@evms.com"
#define EMAIL_REPLY_TO_ADDRESS "support@evms.com"
#define EMAIL_MAX_RECIPIENTS 100

// ================== Security Settings ==================
#define PASSWORD_HASH_ALGORITHM "bcrypt"
#define PASSWORD_HASH_COST 12
#define SESSION_TIMEOUT_MINUTES 30
#define MAX_LOGIN_ATTEMPTS 5
#define ACCOUNT_LOCK_DURATION_MINUTES 15
#define ENABLE_2FA 1
#define ENABLE_EMAIL_VERIFICATION 1
#define ENABLE_PASSWORD_COMPLEXITY_CHECK 1

// ================== Feature Flags ==================
#define FEATURE_AUDIT_LOGS 1
#define FEATURE_API_RATE_LIMITING 1
#define FEATURE_ADVANCED_SECURITY 1
#define FEATURE_USER_TAGGING 1
#define FEATURE_EXPORT_USER_DATA 1
#define FEATURE_DARK_MODE 1
#define FEATURE_MULTI_LANGUAGE_UI 1

// ================== Secret Keys (Replace in Production) ==================
// NOTE: In production, load these securely from environment variables or a vault!
#define SECRET_API_KEY "replace_with_real_key"
#define SECRET_ENCRYPTION_KEY "replace_with_real_encryption_key"
#define SECRET_JWT_SIGNING_KEY "replace_with_real_jwt_key"
#define SECRET_SESSION_KEY "replace_with_real_session_key"

// ================== Logging Configuration ==================
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO  1
#define LOG_LEVEL_WARN  2
#define LOG_LEVEL_ERROR 3
#if IS_DEVELOPMENT
    #define LOG_LEVEL LOG_LEVEL_DEBUG
#elif IS_STAGING
    #define LOG_LEVEL LOG_LEVEL_INFO
#else
    #define LOG_LEVEL LOG_LEVEL_WARN
#endif
#define LOG_TO_FILE 1
#define LOG_TO_SYSLOG 0
#define LOG_TO_REMOTE 0
#define LOG_FILE_PATH "/var/log/evms/app.log"
#define LOG_MAX_FILE_SIZE_MB 10
#define LOG_BACKUP_COUNT 5
#define LOG_INCLUDE_TIMESTAMP 1
#define LOG_INCLUDE_THREAD_ID 1

// ================== API Pagination Defaults ==================
#define API_DEFAULT_PAGE_SIZE 25
#define API_MAX_PAGE_SIZE 100

// ================== Data Retention Policies ==================
#define DATA_RETENTION_USER_DAYS 730
#define DATA_RETENTION_LOGS_DAYS 90
#define DATA_RETENTION_AUDIT_DAYS 365
#define DATA_RETENTION_NOTIFICATIONS_DAYS 30

// ================== Search Configuration ==================
#define SEARCH_ENABLED 1
#define SEARCH_PROVIDER "internal"
#define SEARCH_INDEX_REFRESH_INTERVAL_MINUTES 15
#define SEARCH_MAX_RESULTS 1000

// ================== User Profile Settings ==================
#define USER_PROFILE_PICTURE_ENABLED 1
#define USER_PROFILE_MAX_BIO_LENGTH 500
#define USER_PROFILE_MAX_SOCIAL_LINKS 5

// ================== External Authentication Providers ==================
#define AUTH_GOOGLE_ENABLED 1
#define AUTH_FACEBOOK_ENABLED 0
#define AUTH_GITHUB_ENABLED 0
#define AUTH_MICROSOFT_ENABLED 0
#define AUTH_TWITTER_ENABLED 0

// ================== Feature Toggles for UI/UX Experiments ==================
#define FEATURE_NEW_DASHBOARD 0
#define FEATURE_BETA_ONBOARDING 0
#define FEATURE_SIDEBAR_NAVIGATION 1
#define FEATURE_INLINE_EDITING 1

// ================== Admin API Rate Limiting ==================
#define ADMIN_API_RATE_LIMIT 500 // requests per minute

// ================== Data Export/Import ==================
#define DATA_EXPORT_ENABLED 1
#define DATA_IMPORT_ENABLED 1
#define DATA_EXPORT_FORMATS "csv,json"
#define DATA_IMPORT_FORMATS "csv,json"
#define DATA_EXPORT_MAX_SIZE_MB 50

// ================== Custom Branding ==================
#define BRANDING_LOGO_PATH "/assets/logo.png"
#define BRANDING_PRIMARY_COLOR "#0057B8"
#define BRANDING_SECONDARY_COLOR "#FFD700"
#define BRANDING_FAVICON_PATH "/assets/favicon.ico"

// ================== Geo-Restrictions ==================
#define GEO_RESTRICTIONS_ENABLED 0
#define GEO_ALLOWED_COUNTRIES "US,CA,GB,DE"
#define GEO_BLOCKED_COUNTRIES "CN,RU,IR,CU,SD,SY,KR"

// ================== License Management ==================
#define LICENSE_TYPE "enterprise"
#define LICENSE_EXPIRY_DATE "2025-12-31"
#define LICENSE_MAX_USERS 1000

// ================== Maintenance Mode ==================
#define MAINTENANCE_MODE 0 // Set to 1 to enable maintenance mode
#define MAINTENANCE_MESSAGE "Scheduled maintenance in progress. Please try again later."

// ================== Monitoring & Metrics ==================
#define MONITORING_ENABLED 1
#define MONITORING_PROVIDER_PROMETHEUS 1
#define MONITORING_PROVIDER_DATADOG 2
#define MONITORING_PROVIDER MONITORING_PROVIDER_PROMETHEUS
#define MONITORING_ENDPOINT "/metrics"
#define MONITORING_ALERT_EMAIL "alerts@evms.com"
#define MONITORING_HEARTBEAT_INTERVAL_SECONDS 60

// ================== Backup Configuration ==================
#define BACKUP_ENABLED 1
#define BACKUP_SCHEDULE_CRON "0 2 * * *" // Every day at 2 AM
#define BACKUP_RETENTION_DAYS 14
#define BACKUP_LOCATION "/var/backups/evms"
#define BACKUP_ENCRYPTION_ENABLED 1
#define BACKUP_REMOTE_UPLOAD_ENABLED 0

// ================== File Storage Configuration ==================
#define FILE_STORAGE_LOCAL 1
#define FILE_STORAGE_S3 2
#if IS_PRODUCTION
    #define FILE_STORAGE_TYPE FILE_STORAGE_S3
    #define FILE_STORAGE_BUCKET "evms-prod-bucket"
    #define FILE_STORAGE_REGION "us-east-1"
    #define FILE_STORAGE_ENCRYPTION_ENABLED 1
#else
    #define FILE_STORAGE_TYPE FILE_STORAGE_LOCAL
    #define FILE_STORAGE_PATH "./uploads"
    #define FILE_STORAGE_ENCRYPTION_ENABLED 0
#endif
#define FILE_STORAGE_MAX_SIZE_MB 1024

// ================== Payment Gateway Configuration ==================
#define PAYMENT_GATEWAY_STRIPE 1
#define PAYMENT_GATEWAY_PAYPAL 2
#if IS_PRODUCTION
    #define PAYMENT_GATEWAY PAYMENT_GATEWAY_STRIPE
    #define PAYMENT_GATEWAY_API_KEY "prod_stripe_api_key"
#elif IS_STAGING
    #define PAYMENT_GATEWAY PAYMENT_GATEWAY_STRIPE
    #define PAYMENT_GATEWAY_API_KEY "staging_stripe_api_key"
#else
    #define PAYMENT_GATEWAY PAYMENT_GATEWAY_PAYPAL
    #define PAYMENT_GATEWAY_API_KEY "dev_paypal_api_key"
#endif
#define PAYMENT_CURRENCY "USD"
#define PAYMENT_MAX_AMOUNT 10000

// ================== Internationalization (i18n) ==================
#define SUPPORTED_LANGUAGES "en,es,fr,de"
#define DEFAULT_LANGUAGE "en"
#define I18N_FALLBACK_LANGUAGE "en"
#define I18N_AUTO_DETECT 1

// ================== Rate Limiting ==================
#define GLOBAL_RATE_LIMIT 1000 // requests per minute
#define USER_RATE_LIMIT 100    // requests per minute per user
#define RATE_LIMIT_BURST 200

// ================== Internal Scheduler ==================
// Enables/disables the built-in task scheduler for periodic jobs
#define INTERNAL_SCHEDULER_ENABLED 1
#define SCHEDULER_MAX_CONCURRENT_JOBS 10
#define SCHEDULER_JOB_RETRY_LIMIT 3

// ================== Notification System ==================
// Built-in notification channels (email, SMS, in-app)
#define NOTIFICATION_EMAIL_ENABLED 1
#define NOTIFICATION_SMS_ENABLED 0
#define NOTIFICATION_INAPP_ENABLED 1
#define NOTIFICATION_RETRY_LIMIT 3
#define NOTIFICATION_PUSH_ENABLED 1
#define NOTIFICATION_WEBHOOK_ENABLED 1
#define NOTIFICATION_WEBHOOK_RETRY_LIMIT 5

// ================== Session Management ==================
#define SESSION_RENEWAL_ENABLED 1
#define SESSION_RENEWAL_INTERVAL_MINUTES 10
#define SESSION_COOKIE_SECURE 1
#define SESSION_COOKIE_HTTPONLY 1
#define SESSION_COOKIE_SAMESITE "Strict"
#define SESSION_COOKIE_DOMAIN ".evms.com"

// ================== API Security ==================
#define API_KEY_REQUIRED 1
#define API_KEY_HEADER "X-API-KEY"
#define API_CORS_ENABLED 1
#define API_CORS_ALLOWED_ORIGINS "*"
#define API_CSRF_PROTECTION_ENABLED 1
#define API_THROTTLE_BURST 200
#define API_ALLOWED_IPS ""

// ================== Reporting & Analytics ==================
#define REPORTING_ENABLED 1
#define REPORT_GENERATION_SCHEDULE_CRON "0 3 * * *"
#define ANALYTICS_ENABLED 1
#define ANALYTICS_PROVIDER "internal"
#define ANALYTICS_RETENTION_DAYS 365
#define ANALYTICS_EXPORT_ENABLED 1

// ================== Blockchain Integration ==================
#define BLOCKCHAIN_ENABLED 0
#define BLOCKCHAIN_PROVIDER "none"
#define BLOCKCHAIN_NETWORK "mainnet"
#define BLOCKCHAIN_WALLET_ADDRESS ""
#define BLOCKCHAIN_EXPLORER_URL ""

// ================== Mobile Integration ==================
#define MOBILE_PUSH_NOTIFICATIONS_ENABLED 1
#define MOBILE_APP_VERSION_MIN "1.0.0"
#define MOBILE_APP_VERSION_LATEST "1.2.0"
#define MOBILE_DEEP_LINKING_ENABLED 1

// ================== Webhooks ==================
#define WEBHOOKS_ENABLED 1
#define WEBHOOKS_MAX_CONCURRENT 10
#define WEBHOOKS_SIGNATURE_SECRET "replace_with_webhook_secret"
#define WEBHOOKS_TIMEOUT_SECONDS 10

// ================== Sandbox & Testing ==================
#define SANDBOX_MODE_ENABLED 0
#define TEST_USER_EMAIL "test@evms.com"
#define TEST_API_KEY "test_api_key"
#define TEST_MODE_VERBOSE_LOGGING 1

// ================== Legal & Compliance ==================
#define TERMS_VERSION "2024-01"
#define PRIVACY_POLICY_VERSION "2024-01"
#define KYC_REQUIRED 1
#define AML_CHECKS_ENABLED 1
#define GDPR_COMPLIANCE_ENABLED 1

// ================== Support & Feedback ==================
#define SUPPORT_EMAIL "support@evms.com"
#define FEEDBACK_ENABLED 1
#define FEEDBACK_STORAGE "internal"
#define FEEDBACK_MAX_LENGTH 2000

// ================== Disaster Recovery ==================
#define DISASTER_RECOVERY_ENABLED 1
#define DR_BACKUP_LOCATION "/dr/backups"
#define DR_CONTACT_EMAIL "dr@evms.com"
#define DR_FAILOVER_ENABLED 1

// ================== Multi-Tenancy ==================
#define MULTI_TENANCY_ENABLED 0
#define MAX_TENANTS 1
#define TENANT_ISOLATION_LEVEL "database"

// ================== Localization ==================
#define TIME_FORMAT_24H 1
#define DATE_FORMAT_ISO 1
#define LOCALE_DEFAULT "en_US"

// ================== Accessibility ==================
#define ACCESSIBILITY_MODE_ENABLED 1
#define ACCESSIBILITY_FONT_SIZE "medium"

// ================== API Documentation ==================
#define API_DOCS_ENABLED 1
#define API_DOCS_URL "/docs"
#define API_DOCS_VERSION "1.0.0"

// ================== Third-Party Integrations ==================
#define THIRD_PARTY_INTEGRATIONS_ENABLED 1
#define INTEGRATION_MAX_ACTIVE 10
#define INTEGRATION_SLACK_ENABLED 0
#define INTEGRATION_ZENDESK_ENABLED 0

// ================== Resource Quotas ==================
#define STORAGE_QUOTA_PER_USER_MB 1024
#define API_QUOTA_PER_USER_PER_DAY 10000
#define MAX_CONCURRENT_SESSIONS_PER_USER 5

// ================== Scheduled Maintenance ==================
#define SCHEDULED_MAINTENANCE_ENABLED 0
#define SCHEDULED_MAINTENANCE_WINDOW "Sunday 02:00-03:00 UTC"

// ================== System Flags ==================
#define SYSTEM_READ_ONLY_MODE 0
#define SYSTEM_DEPRECATED 0
#define SYSTEM_SELF_DESTRUCT_ENABLED 0

// ================== Miscellaneous ==================
#define ENABLE_DEBUG_TOOLS 0
#define ENABLE_BETA_FEATURES 0
#define ENABLE_EXPERIMENTAL_APIS 0

// ================== Build & Version Info ==================
#define SYSTEM_VERSION "1.0.0"
#define SYSTEM_BUILD_DATE __DATE__
#define SYSTEM_BUILD_TIME __TIME__
#define SYSTEM_COMMIT_HASH "unknown"

// ================== Documentation & Maintenance ==================
// To add new environments, define ENVIRONMENT_<NAME> and update all relevant sections.
// Secrets should be loaded securely in production (e.g., from environment variables or a vault).
// All configuration macros should be documented for clarity and maintainability.
// For further customization, extend this file as needed for your deployment.

#endif // ENVIRONMENT_H
