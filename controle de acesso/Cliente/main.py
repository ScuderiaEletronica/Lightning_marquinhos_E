# -*- coding: utf-8 -*-

import csv
import sys
import datetime
#####################não modifique#####################
import firebase_admin
from firebase_admin import credentials, firestore

cred = credentials.Certificate('./credentials.json')
default_app = firebase_admin.initialize_app(cred)
db = firestore.client()

users_ref = db.collection(u'users')
docs = users_ref.get()

values = [[], [], [], []]  # 0 -> id da pessoa; 1 -> nome; 2 -> entrada.apend(data); 3 -> saida
data = []  # .apend(dado) contem [[ano],[mes], .... [segundo]]
saida = []
entrada = []
saida_final = [[],[]]
entrada_final = [[],[]]

for doc in docs:
    try:
        users_ref = db.collection(u'users').document(doc.id)
        get_nome = users_ref.get({u'nome'})
        get_entrada = users_ref.get({u'entrada'})
        get_saida = users_ref.get({u'saida'})

        values[0].append(doc.id)
        values[1].append(u'{}'.format(get_nome.to_dict()['nome']))
        values[2].append(u'{}'.format(get_entrada.to_dict()['entrada']))
        values[3].append(u'{}'.format(get_saida.to_dict()['saida']))
    except:
        print("usuario " + doc.id + " nao tem nenhuma entrada de tempo")


#####################limite de modificação#####################

# daqui para baixo fique a vontade mas não tente esquever nada na database por problema de corupção de dados (vai estar log tambem, então eu vou saber)
i = -1
for x in values[0]:
    try:
        i = i + 1
        values[2][i] = values[2][i].replace("DatetimeWithNanoseconds", "")
        values[3][i] = values[3][i].replace("DatetimeWithNanoseconds", "")
        values[2][i] = values[2][i].replace(", tzinfo=<UTC>", "")
        values[3][i] = values[3][i].replace(", tzinfo=<UTC>", "")
        values[2][i] = values[2][i].replace("(", "[")
        values[3][i] = values[3][i].replace("(", "[")
        values[2][i] = values[2][i].replace(",", "], [")
        values[3][i] = values[3][i].replace(",", "], [")
    #   values[2][i] = values[2][i].replace(")][", "],")
    #   values[3][i] = values[3][i].replace(")][", "],")
        values[2][i] = values[2][i].replace(")", "]")
        values[3][i] = values[3][i].replace(")", "]")
    except:
        print("usuario " + values[0][i] + " nao tem nenhuma entrada de tempo")

i = -1
for x in values[0]:
    try:
        entrada.extend([[2019]])
        saida.extend([[2019]])
        i = i + 1
        data = eval(values[2][i])
        entrada[i].extend(data)
        data = eval(values[3][i])
        saida[i].extend(data)
    except:
        i = -1
        print("usuario " + values[0][i] + " nao tem entrada de tempo")

j = -1
k = 0

for a in entrada:
    j = j + 1
    leng = len(entrada[j]) - 1
    for z in range(0, leng):
        try:
            k = k + 1
            entrada_final[j].append(
                datetime.datetime(entrada[j][k][0][0], entrada[j][k][1][0], entrada[j][k][2][0], entrada[j][k][3][0], entrada[j][k][4][0],
                                  entrada[j][k][5][0]) - datetime.timedelta(hours=3))
            saida_final[j].append(
                datetime.datetime(saida[j][k][0][0], saida[j][k][1][0], saida[j][k][2][0], saida[j][k][3][0], saida[j][k][4][0],
                                  saida[j][k][5][0]) - datetime.timedelta(hours=3))
        except:
            try:
                print("usuario: " + values[0][k-1] + " com entrada/saida unica")
            except:
                i = -1
    k = 0
i = -1
j = -1
print(entrada_final)
print(saida_final)

f = csv.writer(open("test.csv", "wt"))

f.writerow(['id', 'nome', 'entrada(YMD)', 'saida(YMD)', 'tempo no lab/oficina'])

for x in values[0]:
    i = i + 1
    for y in entrada_final[i]:
        j = j + 1
        print(j)
        print(i)
        f.writerow([values[0][i],
                    values[1][i],
                    entrada_final[i][j],
                    saida_final[i][j],
                    saida_final[i][j]-entrada_final[i][j]])
    j = -1
