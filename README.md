<p align="center">
<img src="https://github.com/daviduartecf/philosophers/blob/main/dining-philosopher.jpg" style="width: 25%;">
</p>
<h1 align="center">Philosophers</h1>

## Dining Philosophers Problem

The **Dining Philosophers Problem** is a classic concurrency problem that helps to understand synchronization issues when multiple processes share limited resources. In this problem:

- A group of philosophers sit around a round table with a large bowl of spaghetti in the center.
- Philosophers alternate between three states: eating, thinking, and sleeping. A philosopher can only eat if they have acquired both the fork to their right and the fork to their left.
- The table has as many forks as philosophers, with each fork shared between neighboring philosophers. Philosophers cannot share information or communicate with one another.
- The challenge is to design a solution that allows all philosophers to eat without leading to deadlock (where no one can eat) or starvation (where a philosopher never gets to eat).

### Key Features
- Philosophers alternate between eating, thinking, and sleeping.
- To eat, a philosopher needs to pick up both their left and right forks.
- After eating, they return the forks to the table and go to sleep.
- Philosophers must avoid starvation, meaning each philosopher must get the chance to eat.
- The solution should prevent deadlock, where all philosophers could be waiting indefinitely for forks to become available.

### Goals
- Ensure that all philosophers eventually get a chance to eat.
- Prevent any philosopher from dying due to starvation.
- Implement a fair and deadlock-free solution to the resource-sharing problem.

This project provides a simulation of the Dining Philosophers Problem and demonstrates the use of synchronization techniques in concurrent programming.

## Installation and Usage intructions
1. Clone the repository:
    ```sh
    git clone https://github.com/daviduartecf/philosophers.git
    ```
2. Compile the project:
    ```sh
    make
    ```
3. Run the executable:
    ```sh
    ./philo 5 600 200 200 5
    ```
