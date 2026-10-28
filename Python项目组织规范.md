# 像高手一样组织 Python 代码

> 出处:[Organize Python code like a PRO - guicommits.com](https://guicommits.com/organize-python-code-like-a-pro/)
> 作者 gui 根据多年公司工作经验总结的 Python 项目组织与命名规范,核心观点:**Python 极其灵活,而过度灵活会增加做出糟糕决定的可能性,所以需要一套自律性的组织准则。**

## 一、项目结构:使用 src 布局

推荐的顶层结构:

```text
<project>/
├── src/
│   └── <module>/
│       ├── __init__.py
│       └── ...
├── tests/
│   └── ...
├── .gitignore
├── pyproject.toml
└── README.md
```

要点:

- 所有业务代码放进 `src/` 目录,主模块名 `<module>` 通常与项目同名(非强制),可以参考"别人 `pip install` 时会安装什么"来决定。
- **为什么用 src/**:不推荐的布局是各模块散落在目录树各处,和配置、CI/CD 文件混在一起,受 IDE 字母排序影响显得很乱;集中放 `src/` 可以让"活动的代码"与"配置/元数据"分离,一眼看清边界。
- **缺点**:开箱无法直接 `import` 模块,需要把项目配置成可安装的包(比如 `pip install -e .`)。

## 二、文件(模块)命名的三条规则

1. **Python 中没有"文件"的概念** - 含 `__init__.py` 的目录由模块组成,应当把每个模块视为一个**命名空间**,而不是一个个孤立文件。
2. **相关的类可以放在同一个模块内**,只有当模块过大、或涉及不同关注点时才拆分(这点与 Java/C# 的"一类一文件"习惯相反)。
3. **默认使用复数命名,并以业务上下文命名**;例外是 `core`、`main.py` 这类表示单一事物的情况。

作者的真实项目 [GMaps Crawler](https://github.com/guilatrova/GMaps-Crawler) 结构示例:

```text
gmaps_crawler/
├── config.py
├── drivers.py
├── entities.py
├── exceptions.py
├── facades.py
├── main.py
└── storages.py
```

用法如 `from gmaps_crawler.storages import get_storage`。**复数命名的好处**:模块不会太小、日后可以随时拆分、光看名字就能预知内部大概有什么。

## 三、类、函数、变量的命名

### 函数/方法用动词

- ✅ `get_orders()`、`acknowledge_event()`
- ❌ `email_send()`、`api_call()`(语义不明,看不懂会做什么)
- 例外:`main()` 函数和 `@property` 属性方法。

### 变量/常量用名词

- ✅ `plane = Plane()`、`KEY_COMPARISON = "abc"`
- ❌ `fly = Plane()`、`COMPARE_KEY`
- 集合用复数:`planes`、`customer_ids`;字典保持单数。

### 类名自解释,允许后缀

- 类用单数、直接用业务名词:`Order`、`Store`。
- 允许加表意后缀(Service、Strategy、Sender 等):发邮件的类应叫 `EmailSender` 而不是 `Email`。

## 四、大小写约定速查表

| 类型 | Public | Internal |
| --- | --- | --- |
| 包/目录 | `lower_with_under` | - |
| 模块 | `lower_with_under.py` | - |
| 类 | `CapWords` | - |
| 函数 | `lower_with_under()` | `_lower_with_under()` |
| 常量 | `ALL_CAPS_UNDER` | `_ALL_CAPS_UNDER` |

## 五、关于"私有"方法

Python 的双下划线名称改写(name mangling)**并不是真正的私有保护**。正如 Guido 所说:"We're all consenting adults here(我们都是成年人)"。实践中建议只用**单个前导下划线** `_method()` 标注内部意图即可,不必用双下划线。

## 六、何时用函数,何时用类

- 模块本身就是组织函数的好方式,比如 `storages.get_storage()`。
- 判断时机:当模块里出现**多个可以分组、且组内互相调用的函数子集**时,把它们升级为类。例如 storages 模块中,debug 相关函数(`format_for_debug`、`save_debug`)归为 `DebugStorage`,S3 相关函数(`create_s3`、`save_s3`)归为 `S3Storage`。
- **经验法则:总是从函数开始,发现可分组的函数子集时再升级为类。** 不要一上来就写一堆类。

## 七、模块与入口点

入口点要加保护条件,防止被 import 时意外执行:

```python
if __name__ == "__main__":
    execute_main()
```

如果希望安装后能用 `python -m <module>` 的方式运行(如 `python -m pytest`),需要在主模块中添加 `__main__.py` 文件。

## 总结

整篇文章的递进脉络:**项目结构 → 文件命名 → 函数/变量/类命名 → 大小写约定 → 函数 vs 类的取舍 → 入口点写法**。核心思想可以浓缩成三句话:

1. 用 `src/` 布局把代码和配置分开,把项目做成可安装的包;
2. 模块即命名空间,复数命名 + 业务上下文,函数用动词、变量用名词、类用名词并允许后缀;
3. 先写函数,需要时再重组为类;入口永远用 `if __name__ == "__main__":` 保护。
