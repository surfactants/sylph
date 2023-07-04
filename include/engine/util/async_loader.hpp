#pragma once

#include <atomic>
#include <filesystem>
#include <thread>

/// Async_Loader ///
/// \brief Successively calls a list of functions, launching them on a separate thread.
/// Only works on derived functions because of the atomic flag.
/// test_and_set MUST be called at the end of each and every task.
///
class Async_Loader {
public:
    bool update();
    void addTask(std::function<void()> task);

protected:
    Async_Loader();

    std::atomic_flag thread_done { ATOMIC_FLAG_INIT };
    std::thread thread;
    std::vector<std::function<void()>> tasks;
    size_t task_index { 0 };
};
