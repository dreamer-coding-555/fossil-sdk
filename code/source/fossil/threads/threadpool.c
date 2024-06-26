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
#include "fossil/threads/threadpool.h"
#include "fossil/common/common.h"
#include <stdlib.h>

/**
 * @brief Platform-independent worker function for the thread pool.
 *
 * @param arg Pointer to the thread pool structure.
 * @return void
 */
static inline void thread_pool_worker(fossil_xtask_arg_t arg) {
    fossil_xthread_pool_t* pool = (fossil_xthread_pool_t*)arg;
    while (1) {
        fossil_mutex_lock(&pool->queue_mutex);
        while (atomic_load(&pool->task_count) == 0 && !atomic_load(&pool->shutdown)) {
            fossil_cond_wait(&pool->queue_cond, &pool->queue_mutex);
        }
        if (atomic_load(&pool->shutdown) && atomic_load(&pool->task_count) == 0) {
            fossil_mutex_unlock(&pool->queue_mutex);
            break;
        }
        fossil_xtask_t task = pool->task_queue[pool->queue_front];
        pool->queue_front = (pool->queue_front + 1) % pool->queue_size;
        atomic_fetch_sub(&pool->task_count, 1);
        fossil_mutex_unlock(&pool->queue_mutex);
        task.task_func(task.arg);
    }
}

int32_t fossil_thread_pool_create(fossil_xthread_pool_t *pool, int32_t thread_count, int32_t queue_size) {
    if (!pool || thread_count <= 0 || queue_size <= 0) return FOSSIL_ERROR;

    pool->threads = (fossil_xthread_t*)malloc(sizeof(fossil_xthread_t) * thread_count);
    if (!pool->threads) return FOSSIL_ERROR;

    pool->thread_count = thread_count;
    pool->queue_size = queue_size;
    pool->queue_front = 0;
    pool->queue_rear = 0;
    atomic_init(&pool->shutdown, 0);
    atomic_init(&pool->task_count, 0);

    pool->task_queue = (fossil_xtask_t*)malloc(sizeof(fossil_xtask_t) * queue_size);
    if (!pool->task_queue) {
        free(pool->threads);
        pool->threads = NULL;
        return FOSSIL_ERROR;
    }

    if (fossil_mutex_create(&pool->queue_mutex) != 0) {
        free(pool->threads);
        free(pool->task_queue);
        pool->threads = NULL;
        pool->task_queue = NULL;
        return FOSSIL_ERROR;
    }

    if (fossil_cond_create(&pool->queue_cond) != 0) {
        fossil_mutex_erase(&pool->queue_mutex);
        free(pool->threads);
        free(pool->task_queue);
        pool->threads = NULL;
        pool->task_queue = NULL;
        return FOSSIL_ERROR;
    }

    for (int i = 0; i < thread_count; ++i) {
        fossil_xtask_t task = { .task_func = (fossil_xtask_func_t)thread_pool_worker, .arg = pool };
        if (fossil_thread_create(&pool->threads[i], NULL, task) != FOSSIL_SUCCESS) {
            atomic_store(&pool->shutdown, 1);
            fossil_mutex_lock(&pool->queue_mutex);
            fossil_cond_broadcast(&pool->queue_cond);
            fossil_mutex_unlock(&pool->queue_mutex);

            for (int j = 0; j < i; ++j) {
                fossil_thread_join(pool->threads[j], NULL);
            }
            fossil_mutex_erase(&pool->queue_mutex);
            fossil_cond_erase(&pool->queue_cond);
            free(pool->threads);
            free(pool->task_queue);
            pool->threads = NULL;
            pool->task_queue = NULL;
            return FOSSIL_ERROR;
        }
    }

    return FOSSIL_SUCCESS;
}

int32_t fossil_thread_pool_erase(fossil_xthread_pool_t *pool) {
    if (!pool) return FOSSIL_ERROR;

    atomic_store(&pool->shutdown, 1);

    fossil_mutex_lock(&pool->queue_mutex);
    fossil_cond_broadcast(&pool->queue_cond);
    fossil_mutex_unlock(&pool->queue_mutex);

    for (int i = 0; i < pool->thread_count; ++i) {
        fossil_thread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    free(pool->task_queue);
    fossil_mutex_erase(&pool->queue_mutex);
    fossil_cond_erase(&pool->queue_cond);

    return FOSSIL_SUCCESS;
}

int32_t fossil_thread_pool_add_task(fossil_xthread_pool_t *pool, fossil_xtask_func_t task_func, void *arg) {
    if (!pool || !task_func) return FOSSIL_ERROR;

    fossil_mutex_lock(&pool->queue_mutex);
    if ((pool->queue_rear + 1) % pool->queue_size == pool->queue_front) {
        fossil_mutex_unlock(&pool->queue_mutex);
        return FOSSIL_ERROR; // Queue is full
    }

    fossil_xtask_t new_task = { .task_func = task_func, .arg = arg };
    pool->task_queue[pool->queue_rear] = new_task;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_size;
    atomic_fetch_add(&pool->task_count, 1);
    fossil_cond_signal(&pool->queue_cond);
    fossil_mutex_unlock(&pool->queue_mutex);

    return FOSSIL_SUCCESS;
}
