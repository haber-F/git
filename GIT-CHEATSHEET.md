# Git 常用命令速查表

> 本仓库已配置好：默认分支 `main`，远程 `origin` 指向 GitHub，提交身份为 `haber-F`。
> 日常推送直接用 `git push` 即可（已设上游跟踪）。

## 一、日常三步走（最常用）

```bash
git add .                 # 1. 把改动加入暂存区（. 表示全部，也可写具体文件名）
git commit -m "改动说明"   # 2. 提交到本地仓库
git push                  # 3. 推送到 GitHub
```

## 二、查看与对比

| 命令 | 作用 |
|---|---|
| `git status` | 看当前哪些文件改了、哪些没跟踪 |
| `git diff` | 看还没提交的具体改动内容 |
| `git log --oneline` | 看提交历史（一行一条） |
| `git log -p` | 看每次提交改了哪些内容 |

## 三、撤销与回退

| 命令 | 作用 |
|---|---|
| `git checkout -- 文件` | 撤销某个文件的未提交改动 |
| `git restore 文件` | 同上（新版 git 推荐写法） |
| `git reset HEAD 文件` | 把文件从暂存区撤出（改动还在） |
| `git reset --hard 提交号` | 回退到某次提交（**改动会丢失，慎用**） |
| `git revert 提交号` | 生成一个反向提交来撤销（安全，推荐） |

## 四、分支（推荐用分支做新功能）

```bash
git branch                 # 列出所有分支
git checkout -b 分支名      # 新建并切换到分支
git switch -c 分支名        # 同上（新版推荐）
git checkout main          # 切回主分支
git merge 分支名            # 把分支合并进当前分支
git branch -d 分支名        # 删除已合并的分支
```

## 五、远程协作

| 命令 | 作用 |
|---|---|
| `git pull` | 拉取远程更新并合并（推送前建议先 pull） |
| `git fetch` | 只拉取不合并，先看有什么更新 |
| `git remote -v` | 查看远程仓库地址 |
| `git clone 地址` | 第一次把仓库下载到本地 |

## 六、.gitignore 说明

已在仓库中加入 `.gitignore`，自动忽略：
- 依赖目录（`node_modules/`、`__pycache__/` 等）
- 日志、缓存、临时文件
- 密钥/环境变量（`.env`、`*.key`、`*.pem`）——**真实密钥千万别提交**
- 本地工具目录 `.workbuddy/`

要新增忽略项，直接在 `.gitignore` 末尾加一行规则即可。

## 七、几个容易踩的坑

1. **推送被拒** → 多半是远程有别人的更新，先 `git pull` 再 `git push`。
2. **提交要勤、信息要清楚** → 一次一个小改动就 commit，别攒一大堆。
3. **别提交大文件/密钥** → 大文件用 Git LFS 或对象存储；密钥走 `.env`（已被忽略）。
4. **本仓库的特殊配置** → 因本地代理环境，已设 `http.sslVerify=false`，仅对本仓库生效，正常用即可。
