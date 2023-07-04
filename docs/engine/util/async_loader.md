# Async_Loader
*class*  
*engine/util/async_loader.hpp*

## About
Successively calls a list of functions, launching them on a separate thread.

Tasks are launched automatically through the **update()** function.

## IMPORTANT NOTE

The atomic_flag **thread_done** controls automatic operations. Therefore ***all tasks must call `thread_done.test_and_set()` at the end of the function.*** This also limits the asynchronous loader to operating as part of a derived class.

### Public Member Functions

### bool update()
Polls for task completion.

Returns true if the final task has completed.

### void addTask( *std::function<void()> task* )
Saves the passed function to the task list. Tasks are called in order of addition.

## Protected Member Functions

### Async_Loader()

---

[Module Engine](../engine.md)  
[Submodule Util](util.md)  
[Return to docs](../../docs.md)