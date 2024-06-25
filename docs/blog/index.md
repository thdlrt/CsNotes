# 博客文章

{% for post in blog.posts %}
- [{{ post.title }}]({{ post.url }}) ({{ post.date }})
{% endfor %}
