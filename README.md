# Philosophers - A Concurrency Simulation

![42 Project](https://img.shields.io/badge/42%20Project-Philosophers-blue) ![Language](https://img.shields.io/badge/Language-C-informational) ![Concurrency](https://img.shields.io/badge/Concurrency-Pthreads-critical)

This project is a C implementation of the famous **Dining Philosophers problem**, a classic computer science challenge used to illustrate synchronization issues and solutions in concurrent programming.

The goal is to simulate a table of philosophers who do nothing but think, eat, and sleep. To eat, a philosopher must pick up two forks—one on their left and one on their right. The challenge is to design a system where no philosopher starves and, most importantly, the system does not enter a **deadlock** (a state where every philosopher is waiting for a fork held by another).

This implementation uses **POSIX threads (pthreads)** and **mutexes** to manage the philosophers and their access to shared resources (the forks).

## 🏛️ Core Concepts & Solution

The simulation is built around a few key principles to ensure correctness and prevent common concurrency pitfalls.

### 1. The Simulation Structure
*   **Philosopher Threads**: Each philosopher is represented by a dedicated `pthread`. They run a routine that cycles through eating, sleeping, and thinking.
*   **Forks as Mutexes**: Each fork on the table is represented by a `pthread_mutex_t`. To "pick up" a fork, a philosopher must lock its corresponding mutex. This ensures that only one philosopher can hold a fork at any given time.
*   **The Monitor (Thanatos)**: A separate supervisor thread, named `thanatos` (Death), constantly monitors the state of all philosophers. Its purpose is twofold:
    1.  **Detect Starvation**: It checks if any philosopher has gone too long without eating (`time_to_die`). If so, it ends the simulation.
    2.  **Check for Satiation**: If an optional number of meals is provided, it checks if all philosophers have eaten that many times and gracefully ends the simulation.

### 2. Deadlock Prevention
A naive approach where every philosopher tries to pick up their left fork and then their right fork will inevitably lead to deadlock. This implementation prevents deadlock using an **asymmetric resource allocation strategy**:

*   Philosophers with an **even ID** pick up their **left fork first**, then their right.
*   Philosophers with an **odd ID** pick up their **right fork first**, then their left.

This simple rule breaks the circular dependency that causes deadlock, ensuring that at least one philosopher can always acquire both forks and eat.

### 3. Race Condition Prevention
To ensure thread safety and accurate logging, several mutexes are used:
*   **Fork Mutexes**: One for each fork to prevent two philosophers from picking up the same fork.
*   **Print Mutex**: A single, global mutex that protects `printf`. This prevents log messages from multiple threads from being interleaved and garbled.
*   **State Mutexes**: Each philosopher has a mutex to protect their personal state (last meal time, number of meals eaten) from being read and written simultaneously by the monitor thread.

## 🔄 Simulation Logic

1.  **Initialization**: The main thread initializes the `academia` (the simulation environment), creates a mutex for each fork, and spawns one thread per philosopher plus the monitor thread.
2.  **Execution**: Each philosopher thread begins its life cycle:
    *   **Thinking**: Waits for its turn to eat. A slight delay is introduced for odd-numbered philosophers to stagger the initial fork requests.
    *   **Eating**: Attempts to lock the mutexes for both adjacent forks (using the deadlock-prevention strategy). Once acquired, it "eats" for a specified duration, updates its last meal time, and then releases the forks (unlocks the mutexes).
    *   **Sleeping**: Pauses for a specified duration before starting to think again.
3.  **Termination**: The simulation ends when one of two conditions is met:
    *   A philosopher dies (the time since their last meal exceeds `time_to_die`).
    *   All philosophers have eaten the optional `number_of_times_each_philosopher_must_eat`.

## 🚀 How to Use

### Compilation
A `Makefile` is included for easy compilation.
```bash
make
```

### Execution
The program takes 4 mandatory arguments and 1 optional argument:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

### Arguments

| Argument | Description | Unit |
| :--- | :--- | :--- |
| `number_of_philosophers`| The number of philosophers (and forks) at the table. | - |
| `time_to_die` | The time a philosopher has to start eating before they die. | Milliseconds |
| `time_to_eat` | The time it takes for a philosopher to eat. | Milliseconds |
| `time_to_sleep` | The time a philosopher spends sleeping. | Milliseconds |
| `[number_of_meals]` | **(Optional)** If specified, the simulation stops after every philosopher has eaten this many times. | - |

### Example
```bash
./philo 5 800 200 200
```
This will start a simulation with 5 philosophers, who will die if they don't eat within 800ms. Each meal takes 200ms, and they sleep for 200ms afterward.

## 🎬 Example Output

The output is formatted as `timestamp_in_ms philosopher_id action`. The print mutex ensures each line is printed atomically.

```
0 1 is thinking
0 2 is thinking
0 3 is thinking
0 4 is thinking
0 5 is thinking
2 2 has taken a fork
3 2 has taken a fork
3 2 is eating
203 2 is sleeping
204 4 has taken a fork
...
805 1 died
```

## 💻 Technologies Used

*   **Language:** C
*   **Compiler:** GCC
*   **Concurrency API:** POSIX Threads (pthreads)
*   **Synchronization Primitives:** Mutexes (`pthread_mutex_t`)

## 👤 Author

*   **A. Duvillaret** ([C0rvax](https://github.com/C0rvax))
