var velocidade = {
    valor: document.querySelector(".velocidade span"),
    min: 0,
    max: 120
}
genRandom(velocidade)


var rpm = {
    valor: document.querySelector(".rpm span"),
    min: 0,
    max: 500
}
genRandom(rpm)

var map = {
    valor: document.querySelector(".map span"),
    min: 0,
    max: 120
}
genRandom(map)

var mat = {
    valor: document.querySelector(".mat span"),
    min: 0,
    max: 120
}
genRandom(mat)

var clt = {
    valor: document.querySelector(".clt span"),
    min: 0,
    max: 120
}
genRandom(clt)

var cgs = {
    valor: document.querySelector(".cgs span"),
    min: 0,
    max: 3
}
genRandom(cgs)

var voltagem = {
    valor: document.querySelector(".voltagem span"),
    min: 0,
    max: 15
}
genRandom(voltagem)

var o2 = {
    valor: document.querySelector(".o2 span"),
    min: 0,
    max: 15
}
genRandom(o2)

var ECU = {
    valor: document.querySelector(".ECU span"),
    min: 0,
    max: 50
}
genRandom(ECU)

function genRandom(value) {
    var random = Math.random() * (+value.max - +value.min) + +value.min;
    value.valor.innerHTML = parseFloat(random.toFixed(2))

    setTimeout(() => {
        requestAnimationFrame(() => genRandom(value))
    }, 500);
}