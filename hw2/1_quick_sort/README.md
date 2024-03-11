# Performance test log of quick sort
## structure
* original version 
    > quick sort time[original] : 36316 
* double - linked list
    > quick sort time [double-linked]: 30261
---
## pivot selection
(size_t count = 100000)
* first entry
Segmentation fault (core dumped)
> max level = 50000       quick sort time (avg.  case): 6359356  
> max level = 100000      quick sort time (worst case): 6359356  
> max level = 100000      quick sort time (best  case): 14961502 
--- 
> max level = 4   size = 10       quick sort time 6  
> max level = 14  size = 100      quick sort time 33  
> max level = 26  size = 1000     quick sort time 409  
> max level = 38  size = 10000    quick sort time 6733  
> max level = 48  size = 100000   quick sort time 33866  

* random pivot
> max level = 8   size = 10       quick sort time 7  
> max level = 18  size = 100      quick sort time 39  
> max level = 24  size = 1000     quick sort time 488  
> max level = 36  size = 10000    quick sort time 3591  
> max level = 52  size = 100000   quick sort time 54835  
---
> max level = 50  quick sort time (avg.  case): 30540  
> max level = 48  quick sort time (worst case): 30540  
> max level = 48  quick sort time (best  case): 24480  