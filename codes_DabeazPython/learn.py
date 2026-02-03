# s = "hello python".replace("hello", "hi")
# a = s.find("o")
# print(dir(s))
# st = str(42)
# print(type(s).__name__)
# print(isinstance(st, str))


from typing import Any


name = ["sd", 1]
name[0] = 1
print(name)
# name.append(1)
# name.insert(2, 1.1)
# if True:
#     print(f"{name}")
# else:
#     print(f"ok")
# name.remove("sd")
# name.sort(reverse=True)
# na = sorted(name)

# file = open("./CS106b.md", "rt")  # 与执行路径有关
# data = file.read(10)
# file.close()
# print(data)

tup: tuple[Any] = ("sd",)
print(tup)
# with open("./CS106b.md", "rt") as file:
#     # data = file.read(40)
#     for line in file:
#         print(line)

dic: dict[Any, Any] = {"as": 1, "qw": "11", "qw": "12"}
if dic.get("ass", None):
    kv = dic.items()
    for k, v in kv:
        print(f"{k}= {v}")
else:
    print("none")

dic[11] = 11
print(dic)

holidays = {
    (1, 1): "New Years",
    (3, 14): "Pi day",
    (9, 13): "Programmer's day",
}
print(holidays[(1, 1)])

se = {1, 1, 3}
print(len(se))
se.add(2)
print(len(se))

for n in range(-2, 3.5, 0.5):
    print(n)
