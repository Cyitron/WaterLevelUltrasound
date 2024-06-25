import json
from flask import jsonify

def atualziaNivel(data_json):
    
    if 'nivel_de_agua' not in data_json:
        return jsonify({"erro": "JSON inválido, 'nivel_de_agua' não encontrado"}), 400
    
    try:
        with open('nivel_da_agua.json', 'r') as file:
            niveis = json.load(file)
    except FileNotFoundError:
        niveis = [{"nivel_de_agua": 0}]
        
    niveis[0]['nivel_de_agua'] = data_json['nivel_de_agua']
    
    # Salvar as alterações de volta no arquivo
    with open('nivel_da_agua.json', 'w') as file:
        json.dump(niveis, file, indent=4)
        
    return jsonify({"mensagem": "Nível de água atualizado com sucesso"}), 200

def verificaNivel():
    
    try:
        with open('nivel_da_agua.json', 'r') as file:
            niveis = json.load(file)
        return niveis[0]
    
    except FileNotFoundError:
        niveis = [{"nivel_de_agua": 0}]
        return niveis