# s = "hello python".replace("hello", "hi")
# a = s.find("o")
# print(dir(s))
# st = str(42)
# print(type(s).__name__)
# print(isinstance(st, str))


from typing import Any


name = ["sd", 1]
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

tup = ("sd", "ss", "df")
print(tup)
# with open("./CS106b.md", "rt") as file:
#     # data = file.read(40)
#     for line in file:
#         print(line)

dic: dict[Any, Any] = {"qw": 1, "as": "11", "qw": "12"}
if dic.get("ass", None):
    kv = dic.items()
    for k, v in kv:
        print(f"{k}= {v}")
else:
    print("none")

for k in dic:
    print(k)

print(f"dic :{sorted(dic)}")

dic[11] = 11
print(dic)


holidays = {
    (1, 1): "New Years",
    (3, 14): "Pi day",
    (9, 13): "Programmer's day",
}
print(holidays[(1, 1)])

se = {1, 2, 3}
print(se)

# for n in range(-4, 5, 1):
#     print(n)

for n, s in enumerate(se, start=0):
    print(f"{n} = {s}")

ts = zip(tup, se)
print(type(ts))
print(list(ts))
for t, s in ts:
    print(f"{t}:{s}")

for n, x in enumerate(se):
    print(n, x, sep="*")
