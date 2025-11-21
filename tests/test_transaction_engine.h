/**
 * @file test_transaction_engine.h
 * @brief Transaction engine test suite
 */

#ifndef TEST_TRANSACTION_ENGINE_H
#define TEST_TRANSACTION_ENGINE_H

void testTransactionCreation();
void testTransactionValidation();
void testTransactionRollback();
void testConcurrentTransactions();
void runAllTransactionEngineTests();

#endif
