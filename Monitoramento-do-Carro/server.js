import express from 'express'
import http from 'http'

//Configurando o Servidor
const app = express()
const server = http.createServer(app)

//Configurar o servidor para apresentar arquivos estáticos 
app.use(express.static('public'))

//ligar o servidor e permitir o acesso na porta 3000
server.listen(3000, function () { 
    console.log("iniciei o servidor")
})