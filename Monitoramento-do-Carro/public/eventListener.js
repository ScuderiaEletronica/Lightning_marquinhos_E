document
    .querySelector('.principal')
    .addEventListener("click", function() {
        document
            .querySelector('.Principal')
            .classList.remove('hide')
        document
            .querySelector('.principal')
            .classList.add('pressionado')
        document
            .querySelector('.Oleo')
            .classList.add('hide')
        document
            .querySelector('.oleo')
            .classList.remove('pressionado')
        document
            .querySelector('.Combustivel')
            .classList.add('hide')
        document
            .querySelector('.combustivel')
            .classList.remove('pressionado')
        document
            .querySelector('.Energia')
            .classList.add('hide')
        document
            .querySelector('.energia')
            .classList.remove('pressionado')
    })
document
    .querySelector('.oleo')
    .addEventListener("click", function() {
        document
            .querySelector('.Principal')
            .classList.add('hide')
        document
            .querySelector('.principal')
            .classList.remove('pressionado')
        document
            .querySelector('.Oleo')
            .classList.remove('hide')
        document
            .querySelector('.oleo')
            .classList.add('pressionado')
        document
            .querySelector('.Combustivel')
            .classList.add('hide')
        document
            .querySelector('.combustivel')
            .classList.remove('pressionado')
        document
            .querySelector('.Energia')
            .classList.add('hide')
        document
            .querySelector('.energia')
            .classList.remove('pressionado')
    })
document
    .querySelector('.combustivel')
    .addEventListener("click", function() {
        document
            .querySelector('.Principal')
            .classList.add('hide')
        document
            .querySelector('.principal')
            .classList.remove('pressionado')
        document
            .querySelector('.Oleo')
            .classList.add('hide')
        document
            .querySelector('.oleo')
            .classList.remove('pressionado')
        document
            .querySelector('.Combustivel')
            .classList.remove('hide')
        document
            .querySelector('.combustivel')
            .classList.add('pressionado')
        document
            .querySelector('.Energia')
            .classList.add('hide')
        document
            .querySelector('.energia')
            .classList.remove('pressionado')
    })
document
    .querySelector('.energia')
    .addEventListener("click", function() {
        document
            .querySelector('.Principal')
            .classList.add('hide')
        document
            .querySelector('.principal')
            .classList.remove('pressionado')
        document
            .querySelector('.Oleo')
            .classList.add('hide')
        document
            .querySelector('.oleo')
            .classList.remove('pressionado')
        document
            .querySelector('.Combustivel')
            .classList.add('hide')
        document
            .querySelector('.combustivel')
            .classList.remove('pressionado')
        document
            .querySelector('.Energia')
            .classList.remove('hide')
        document
            .querySelector('.energia')
            .classList.add('pressionado')
    })


document.querySelector('.mode')
    .addEventListener("click", function() {
        document.querySelector('body').classList.toggle('lightmode')
        document.querySelector('main').classList.toggle('lightmode')
        document.querySelector('aside').classList.toggle('lightmode')
        document.querySelector('.mode').classList.toggle('lightmode')
        document.querySelector('footer').classList.toggle('lightmode')
        if (document.querySelector('.mode').classList.contains('lightmode')) {
            document.querySelector('.mode').innerHTML = 'Dark Mode'
        } else {
            document.querySelector('.mode').innerHTML = 'White Mode'
        }
    })