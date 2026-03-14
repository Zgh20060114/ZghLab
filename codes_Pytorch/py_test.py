#!/usr/bin/env python3
fruits = {1: "apple", 2: "banana", 3: "orange"}
for n, name in fruits.items():
    print(n, name)

print(*fruits.items())
animals = {"a", "c", "b"}
print(*animals)

tuple1 = (1, 2)
tuple2 = tuple1 + (3, 4)
print(tuple2)

list1 = [1, 2]
list2 = list1 + [3, 4]
print(list2)
