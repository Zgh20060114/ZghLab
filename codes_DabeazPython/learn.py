# s = "hello python".replace("hello", "hi")
# a = s.find("o")
# print(dir(s))
# st = str(42)
# print(type(s).__name__)
# print(isinstance(st, str))


from typing import Any
from collections import Counter
from collections import deque


name = ["sd", 1]
na = list(name)
print(na)
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
di = dict(dic)
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
dic.update({1: 1})
print(dic.setdefault(11, 12))
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


portfolio = [
    ("IBM", 50, 120),
    ("AAPL", 100, 150),
    ("IBM", 100, 125),  # 同一股票，持股数累加
    ("GOOG", 80, 200),
]
total_shares = Counter()
for name, shares, price in portfolio:
    # if name not in total_shares:  # 必须手动判断，否则报错
    #     total_shares[name] = 0
    # 不用Counter需手动给刚开始是空的字典的值初始化为零,否则+=会报错,因为会先取值,取到了不存在的值
    total_shares[name] += shares
print(total_shares)

print(Counter(tup))

# de = deque(maxlen=10)

# a = ["sd", 2, 3]
# b = [2 * x for x in a if type(x) is int]
# print(b)

# b = a
# print(hex(id(b)))

a = [1, 2, 3]
b = a
a.append(4)
print(a)
print(b)
