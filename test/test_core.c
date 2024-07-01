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
#include <fossil/core/arguments.h>
#include <fossil/core/bitwise.h>
#include <fossil/core/command.h>
#include <fossil/core/datetime.h>
#include <fossil/core/filesystem.h>
#include <fossil/core/bluecrab.h>
#include <fossil/core/hostsystem.h>
#include <fossil/core/memory.h>
#include <fossil/core/money.h>
#include <fossil/core/random.h>
#include <fossil/core/regex.h>
#include <fossil/core/smartptr.h>

#include <fossil/unittest.h> // basic test tools
#include <fossil/xassume.h>  // extra asserts

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Function to read the content of a file
char* read_file_content(const char* file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        return cnullptr;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = malloc(length + 1);
    if (content) {
        size_t read_length = fread(content, 1, length, file);
        content[read_length] = '\0'; // Ensure null termination
    }

    fclose(file);
    return content;
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test command line interface
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_cli_fixture);

FOSSIL_SETUP(core_cli_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_cli_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_fossil_arg_parse_has) {
    // Test fossil_arg_parse_has function
    fossil_option_t options[] = {
        {"option1", COPTION_TYPE_BOOL, {.bool_val = 0}, cnull, 0, 0},
        {"option2", COPTION_TYPE_INT, {.int_val = 42}, cnull, 0, 0}
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Assuming fossil_arg_parse_has returns 1 for the existing option
    ASSUME_ITS_EQUAL_I32(0, fossil_arg_parse_has(options, num_options, "option1"));
}

FOSSIL_TEST(test_fossil_arg_parse) {
    // Test fossil_arg_parse function
    const char* argv[] = {"program", "-number", "42", "-name", "John", "-flag", "-choice", "choice2", "-feature", "enable"};
    const int argc = sizeof(argv) / sizeof(argv[0]);

    fossil_command_line_t cmd = {argc, (char **)argv};
    
    fossil_option_t options[] = {
        {"option1", COPTION_TYPE_INT, {.int_val = 0}, cnull, 0, 0},
        {"option2", COPTION_TYPE_BOOL, {.bool_val = 0}, cnull, 0, 0}
    };
    int num_options = sizeof(options) / sizeof(options[0]);

    // Assuming fossil_arg_parse modifies the options array
    fossil_arg_parse(&cmd, options, num_options);

    ASSUME_ITS_EQUAL_I32(0, options[0].value.int_val);
    ASSUME_ITS_EQUAL_I32(0, options[1].value.bool_val);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test bitwise operations
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_bitwise_fixture);

FOSSIL_SETUP(core_bitwise_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_bitwise_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_fossil_binary_and) {
    // 8-bit AND
    ASSUME_ITS_EQUAL_U8(0x01, fossil_binary_and8(0x0F, 0x01));
    
    // 16-bit AND
    ASSUME_ITS_EQUAL_U16(0x0001, fossil_binary_and16(0x00FF, 0x0001));
    
    // 32-bit AND
    ASSUME_ITS_EQUAL_U32(0x00000001, fossil_binary_and(0x0000000F, 0x00000001));
    
    // 64-bit AND
    ASSUME_ITS_EQUAL_U64(0x0000000000000001, fossil_binary_and64(0x00000000000000FF, 0x0000000000000001));
}

FOSSIL_TEST(test_fossil_binary_or) {
    // 8-bit OR
    ASSUME_ITS_EQUAL_U8(0x0F, fossil_binary_or8(0x0F, 0x01));
    
    // 16-bit OR
    ASSUME_ITS_EQUAL_U16(0x00FF, fossil_binary_or16(0x00FF, 0x0001));
    
    // 32-bit OR
    ASSUME_ITS_EQUAL_U32(0x0000000F, fossil_binary_or(0x0000000F, 0x00000001));
    
    // 64-bit OR
    ASSUME_ITS_EQUAL_U64(0x00000000000000FF, fossil_binary_or64(0x00000000000000FF, 0x0000000000000001));
}

FOSSIL_TEST(test_fossil_binary_xor) {
    // 8-bit XOR
    ASSUME_ITS_EQUAL_U8(0x0E, fossil_binary_xor8(0x0F, 0x01));
    
    // 16-bit XOR
    ASSUME_ITS_EQUAL_U16(0x00FE, fossil_binary_xor16(0x00FF, 0x0001));
    
    // 32-bit XOR
    ASSUME_ITS_EQUAL_U32(0x0000000E, fossil_binary_xor(0x0000000F, 0x00000001));
    
    // 64-bit XOR
    ASSUME_ITS_EQUAL_U64(0x00000000000000FE, fossil_binary_xor64(0x00000000000000FF, 0x0000000000000001));
}

FOSSIL_TEST(test_fossil_binary_left_shift) {
    // 8-bit Left Shift
    ASSUME_ITS_EQUAL_U8(0x1E, fossil_binary_left_shift8(0x0F, 1));
    
    // 16-bit Left Shift
    ASSUME_ITS_EQUAL_U16(0x0002, fossil_binary_left_shift16(0x0001, 1));
    
    // 32-bit Left Shift
    ASSUME_ITS_EQUAL_U32(0x0000001E, fossil_binary_left_shift(0x0000000F, 1));
    
    // 64-bit Left Shift
    ASSUME_ITS_EQUAL_U64(0x00000000000000FE, fossil_binary_left_shift64(0x000000000000007F, 1));
}

FOSSIL_TEST(test_fossil_binary_right_shift) {
    // 8-bit Right Shift
    ASSUME_ITS_EQUAL_U8(0x07, fossil_binary_right_shift8(0x0F, 1));
    
    // 16-bit Right Shift
    ASSUME_ITS_EQUAL_U16(0x0000, fossil_binary_right_shift16(0x0001, 1));
    
    // 32-bit Right Shift
    ASSUME_ITS_EQUAL_U32(0x00000007, fossil_binary_right_shift(0x0000000F, 1));
    
    // 64-bit Right Shift
    ASSUME_ITS_EQUAL_U64(0x000000000000003F, fossil_binary_right_shift64(0x000000000000007F, 1));
}

FOSSIL_TEST(test_fossil_binary_toggle_bits) {
    // 8-bit Toggle Bits
    ASSUME_ITS_EQUAL_U8(0xF0, fossil_binary_toggle_bits8(0x0F));
    
    // 16-bit Toggle Bits
    ASSUME_ITS_EQUAL_U16(0xFF00, fossil_binary_toggle_bits16(0x00FF));
    
    // 32-bit Toggle Bits
    ASSUME_ITS_EQUAL_U32(0xFFFFFFF0, fossil_binary_toggle_bits(0x0000000F));
    
    // 64-bit Toggle Bits
    ASSUME_ITS_EQUAL_U64(0xFFFFFFFFFFFFFFF0, fossil_binary_toggle_bits64(0x000000000000000F));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test host system
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_hostsystem_fixture);

FOSSIL_SETUP(core_hostsystem_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_hostsystem_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_fossil_hostsys_get) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_NOT_EQUAL_CSTR("", info.os_name);
    ASSUME_NOT_EQUAL_CSTR("", info.os_version);
    ASSUME_NOT_EQUAL_CSTR("", info.cpu_model);
    ASSUME_ITS_MORE_OR_EQUAL_I32(0, info.free_memory);
    ASSUME_ITS_MORE_OR_EQUAL_I32(0, info.total_memory);
}

FOSSIL_TEST(test_fossil_hostsys_endian) {
    fossil_hostsystem_t info;
    fossil_hostsys_get(&info);
    ASSUME_ITS_EQUAL_CSTR(fossil_hostsys_endian(&info), info.is_big_endian ? "Big Endian" : "Little Endian");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test memory
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_memory_fixture);

FOSSIL_SETUP(core_memory_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_memory_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_memory_alloc) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);
    fossil_memory_free(ptr); // Cleanup
}

FOSSIL_TEST(test_memory_realloc) {
    size_t size = 10;
    fossil_memory_t ptr = fossil_memory_alloc(size);
    ASSUME_NOT_CNULL(ptr);

    size *= 2;
    ptr = fossil_memory_realloc(ptr, size);
    ASSUME_NOT_CNULL(ptr);

    fossil_memory_free(ptr); // Cleanup
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test money
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_money_fixture);

FOSSIL_SETUP(core_money_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_money_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_money_create) {
    fossil_money_t m = fossil_money_create(10, 50, USD);
    ASSUME_ITS_EQUAL_I32(10, m.dollars);
    ASSUME_ITS_EQUAL_I32(50, m.cents);
    ASSUME_ITS_EQUAL_I32(USD, m.currency);
}

FOSSIL_TEST(test_money_add) {
    fossil_money_t m1 = fossil_money_create(10, 50, USD);
    fossil_money_t m2 = fossil_money_create(5, 25, USD);
    fossil_money_t result = fossil_money_add(m1, m2);
    ASSUME_ITS_EQUAL_I32(15, result.dollars);
    ASSUME_ITS_EQUAL_I32(75, result.cents);
    ASSUME_ITS_EQUAL_I32(USD, result.currency);
}

FOSSIL_TEST(test_money_convert) {
    fossil_money_t source = fossil_money_create(10, 50, USD);
    fossil_money_t result = fossil_money_convert(source, CAD);
    ASSUME_ITS_EQUAL_I32(10, result.dollars);
    ASSUME_ITS_EQUAL_I32(50, result.cents);
    ASSUME_ITS_EQUAL_I32(CAD, result.currency);
}

FOSSIL_TEST(test_money_is_valid) {
    fossil_money_t m = fossil_money_create(10, 50, USD);
    ASSUME_ITS_TRUE(fossil_money_is_valid(m));
}

FOSSIL_TEST(test_money_compare) {
    fossil_money_t m1 = fossil_money_create(10, 50, USD);
    fossil_money_t m2 = fossil_money_create(5, 25, USD);
    ASSUME_ITS_EQUAL_I32(1, fossil_money_compare(m1, m2));
}

FOSSIL_TEST(test_money_subtract) {
    fossil_money_t m1 = fossil_money_create(10, 50, USD);
    fossil_money_t m2 = fossil_money_create(5, 25, USD);
    fossil_money_t result = fossil_money_subtract(m1, m2);
    ASSUME_ITS_EQUAL_I32(5, result.dollars);
    ASSUME_ITS_EQUAL_I32(25, result.cents);
    ASSUME_ITS_EQUAL_I32(USD, result.currency);
}

FOSSIL_TEST(test_money_multiply_scalar) {
    fossil_money_t m = fossil_money_create(10, 50, USD);
    fossil_money_t result = fossil_money_multiply_scalar(m, 2);
    ASSUME_ITS_EQUAL_I32(21, result.dollars);
    ASSUME_ITS_EQUAL_I32(0, result.cents);
    ASSUME_ITS_EQUAL_I32(USD, result.currency);
}

FOSSIL_TEST(test_money_divide_scalar) {
    fossil_money_t m = fossil_money_create(10, 50, USD);
    fossil_money_t result = fossil_money_divide_scalar(m, 2);
    ASSUME_ITS_EQUAL_I32(5, result.dollars);
    ASSUME_ITS_EQUAL_I32(25, result.cents);
    ASSUME_ITS_EQUAL_I32(USD, result.currency);
}

FOSSIL_TEST(test_money_round) {
    fossil_money_t m = fossil_money_create(10, 55, USD);
    fossil_money_t result = fossil_money_round(m);
    ASSUME_ITS_EQUAL_I32(10, result.dollars);
    ASSUME_ITS_EQUAL_I32(55, result.cents);
    ASSUME_ITS_EQUAL_I32(USD, result.currency);
}

FOSSIL_TEST(test_money_is_positive) {
    fossil_money_t m = fossil_money_create(10, 50, USD);
    ASSUME_ITS_TRUE(fossil_money_is_positive(m));
}

FOSSIL_TEST(test_money_is_zero) {
    fossil_money_t m = fossil_money_create(0, 0, USD);
    ASSUME_ITS_TRUE(fossil_money_is_zero(m));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test random
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_random_fixture);

FOSSIL_SETUP(core_random_fixture) {
    // Setup code if needed
}

FOSSIL_TEARDOWN(core_random_fixture) {
    // Teardown code if needed
}

FOSSIL_TEST(test_fossil_random_seed) {
    fossil_random_t rng;
    uint32_t seed = 12345;
    fossil_random_seed(&rng, seed);
    ASSUME_ITS_EQUAL_U32(seed, rng.current_seed);
}

FOSSIL_TEST(test_fossil_random_uint32) {
    fossil_random_t rng;
    fossil_random_seed(&rng, 12345);
    uint32_t value = fossil_random_uint32(&rng);
    ASSUME_ITS_LESS_THAN_U32(65536, value);
}

FOSSIL_TEST(test_fossil_random_uint64) {
    fossil_random_t rng;
    fossil_random_seed(&rng, 12345);
    uint64_t value = fossil_random_uint64(&rng);
    ASSUME_ITS_LESS_THAN_U32(65536, value);
}

FOSSIL_TEST(test_fossil_random_int_range) {
    fossil_random_t rng;
    fossil_random_seed(&rng, 12345);
    fossil_random_int_range(&rng, 0, 10);
    ASSUME_ITS_LESS_THAN_U32(10, rng.current_seed);
}

FOSSIL_TEST(test_fossil_random_float) {
    fossil_random_t rng;
    fossil_random_seed(&rng, 12345);
    float value = fossil_random_float(&rng);
    ASSUME_ITS_TRUE(value >= 0.0f && value < 1.0f); // Check if value is between 0 and 1
}

FOSSIL_TEST(test_fossil_random_double) {
    fossil_random_t rng;
    fossil_random_seed(&rng, 12345);
    double value = fossil_random_double(&rng);
    ASSUME_ITS_TRUE(value >= 0.0 && value < 1.0); // Check if value is between 0 and 1
}

FOSSIL_TEST(test_fossil_random_yield_seed) {
    uint32_t seed = fossil_random_yield_seed();
    // Since seed is based on time and other factors, just check if it's non-zero
    ASSUME_NOT_EQUAL_I32(0, seed);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Blue CrabDB
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_FIXTURE(core_crabdb_fixture);
fossil_crabdb_t *db = cnullptr;

FOSSIL_SETUP(core_crabdb_fixture) {
    db = fossil_crabdb_create();
}

FOSSIL_TEARDOWN(core_crabdb_fixture) {
    fossil_crabdb_erase(db);
}

FOSSIL_TEST(test_create_namespace) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_error_t result = fossil_crabdb_create_namespace(db, "namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);
}

FOSSIL_TEST(test_insert_and_get_value) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");

    fossil_crabdb_error_t result = fossil_crabdb_insert(db, "namespace1", "key1", "value1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    char *value = NULL;
    result = fossil_crabdb_get(db, "namespace1", "key1", &value);
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);
    ASSUME_ITS_EQUAL_CSTR("value1", value);

    free(value);
}

FOSSIL_TEST(test_update_value) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");

    fossil_crabdb_insert(db, "namespace1", "key1", "value1");

    fossil_crabdb_error_t result = fossil_crabdb_update(db, "namespace1", "key1", "value2");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    char *value = NULL;
    result = fossil_crabdb_get(db, "namespace1", "key1", &value);
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);
    ASSUME_ITS_EQUAL_CSTR("value2", value);

    free(value);
}

FOSSIL_TEST(test_delete_value) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");

    fossil_crabdb_insert(db, "namespace1", "key1", "value1");

    fossil_crabdb_error_t result = fossil_crabdb_delete(db, "namespace1", "key1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    char *value = xnull;
    result = fossil_crabdb_get(db, "namespace1", "key1", &value);
    ASSUME_ITS_EQUAL_I32(CRABDB_ERR_KEY_NOT_FOUND, result);
}

FOSSIL_TEST(test_create_sub_namespace) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");

    fossil_crabdb_error_t result = fossil_crabdb_create_sub_namespace(db, "namespace1", "sub_namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    result = fossil_crabdb_create_sub_namespace(db, "namespace1", "sub_namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_ERR_SUB_NS_EXISTS, result);
}

FOSSIL_TEST(test_erase_namespace) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");

    fossil_crabdb_error_t result = fossil_crabdb_erase_namespace(db, "namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    result = fossil_crabdb_erase_namespace(db, "namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_ERR_NS_NOT_FOUND, result);
}

FOSSIL_TEST(test_erase_sub_namespace) {
    ASSUME_NOT_CNULL(db);

    fossil_crabdb_create_namespace(db, "namespace1");
    fossil_crabdb_create_sub_namespace(db, "namespace1", "sub_namespace1");

    fossil_crabdb_error_t result = fossil_crabdb_erase_sub_namespace(db, "namespace1", "sub_namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_OK, result);

    result = fossil_crabdb_erase_sub_namespace(db, "namespace1", "sub_namespace1");
    ASSUME_ITS_EQUAL_I32(CRABDB_ERR_SUB_NS_NOT_FOUND, result);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_core_tests) {    
    // Core Command Parser Fixture
    ADD_TESTF(test_fossil_arg_parse_has, core_cli_fixture);
    ADD_TESTF(test_fossil_arg_parse, core_cli_fixture);

    // Core Bitwise Fixture
    ADD_TESTF(test_fossil_binary_and, core_bitwise_fixture);
    ADD_TESTF(test_fossil_binary_or, core_bitwise_fixture);
    ADD_TESTF(test_fossil_binary_xor, core_bitwise_fixture);
    ADD_TESTF(test_fossil_binary_left_shift, core_bitwise_fixture);
    ADD_TESTF(test_fossil_binary_right_shift, core_bitwise_fixture);
    ADD_TESTF(test_fossil_binary_toggle_bits, core_bitwise_fixture);

    // Core Host System Fixture
    ADD_TESTF(test_fossil_hostsys_get, core_hostsystem_fixture);
    ADD_TESTF(test_fossil_hostsys_endian, core_hostsystem_fixture);

    // Core Memory Fixture
    ADD_TESTF(test_memory_alloc, core_memory_fixture);
    ADD_TESTF(test_memory_realloc, core_memory_fixture);

    // Core Money Fixture
    ADD_TESTF(test_money_create, core_money_fixture);
    ADD_TESTF(test_money_add, core_money_fixture);
    ADD_TESTF(test_money_convert, core_money_fixture);
    ADD_TESTF(test_money_is_valid, core_money_fixture);
    ADD_TESTF(test_money_compare, core_money_fixture);
    ADD_TESTF(test_money_subtract, core_money_fixture);
    ADD_TESTF(test_money_multiply_scalar, core_money_fixture);
    ADD_TESTF(test_money_divide_scalar, core_money_fixture);
    ADD_TESTF(test_money_round, core_money_fixture);
    ADD_TESTF(test_money_is_positive, core_money_fixture);
    ADD_TESTF(test_money_is_zero, core_money_fixture);

    // Core Random Fixture
    ADD_TESTF(test_fossil_random_seed, core_random_fixture);
    ADD_TESTF(test_fossil_random_uint32, core_random_fixture);
    ADD_TESTF(test_fossil_random_uint64, core_random_fixture);
    ADD_TESTF(test_fossil_random_int_range, core_random_fixture);
    ADD_TESTF(test_fossil_random_float, core_random_fixture);
    ADD_TESTF(test_fossil_random_double, core_random_fixture);
    ADD_TESTF(test_fossil_random_yield_seed, core_random_fixture);

    // Core Blue CrabDB Fixture
    ADD_TESTF(test_create_namespace, core_crabdb_fixture);
    ADD_TESTF(test_insert_and_get_value, core_crabdb_fixture);
    ADD_TESTF(test_update_value, core_crabdb_fixture);
    ADD_TESTF(test_delete_value, core_crabdb_fixture);
    ADD_TESTF(test_create_sub_namespace, core_crabdb_fixture);
    ADD_TESTF(test_erase_namespace, core_crabdb_fixture);
    ADD_TESTF(test_erase_sub_namespace, core_crabdb_fixture);
} // end of tests
