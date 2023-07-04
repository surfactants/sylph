#include <engine/util/async_loader.hpp>

Async_Loader::Async_Loader()
{
    thread_done.test_and_set();
}

bool Async_Loader::update()
{
    bool done { false };
    if (thread_done.test()) {
        thread_done.clear();
        if (thread.joinable()) {
            thread.join();
        }
        done = (task_index == tasks.size());
        if (done) {
            task_index = 0;
        }
        else {
            // launch next thread
            thread = std::thread(tasks[task_index++]);
        }
    }
    return done;
}

void Async_Loader::addTask(std::function<void()> task)
{
    tasks.push_back(task);
}
