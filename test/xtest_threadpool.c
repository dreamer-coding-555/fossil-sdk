/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include <fossil/threads/threadpool.h> // library under test

#include <fossil/unittest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// placeholder

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Test case 1: Test fossil_thread_pool_create with valid parameters
FOSSIL_TEST(test_fossil_thread_pool_create_valid_params) {
    fossil_xthread_pool_t pool;
    ASSUME_ITS_EQUAL_I32(0, fossil_thread_pool_create(&pool, 4, 10));
}

// Test case 2: Test fossil_thread_pool_erase with valid parameters
FOSSIL_TEST(test_fossil_thread_pool_erase_valid_params) {
    fossil_xthread_pool_t pool;
    fossil_thread_pool_create(&pool, 4, 10); // Create a thread pool before erasing it
    ASSUME_ITS_EQUAL_I32(0, fossil_thread_pool_erase(&pool));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(poolthreads_group) {
    ADD_TEST(test_fossil_thread_pool_create_valid_params);
    ADD_TEST(test_fossil_thread_pool_erase_valid_params);
} // end of fixture
