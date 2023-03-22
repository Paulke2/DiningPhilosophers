# DiningPhilosophers
the dining philosophers problem (invented by Edsger Dijkstra) involves 5 philosophers sitting around a table and only think and eat. between each philosopher, there is only one chopstick. each philosopher wants to eat at the same time, and grabs the chopstick to his left, when the philosopher goes to grab the chopstick on his right, he will be delayed forever from eating(deadlock) as the philosopher on his right has already grabbed the chopstick. here I will model the dining philosophers problem using semaphores.


My solution was to create a binary semaphore, and lock the semaphore once one philosopher reached for a chopstick(a thread tryes to lock a chopstick semaphore). the semaphore is called "eating". I also used a busy wait on a variable "hungry" initialized to 0, to ensure all philosophers became "hungry" at the same time.
