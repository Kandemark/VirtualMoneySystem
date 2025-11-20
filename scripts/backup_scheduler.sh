#!/bin/bash

# Backup Scheduler Script for VirtualMoneySystem
# Usage: ./backup_scheduler.sh
#
# This script creates a compressed backup of the 'database' and 'config' directories.
# It enforces a retention policy to keep backups for a configurable number of days.

set -euo pipefail

# --- Configuration ---
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BACKUP_DIR="${PROJECT_ROOT}/backups"
LOG_DIR="${PROJECT_ROOT}/logs"
LOG_FILE="${LOG_DIR}/backup_scheduler.log"
RETENTION_DAYS=7
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
BACKUP_FILENAME="vms_backup_${TIMESTAMP}.tar.gz"

# Directories to backup (relative to PROJECT_ROOT)
SOURCE_DIRS=("database" "config")

# --- Functions ---

# Ensure directories exist
setup_dirs() {
    mkdir -p "$BACKUP_DIR"
    mkdir -p "$LOG_DIR"
}

# Logging function
log() {
    local level="$1"
    local message="$2"
    local timestamp
    timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    echo "[${timestamp}] [${level}] ${message}" | tee -a "$LOG_FILE"
}

# Create backup
create_backup() {
    log "INFO" "Starting backup process..."
    
    local temp_backup_path="${BACKUP_DIR}/${BACKUP_FILENAME}"
    
    # Check if source directories exist
    local valid_sources=()
    for dir in "${SOURCE_DIRS[@]}"; do
        if [ -d "${PROJECT_ROOT}/${dir}" ]; then
            valid_sources+=("$dir")
        else
            log "WARN" "Source directory not found: ${dir}"
        fi
    done

    if [ ${#valid_sources[@]} -eq 0 ]; then
        log "ERROR" "No valid source directories found to backup. Aborting."
        exit 1
    fi

    # Create tarball
    # Using -C to change directory to PROJECT_ROOT so paths in archive are relative
    if tar -czf "$temp_backup_path" -C "$PROJECT_ROOT" "${valid_sources[@]}"; then
        log "INFO" "Backup created successfully: ${temp_backup_path}"
        
        # Calculate size
        local size
        size=$(du -h "$temp_backup_path" | cut -f1)
        log "INFO" "Backup size: ${size}"
    else
        log "ERROR" "Failed to create backup archive."
        exit 1
    fi
}

# Cleanup old backups
cleanup_old_backups() {
    log "INFO" "Checking for backups older than ${RETENTION_DAYS} days..."
    
    # Find and delete files in BACKUP_DIR older than RETENTION_DAYS matching the pattern
    # Note: -mtime +N means strictly greater than N days
    find "$BACKUP_DIR" -name "vms_backup_*.tar.gz" -type f -mtime +"$RETENTION_DAYS" -print0 | while IFS= read -r -d '' file; do
        if rm "$file"; then
            log "INFO" "Deleted old backup: $file"
        else
            log "ERROR" "Failed to delete old backup: $file"
        fi
    done
    
    log "INFO" "Cleanup complete."
}

# --- Main Execution ---

setup_dirs
log "INFO" "=== Backup Scheduler Started ==="

create_backup
cleanup_old_backups

log "INFO" "=== Backup Scheduler Finished ==="