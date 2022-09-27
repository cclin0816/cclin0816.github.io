---
title: Writing This Blog
category: Blog
tags:
  - Hexo
  - Fluid
  - Blog
  - Mimikyu
date: 2022-02-10 07:08:40
index_img: /img/miniQ-3.webp
author: cclin0816
---

關於寫這個 Blog 的一些紀錄

<!-- more -->

{% note primary %}
Blog 的 source code 在 [source branch](https://github.com/cclin0816/cclin0816.github.io/tree/source)  
static site publish 在 [main branch](https://github.com/cclin0816/cclin0816.github.io)  
{% endnote %}

## Framework

原本想用 hugo，用 Go 寫的好像很快，但是我好像不需要他很快，然後跟 Go 又沒很熟，另一個是 hexo ，好處是 theme 很多，而且功能算齊全，看到了不錯的 theme 所以決定用 hexo，雖然之後有點被雷到。

## Theme

theme 選了 [fluid](https://github.com/fluid-dev/hexo-theme-fluid)，滿好看的而且 document 做的還行，light mode 顏色有點爛掉，但我預設 dark mode 所以就算了，另外 renderer 換成了 `hexo-renderer-markdown-it`。

最後加了 google analytics 還有 giscus，雖然應該沒人會看我的 blog 也不會來留言，但是滿酷的所以加了。

## Mimikyu

放了很多迷你Q，大多是 [\@metikyun](https://twitter.com/metikyun/) 畫的，網站上寫可以非營利使用，所以就拿來用了，所以幫忙宣傳一下?  
![Mimikyu](/img/miniQ-d.webp)

## Pitfalls

hexo server 的 file watch 不包括 `_config.yml` 之類的，能理解為什麼這樣設計，但在初期改 theme 的時候還是很煩。

## Other

其實花很多時間弄圖片，優化檔案大小之類的，最後全用 webp，但是花最多時間 load 果然還是 js bundle，然後字體用 JetBrains Mono，加上一堆 fallback 的 monospace。

Gist 還有 Mermaid 的顏色有點爛掉，之後再改。

> 感謝那些被我叫來測垃圾 blog 的人?  
