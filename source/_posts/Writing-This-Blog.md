---
title: Writing This Blog
category: blog
tags:
  - hexo
  - fluid
  - blog
date: 2022-02-10 07:08:40
index_img: /img/miniQ-3.webp
---


關於寫這個 Blog 的一些紀錄

<!-- more -->
{% note info %}
所有 Blog 的 source code 都在 [source branch](https://github.com/cclin0816/cclin0816.github.io/tree/source)
static site publish 在 [main branch](https://github.com/cclin0816/cclin0816.github.io)
{% endnote %}

framework 原本想用 hugo，用 Go 寫的好像很快，但是我好像不需要他很快，然後跟 Go 又沒很熟，hexo 的好處 theme 很多，而且功能算齊全，看到了不錯的 theme 所以決定用 hexo，雖然之後有點被雷到，雷點是 hexo serve 真的有點爛，browser sync 也是，會一直卡住，所以後來都直接 generate 然後用 php serve static 了  

theme 選了 fluid，是國人寫的，但滿好看的所以就算了，而且 document 做的還行，沒有支援繁體中文，所以設成英文的，fluid 的 document 裡面寫如過要用 LATEX 要換 render engine 但是原生的好像就能動了，所以就沒換了，light mode 顏色有點爛掉，但我預設 dark mode 所以就算了，不想改了，然後 mermaid 背景只有白色，但我估計也不會用，所以也算了，最後加了 google analytics 還有 utteranc，雖然應該沒多少人看我 blog 也不會來留言，但是滿酷的所以加了，其實花很多時間弄照片，讓檔案變小，但是花最多時間果然還是 js bundle 嘻嘻，然後 ffmpeg 甚麼時候要支援 avif 啦
