---
title: Writing This Blog
category: Blog
tags:
  - hexo
  - fluid
  - blog
  - mimikyu
date: 2022-02-10 07:08:40
index_img: /img/miniQ-3.webp
author: Me
---


關於寫這個 Blog 的一些紀錄

<!-- more -->
{% note primary %}
Blog 的 source code 在 [source branch](https://github.com/cclin0816/cclin0816.github.io/tree/source)
static site publish 在 [main branch](https://github.com/cclin0816/cclin0816.github.io)
{% endnote %}

## Framework

原本想用 hugo，用 Go 寫的好像很快，但是我好像不需要他很快，然後跟 Go 又沒很熟，另一個是 hexo ，好處是 theme 很多，而且功能算齊全，看到了不錯的 theme 所以決定用 hexo，雖然之後有點被雷到，~~hexo serve 和 browser sync  有點爛，會一直卡住，所以後來都直接 generate 然後用 php serve 了~~ (後來又莫名其妙的好了，但是改 _config 不會更新，也是有點難過)

## Theme

theme 選了 fluid，滿好看的而且 document 做的還行，但是沒有支援繁體中文，所以設成英文，light mode 顏色有點爛掉，但我預設 dark mode 所以就算了，還有 mermaid 背景只有白色，但我估計也不會用，所以也算了，auto excerpt 也是很難看
> [docs](https://hexo.fluid-dev.com/docs/en/guide/)
> fluid 的 docs 寫如過要用 LATEX 要換 renderer 但是原生的就能動了，所以就沒換了
> OpenGraph 怎麼用也是個謎

最後加了 google analytics 還有 utteranc，雖然應該沒人會看我的 blog 也不會來留言，但是滿酷的所以加了

## Mimikyu

放了很多迷你Q，大多是 [@metikyun](https://twitter.com/metikyun/) 畫的，網站上寫可以非營利使用(我其實有私訊他，但他不理我)，所以就拿來用了，所以幫忙宣傳一下?
![Mimikyu](/img/miniQ-d.webp)

## Other

其實花很多時間弄照片，優化檔案大小之類的，最後全用 webp，但是花最多時間 load 果然還是 js bundle 嘻嘻，然後 ffmpeg 甚麼時候要支援 avif 啦
字體用 JetBrains Mono，加上一堆 fallback 的 monospace
> 感謝那些被我叫來測垃圾 blog 的人?
