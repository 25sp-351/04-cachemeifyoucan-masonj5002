# 04-CacheMeIfYouCan

## Instructions

### Build:

`make`

### Policy A (Least Recently Used):

`./rodcut_lru length_value_pairs.txt`

### Policy B (Least Frequently Used):

`./rodcut_lfu length_value_pairs.txt` 

### Policy C (Random Replacement):

`./rodcut_rr length_value_pairs.txt` 

## Task Overview

Add a cache to the ROD CUT problem. **NOT THE MONEY problem.** Implement **TWO policies** as described in class.

### Requirements

- **Makefile:** Create two executables — one with policy A and one with policy B. The only change should be which policy code/module you link in.
- **Program Modification:**
  - Change the program to make the first argument a file name. That file contains a list of (length, value) pairs, each on one line. Read them all in.
  - Read sample lengths from stdin. One number on a line representing the length.
  - Output the cuts/total amount, same format as assignment 1.
  - Keep reading candidate lengths (e.g., "what if I cut up a rod length 4300?") from the line and using the original (length/value) pairs, do the same cost/cut calculations.

### Explanation

An execution of your program has **ONE set** of length/value pairs, and those are used to "value" several independent rod lengths.

Hope this helps! (and makes it clearer why caching is "valid" for this program).

### Important Note

From this assignment on, I will down-grade any assignment that has 47,000 functions of different purposes in a single file. **SEPARATE!** Tired of "one big file". Group purposes into files. Use `.h` files. Don't expose things that are not necessary/used. <thank you> Yeah, sorry, those of you who have completed it might have to go back and fix this. Tough. Told ya so much earlier. (The reason I've hit my limit is that I'm TIRED of weeding through big single files to find relevant things.)

### Extra Fun Credit (25 pts)

Instead of taking just a length and value, include a "max number of these to be cut" for each length. If 0, no limit. Now think through (and implement) how this affects your cache.

### Update

This assignment is **HARD**. There are "steps" of integration and understanding. I'm pushing it back a week so we can talk. This is good info! Not a waste of time!

### Caching Strategy

Store 100 items or less. Experiment until you find a cache size that leads to eviction and test with that.
