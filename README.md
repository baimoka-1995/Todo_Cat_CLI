## 结构：

```
todo/
├── Makefile
├── todo                  # 可执行文件
├── build/                # .o 中间文件
│
├── data/
│   └── todo.txt          # 持久化
│
└── src/                  # 功能实现
    │
    ├── main.c
    │
    ├── cat/
    │   ├── cat.c
    │   ├── cat.h
    │   ├── cat_assets.c
    │   └── cat_assets.h
    │
    ├── core/
    │   ├── list.c
    │   ├── list.h
    │   ├── search.c
    │   └── search.h
    │
    ├── cmd/
    │   ├── cmd.c
    │   └── cmd.h
    │
    └── storage/
        ├── storage.c
        └── storage.h

```

## zsh 自动触发 `cat-wait`

在 `~/.zshrc` 末尾添加 (`nano ~/.zshrc`)：

```zsh
typeset -g LAST_CMD

if [[ $- == *i* ]]; then
    todo time-check
    todo today
fi

preexec() {
  LAST_CMD=$1
}

precmd() {
  if [[ $- == *i* ]] && [[ ${LAST_CMD%% *} != todo ]]; then
    todo cat-wait
  fi
}
```
直接复制即可。

> 这个配置会：

> 1. 每次打开终端实现一次 todo time-check 和 todo today，如果不需要每次打开终端列出一次清单，可以删掉 todo today。

> 2. 每次命令后执行一次 cat-wait 进行交互，但如果刚执行的是 `todo ...` 命令，就不会再额外执行一次

## 权限检查

检查 `~/.zshrc` 是否可写：

```zsh
ls -l ~/.zshrc
```

如果不可写，给当前用户添加写权限：

```zsh
chmod u+w ~/.zshrc
```

检查 `todo` 是否可执行：

```zsh
ls -l ./todo
```

如果需要，可执行：

```zsh
chmod u+x ./todo
```

## 使用方法
#### 列出完整清单
```
todo today
```

#### 添加 (Add) ：
```
todo add AAA 1
```
其中 1 为 priority（$p\in [1,4]$），内容可以有空格

#### 删除 (Delete)：
```
todo delete AAA
```
字串搜索：输入某任务的关键字/词即可，中间用空格隔开

#### 完成 (Done)：
```
todo done AAA
```
字串搜索：输入某任务的关键字/词即可，中间用空格隔开

#### 查询 (Search)：
```
todo find AAA
```
字串搜索：输入某任务的关键字/词即可，中间用空格隔开

#### 排序 (Sort)：
```
todo sort
```
按照优先级排序
