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
#include "fossil/string/wstring.h" // for the cstring types
#include "fossil/string/common.h"   // for the common types

#include <fossil/xtest.h>   // basic test tools
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

XTEST(test_fossil_wstr_create) {
    const_wstring test_str = L"Hello, World!";
    wstring copy_str = fossil_wstr_create(test_str);
    
    TEST_ASSUME_NOT_CNULLPTR(copy_str);
    // TEST_ASSUME_EQUAL_CSTRING(test_str, copy_str); // in need of new assert in Xtest for wstring

    fossil_wstr_erase(copy_str);
}

XTEST(test_fossil_wstr_create_null) {
    const_wstring test_str = cnullptr;
    wstring copy_str = fossil_wstr_create(test_str);
    
    TEST_ASSUME_CNULLPTR(copy_str);
}

XTEST(test_fossil_wstr_erase) {
    const_wstring test_str = L"Hello, World!";
    wstring copy_str = fossil_wstr_create(test_str);
    
    fossil_wstr_erase(copy_str);
    
    // If memory is correctly deallocated, the program should not crash.
    // Let's assert that the pointer is null after erasing.
    TEST_ASSUME_CNULLPTR(copy_str);
}

XTEST(test_fossil_wstr_length) {
    const_wstring test_str = L"Hello, World!";
    size_t len = fossil_wstr_length(test_str);
    
    TEST_ASSUME_EQUAL_INT(13, len);

    const_wstring empty_str = L"";
    size_t empty_len = fossil_wstr_length(empty_str);
    
    TEST_ASSUME_EQUAL_INT(0, empty_len);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
XTEST_DEFINE_POOL(fossil_wstring_group) {
    XTEST_RUN_UNIT(test_fossil_wstr_create);
    XTEST_RUN_UNIT(test_fossil_wstr_create_null);
    XTEST_RUN_UNIT(test_fossil_wstr_erase);
    XTEST_RUN_UNIT(test_fossil_wstr_length);
} // end of function main