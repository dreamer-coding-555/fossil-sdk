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
#ifndef FOSSIL_THREADS_SPINLOCKS_H
#define FOSSIL_THREADS_SPINLOCKS_H

#ifdef _WIN32
#include <windows.h>
typedef CRITICAL_SECTION fossil_xspinlock_t;
#else
#include <pthread.h>
#include <stdatomic.h>
typedef atomic_flag fossil_xspinlock_t;
#endif
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initializes a spinlock.
 *
 * @param lock Pointer to the spinlock to initialize.
 * @return int32_t 0 if the spinlock is successfully initialized, -1 otherwise.
 */
int32_t fossil_spinlock_create(fossil_xspinlock_t *lock);

/**
 * @brief Destroys a spinlock.
 *
 * @param lock Pointer to the spinlock to destroy.
 * @return int32_t 0 if the spinlock is successfully destroyed, -1 otherwise.
 */
int32_t fossil_spinlock_erase(fossil_xspinlock_t *lock);

/**
 * @brief Acquires a spinlock, blocking if necessary until the lock is available.
 *
 * @param lock Pointer to the spinlock to acquire.
 * @return int32_t 0 if the spinlock is successfully acquired, -1 otherwise.
 */
int32_t fossil_spinlock_lock(fossil_xspinlock_t *lock);

/**
 * @brief Releases a spinlock.
 *
 * @param lock Pointer to the spinlock to release.
 * @return int32_t 0 if the spinlock is successfully released, -1 otherwise.
 */
int32_t fossil_spinlock_unlock(fossil_xspinlock_t *lock);

/**
 * @brief Attempts to acquire a spinlock without blocking.
 *
 * @param lock Pointer to the spinlock to acquire.
 * @return int32_t 0 if the spinlock is successfully acquired, -1 otherwise.
 */
int32_t fossil_spinlock_trylock(fossil_xspinlock_t *lock);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <stdexcept>

namespace fossil {

class Spinlock {
public:
    Spinlock() {
        if (fossil_spinlock_create(&lock_) != 0) {
            throw std::runtime_error("Failed to create spinlock");
        }
    }

    ~Spinlock() {
        if (fossil_spinlock_erase(&lock_) != 0) {
            throw std::runtime_error("Failed to destroy spinlock");
        }
    }

    void lock() {
        if (fossil_spinlock_lock(&lock_) != 0) {
            throw std::runtime_error("Failed to acquire spinlock");
        }
    }

    void unlock() {
        if (fossil_spinlock_unlock(&lock_) != 0) {
            throw std::runtime_error("Failed to release spinlock");
        }
    }

    bool trylock() {
        return fossil_spinlock_trylock(&lock_) == 0;
    }

private:
    fossil_xspinlock_t lock_;
};

} // namespace fossil

#endif // __cplusplus

#endif
