# Cache replacement policies

This is the implementation of differnt cache replacement policies with analyzing them on different workloads.

Policies: LRU (exact and approx), FIFO, Random
Workloads: 80-20 (local), looping, random

## Usage

To generate plots for each workload use make as follows:
1. **Random Workload** - `make random`
2. **Looping Workload** - `make loop`
3. **Local Workload** - `make local`


## Plots and Analysis

### Random Workload
![alt text](images/random.PNG?raw=true)

### 80-20 Workload
![alt text](images/local.PNG?raw=true)

### Loop Workload
![alt text](images/loop.PNG?raw=true)

## Policy Analysis

- **hit function** will iterate through the cache array to search for a page so it takes linear time to search for a page. Time complexity of this function is **O(cache size)**

### FIFO (First In First Out) Policy

1. Time complexity - the algorithm will iterate over the workload containing pages to be accessed. For each page, a call to hit function will take O(cache size). Therefore the overall time complexity becomes **O(workload size * cache size)**

2. Space complexity - It takes an array for storing cache **O(cache size)**

### Random Policy

1. Time complexity - 
    - the algorithm will iterate over the workload containing pages to be accessed. For each page, a call to hit function will take O(cache size). Therefore the overall time complexity becomes **O(workload size * cache size)**
    
    - **Do this policy takes O(1) time?** - No the policy do not take a constant time for a page because the page to be replaced is selected by a random choice so to replace that page in the cache it will take linear time to search for that node. However it is not taking the linear time here because of linear time search also.
 
2. Space complexity - It takes an array for storing cache **O(cache size)**

### Least Frequently Used (LRU) Policy

1. Time complexity - 
    - the algorithm will iterate over the workload containing pages to be accessed. For each page, a call to hit function will take O(cache size). Therefore the overall time complexity becomes **O(workload size * cache size)**

2. Space complexity - It takes an array for storing cache **O(cache size)**

### Least Frequently used Approx Policy

1. Time complexity - 
    - the algorithm will iterate over the workload containing pages to be accessed. For each page, a call to hit function will take O(cache size). 

    - After getting a miss the algorithm searches for a page whose **used bit** is 1 which takes a linear time. Therefore the overall time complexity becomes **O(workload size * cache size)**

2. Space complexity - It takes array for storing cache and one more array to store used bits so complexity becomes **O(2*cache size)**