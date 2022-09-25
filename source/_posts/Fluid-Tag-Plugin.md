---
title: Fluid Tag Plugin
category: Fluid
tags:
  - hexo
  - fluid
  - markdown
author: Me
index_img: /img/miniQ-8.webp
math: true
mermaid: true
date: 2022-02-11 06:44:03
---


just a note for tag plugin markdown syntax, so I don't need to lookup the document every time

<!-- more -->

## Note

{% note primary %}
primary
{% endnote %}
{% note secondary %}
secondary
{% endnote %}
{% note success %}
success
{% endnote %}
{% note danger %}
danger
{% endnote %}
{% note warning %}
warning
{% endnote %}
{% note info %}
info
{% endnote %}
{% note light %}
light
{% endnote %}

## Check Box

{% cb None, false, false %} None-text
{% cb Check, true, false %} Check-text
{% cb Inline, false, true %} Inline-text

## Button

{% btn ./, text, title %}

## Group Image

{% gi 10 3-2-2-3 %}
![miniQ-1](/img/miniQ-1.webp)
![miniQ-2](/img/miniQ-2.webp)
![miniQ-3](/img/miniQ-3.webp)
![miniQ-4](/img/miniQ-4.webp)
![miniQ-5](/img/miniQ-5.webp)
![miniQ-6](/img/miniQ-6.webp)
![miniQ-7](/img/miniQ-7.webp)
![miniQ-8](/img/miniQ-8.webp)
![miniQ-9](/img/miniQ-9.webp)
![miniQ-10](/img/miniQ-10.webp)
{% endgi %}

## Latex

$$
E=mc^2
$$

## Mermaid

{% mermaid %}
pie showData
    title Key elements in Product X
    "Calcium" : 42.96
    "Potassium" : 50.05
    "Magnesium" : 10.01
    "Iron" :  5
{% endmermaid %}
