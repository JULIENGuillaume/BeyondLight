var elements = document.querySelectorAll('link[rel=import]');
for(var i = 0; i < elements.length; i++){
    if (elements[i].getAttribute("href") === "header.html") {
        var post = elements[i].import.querySelector('#header-template');
        var container = document.querySelector('header');
        container.appendChild(post.cloneNode(true));
    }
    else if (elements[i].getAttribute("href") === "left-menu.html") {
        var post = elements[i].import.querySelector('#left-menu-template');
        var container = document.querySelector('left-menu');
        container.appendChild(post.cloneNode(true));
    }
    else if (elements[i].getAttribute("href") === "main-content.html") {
        var post = elements[i].import.querySelector('#main-content-template');
        var container = document.querySelector('main-content');
        container.appendChild(post.cloneNode(true));
    }
}