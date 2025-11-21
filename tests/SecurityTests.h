/**
 * @file SecurityTests.h
 * @brief Security system tests
 */

#ifndef SECURITY_TESTS_H
#define SECURITY_TESTS_H

void testEncryption();
void testAuthentication();
void testAuthorization();
void testRateLimiting();
void testTwoFactorAuth();
void runAllSecurityTests();

#endif
