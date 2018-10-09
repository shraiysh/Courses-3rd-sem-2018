# Cache Relacement Policies
This is a program assignment from the course in Computer Architechture at IIT Hyderabad. This program calculates the HIT/MISS, given the replacement policy, cache size and address list.

## How to Run?
1. Compile the file `Assignment.cpp` to a binary file `Assignment`
    * Linux - `g++ Assignment.cpp -o Assignment`
2. Given a file `SampleFile`, run it in the following format
```
$ ./Assignment LRU SampleFile.txt 18 
```
where
- Assignment = Binary file name
- LRU = Replacement policy, which can be `LRU`, `FIFO`, or `OPTIMAL`.
- Sample_input1.txt = File Name
- 18 = Cache size
3. The output is displayed in a file named `CS17BTECH11050_LRU_SampleFile_18.out`
where
- CS17BTECH11050 is my roll number
- LRU is replacement policy
- SampleFile is file name without extension
- 18 is cache size

## What is LRU?

LRU stands for Least Recently Used. LRU replacement policy involves the replacement of Least Recently Used cache entry in case there is no empty space in the cache as the name suggests.

This program maintains a deque of cache where the first element is the Most Recently Used and the last one is Least Recently Used. `pop_back` is called when an element is to be added to a full cache. New element is always `push_front` to the deque. When an element is accessed again, it is pushed to the front of the deque by calling `rotate`

    Original    : (MRU)<|1  |2  |3  |4  |5  |<(LRU)
    Accessing   : 3
    Final       : (MRU)<|3  |1  |2  |4  |5  |<(LRU)

Observe that only the first 3 entried are rotated.

# What is FIFO?

FIFO stands for First In First Out. As the name suggests, it replaces the cache entry that entered the earliest in the cache once it it full.

This program maintains a deque for FIFO, which calls `push_front` when a new entry comes and `pop_back` when cache is full and new access is made.
The difference between LRU and FIFO is in the case of repeated accesses, the nature of queue does not change.

# What is OPTIMAL?

This is the best replacement policy. It requires access to the future. Since we know all the accesses in a file already, we can use this here. When cache is full, and a new entry is to be added, it removes the element from the cache that is going to be accessed farthest in the future. This makes sure all other elements have to be accessed before this element is needed again. Hence we can safely replace this. This also means that if there exists an element in the cache that is never accessed again(infinite distance to next occurence), it is replaced first.

The program uses a map for cache here where the keys are cache memory address strings and values are distances to next occurences from the current point in the file. When a new element is accessed, all the distances are upadted by reducing them by -1. If the distance of any element becomes zero in this process, then there's a HIT and it's distance needs to be updated. Otherwise, farthest one is replaced.
