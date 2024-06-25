from flask import Flask, request, render_template
from helpers import atualziaNivel, verificaNivel

app = Flask(__name__)

@app.route('/atualizar-nivel', methods=['POST'])
def atualizar_nivel():
    data_json = request.json
    resposta = atualziaNivel(data_json)
    
    return resposta

@app.route('/verificar-nivel')
def verificar_nivel():
    reposta = verificaNivel()
    return reposta

@app.route('/')
def inicion():
    valor = verificaNivel()
    
    return render_template('index.html', valor=valor)

if __name__ == '__main__':
    app.run()




