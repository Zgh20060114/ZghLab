# s = "hello python".replace("hello", "hi")
# a = s.find("o")
# print(dir(s))
# st = str(42)
# print(type(s).__name__)
# print(isinstance(st, str))


from typing import Any


name: list[Any] = ["sd", "fg", "kl"]
# name.append(1)
# name.insert(2, 1.1)
# if True:
#     print(f"{name}")
# else:
#     print(f"ok")
name.remove("sd")
name.sort(reverse=True)
na = sorted(name)

# file = open("./CS106b.md", "rt")  # 与执行路径有关
# data = file.read(10)
# file.close()
# print(data)

with open("./CS106b.md", "rt") as file:
    # data = file.read(40)
    for line in file:
        print(line)
