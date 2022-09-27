---
title: Hexo Tag Plugins
category: Hexo
tags:
  - Hexo
  - Fluid
  - Markdown
author: cclin0816
index_img: /img/miniQ-8.webp
math: true
mermaid: true
date: 2022-02-11 06:44:03
---

Note of tag plugins' syntax, also works as checklist after theme updates.

<!-- more -->

## Block Quote

{% blockquote Antoine de Saint-Exupéry, The Little Prince %}
I am who I am and I have the need to be.
{% endblockquote %}

## Code Block

```cpp
#include <functional>

constexpr decltype(auto) curry(auto f, auto... ps) {
  if constexpr (requires { std::invoke(f, ps...); }) {
    return std::invoke(f, ps...);
  } else {
    return [f, ps...](auto... qs) -> decltype(auto) {
      return curry(f, ps..., qs...);
    };
  }
}
```

## Pull Quote

{% pullquote %}
quote with class
{% endpullquote %}

> quote without class

## jsFiddle

{% jsfiddle kizu/zfUyN result light 640 360 %}

## Gist

{% gist 704490cbbc07822e53968a159f3e3862 hello_world.rs %}

## iframe

{% iframe /about/ 640 360 %}

## Include Code

{% include_code lang:python example.py %}

## YouTube

{% youtube zI383uEwA6Q %}

## Post Link

{% post_link Hexo-Tag-Plugins %}

## Raw

{% raw %}
{% raw %}
{% endraw %}
{% endraw %}

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

## HTML

<h3> level 3 </h3>
<script> alert('script works'); </script>
<!-- comment works -->

## Footnote

google[^1]

[^1]: https://www.google.com