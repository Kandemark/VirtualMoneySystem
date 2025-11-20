CREATE TABLE IF NOT EXISTS Wallets (
    userId TEXT PRIMARY KEY,
    currency TEXT NOT NULL,
    balance REAL NOT NULL DEFAULT 0.0
);

CREATE TABLE IF NOT EXISTS Transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    senderId TEXT NOT NULL,
    receiverId TEXT NOT NULL,
    amount REAL NOT NULL,
    currency TEXT NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(senderId) REFERENCES Wallets(userId),
    FOREIGN KEY(receiverId) REFERENCES Wallets(userId)
);
