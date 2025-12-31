# Data structure and algorithms in various languages
DISCLAIMER: None of these will be good. 

I am writing these as practice, and if *somehow* they are good enough, maybe used in other projects. Do I think I can do better than standard library? Not at the moment, no.

## Work in progress
### cpp
- It is AWFUL, do NOT take it seriously.
- Implemented V1 of doubly linked list. Attempted to use shared pointers for best practices, as `std::unique_ptr` would violate single owner principle. 
- However, `std::shared_ptr` in doubly linked list is leaking memory, as there is cyclic dependencies. Big time. DO NOT DO THIS. IT IS MY FIRST TIME USING SMART POINTERS.
- Benchmarked against standard libraries' `std::list`. Mine is 100x slower. Fuck.
- Idea? Forward pointer is unique, backwards pointer is raw.

