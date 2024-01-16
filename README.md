
## Dinner Philosopher Problem

The dining philosopher problem is a classic example of a synchronization problem in computer science. The problem is to find a way to ensure that no philosopher starves while they are eating, while also ensuring that no two philosophers are eating at the same time.

The problem is typically described as follows:

* There are five philosophers sitting at a table, each with a plate of food and a fork.
* The philosophers can only eat when they have both forks, one in each hand.
* When a philosopher finishes eating, they put down their forks and start thinking again.
* If a philosopher needs to eat, but both forks are taken, they must wait until one of the other philosophers puts down a fork.

The problem is to find a solution that ensures that no philosopher starves while they are eating, while also ensuring that no two philosophers are eating at the same time.

There are a number of different solutions to the dining philosopher problem. One common solution is to use a **dining philosophers mutex**. A mutex is a lock that can be used to protect a shared resource. In this case, the shared resource is the forks. The mutex is used to ensure that only one philosopher can access the forks at a time.

# Arguments.
* number_of_philosophers
* time_to_die 
* time_to_eat 
* time_to_sleep 
* [number_of_times_each_philosopher_must_eat]

Another solution to the dining philosopher problem is to use a **dining philosophers algorithm**. A dining philosophers algorithm is a set of rules that the philosophers must follow in order to avoid deadlock. One common algorithm is the **Peterson algorithm**. The Peterson algorithm works by giving each philosopher a number. The philosophers take turns eating, starting with the philosopher with the lowest number. When a philosopher is eating, they set their number to 1. When a philosopher is finished eating, they set their number to 0. The philosophers can only eat if their number is 0 and no other philosopher has a number of 1.

The dining philosopher problem is a challenging problem, but it is also a valuable one. The solutions to the dining philosopher problem can be used to solve a variety of other synchronization problems in computer science.